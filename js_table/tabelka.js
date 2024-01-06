
function main() {
    console.log("MAIJN!");
    for(let i=0; i<2; i++) {
        dodajWiersz();
    }
}

function dodajWiersz() {
    let tabelka = document.getElementById("tabelka");

    let str = "";  //wstawiany wiersz
    for(let i=0; i<3; i++) {
        str += "<td><input type='text'></input></td>";
    }
    str += "<td><button onclick='usunWiersz(this);'>-</button><input class='zaznaczanie' type='checkbox'></input></td>";
    str += "<td class='sortowanie'><button class='w_gore' onclick='przesun_wiersz(this)'>&#x2B06;</button><button class='w_dol' onclick='przesun_wiersz(this)'>&#x2B07;</button></td>";

    let nowy_wiersz= document.createElement("tr");
    nowy_wiersz.innerHTML= str;
    let wiersz_dodaj = document.getElementById("wiersz_dodaj");
    tabelka.lastChild.insertBefore(nowy_wiersz, wiersz_dodaj); //(co wstawiamy, przed czym wstawiamy)
    ile_wierszy();
    koloruj_wiersze();
}

function usunWiersz(przycisk_minus) {
   przycisk_minus.parentElement.parentElement.remove();
   ile_wierszy();
   koloruj_wiersze();
}

function ile_wierszy(){
    let tabelka = document.getElementById("tabelka");
    let liczba_wierszy = document.getElementById("liczba_wierszy");
    liczba_wierszy.textContent = tabelka.lastChild.childElementCount-1;
}

function koloruj_wiersze() {
    let tabelka = document.getElementById("tabelka");
    for(let i=0; i<tabelka.lastChild.childElementCount; i++) {
        if(i % 2 == 0) {
            tabelka.lastChild.children[i].classList.remove("kolor2");
            tabelka.lastChild.children[i].classList.add("kolor1");
        } else {
            tabelka.lastChild.children[i].classList.remove("kolor1");
            tabelka.lastChild.children[i].classList.add("kolor2");
        }
    }
}

function przesun_wiersz(przycisk_przesun) {
    let tabelka = document.getElementById("tabelka");
    let wiersz = przycisk_przesun.parentElement.parentElement;
    let wiersz_poprzedni = wiersz.previousSibling;
    let wiersz_nastepny = wiersz.nextSibling;
    let wiersz_nastepny_za_nastepnym = wiersz_nastepny.nextSibling;
    if(przycisk_przesun.classList.contains("w_gore")){
        if(wiersz_poprzedni != null) {
            wiersz.remove();
            tabelka.lastChild.insertBefore(wiersz, wiersz_poprzedni);
        }
    }
    else if(przycisk_przesun.classList.contains("w_dol")){
        if(!wiersz_nastepny.classList.contains("wiersz_dodaj")){
            wiersz.remove();
            tabelka.lastChild.insertBefore(wiersz, wiersz_nastepny_za_nastepnym);
        }
    }
    koloruj_wiersze();
}

function usun_zaznaczone() {
    let lista_zaznaczen = document.getElementsByClassName("zaznaczanie");
    for (let i=lista_zaznaczen.length-1; i>=0; i--){
        if(lista_zaznaczen[i].checked==true) {
            let wiersz = lista_zaznaczen[i].parentElement.parentElement;
            wiersz.remove();
        }
    }
    ile_wierszy();
    koloruj_wiersze();
}

window.onload = main;