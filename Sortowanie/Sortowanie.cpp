/*
	Program Sortujący
	Zaimplementowane sortowania:

		- sortowanie przez wstawianie (insertion sort) w programie W_sortowanie

		- sortowanie przez kopcowanie (heap sort) w programie K_sortowanie

		- sortowanie przez scalanie (merge sort) w programie S_sortowanie

	WAŻNE!! jesli ostatni parametr funkcji quicksort = 0 sortuje malejąco w pozostałych przypadkach rosnąco
		- szybkie sortowanie (quicksort) w programie Q_sortowanie

		- sortowanie Introspektywne (Introsort) w programie I_sortowanie

*/


#include "pch.h"
#include "math.h"
#include <iostream>
#include <ctime>
using namespace std;

int *pom; //wskaźnik globalny używany do stworzenia tablicy pomocniczej

template<typename T>
bool czy_posortowane_malejaco(T tab[], int koniec)
{
	for (int i = 0; i < koniec; i++)
	{
		if (tab[i] <= tab[i + 1])
		{
			cout << "nie posortowana" << endl;
			return false;
		}
	
	}
	cout << "posortowana" << endl;
	return true;
}
template<typename T>
bool czy_posortowane_rosnaco(T tab[], int koniec)
{
	for (int i = 0; i < koniec; i++)
	{
		if (tab[i] > tab[i + 1])
		{
			cout << "nie posortowana" << endl;
			return false;
		}

	}
	cout << "posortowana" << endl;
	return true;
}
template<typename T>
bool czy_posortowane(T tab[], int koniec)
{
	for (int i = 0; i < koniec; i++)
	{
		if (tab[i] > tab[i + 1])
		{
			return false;
		}

	}
	return true;
}
template<typename T>
void wyswietlanie(T tab, int wielkosc, int ilosc)
{
	for (int i = 0; i < ilosc; i++)
	{
		cout << endl << endl;
		for (int j = 0; j < wielkosc; j++)
		{
			cout << tab[i][j] << " ";
		}
	}

}

template<typename T>
void losuj(T tab, int wielkosc, int ilosc)
{
	for (int i = 0; i < ilosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			tab[i][j] = rand() % 25000;
		}
	}
}
template<typename T>
void W_sortowanie(T tab[], int wielkosc)
{
	int temp, j;
	for (int i = 1; i < wielkosc; i++)
	{
		//przechowywanie wartości 
		temp = tab[i];
		j = i - 1;

		//szukanie miejsca dla elementu
		while (j >= 0 && tab[j] > temp)
		{
			tab[j + 1] = tab[j];
			--j;
		}
		tab[j + 1] = temp; //wstawienie elementu w odpowiednie miejsce
	}
}






template<typename T>
void kopcowanie(T tab[], int wielkosc, int i) // funkcja ustawiajaca prawidłowo strukture kopca 
{
	int temp;
	int najwiekszy = i; // ustawienie zmiennej najwiekszy jako korzeń 
	int lewy = 2 * i + 1, prawy = 2 * i + 2;

	// sprawdzenie czy lewe dziecko jest wieksze od korzenia
	if (lewy < wielkosc && tab[lewy] > tab[najwiekszy])
		najwiekszy = lewy;
	// sprawdzenie czy prawe dziecko jest wieksze od korzenia
	if (prawy < wielkosc && tab[prawy] > tab[najwiekszy])
		najwiekszy = prawy;

	//jeśli najwiekszy nie jest korzeniem 
	if (najwiekszy != i)
	{

		temp = tab[najwiekszy];
		tab[najwiekszy] = tab[i];
		tab[i] = temp;
		//wywołanie rekurencyjne dla niższych gałęźi 
		kopcowanie(tab, wielkosc, najwiekszy);

	}
}


template<typename T>
void K_sortowanie(T tab[], int wielkosc)
{
	int temp;
	// tworzenie kopca
	for (int i = wielkosc / 2 - 1; i >= 0; i--)
	{
		kopcowanie(tab, wielkosc, i);
	}
	// usuwanie najwiekszego elementu kopca i ustawianie go na końcu tablicy głównej
	for (int i = wielkosc - 1; i >= 0; i--)
	{

		temp = tab[i];
		tab[i] = tab[0];
		tab[0] = temp;

		//naprawianie kopca
		kopcowanie(tab, i, 0);

	}
}


template<typename T>
void scalanie(T tab[], int poczatek, int srodek, int koniec)
{
	int i, j;
	//zapisanie polowy glownej tablicy w tablicy pomocniczej
	for (i = srodek + 1; i > poczatek; i--)
		pom[i - 1] = tab[i - 1];
	//zapisanie drugiej polowy glownej tablicy w tablicy pomocniczej
	for (j = srodek; j < koniec; j++)
		pom[koniec + srodek - j] = tab[j + 1];
	//scalanie tablic pomocniczych i zapisanie ich w glowej tablicy w odpowiedniej kolejności 
	for (int k = poczatek; k <= koniec; k++)
		if (pom[j] < pom[i])
			tab[k] = pom[j--];
		else
			tab[k] = pom[i++];
}

template<typename T>
void S_sortowanie(T tab[], int poczatek, int koniec)
{
	//warunek sprawdzajacy czy tablica jest jednoelementowa
	if (koniec <= poczatek) return;
	//wyznaczanie srodka tablicy
	int srodek = (koniec + poczatek) / 2;
	//dzielenie tablicy na dwie czesci 
	S_sortowanie(tab, poczatek, srodek);
	S_sortowanie(tab, srodek + 1, koniec);

	//sclanie podtablic
	scalanie(tab, poczatek, srodek, koniec);
}







template<typename T>
void Q_sortowanie(T tab[], int poczatek, int koniec, int kierunek)
{
	int i = poczatek, j = koniec, temp;
	//warunek sprawdzajacy czy tablica jest jednoelementowa
	if (koniec <= poczatek) return;
	int pivot = tab[(poczatek + koniec) / 2]; //wybieranie punktu odniesienia

	do
	{
		if (kierunek == 0) // sortowanie od najwiekszej do mnajmniejszej
		{
			//szukanie elementu mniejszego od pivot
			while (pivot < tab[i])
				i++;

			//szukanie elementu wiekszego od pivot
			while (pivot > tab[j])
				j--;
		}
		else // sortowanie od najmniejszej do największej 
		{
			//szukanie elementu wiekszego od pivot
			while (pivot > tab[i])
				i++;

			//szukanie elementu mniejszego od pivot
			while (pivot < tab[j])
				j--;
		}

		//zamienianie miejscami elementów stojacych po zlej stronie jesli liczniki sie nie minęły
		if (i <= j)
		{
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;

		}

	} while (i <= j); //koniec pętli jeśli liczniki się minęły 

	// rekurencja 
	if (j> poczatek)
		Q_sortowanie(tab, poczatek, j, kierunek);
	if (i < koniec)
		Q_sortowanie(tab, i, koniec, kierunek);
	return;
}





template<typename T>
int Q_intro(T tab[], int poczatek, int koniec)
{
	//warunek sprawdzajacy czy tablica jest jednoelementowa

	int i = poczatek, j = koniec, temp;
	if (koniec <= poczatek) return i; // zwracanie indeksu w którym tablica ma zostać "podzielona"
	int pivot = tab[(poczatek + koniec) / 2]; //wybieranie punktu odniesienia

	do
	{
		//szukanie elementu wiekszego od pivot
		while (pivot > tab[i])
			i++;

		//szukanie elementu mniejszego od pivot
		while (pivot < tab[j])
			j--;
		//zamienianie miejscami elementów stojacych po zlej stronie jesli liczniki sie nie minęły
		if (i <= j)
		{
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;

		}

	} while (i <= j);
	return i; // zwracanie indeksu w którym tablica ma zostać "podzielona"
}



template<typename T>
void IntroSort(T tab, int wielkosc, int M)
{
	int i;
	if (wielkosc < 16) 
	{
		W_sortowanie(tab, wielkosc);
		return;
	}
	// sortowanie tablicy przy użyciu sortowania przez kopcowanie w sytuacji osiągnięcia maksymalnej głebokości rekurencji 
	if (M <= 0)
	{
		K_sortowanie(tab, wielkosc);
		return;
	}

	i = Q_intro(tab, 0, wielkosc - 1); // indeks podziału tablicy 
	// rekurencja zliczajaca głębokość 
	IntroSort(tab, i, M - 1);
	IntroSort(tab + i, wielkosc - i, M - 1);
}

template<typename T>
void I_sortowanie(T tab[], int wielkosc)
{
	int glebokosc = 2 * (int)log(wielkosc); // maksymalna głębokość rekurencji
	IntroSort(tab, wielkosc, glebokosc);
	
}


int main()
{
	// zmienne potrzebne do zmierzenia czasu wykonywania się algorytmu
	clock_t start;
	double czas_trwania;
	

	// zmienne określające wielkość tablic i ilość tablic do posortowania
	int wielkosc = 1000000, ilosc = 100;

	//tworzenie tablicy pomocniczej 
	pom = new int[wielkosc];

	//tworzenie określonej ilości tablic o okreśłonej wielkości
	int** tab = new int *[ilosc];
	for (int i = 0; i < ilosc; i++)
	{
		tab[i] = new int[wielkosc];
	}

	// wpisywanie do tablic losowych wartości 
	losuj(tab, wielkosc, ilosc);


	//for (int i = 0; i < ilosc; i++) Q_sortowanie(tab[i], 0, (int)(0.5*(wielkosc - 1)), 0); // Tworzenie tablic częsciowo posortowanych lub posortowanych odwrotnie

	start = clock(); // włączenie odliczania czasu

	for (int i = 0; i < ilosc; i++)
	{
		//W_sortowanie(tab[i], wielkosc); // algorytm sortowania przez wstawianie


		//K_sortowanie(tab[i], wielkosc); // algorytm sortowania przez kopcowanie


		//S_sortowanie(tab[i], 0, wielkosc-1);  // algorytm sortowania przez scalanie


		// jesli ostatni parametr funkcji Q_sortowanie = 0 sortuje malejąco w pozostałych przypadkach rosnąco
		//Q_sortowanie(tab[i], 0, wielkosc-1,1);  // algorytm szybkiego sortowania (quicksort)

		I_sortowanie(tab[i],wielkosc); // algorytm sortowania introspektywnego


		czy_posortowane_rosnaco(tab[i], wielkosc-1);
		//czy_posortowane_malejaco(tab[i], wielkosc);


	}

	czas_trwania = (clock() - start) / (double)CLOCKS_PER_SEC; // przeliczenia cykli zegara na sekundy
	cout << "Czas sortowania w sekundach " << czas_trwania << endl; // wyświetlenie ile czasu sortował algorytm

	// wyświetlanie tablic 
	//wyswietlanie(tab, wielkosc, ilosc);



	// usuwanie tablic
	delete pom;
	delete tab;
	// Pauzowanie systemu potrzebne przy uruchamianiu programu przez plik wykonawczy
	cout << endl;
	//system("Pause");
}
