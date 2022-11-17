#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



void generuj_losowa(int* tab_losowa, int n) {
	for (int i = 0;i < n; i++) {
		int losowa = ((float)rand() / (RAND_MAX + 1)) * 10000;
		tab_losowa[i] = losowa;
	}
}

void generuj_rosnaco(int* tab_rosnaca, int n) {
	for (int i = 0;i < n; i++) {
		tab_rosnaca[i] = i;
	}
}

void generuj_malejaco(int* tab_malejaca, int n) {
	for (int i = 0;i < n; i++) {
		tab_malejaca[i] = n - 1 - i;
	}
}

void generuj_stale(int* tab_stala, int n) {
	for (int i = 0; i < n; i++) {
		tab_stala[i] = 4;
	}
}

void generuj_V(int* tab_V, int n) {
	for (int i = 0; i < (n / 2); i++) {
		tab_V[i] = ((n / 2) - 1) - i;
	}
	for (int i = (n / 2); i < n; i++) {
		tab_V[i] = i - (n / 2);
	}
}


void MERGE_SORT_algorytm(int* A, int l, int r, int* B); 

int* MERGE_SORT(int* A, int n) {
	int* tablica_pomocnicza = (int*)malloc(n * sizeof(int));
	MERGE_SORT_algorytm(A, 0, n - 1, tablica_pomocnicza);
	free(tablica_pomocnicza);
	return A;
}

void MERGE_SORT_algorytm(int* A, int l, int r, int* B) {
	int m = (l + r) / 2;
	if ((m - l) > 0) {
		MERGE_SORT_algorytm(A, l, m, B);
	}
	if ((r - (m + 1)) > 0) {
		MERGE_SORT_algorytm(A, m + 1, r, B);
	}
	int i = l;
	int j = m + 1;
	for (int k = l; k <= r; k++) {
		if (((i <= m) && (j > r)) || (((i <= m) && (j <= r)) && A[i] <= A[j])) {
			B[k] = A[i];
			i++;
		}
		else {
			B[k] = A[j];
			j++;
		}
	}
	for (int k = l; k <= r; k++) {
		A[k] = B[k];
	}
}


void print_tablica(int* t, int n) {
	for (int p = 0; p < n; p++) {
		printf("%d ", *(t + p));
	}
	printf("\n");
}


int main(void) {

	FILE* pliczek = fopen("wyniki_sortowania_MS.txt", "w");
	if (pliczek == NULL) {
		return 1;
	}

	srand(time(NULL));
	for (int i = 0; i < 100; i++) rand();

	for (int i = 1; i <= 15; i++) {
		int n = i * 1000000;
		int* tablica = (int*)malloc(n * sizeof(int));

		fprintf(pliczek, "%d\t", n);

		for (int j = 1; j <= 5;j++) {
			switch (j) {
				case 1: {
					generuj_losowa(tablica, n);
					break;
				}
				case 2: {
					generuj_rosnaco(tablica, n);
					break;
				}
				case 3: {
					generuj_malejaco(tablica, n);
					break;
				}
				case 4: {
					generuj_stale(tablica, n);
					break;
				}
				case 5: {
					generuj_V(tablica, n);
				}
			}

			unsigned int czas_poczatek = GetTickCount();
			MERGE_SORT(tablica, n);
			unsigned int czas_koniec = GetTickCount();
			unsigned int czas = czas_koniec - czas_poczatek; // czas w [ms]

			printf("n=%d, czas=%u \n", n, czas);
			fprintf(pliczek, "%u\t", czas);
		}

		fprintf(pliczek, "\n");
		free(tablica);
	}

	fclose(pliczek);

	return 0;
}








