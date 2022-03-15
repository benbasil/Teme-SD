#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <tuple>

using namespace std;
using namespace std::chrono;

void afisare(int l[], int n){
    for (int i=0; i<n; i++)
        cout << l[i] << ' ';
    cout<<endl;
}

void interschimbare(int *x, int *y){
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}


int selectarepivot(int lista[], int s, int d){
    int aux = lista[(d+s)/2];
    int a = lista[s];
    int b = lista[d];
    int mediana = max(min(a,b), min(max(a,b),aux));

    if (mediana == a)
        return s;
    else {
        if (mediana == b)
            return d;
        else return (d+s)/2;
    }
}

int quicksortpartition (int lista[], int s, int d){
    int pivot = d;
    int i = s, j = d;
        while (i<j){

            while ((i<j) && (lista[i] <= lista[pivot]))
                i++;

            while ((j>i) && (lista[j] >= lista[pivot]))
                j--;
            if(i<j)
                interschimbare(&lista[i], &lista[j]);
        }
    if (pivot!=j)
        interschimbare(&lista[pivot],&lista[j]);

    return j;
}

void quicksort(int lista[], int s, int d){
    int mij;
    if (s < d){
        mij = quicksortpartition(lista, s, d);
        quicksort(lista,s,mij-1);
        quicksort(lista, mij+1, d);

    }

}



void merge(int lista[], int s, int mij, int d){
    int* auxstanga = new int[mij-s+1];
    int* auxdreapta = new int[d-mij];
    int i, j, k;
    int nrelemstanga = mij-s+1, nrelemdreapta = d-mij;

    for(i = 0; i < nrelemstanga; i++)
        auxstanga[i] = lista[s+i];
    for(j = 0; j < nrelemdreapta; j++)
        auxdreapta[j] = lista[mij+1+j];

    i = 0; j = 0; k = s;
    while (i < nrelemstanga && j < nrelemdreapta){
        if (auxstanga[i] <= auxdreapta[j]){
            lista[k] = auxstanga[i];
            i++;
        }
        else{
            lista[k] = auxdreapta[j];
            j++;
        }
        k++;
    }
    while(i < nrelemstanga){
        lista[k] = auxstanga[i];
        i++; k++;
    }
    while(j < nrelemdreapta){
        lista[k] = auxdreapta[j];
        j++; k++;
    }
    delete[] auxstanga;
    delete[] auxdreapta;
}

void mergesort(int lista[],int s, int d){
    if (s < d){
        int mij = s + ((d - s) / 2);
        mergesort(lista, s, mij);
        mergesort(lista, mij+1, d);

        merge(lista, s, mij, d);
    }
}



void shellsort(int lista[], int n){

    int shell, i, j, dec, aux;
    for (shell = n/2; shell > 0; shell /= 2){
        for (dec = 0; dec < shell; dec++){
            for (i = dec; i < n; i+=shell){
                aux = lista[i];
                for (j = i; j>=shell && lista[j-shell] > aux; j-= shell)
                    lista[j] = lista[j-shell];
                lista[j] = aux;
            }
        }
    }
}


int maxim(int lista[], int n){
    int max = lista[0];
    for(int i=0; i<n; i++)
        if (max<lista[i]) max = lista[i];
    return max;
}

void bucketsort(int lista[], int n){
    int nrbucket = floor(sqrt(n))/2;
    //array<vector<int>, 100> buckets ;
    vector<int> buckets[n];
    int poz, i, j;
    int mbucket = maxim(lista,n) / nrbucket;
    for(i=0; i<n; i++){
        poz = lista[i]/mbucket;
        if (poz == 0)
            buckets[1].push_back(lista[i]);
        else
            buckets[poz].push_back(lista[i]);
    }
    for (i = 0; i<=nrbucket;i++)
        sort(buckets[i].begin(), buckets[i].end());

    int index = 0;
    for (i = 0; i<=nrbucket; i++){
        for (j=0; j<buckets[i].size();j++){
            lista[index] = buckets[i][j];
            index++;
        }
    }
}



void bubblesort(int lista[], int n){
    bool ok;
    for (int i = 0; i<n; i++){
        ok = true;
        for (int j = 0; j<n-1; j++)
            if (lista[j] > lista[j+1]){
                ok = false;
                interschimbare(&lista[j], &lista[j+1]);
            }
        if (ok == true)
            break;
    }
}



void initializare(int l[], int n, int max){
    for (int i = 0; i < n; i++)
        l[i] = rand() % max;

}

void verificare(int l[], int n){
    for (int i = 0; i<n-1; i++){
        for (int j = i+1;j<n;j++)
            if (l[i] > l[j]){
                cout<<"Nu este corect sortat"<<endl;
                return;
            }
    }
    cout<<"Este corect sortat."<<endl;
}


void countsort(int lista[], int n){
    int max = maxim(lista, n), k = 0, i;
    int* count = new int[max];
    for (i = 0; i <= max; i++)
        count[i] = 0;
    for (i = 0; i < n; i++)
        count[lista[i]]++;
    for (i = 0; i <= max; i++){
        while (count[i] != 0){
            lista[k] = i;
            k++; count[i]--;
        }
    }
    delete[] count;
}

void countsortradix(int lista[], int n, int x){
    int max = maxim(lista, n), i;
    int count[10] = { 0 };
    int* aux = new int[n];

    for (i = 0; i < n; i++){
        aux[i] = 0;
    }
    for (i = 0; i < n; i++)
        count[(lista[i]/x) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i-1];

    for (i = n-1; i >= 0; i--){
        aux[count[(lista[i]/x)%10]-1] = lista[i];
        count[(lista[i]/x)%10]--;
        }

    for (i = 0; i < n; i++)
        lista[i] = aux[i];
    delete[] aux;
}

void radixsort(int lista[], int n){
    int max = maxim(lista,n);
    int x;
    for(x = 1; max / x > 0; x *= 10)
        countsortradix(lista, n, x);
}

tuple<int, int> citiredouanumere(string str){
    string nr = "";
    int nr1, nr2;
    for (auto x : str)
    {
        if (x == ' ')
        {
            nr1 = stoi(nr);
            nr = "";
        }
        else {
            nr = nr + x;
        }
    }
    nr2 = stoi(nr);
    return {nr1, nr2};
}

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int nrteste, k = 1;
    string text;
    char* nr;
    ifstream f("teste.txt");
    getline(f, text);
    nrteste = stoi(text);

    while(k <= nrteste) {
        cout<<"Test "<<k<<':'<<endl;
        getline(f, text);
        auto [n, marimenumere] = citiredouanumere(text);
        cout<<"Numere: "<<n<<" Marimea Numerelor:"<<marimenumere<<' '<<endl;
        text.clear();
        int* lista = new int[n];
        initializare(lista, n, marimenumere);

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        //countsort(lista, n);
        //bucketsort(lista, n);  //nu merge inca;
        //bubblesort(lista, n);
        //mergesort(lista, 0, n-1);
        //shellsort(lista, n);
        //quicksort(lista,0,n-1); //cu mediana a 3 nr;
        radixsort(lista,n); // doar in baza 10;


        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> d = duration_cast<duration<double>>(t2 - t1);

        //afisare (lista, n);
        //verificare(lista, n);
        cout << "Timpul executiei sortarii este de "<< d.count() << " secunde" <<endl<<endl<< endl;
        k++;
        delete[] lista;
    }
    //initializare(lista, n, marimenumere);
    //verificare(lista, n);
    //afisare(lista, n);
    //cout<<endl;



    //countsort(lista, n);
    //bucketsort(lista, n);  //nu merge inca;
    //bubblesort(lista, n);
    //mergesort(lista, 0, n-1);
    //shellsort(lista, n);
    //quicksort(lista,0,n-1); //cu mediana a 3 nr;
    //radixsort(lista,n);


    //afisare (lista, n);
    //verificare(lista, n);
    f.close();

    return 0;
}
