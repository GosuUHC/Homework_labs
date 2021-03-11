#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;


void NewMemoryForMatr(double**& a, int n, int m)
{
	
	a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[m];
}
void DelMatrMemory(double**& a, int n, int m)
{
	
	for (int i = 0; i < n; i++)
		delete[]a[i];
	delete[]a;
}
int GetNumber()
{
	float n;
	do {
		cout << "Enter number(int):";
		cin >> n;
		if (n <= 0 || (n - (int)n))
			cout << "Error not found!(Marat edition)" << endl;
	} while (n <= 0 || (n - (int)n));

	return n;
}

void Out(double** a, int n, int m)
{
	cout << endl << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout <<setw(15)<< a[i][j];
		cout << endl;
	}
}
bool GetFileMatr(double** a, int n, int m) {

	ifstream f;
	f.open("file.txt");
	if (f) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				f >> a[i][j];
			}
		}
	}
	f.close();
	return true;
}
void triangMatr(double** A, double** B, int n) {
	double koef;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = k + 1; i < n; i++) {
			koef = -1. * B[i][k] / B[k][k];
			for (int j = k; j < n + 1; j++) {
				B[i][j] = B[i][j] + B[k][j] * koef;
			}
		}
	}
	Out(B, n, n + 1);
}
void PrintVect(double* x, int n) {
	cout << endl;
	cout << "Vector resheniy" << endl;
	for (int j = 0; j < n; j++)
		cout << setw(5) << x[j];
	cout << endl;
}
void Solve(double** A, double* x, int n) {
	double res = 0;
	double** B;
	NewMemoryForMatr(B, n, n + 1);
	triangMatr(A, B, n);
	for (int i = n - 1; i >= 0; i--) {
		res = 0;
		for (int j = i + 1; j <= n - 1; j++) {
			res = res - x[j] * B[i][j];
		}
		res += B[i][n];
		x[i] = res / B[i][i];
	}
	
	DelMatrMemory(B, n, n + 1);
	
}
void OpredGauZzZ(double **a, int n, int m)
{
	double op=1;
	double** B;
	NewMemoryForMatr(B, n, n + 1);
	triangMatr(a, B, n);
	int i=0, j=0;
	for(;i<n;i++)
		{
			j = i;
			op *= B[i][j];
		}
	cout << "\nOpred=" << op << endl;
}
void clone(double**& M, int n, int m, double** M1)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M1[i][j] = M[i][j];
}
void inver(double** M, int n, int m, double**& rev)
{
	cout <<endl<< "obratka" << endl;
	double* x = new double[n];
	bool t = true;
	for (int i = 0; i < n; i++)
	{
		double** buff;
		NewMemoryForMatr(buff, n, m);
		clone(M, n, m, buff);
		for (int j = 0; j < n; j++)
		{
			if (i == j) buff[j][m - 1] = 1;
			else buff[j][m - 1] = 0;
		}
		Solve(buff, x, n);
		for (int j = 0; j < n; j++)
			rev[j][i] = x[j];
		DelMatrMemory(buff, n, m);
	}
	delete[] x;
	x = NULL;
	
}
void test(double**& A, int n, int m)
{
	int s;
	cout << "Enter number test: "; cin >> s;
	switch (s)
	{
	case 1:
	{
		GetFileMatr(A, n, m);
		break;
	}
	case 2:
	{
		double a, b;
		srand(time(0));
		a = -10;
		b = 10;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				A[i][j] = a + ((double)rand() / RAND_MAX) * (b - a);
			}
		break;
	}
	case 3:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (i == j) A[i][j] = 1;
				else A[i][j] = 0;
		break;
	}
	case 4:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				A[i][j] = 0;
		break;
	}
	case 5:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				A[i][j] = 1. / (i + j + 1);
		break;
	}
	}
}
int main()
{
	int n = GetNumber();
	
	double** a;
	double** copya;
	double** re;
	double* x = new double[n];
	NewMemoryForMatr(a, n, n+1);
	NewMemoryForMatr(copya, n, n + 1);
	NewMemoryForMatr(re, n, n + 1);
	test(a, n, n + 1);
	Out(a, n, n+1);
	clone(a, n, n + 1, copya);
	Solve(a, x, n);
	PrintVect(x, n);
	inver(copya, n, n + 1, re);
	Out(re, n, n);
	OpredGauZzZ(a, n, n + 1);
	DelMatrMemory(a, n, n+1);
	delete[]x;
	x = NULL;
	cout << "bye";
	return 0;
}
