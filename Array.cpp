#include "Array.h"

/* Konstruktor bezparametryczny, zwraca tablice z losowymi elementami*/
template <class TYPE, int Size>
Array<TYPE, Size>::Array() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1,Size);

    for(auto & i : element)  {
        i = distribution(mt);
    }
}
/* Konstruktor kopiujący*/
template<class TYPE, int Size>
Array<TYPE, Size>::Array(const Array &Arr_to_copy) {
    for(int i = 0; i < Size; i++)  {
        element[i] = Arr_to_copy[i];
    }
}

/* Operatory []*/
template <class TYPE, int Size>
const TYPE & Array<TYPE, Size>::operator[](int index) const {
    if (index < 0 || index >= Size) {
        std::cerr << "Blad: zly index tablicy";
        exit(1);
    }
    return element[index];
}
template <class TYPE, int Size>
TYPE & Array<TYPE, Size>::operator[](int index) {
    if (index < 0 || index >= Size) {
        std::cerr << "Blad: zly index tablicy";
        exit(1);
    }
    return element[index];
}

/* Sprawdza poprawnosc sortowania*/
template <class TYPE, int Size>
void Array<TYPE, Size>::Is_correct(char parameter) const{
    if (parameter=='u'){
        for(int i = Size-1; i > 0; i--) {
            if (element[i] < element[i-1]) {
                std::cerr << "Blad sortowania: Na " << i << ". elemencie"; /* od tylu*/
                exit(1);
            }
        }
    } else if (parameter=='d'){
        for(int i = Size-1; i > 0; i--) {
            if (element[i] > element[i-1]) {
                std::cerr << "Blad sortowania: Na " << i << ". elemencie"; /* od tylu*/
                exit(1);
            }
        }
    } else {
        std::cerr << "Blad Is_correct: zly parametr sortowania";
        exit(1);
    }
}

/* HEAPSORT*/

/* Metoda porzadkujaca kopiec zgodnie z zależnościami rodzic - dziecko*/

template<class TYPE, int Size>
void Array<TYPE, Size>::Heapify(int heapSize, int parentIndex) {
    int maxIndex = parentIndex; //indeks maksymalnego elementu, na poczatku indeks rodzica
    int  leftChild = 2 * parentIndex + 1; //indeks lewego dziecka
    int rightChild = 2 * parentIndex + 2; //indeks prawego dziecka

    if ((leftChild < heapSize) && (element[leftChild] > element[maxIndex])) {
//        if indeks lewego dziecka < rozmiar kopca and
//        wartosc lewego dziecka > wartosc max elementu (czyli wartosc rodzica) to
//        indeks maksymalnego elementu = indeks lewego dziecka
        maxIndex = leftChild;
    }
    if ((rightChild < heapSize) && (element[rightChild] > element[maxIndex])) {
//        amalogicznie jak wyzej
        maxIndex = rightChild;
    }
    if (maxIndex != parentIndex) {
//        jesli ktorys z ifów wyżej został wykonany to
//        zamien lewe/prawe dziecko z rodzicem i wywolaj rekurencyjnie tą funkcje
        std::swap(element[maxIndex], element[parentIndex] );
        Heapify(heapSize, maxIndex);
    }
}


/* Motoda tworzy kopiec następnie go sortuje */

template<class TYPE, int Size>
void Array<TYPE, Size>::Sort_heapsort() {
    int n = Size;
//    tworzy kopiec
    for (int i = n/2 - 1; i >= 0; i--) {
        Heapify(n, i);
    }

//    sortuje kopiec
    for (int i = n - 1; i > 0; i--) {
//        zamienia element najstarszy z elementem o aktualnym indeksie,
//        odbudowuje relacje w kopcu
        std::swap( element[0], element[i] );
        n--;
        Heapify(n, 0);
    }
}

/* QUICKSORT*/
/* Metoda pomocnicza*/
template<class TYPE, int Size>
TYPE Array<TYPE, Size>::Quick_chose_pivot(int left, int right) {
    int mid = left + (right - left) / 2;
    TYPE Pivot_value = element[mid];
    std::swap(element[mid], element[right] );
    return Pivot_value;
}

template<class TYPE, int Size>
int Array<TYPE, Size>::Quick_partition(int left, int right) {
    TYPE Pivot_value = Quick_chose_pivot(left, right);   /*  wartosc do ktorej elementy tablicy są porównywane,
                                            w pierwszym wywołaniu ostatni element tablicy*/
    int border = left -1;   //granica, w pierwszym wywołaniu przed pierwszym elementem tablicy
    int i = left; //iterator

    while (i < right) {
        if (element[i] < Pivot_value) {
            /* jesli  wartosc elementu jest mniejsza od wartosci do ktorej porownuje*/
            border++; // przesuwam granice o 1 w prawo
            if (border != i) {
                std::swap(element[border], element[i] );
                /* zamien 1 element po prawej od granicy z aktualnie wzietym elementem */
            }
        }
        i++;
    }
    border++;// przesuwam granice o 1 w prawo
    if (border != right) {
        std::swap(element[right], element[border] );
    }
    return border;
}

template<class TYPE, int Size>
void Array<TYPE, Size>::Quick_sort(int left, int right) {
    if (left >= right) {
        return; // jesli jeden element
    }

    int border = Quick_partition(left, right);

    /* od lewego elementu do elementu po lewej stronie granicy*/
    Quick_sort(left, border - 1); /* lewa część*/
    /* od pierwszego elementu po prawej stornie granicy do ostatniego elementu */
    Quick_sort(border + 1, right); /* prawa część*/
}

template<class TYPE, int Size>
void Array<TYPE, Size>::Sort_quicksort() {
    if ((this == NULL) || (Size == 0)) {
        return;
    }
    int n = Size;
    Quick_sort( 0, n-1);
}

template<class TYPE, int Size>
void Array<TYPE, Size>::Part_sort(float percent) {
Sort_heapsort();
    if(percent == 25){
        Unsorted_part(percent);
    } else if(percent == 50){
        Unsorted_part(percent);
    } else if(percent == 75){
        Unsorted_part(percent);
    } else if(percent == 95){
        Unsorted_part(percent);
    } else if(percent == 99){
        Unsorted_part(percent);
    } else if(percent - 99.7 <= 0.0001){
        Unsorted_part(percent);
    } else{
    std::cerr << "Blad Part_sort: zly parametr sortowania";
    exit(1);
    }
}

template<class TYPE, int Size>
void Array<TYPE, Size>::Unsorted_part(float percent) {

    int size_percent = Size * percent /100;
    TYPE tmp = element[size_percent];

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(tmp,Size);
    for(int i = size_percent; i < Size; i++)  {
        element[i] = distribution(mt);
    }
}

template<class TYPE, int Size>
void Array<TYPE, Size>::Reverse() {
    Sort_heapsort();

    if  (Size % 2) {
        int tmp = Size/2 - 1;
        for(int i = 0; i < tmp; i++)  {
            std::swap(element[i],element[Size-i]);
        }
    } else {
        int tmp = Size/2;
        for(int i = 0; i < tmp; i++)  {
            std::swap(element[i],element[Size-i]);
        }
    }
}

/* MERGESORT*/
template<class TYPE, int Size>
void Array<TYPE, Size>::Sort_mergesort() {
    /* do pomocniczej tablicy kopiuje glowna tablice*/
    for(int i = 0; i < Size; i++)  {
        extra_elem[i] = element[i];
    }
    Merge_sort(0, Size-1);
}

/* prywatna metoda sortująca*/
template<class TYPE, int Size>
void Array<TYPE, Size>::Merge_sort(int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) { /* jesli przynajmniej jeden element*/
        int middle = (leftIndex + rightIndex) /2; /*wyznaczam srodek do podzialu na podtablice*/
        /* wywołanie dla podprobelmów*/
        Merge_sort(leftIndex, middle);  /* od lewego elementu, do elementu przed granicy podzialu*/
        Merge_sort(middle +1 , rightIndex); /* od kolejnego elementu po granicy podzalu
 *                                                      do ostatniego elementu */
        Merge(leftIndex, middle, rightIndex); /* scalanie*/
    }
}

/* prywatna metoda scalająca*/
template<class TYPE, int Size>
void Array<TYPE, Size>::Merge(int leftIndex, int middleIndex, int rightIndex) {
    /* skopiowanie do pomocniczej tablicy oryginalnej tablicy(po czasie juz czesciowo posortowanej)*/
    for(int i = leftIndex; i <= rightIndex; i++)  {
         extra_elem[i] = element[i];
    }

    int finger1 = leftIndex; /* poczatkowy indeks lewej podtablicy*/
    int finger2 = middleIndex + 1; /* poczatkowy indeks prawej podtablicy*/
    int current = leftIndex; /* na jakie miejsce wpisujemy najmniejszy element do wynikowej tablicy(oryginalnej)*/

    while ((finger1 <= middleIndex) && (finger2 <= rightIndex)) {/* dopóki  nie dojdzeimy do konca pierwszej podtablicy
 *                                                                  i nie wyczerpią się elementy w drugiej podtablicy*/
        if (extra_elem[finger1] <= extra_elem[finger2]) { /* jesli element pierwszej podtablicy jest mniejszy od
 *                                                           elementu z drugiej podtablicy*/
            element[current] = extra_elem[finger1];
            finger1++; /* przesun indeks lewej podtablicy*/
        } else{
            element[current] = extra_elem[finger2];
            finger2++; /* przesun indeks prawej podtablicy*/
        }
        current++; /* przesun indeks obecnego elementu*/
    }
    while (finger1 <= middleIndex) { /* kiedy druga podtablica jest pusta*/
        element[current] = extra_elem[finger1];
        current++;
        finger1++;
    }/* jesli lewa podtablica jest pusta to w oryginalnej tablicy juz ona jest na odpowienim miejscu*/
}

/* Wsywietla na standardowym wyjsciu elementy tablicy.*/
template <class TYPE, int Size>
std::ostream& operator << (std::ostream & Strm, const Array<TYPE, Size> & Arr){
    for (int i = 0; i < Size; i++) {
        Strm << Arr[i] << " ";
    }
    Strm <<std::endl;
    return Strm;
}
