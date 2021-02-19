#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
double* EnterMass(int n)
{
    double* a = new double[n];
    return a;
}
void In(double n, double* a)
{
    for (int i = 0; i < n; i++) {
        double x;
        cout << "\na="; cin >> x;
        a[i] = x;
    }
}
void out(int n, double* a)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}
void Add(int& n, double*& a, double y, int k)
{
    if (k<1 || k>n + 2)
        cout << "error" << endl;
    else {
        double* t = EnterMass(n + 1);
        n++;
        for (int i = 0; i < k - 1; i++)
        {
            t[i] = a[i];
        }
        t[k - 1] = y;
        for (int i = k; i < n; i++)
        {
            t[i] = a[i - 1];
        }
        delete[] a;
        a = t;
    }

}
int FileIn()
{
    double buff;
    int count = 0;
    ifstream mass;
    mass.open("MassLaba.txt");
    if (!mass)
    {
        cout << "\o/ You've got an error" << endl;
        return 0;
    }
    while (mass >> buff)
        count++;
    mass.close();
    return count;
}

void MassInFileFilling(int& n, double*& a)
{
    ifstream mass;
    mass.open("MassLaba.txt");
    if (!mass)
    {
        cout << ":( You've got an error" << endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        mass >> a[i];
    }
    mass.close();

}
bool DelElem(double*& a, int &CountN, int k)
{
    if (k > CountN || k < 1)
    {
        cout << "Error!" << endl;
        return false;
    }

    for (int ix = k - 1; ix < CountN - 1; ix++)
    {
        a[ix] = a[ix + 1];
    }
    CountN--;
    return true;
}
void AddAfterTheFirstElem(double*& a, int &countN, double k, double y)
{
    bool x = 0;
    for (int i = 0;i < countN;i++)
    {
        if (a[i] == k) {
            Add(countN, a, y, i+2);
            x = 1;
            break;
        }
    }
    if (x == 0) cout << "No such element!" << endl;
}
void DeleteSelectedElems(double*& a, int& countN, double k)
{
    bool x = 0;
    for (int i = 0;i < countN;i++)
    {
        if (a[i] == k) {
            DelElem(a, countN, i+1);
            i--;
            x = 1;
        }
    }
    if (x == 0) cout << "No such element!" << endl;

}
int main()
{
    int k;
    int countN = 0;
    double y;

    countN = FileIn();
    cout << "LenghtOfArray=" << countN << endl;
    double* a = EnterMass(countN);
    MassInFileFilling(countN, a);
    out(countN, a);
    cout << "(adding) k=";cin >> k;
    cout << "Enter what you want to add=";cin >> y;
    Add(countN, a, y, k);
    srand(time(0));
    double y1 = rand();
    out(countN, a);
    cout << "(random adding) k=";cin >> k;
    Add(countN, a, y1, k);
    out(countN, a);
    cout << "(deleting) k=";cin >> k;
    DelElem(a, countN, k);
    out(countN, a);
    double y2, y3;
    cout << "Enter what elem you want to search=";cin >> y2;
    cout << "Enter what you want to add if elem is found=";cin >> y3;
    AddAfterTheFirstElem(a, countN, y2, y3);
    out(countN, a);
    double persik;
    cout << "What elems you want to delete=";cin >> persik;
    DeleteSelectedElems(a, countN, persik);
    out(countN, a);
    delete[] a;
    a = NULL;
    return 0;
}