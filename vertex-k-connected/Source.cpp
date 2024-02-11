#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

void DFS(int st, int** graph, int n, int* visited)
{
    visited[st] = 1;
    for (int i = 0; i < n; i++)
        if (graph[st][i] != 0 && !visited[i])
            DFS(i, graph, n, visited);
}

int Check(int** a, int k, int n)
{
    bool ret = false;
    int K = 0;
    do {
        K++;
        int res = 0, n1 = n - K, f, k1 = 0, k2 = 0, I = 1;
        int** a1 = new int* [n1];
        for (int i = 0; i < n1; i++)
        {
            a1[i] = new int[n1];
        }
        string bitmask(K, 1); //K лидирующих единиц
        bitmask.resize(n, 0); //дополнить до N позиций нулями
        vector <int> v;
        int* visited = new int[n1];
        do
        {
            f = 0;
            for (int i = 0; i < n; i++)
            {
                if (bitmask[i]) v.push_back(i);
            }
            for (int i = 0; i < n; i++)
            {
                k2 = 0;
                f = 0;
                for (int x = 0; x < K; x++)
                    if (v[x] == i)
                    {
                        f = 1;
                        k1++;
                    }
                if (f == 1)
                    continue;
                for (int j = 0; j < n; j++)
                {
                    f = 0;
                    for (int x = 0; x < K; x++)
                        if (v[x] == j)
                        {
                            f = 1;
                            k2++;
                        }
                    if (f == 1)
                        continue;
                    a1[i - k1][j - k2] = a[i][j];
                }
            }
            for (int i = 0; i < n1; i++)
            {
                visited[i] = 0;
            }
            f = 0;
            for (int i = 0; i < n1; i++)
            {
                for (int j = i + 1; j < n1; j++)
                {
                    if (a1[i][j] == 1)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                    break;
            }
            if (f == 0)
            {
                cout << "Комбинация вершин, которая приводит к разрыву: " << '{';
                for (int i1 = 0; i1 < v.size(); i1++)
                {
                    cout << v[i1] + 1;
                    if (i1 < v.size() - 1) cout << ", ";
                }
                cout << '}' << endl;
                ret = true;
            }
            f = 0;
            DFS(0, a1, n1, visited);
            for (int x = 0; x < n1; x++)
                if (visited[x] == 0)
                {
                    cout << "Комбинация вершин под №" << I << ", которая приводит к разрыву : " << '{';
                    for (int i1 = 0; i1 < v.size(); i1++)
                    {
                        cout << v[i1] + 1;
                        if (i1 < v.size() - 1) cout << ", ";
                    }
                    cout << '}' << endl;
                    ret = true;
                    break;
                }
            k1 = 0;
            v.clear();
            I++;
        } while (prev_permutation(bitmask.begin(), bitmask.end()));
        for (int i = 0; i < n1; i++)
        {
            delete[] a1[i];
        }
        delete[] a1;
        v.clear();
        if (ret)
            return K;
    } while (K != k);
    return k + 1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    chrono::time_point<chrono::steady_clock> start_time, end_time;
    start_time = chrono::high_resolution_clock::now();
    int n, m, k, C;
    ifstream inputFile("input.txt");
    if (!inputFile)
    {
        cout << "Ошибка! Не удалось открыть входной файл input.txt" << endl;
        return 1;
    }
    inputFile >> n >> m >> k;
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        inputFile >> u >> v;
        a[u - 1][v - 1] = 1;
        a[v - 1][u - 1] = 1;
    }
    if (k <= 0)
    {
        cout << "Введенно не верное значение! k должно быть > 0." << endl;
    }
    else if (k == n - 1)
    {
        cout << "В данном случае k = n - 1 и если граф полный то он будет вершинно " << k << "-связнный, а если нет, то попробуйте взять k < " << k << endl;
    }
    else
    {
        int K = Check(a, k, n);
        if (k >= K)
            cout << "Граф вершинно " << K << "-связнный" << endl;
        else
            cout << "Граф не вершинно " << k << "-связнный" << endl;
    }
    for (int i = 0; i < n; i++)
    {
        delete[] a[i];
    }
    delete[] a;
    end_time = chrono::high_resolution_clock::now();//останавливам таймер
    chrono::duration<double, milli> search_time = (end_time - start_time);//вычисляем время в мили секундах
    cout << "Полное время работы программы составляет " << search_time.count() / 1000 << "\n" << endl;
    return 0;
}