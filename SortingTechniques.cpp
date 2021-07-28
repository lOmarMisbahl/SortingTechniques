#include <iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>

using namespace std::chrono;
using namespace std;

void print_vector(vector<int> &vec)
{
    for (int i=0; i<vec.size(); i++)
        cout<<vec[i]<<" ";
    cout << endl << endl;
}

int smallest(int x, int y, int z)
{
    return min(std::min(x, y), z);
}

int largest(int x, int y, int z)
{
    return std::max(std::max(x, y), z);
}

int middlest(int x, int y, int z)
{

    if(y>x && x>=z || z>x && x>=y)
    {
        return x;
    }
    if(x>y && y>=z || z>y && y>=x)
    {
        return y;
    }
    if(x>z && z>=y || y>z && z>=x)
    {
        return z;
    }

}

int find_pivot(vector<int> &vec, int first, int last)
{
    int middle = (last+first-1)/2;

    int maximum;
    int minimum;
    int median;

    minimum=smallest(vec[first],vec[middle],vec[last-1]);
    maximum=largest(vec[first],vec[middle],vec[last-1]);
    median=middlest(vec[first],vec[middle],vec[last-1]);

    vec[first]=minimum;
    vec[last-1]=median;
    vec[middle]=maximum;

    return median;
}
int partition(vector<int> &vec, int first, int last )
{
    int pivot = find_pivot(vec,first,last);

    int L = first;
    int R = last-2;

    while( L < R )
    {
        while( vec[L] <= pivot && L<last-1)
            L++;
        while( vec[R] >= pivot && last-1>R )
            R--;
        if (R>=L)
            std::swap(vec[L++], vec[R--]);
    }

    if (vec[L]!=vec[last-1])
        std::swap(vec[L], vec[last-1]);

    return L;
}

void quicksort(vector<int> &vec, int first, int last )
{
    if (last==first)
        return;

    int pivot_index = partition( vec, first, last );
    quicksort( vec, first, pivot_index );
    quicksort( vec, pivot_index+1, last );


}

void insertionSort(vector<int> &vec, int size)
{
    int k,i;
    for(k=1 ; k<size ; k++)
    {
        int newEntry = vec[k];
        for(int i = k ; i > 0 ; --i )
        {
            if(vec[i-1]>vec[i])
            {
                vec[i]=vec[i-1];
                vec[i-1]=newEntry;
            }
            else
            {
                vec[i]=newEntry;
                break;
            }

        }
    }

}


void heapify(vector<int> &vec, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && vec[l] > vec[largest])
        largest = l;


    if (r < n && vec[r] > vec[largest])
        largest = r;


    if (largest != i)                   //Check if the parent index changed if yes then it swaps it with older son and heapify the new son
    {
        swap(vec[i], vec[largest]);

        heapify(vec, n, largest);

    }
}


void heapSort(vector<int> &vec, int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vec, n, i);


    for (int i = n - 1; i >= 0; i--)    //pop the greatest element push it in the back
    {

        swap(vec[0], vec[i]);


        heapify(vec, i, 0);
    }
}



void Read(vector<int> &vec1, vector<int> &vec2)
{

    ifstream file1,file2;
    int num1,num2;
    char filename1[50],filename2[50];
    cout<<"Enter first file name: ";
    cin.getline(filename1,50);
    file1.open(filename1);
    if(!file1.is_open())
    {
        cout<<"Error Reading File!"<<endl;
        exit(EXIT_FAILURE);
    }
    while(file1.good())
    {
        file1>>num1;
        vec1.push_back(num1);
    }
    cout<<"First file read successfully!"<<endl;
    cout<<"Enter second file name: ";
    cin.getline(filename2,50);
    file2.open(filename2);
    if(!file2.is_open())
    {
        cout<<"Error Reading File!"<<endl;
        exit(EXIT_FAILURE);
    }
    while(file2.good())
    {
        file2>>num2;
        vec2.push_back(num2);
    }
    cout<<"Second file read successfully!"<<endl;



}

int main()
{


    vector<int> vec1,vec2;
    Read(vec1,vec2);
    cout << "First array before sorting : ";
    print_vector(vec1);
    cout << "Second array before sorting : ";
    print_vector(vec2);

    if(vec1.size()==vec2.size())
        cout << "Files are identical!";
    else
        cout << "Files aren't identical!";
    cout << endl << endl;

    auto start1 = high_resolution_clock::now();      // gives the actual time now

    quicksort(vec1,0,vec1.size());
    //heapSort(vec1, vec1.size());
    //insertionSort(vec1,vec1.size());

    auto stop1 = high_resolution_clock::now();
    //auto duration1 = duration_cast<microseconds>(stop1 - start1);

    auto start2 = high_resolution_clock::now();

    //quicksort(vec2,0,vec2.size());
    //heapSort(vec2, vec2.size());
    insertionSort(vec2,vec2.size());

    auto stop2 = high_resolution_clock::now();
    //auto duration2 = duration_cast<microseconds>(stop2 - start2);

    duration<double> duration1 = stop1-start1;
    duration<double> duration2 = stop2-start2;

    cout << "First Array after sorting : ";
    print_vector(vec1);
    cout << "Time taken to sort first array : "<< duration1.count() << " Seconds" << endl << endl;
    cout << "Second array after sorting : ";
    print_vector(vec2);
    cout << "Time taken to sort second array : "<< duration2.count() << " Seconds" << endl << endl;

    return 0;
}
