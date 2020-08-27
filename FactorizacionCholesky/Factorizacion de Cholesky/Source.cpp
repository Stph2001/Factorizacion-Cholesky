#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>
using namespace std;

class Matriz {
private:
	double** matriz;
	int N = 0;
	bool sim = true;
public:
	Matriz(int n):N(n) {
		Crear_matriz();
		Generar_numeros();
	}
	~Matriz() {
		for (int i = 0; i < N; i++)
			delete[] matriz[i];
		delete[] matriz;
	}
	void Imprimir_matriz() {
		Imprimir();
	}
	double** Obtener_matriz() {
		return matriz;
	}
	bool Obtener_simetria() {
		simetria();
		return sim;
	}
	int Obtener_determinante() {
		return Determinante(matriz,N);
	}

private:
	void Crear_matriz() {
		matriz = new double* [N];
		for (int i = 0; i < N; i++)
			matriz[i] = new double[N];
	}
	void Generar_numeros() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				matriz[i][j] = 1;// double(rand() % (101 - 1) + 1) / 10;
		}
	}
	void Imprimir() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout<<matriz[i][j]<<"\t";
			cout << endl;
		}
	}
	void simetria() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matriz[i][j] != matriz[j][i])
					sim = false;
			}
		}
	}
	int Determinante(double**matriz1,int orden) {
		int det = 0;

		for (int i = 0; i < orden; i++) {
			det += matriz1[0][i] * cofactor(matriz1,orden,0,i);
		}
		return det;
	}
	int cofactor(double**matriz1,int orden,int fila,int columna) {
		double** submatriz = new double* [N];
		for (int i = 0; i < N; i++) {
			submatriz[i] = new double[N];
		}
		int n = orden - 1;

		int x = 0;
		int y = 0;
		for (int i = 0; i < orden; i++) {
			for (int j = 0; j < orden; j++) {
				if (i != fila && j != columna) {
					submatriz[x][y] = matriz1[i][j];
					y++;
					if (y>=n) {
						x++;
						y = 0;
					}
				}
			}
		}
		return pow(-1, fila + columna) * Determinante(submatriz,n);
	}
};

int main() {
	srand(time(NULL));
	int n = 0;

	do {
		cout << "Ingrese n entre 4 y 10: "; cin >> n;
	} while (n < 3 || n > 10);

	Matriz *m=new Matriz(n);

	m->Imprimir_matriz();

	if (m->Obtener_simetria() == true) {
		cout << "La matriz es simetrica"<<endl;
	}
	if (m->Obtener_determinante() > 0) {
		cout << "La matriz es definida positiva";
	}

	_getch();
	return 0;
}