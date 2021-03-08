# include <iostream>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <string>
# include <cmath>

using namespace std;

int compteurDeRecursivite = -1;

class Case {

private:

	bool reserve_;
	int valeur_;

public:
	Case(bool reserve, int valeur) {
		reserve_ = reserve;
		valeur_ = valeur;
	}

	bool getReserve() const {
		return reserve_;
	}

	int getValeur() const {
		return valeur_;
	}

	void setValeur(int valeur) {
		valeur_ = valeur;
	}
};

bool uniqueCarre(int i, int j, vector<vector<Case>>& tab, int dimCarre, int dimTab, int chiffre) {

	int ligne = i - (i % dimCarre);
	int col;
	int k = 0;
	int l;
	bool existeDeja = false;
	
	while (k < dimCarre && !existeDeja) {
		l = 0;
		col = j - (j % dimCarre);
		while (l < dimCarre && !existeDeja) {
			if (tab[ligne][col].getValeur() == chiffre) {
				existeDeja = true;
			}
			l ++;
			col ++;
		}
		k ++;
		ligne ++;
	}
	return !existeDeja;

}

bool uniqueLigne(int i, int j, vector<vector<Case>>& tab, int dimTab, int chiffre) {

	int ligne = 0;
	bool existeDeja = false;
	while (ligne < dimTab && !existeDeja) {
		if (tab[ligne][j].getValeur() == chiffre) {
			existeDeja = true;
		} 
		ligne ++;
	}
	return !existeDeja;
}

bool uniqueColonne(int i, int j, vector<vector<Case>>& tab, int dimTab, int chiffre) {

	int col = 0;
	bool existeDeja = false;
	while (col < dimTab && !existeDeja) {
		if (tab[i][col].getValeur() == chiffre) {
			existeDeja = true;
		} 
		col ++;
	}
	return !existeDeja;
}

bool estValide(int i, int j, vector<vector<Case>>& tab, int dimCarre, int dimTab, int chiffre) {

	
	return uniqueCarre(i, j, tab, dimCarre, dimTab, chiffre) &&
			uniqueLigne(i, j, tab, dimTab, chiffre) &&
			uniqueColonne(i, j, tab, dimTab, chiffre);
}

bool estRempli(vector<vector<Case>>& tab, int dimTab) {
	for (int i = 0; i < dimTab; i ++) {
		for (int j = 0; j < dimTab; j ++) {
			if (tab[i][j].getValeur() == 0) return false;
		}
	}
	return true;
}

bool remplir(int i, int j, int dimCarre, vector<vector<Case>>& tab, int dimTab) {
	if (i == dimTab-1 && j == dimTab) return true;
	if (j >= dimTab && i < dimTab) {
		j = 0;
		i ++;
	}
	if (tab[i][j].getReserve()) return remplir(i, j+1, dimCarre, tab, dimTab);
	for (int chiffre = 1; chiffre <= dimTab; chiffre ++) {
		if (estValide(i, j, tab, dimCarre, dimTab, chiffre)) {
			tab[i][j].setValeur(chiffre);
			compteurDeRecursivite ++;
			if (remplir(i, j+1, dimCarre, tab, dimTab)) return true;
		}
	}
	tab[i][j].setValeur(0);
	return false;
		
}

void afficherLigne() {
	cout << " ------------------------------" << endl;
}

void afficherSolution(vector<vector<Case>>& tab, int dimCarre, int dimTab) {

	afficherLigne();
	for (int i = 0; i < dimTab; i ++) {
		cout << "|";
		for (int j = 0; j < dimTab; j ++) {
			cout << tab[i][j].getValeur() << "  ";
			if (j != 0 && (j+1) % dimCarre == 0) {
				cout << "|";
			}
		}
		cout << endl;
		if ((i+1) % dimCarre == 0) {
			afficherLigne();
		}
	}
}

void sudoku(vector<vector<Case>>& tab, int dimCarre, int dimTab) {
	if (remplir(0, 0, dimCarre, tab, dimTab)) {
		cout << "done" << endl;
	} else {
		cout << "ERROR" << endl;
	}
}

// Supposé qu'une grille ait les dimensions 9x9
int main(int argc, char** argv) {

	if (argc > 2) {
		cout << "try: ./sudokuSolver <file containing sudoku>" << endl;
		
	} else {
		ifstream theFile;
		theFile.open(argv[1]);
		if (!theFile) {
			cout << "Unable to open file" << endl;
			cout << "try: ./sudokuSolver <file containing sudoku>" << endl;
			cout << "and make sure the file exists" << endl;
			exit(1);
		}

		cout << "solving ";


		int dimTab = 9;
		int dimCarre = 3;
		bool reserve;
		int number;
		vector<vector<Case>> tab;
		vector<Case> row;
		string line;
		int counterLine = 0;
		while (getline(theFile, line)) {
			if (counterLine == 0) {
 				cout << line << " ... "<< endl;
			} else {
				for (int col = 0; col < dimTab; col ++) {
					number = line[col] - '0';
					row.push_back(Case(!(number == 0), number));
				} 
				tab.push_back(row);
			}
			row.clear();
			counterLine ++;
		}

		theFile.close();
		sudoku(tab, dimCarre, dimTab);
		afficherSolution(tab, dimCarre, dimTab);
		cout << "Recursive calls: " << compteurDeRecursivite << endl;
	}

	return 0;
}