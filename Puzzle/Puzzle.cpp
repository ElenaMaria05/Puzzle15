#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int moves = 0;
bool se_executa = false;

void Generare(int(&matrice)[4][4]) {
	vector<int>aux;
	int count = 0;
	for (int i = 0; i < 16; i++) {
		aux.push_back(count);
		count++;
	}
	// Crearea unui generator de numere aleatoare
	random_device rd;
	mt19937 gen(rd());
	shuffle(aux.begin()+1, aux.end(), gen);

	count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrice[i][j] = aux[count];
			count++;
		}
	}
}

void Afisare(int(&matrice)[4][4]) {
	system("cls");
	if (se_executa) {
		moves++;
	}
	se_executa = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrice[i][j] == 0) {
				cout << ' ' << "   ";
				continue;
			}
			if (matrice[i][j] < 10) {
				cout << matrice[i][j] << "   ";
				continue;
			}
			if (matrice[i][j] > 0) {
				cout << matrice[i][j] << "  ";
				continue;
			}

		}
		cout << endl;
	}
	cout << endl << "(moves): " << moves;
	cout << endl << "(w,a,s,d,q): ";

}

bool MutareValida(int linie_gol, int coloana_gol, int linie_element, int coloana_element) {
	bool este_adiacent = (linie_gol == linie_element && abs(coloana_gol - coloana_element) == 1) ||
		(coloana_gol == coloana_element && abs(linie_gol - linie_element) == 1);

	bool in_limite = linie_element >= 0 && linie_element <= 3 && coloana_element >= 0 && coloana_element <= 3;

	return este_adiacent && in_limite;
}

void Update(int (&matrice)[4][4], int linie_gol,int coloana_gol, int linie_element,int coloana_element) {
		int aux = matrice[linie_gol][coloana_gol];
		matrice[linie_gol][coloana_gol] = matrice[linie_element][coloana_element];
		matrice[linie_element][coloana_element] = aux;
}

bool Win(int(&matrice)[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 3 && j == 2) {
				break;
			}
			if (matrice[i][j] > matrice[i][j + 1]) {
				return false;
			}
		}
	}
	return true;
}
void Joc(int(&matrice)[4][4]) {
	char comanda;
	do {
		cin >> comanda;
		
		int pozitie_gol_x, pozitie_gol_y;
		bool continua_cautarea = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrice[i][j] == 0) {
					pozitie_gol_x = i;
					pozitie_gol_y = j;
					continua_cautarea = false;
					break;
				}
			}
			if (!continua_cautarea) break;
		}

		if (comanda == 'a') {
			if (MutareValida(pozitie_gol_x, pozitie_gol_y, pozitie_gol_x, pozitie_gol_y + 1)) {
				Update(matrice, pozitie_gol_x, pozitie_gol_y, pozitie_gol_x, pozitie_gol_y + 1);
				se_executa = true;
			}
		}
		else if (comanda == 's') {
			if (MutareValida(pozitie_gol_x, pozitie_gol_y, pozitie_gol_x - 1, pozitie_gol_y)) {
				Update(matrice, pozitie_gol_x, pozitie_gol_y, pozitie_gol_x - 1, pozitie_gol_y);
				se_executa = true;
			}
		}
		else if (comanda == 'd') {
			if (MutareValida(pozitie_gol_x, pozitie_gol_y, pozitie_gol_x, pozitie_gol_y - 1)) {
				Update(matrice, pozitie_gol_x, pozitie_gol_y, pozitie_gol_x, pozitie_gol_y - 1);
				se_executa = true;
			}
		}
		else if (comanda == 'w') {
			if (MutareValida(pozitie_gol_x, pozitie_gol_y, pozitie_gol_x + 1, pozitie_gol_y)) {
				Update(matrice, pozitie_gol_x, pozitie_gol_y, pozitie_gol_x + 1, pozitie_gol_y);
				se_executa = true;
			}
		}

		Afisare(matrice);

		if (Win(matrice)) {
			cout << " ********************* AI CASTIGAT *********************  \n";
			return;
		}

	} while (comanda != 'q');
}
int main(){
	int matrice[4][4];
	Generare(matrice);
	Afisare(matrice);
	Joc(matrice);
	cout << "Jocul s-a terminat! ";
}

