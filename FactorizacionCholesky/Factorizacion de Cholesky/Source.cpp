#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <iomanip>
using namespace std;

class Matriz {
private:
	float** matriz;
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
	float** Obtener_matriz() {
		return matriz;
	}
	bool Obtener_simetria() {
		simetria();
		return sim;
	}
	int Obtener_determinante() {
		return Determinante();
	}

private:
	void Crear_matriz() {
		matriz = new float* [N];
		for (int i = 0; i < N; i++)
			matriz[i] = new float[N];
	}
	void Generar_numeros() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				matriz[i][j] = double(rand() % (6 - 1) + 1); //double(rand() % (101 - 1) + 1) / 10;
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
	int Determinante() {
		int det = 1;
		float** submatriz=new float*[N];
		for (int i = 0; i < N; i++) {
			submatriz[i] = new float[N];
		}
		Escalonar(submatriz);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					det *= submatriz[i][j];
			}
		}

		cout << "El determinante es: " << det << endl;
		return det;
	}
	void Escalonar(float**submatriz) {
		float num;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				submatriz[i][j] = matriz[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i != 0 && matriz[i][j] != 0 && j < i) {
					num = submatriz[i][j] / submatriz[j][j];
					for (int k = j; k < N; k++) {
						if (num*submatriz[j][k]==submatriz[i][k]||k<=j)
							submatriz[i][k] = 0;
						else
							submatriz[i][k] = -(num * submatriz[j][k]) + submatriz[i][k];
					}
					if (j + 1 == i)
						break;
				}
				else
					submatriz[i][j] = matriz[i][j];
			}
		}

		cout << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout <<setprecision(2)<< submatriz[i][j] << "\t";
			}
			cout << endl;
		}
	}
};

int main() {
	srand(time(NULL));
	int n = 0;

	do {
		cout << "Ingrese n entre 4 y 10: "; cin >> n;
	} while (n < 4 || n > 10);

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