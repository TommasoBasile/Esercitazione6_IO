#include <SortingAlgorithm.hpp>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <numeric>
#include <vector>
#include <Eigen/Eigen>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace SortLibrary;

int main(int argc, char *argv[])
{
    vector<int> nValues;

    for(int i = 0; i < argc; i++)
    {nValues.push_back(atoi(argv[i]));}  // si memorizza dalla command-line

    nValues.erase(nValues.begin()); // si cancella il primo

    for(int i = 0; i < nValues.size(); i++)
    {    int n = nValues[i];

        double sum1 = 0;
        double sum2 = 0;
        double sum3 = 0;
        double sum4 = 0;
        double sum5 = 0;
        double sum6 = 0;

        vector<double> timeElapsedRand1;
        vector<double> timeElapsedRand2;

        vector<double> timeElapsedOrd1;
        vector<double> timeElapsedOrd2;

        vector<double> timeElapsedPer1;
        vector<double> timeElapsedPer2;

        int iterazioni = 100;
        for(int k = 0; k < iterazioni; k++)
        {
        // vettori Randomici
        vector<int> v1;
        vector<int> v2;
        for(int j = 0; j < n; j++)
        {int num = rand() % 100 + 1;  // numeri casuali da 0 a 100
            v1.push_back(num);
            v2.push_back(num);}

        chrono::steady_clock::time_point t_begin1 = chrono::steady_clock::now();
        MergeSort(v1);
        chrono::steady_clock::time_point t_end1 = chrono::steady_clock::now();
        chrono::steady_clock::time_point t_begin2 = chrono::steady_clock::now();
        BubbleSort(v2);
        chrono::steady_clock::time_point t_end2 = chrono::steady_clock::now();

        timeElapsedRand1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end1-t_begin1).count());
        timeElapsedRand2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end2-t_begin2).count());

        sum1 += timeElapsedRand1[k];  // si sommano i tempi
        sum2 += timeElapsedRand2[k];

        // vettori Ordinati
        chrono::steady_clock::time_point t_begin3 = chrono::steady_clock::now();  // si usano gli stessi di prima perche già ordinati
        MergeSort(v1);
        chrono::steady_clock::time_point t_end3 = chrono::steady_clock::now();
        chrono::steady_clock::time_point t_begin4 = chrono::steady_clock::now();
        BubbleSort(v2);
        chrono::steady_clock::time_point t_end4 = chrono::steady_clock::now();

        timeElapsedOrd1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end3-t_begin3).count());
        timeElapsedOrd2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end4-t_begin4).count());

        sum3 += timeElapsedOrd1[k];  // si sommano i tempi
        sum4 += timeElapsedOrd2[k];

        // vettori Perturbati
        int perturbazione = rand() % (1 - (-1) + 1) + (-1);
        for(int j = 0; j < n; j++)
        {   v1[j] += perturbazione;
            v2[j] += perturbazione;}

        chrono::steady_clock::time_point t_begin5 = chrono::steady_clock::now();  // si usano gli stessi di prima perche già ordinati
        MergeSort(v1);
        chrono::steady_clock::time_point t_end5 = chrono::steady_clock::now();
        chrono::steady_clock::time_point t_begin6 = chrono::steady_clock::now();
        BubbleSort(v2);
        chrono::steady_clock::time_point t_end6 = chrono::steady_clock::now();

        timeElapsedPer1.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end5-t_begin5).count());
        timeElapsedPer2.push_back(chrono::duration_cast<chrono::nanoseconds>(t_end6-t_begin6).count());

        sum5 += timeElapsedPer1[k];  // si sommano i tempi
        sum6 += timeElapsedPer2[k];


    }
        // si devono rappresentare i tempi in nano secondi in qaundo se si rappresentassero in micro alcuni risulterebbero 0
        cout << "Media M con dimensione " << n << " e vettore randomico: " << sum1/iterazioni << endl;  // si calcola la media dei tempi
        cout << "Media B con dimensione " << n << " e vettore randomico: " << sum2/iterazioni << endl;
        cout << "Media M con dimensione " << n << " e vettore ordinato: " << sum3/iterazioni << endl;
        cout << "Media B con dimensione " << n << " e vettore ordinato: " << sum4/iterazioni << endl;
        cout << "Media M con dimensione " << n << " e vettore perturbato: " << sum5/iterazioni << endl;
        cout << "Media B con dimensione " << n << " e vettore perturbato: " << sum6/iterazioni << endl;
    }

    cout << "In tutti i casi si nota la netta differenza tra i tempi di calcolo del mergeSort e del bubbleSort, infatti il secondo è sempre più veloce del primo inoltre all'aumentare della dimensione del vettore la differenza si fa ancora più marcata" << endl;
    return 0;
}

