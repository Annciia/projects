//CZYTELNICY I PISARZE

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 5 //liczba procesów
#define K 6 //liczba miejsc na dzieła
#define L 10 //pętla procesu

enum nazwa_fazy{
    relaks,
    czytelnia
};

enum nazwa_roli{
    czytelnik = 0,
    pisarz = 1
};

const char str_roli[2][64] = { "czytelnik", "pisarz" };


//definicja funkcji do podnoszenia i opuszczania semafora
static struct sembuf sem_buf;

void podnoszenie(int semid, int semnum){
    sem_buf.sem_num = semnum;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = 0;
    if (semop(semid, &sem_buf, 1) == -1){
        perror("Podnoszenie semafora");
        exit(1);
    }
}
void opuszczanie(int semid, int semnum){
    sem_buf.sem_num = semnum;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = 0;
    if (semop(semid, &sem_buf, 1) == -1){
        perror("Opuszczenie semafora");
        exit(1);
    }
}

//struktura kolejki komunikatów
struct msg_buf_elem{
    long mtype;
    int mvalue[N];
};

//struktura pamięci współdzielonej
struct shm_buf_elem {
    int l_czyt; //liczba czytelników w czytelni
    int liczba_dziel; // liczba dzieł w bibliotece
    long id_dziela; //nr ostatniego dzieła
    int czy_czytelnik[N]; //obecny stan, kto jest czytelnikiem, gdy dzieło jest pisane
};


int main(void){

    //Tworzenie semaforów: czytelnika i pisarza oraz do zliczania dzieł w bibliotece (rozmiar kolejki)
    const int semid=semget(IPC_PRIVATE, 3, IPC_CREAT|0600);
    if (semid==-1){
        perror("Utworzenie tablicy semaforow.");
        exit(1);
    }
    //Nadanie wartości początkowych semaforom
    if (semctl(semid, czytelnik, SETVAL, (int)1) == -1){
        perror("Nadanie wartosci semaforowi 0.");
        exit(1);
    }
    if (semctl(semid, pisarz, SETVAL, (int)1) == -1){
        perror("Nadanie wartosci semaforowi 1");
        exit(1);
    }
    if (semctl(semid, 2, SETVAL, (int)1) == -1){
        perror("Nadanie wartosci semaforowi 2");
        exit(1);
    }

    //Tworzenie pamieci wspoldzielonej
    const int shmid=shmget(IPC_PRIVATE, sizeof(struct shm_buf_elem), IPC_CREAT|0600);
    struct shm_buf_elem* shm_buf= (struct shm_buf_elem*)shmat(shmid, NULL, 0);
    (*shm_buf).l_czyt= 0;
    (*shm_buf).liczba_dziel= 0;
    (*shm_buf).id_dziela= 0;
    for(int i=0; i<N; i++) {
        (*shm_buf).czy_czytelnik[i]= 1;
    }
    
    //Tworzenie kolejki komunikatow
    struct msg_buf_elem msg_elem;
    const int msgid=msgget(IPC_PRIVATE, IPC_CREAT|0600);
    if(msgid == -1){
        perror("Utworzenie kolejki komunikatów");
        exit(1);
    }

    // Tworzenie procesów
    int id_procesu= 0;
    int tab_pid[N];
    int nr_pid= -1;
    tab_pid[0] = getpid();
    for(int i=0; i<N-1; i++){
        nr_pid= fork(); 
        if(nr_pid == 0) {
            id_procesu= i+1;
            break; //Nowo utworzony proces wychodzi z pętli a rodzic zostaje, zapisuje jego pid i się rozmnaża
        }
        tab_pid[i+1]=nr_pid;
    }
    if(getpid()==tab_pid[0]){
        for(int i=0; i<N; i++){
            fprintf(stderr,"Pid procesu %d\n", tab_pid[i]);
        }
    }
    fprintf(stderr,"START!!! %d %d\n", getpid(), id_procesu);
    //-----------------------------------------------------------------------//
    
    srand(getpid());

    enum nazwa_fazy faza = relaks;
    enum nazwa_roli rola = czytelnik;

    int i=0;
    double losowa=0.0f;

    while(i < L){
        if(faza==relaks){  //jest w fazie relaks
            losowa= (double)rand()/(RAND_MAX+1.0); //losowanie - jaką rolę otrzyma proces: czytelnik/pisarz
            if(losowa<0.8){
                rola=czytelnik;
                (*shm_buf).czy_czytelnik[id_procesu]= 1;
                fprintf(stderr,"Jestem czytelnikiem w relaksie. %d %.3f\n", getpid(), losowa);
            }
            else{
                rola=pisarz;
                (*shm_buf).czy_czytelnik[id_procesu]= 0;
                fprintf(stderr,"Jestem pisarzem w relaksie. %d %.3f\n", getpid(), losowa);
            }
            losowa= (double)rand()/(RAND_MAX+1.0); //losowanie - czy proces wchodzi do czytelni czy pozostaje w relaksie
            if(losowa<0.7){ //przy spełnieniu warunku proces chce wejść do czytelni
                //wchodzenie do czytelni
                if(rola==czytelnik){
                    opuszczanie(semid, czytelnik);
                    (*shm_buf).l_czyt= (*shm_buf).l_czyt+1; //zliczanie czytelników w czytelni
                    if((*shm_buf).l_czyt == 1) {
                        opuszczanie(semid, pisarz);
                    }
                    podnoszenie(semid, czytelnik);

                    faza=czytelnia;
                    fprintf(stderr,"Przechodzę do czytelni - %s. %d %.3f\n", str_roli[rola], getpid(), losowa);
                    //czytanie max jednego dzieła
                    if(msgrcv(msgid, &msg_elem, N*sizeof(int), 0, IPC_NOWAIT) == -1) {
                        fprintf(stderr, "-- JEST PUSTO!!!!! - %s. %d\n", str_roli[rola], getpid());
                    }
                    else {
                        fprintf(stderr, "++ SPRAWDZAM KSIĄŻKĘ %ld! - %s %d\n", msg_elem.mtype, str_roli[rola], getpid());
                        if(msg_elem.mvalue[id_procesu] != 0) { //jeśli jestem odbiorcą dzieła
                            fprintf(stderr, "Odebrałem dzieło %ld - %s. %d\n", msg_elem.mtype, str_roli[rola], getpid());
                            msg_elem.mvalue[id_procesu]= 0;
                        }
                        else {
                            fprintf(stderr, "Nie jestem zainteresowany dziełem %ld - %s. %d\n", msg_elem.mtype, str_roli[rola], getpid());
                        }
                      
                        //sprawdzenie, czy dzieło ma być usunięte z biblioteki
                        int usuwamy= 1;
                        for(int i=0; i<N; i++) { //jeśli ktoś ma jeszcze do przeczytania, to jednak nie usuwamy
                            if(msg_elem.mvalue[i] == 1) {
                                usuwamy= 0;
                                break;
                            }
                        }
                        if(!usuwamy) {
                            msgsnd(msgid, &msg_elem, N*sizeof(int), 0); 
                        } 
                        else {
                            opuszczanie(semid, 2);
                            (*shm_buf).liczba_dziel--; //usuwając zmniejszamy liczbę dzieł w czytelni
                            fprintf(stderr, "DO KOSZA %ld ! %d l_dziel:%d/%d\n", msg_elem.mtype, getpid(), (*shm_buf).liczba_dziel, K);
                            podnoszenie(semid, 2);
                        }
                    }
                    //koniec czytania

                    faza=relaks;
                    fprintf(stderr,"Wychodzę z czytelni - %s. %d\n", str_roli[rola], getpid());

                    opuszczanie(semid, czytelnik);
                    (*shm_buf).l_czyt= (*shm_buf).l_czyt-1; //zliczanie czytelników w czytelni
                    if((*shm_buf).l_czyt == 0) {
                        podnoszenie(semid, pisarz);
                    }
                    podnoszenie(semid, czytelnik);
                }
                else{ //rola pisarz
                    opuszczanie(semid, pisarz);
                    faza=czytelnia;
                    fprintf(stderr,"Przechodzę do czytelni - %s. %d %.3f id_ostatniego_dziela:%ld\n", str_roli[rola], getpid(), losowa, (*shm_buf).id_dziela);
                    
                    //czytanie max jednego dzieła
                    if(msgrcv(msgid, &msg_elem, N*sizeof(int), 0, IPC_NOWAIT) == -1) {
                        fprintf(stderr, "-- JEST PUSTO!!!!! - %s. %d\n", str_roli[rola], getpid());
                    }
                    else {
                        fprintf(stderr, "++ SPRAWDZAM KSIĄŻKĘ %ld! - %s %d\n", msg_elem.mtype, str_roli[rola], getpid());
                        if(msg_elem.mvalue[id_procesu] != 0) { //jeśli jestem odbiorcą dzieła
                            fprintf(stderr, "Odebrałem dzieło %ld - %s. %d\n", msg_elem.mtype, str_roli[rola], getpid());
                            msg_elem.mvalue[id_procesu]= 0;
                        }
                        else {
                            fprintf(stderr, "Nie jestem zainteresowany dziełem %ld - %s. %d\n", msg_elem.mtype, str_roli[rola], getpid());
                        }
                      
                        //sprawdzenie, czy dzieło ma być usunięte z biblioteki
                        int usuwamy= 1;
                        for(int i=0; i<N; i++) { //jeśli ktoś ma jeszcze do przeczytania, to jednak nie usuwamy
                            if(msg_elem.mvalue[i] == 1) {
                                usuwamy= 0;
                                break;
                            }
                        }
                        if(!usuwamy) {
                            msgsnd(msgid, &msg_elem, N*sizeof(int), 0); 
                        } else {
                            (*shm_buf).liczba_dziel--; //usuwając zmniejszamy liczbę dzieł w czytelni
                            fprintf(stderr, "DO KOSZA %ld ! %d l_dziel:%d/%d\n\n", msg_elem.mtype, getpid(), (*shm_buf).liczba_dziel, K);
                        }
                    }
                    //koniec czytania dzieła

                    //pisanie dzieła
                    if((*shm_buf).liczba_dziel < K) {  // sprawdzanie, czy jest miejsce w bibliotece na nowe dzieła
                        msg_elem.mtype= (*shm_buf).id_dziela + 1; //nadanie id dla nowego dzieła
                        (*shm_buf).id_dziela=(*shm_buf).id_dziela + 1; //aktualizacja pamięci współdzielonej
                        for(int i=0; i<N; i++) {
                            msg_elem.mvalue[i]= (*shm_buf).czy_czytelnik[i]; //1 dla tego id_procesu, który jest czytelnikiem
                        }
                        msgsnd(msgid, &msg_elem, N*sizeof(int), 0);
                        (*shm_buf).liczba_dziel++;
                        fprintf(stderr,"Dodałem swoje dzieło %ld - %s. %d l_dziel:%d/%d\n", msg_elem.mtype, str_roli[rola], getpid(), (*shm_buf).liczba_dziel, K);
                    }
                    else{
                        fprintf(stderr,"Nie piszę nowego dzieła, gdyż brakuje miejsca na półce - %s. %d l_dziel:%d/%d\n", str_roli[rola], getpid(), (*shm_buf).liczba_dziel, K);
                    }
                    faza=relaks;
                    podnoszenie(semid, pisarz);
                    //koniec pisania dzieła
                }
            }
            else{ //gdy wylosowana liczba oznacza, że proces nie wchodzi do czytelni
                fprintf(stderr,"Nie wchodzę do czytelni - %s. %d %.3f\n", str_roli[rola], getpid(), losowa);
            }
        }
        

        fprintf(stderr,"Jeszcze żyję! %d\n", getpid());
        usleep(500000);
        i++;
    }

    //-----------------------------------------------------------------------//

    //Czekanie na wszystkie procesy potomne, by posprzątać obiekty IPC
    if(getpid() == tab_pid[0]) {
        for(int i=1; i<N; i++) {
            fprintf(stderr, "CZEKAM NA %d\n", tab_pid[i]);
            waitpid(tab_pid[i], NULL, 0);
        }
        fprintf(stderr, "KONIEC CZEKANIA\n");

        //zwolnienie zbioru semaforow, pamieci wspoldzielonej, kolejki komunikatowv
        semctl(semid, 0, IPC_RMID);
        shmctl(shmid,IPC_RMID, NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    exit(0);
}