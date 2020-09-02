#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <iomanip>
using namespace std;

class Matriz {
private:
	float** matriz;
	float** matriz2;
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
	void Generar_Cholesky() {
		Cholesky();
	}

private:
	void Crear_matriz() {
		matriz = new float* [N];
		matriz2 = new float* [N];
		for (int i = 0; i < N; i++) {
			matriz[i] = new float[N];
			matriz2[i] = new float[N];
		}
	}
	void Generar_numeros() {
		matriz[0][0] = 5;
		matriz[0][1] = 4;
		matriz[0][2] = 3;
		matriz[1][0] = 4;
		matriz[1][1] = 6;
		matriz[1][2] = 2;
		matriz[2][0] = 3;
		matriz[2][1] = 2;
		matriz[2][2] = 3;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				//matriz[i][j] = double(rand() % (6 - 1) + 1); //double(rand() % (101 - 1) + 1) / 10;
				matriz2[i][j] = matriz[i][j];
			}
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

		cout << "El determinante es: ";
		if (N <= 5) {
			cout << float(*det) << endl;
		}
		else
			cout << int(*det) << endl;

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
	void Cholesky() {
		float** submatriz = new float* [N];
		for (int i = 0; i < N; i++) {
			submatriz[i] = new float[N];
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				submatriz[i][j] = 0;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				float sum = 0;

				if (j == i) {
					for (int k = 0; k < j; k++)
						sum += pow(submatriz[j][k], 2);
					submatriz[j][j] = sqrt(matriz2[j][j] - sum);
				}
				else {
					for (int k = 0; k < j; k++)
						sum += (submatriz[i][k] * submatriz[j][k]);
					submatriz[i][j] = (matriz2[i][j] - sum) / submatriz[j][j];
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matriz[i][j] = submatriz[i][j];
			}
		}
	}
};

int main() {
	srand(time(NULL));
	int n = 0;
	bool flag = false;
	bool flag2 = false;

	do {
		cout << "Ingrese n entre 4 y 10: "; cin >> n;
	} while (n < 3 || n > 10);

	Matriz *m=new Matriz(n);

	m->Imprimir_matriz();

	if (m->Obtener_simetria() == true) {
		cout << "La matriz es simetrica"<<endl;
		flag = true;
	}	

	if (m->Obtener_determinante() > 0) {
		cout << "La matriz es definida positiva";
		flag2 = true;
	}

	if (flag == true && flag2 == true) {
		cout << endl << endl << "Factorizacion de Cholesky: " << endl;
		m->Generar_Cholesky();
		m->Imprimir_matriz();
	}

	_getch();
	return 0;
}