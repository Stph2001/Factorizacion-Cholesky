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
		double* det = new double;
		*det = 1;
		
		Escalonar();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					*det = *det * matriz[i][j];
			}
		}

		cout << "El determinante es: " <<  (int)*det << endl;
		return *det;
	}
	void Escalonar() {
		float num = 1000;
		float** submatriz = new float* [N];
		for (int i = 0; i < N; i++) {
			submatriz[i] = new float[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				submatriz[i][j] = matriz[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int k = 0; k < i; k++) {
				for (int j = k; j < N; j++) {
					if (num == 1000) {
						if (submatriz[j][j] != 0) {
							num = submatriz[i][j] / submatriz[j][j];
						}
						else
							num = 1;
					}
					if (submatriz[k][j] * num != 0) {
						submatriz[i][j] = -(submatriz[k][j] * num) + (submatriz[i][j]);
					}
					else
						submatriz[i][j] = submatriz[i][j];
					submatriz[i][k] = 0;
				}
				num = 1000;
			}
		}

		cout << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matriz[i][j] = submatriz[i][j];
				cout <<setprecision(2)<< matriz[i][j] << "\t";
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
	} while (n < 3 || n > 10);

	Matriz *m=new Matriz(n);

	m->Imprimir_matriz();

	if (m->Obtener_simetria() == true) {
		cout << "La matriz es simetrica"<<endl;
	}

	

	if (m->Obtener_determinante() >= 0) {
		cout << "La matriz es definida positiva";
	}

	_getch();
	return 0;
}