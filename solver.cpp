# include "solver.hpp"

bool sudoku(vector<vector<Case>>& tab, int dimCarre, int dimTab) {
	if (remplir(0, 0, dimCarre, tab, dimTab)) return true;
	else return false;
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
			if (remplir(i, j+1, dimCarre, tab, dimTab)) return true;
		}
	}
	tab[i][j].setValeur(0);
	return false;		
}

bool estValide(int i, int j, vector<vector<Case>>& tab, int dimCarre, int dimTab, int chiffre) {

	
	return uniqueCarre(i, j, tab, dimCarre, chiffre) &&
			uniqueLigne(j, tab, dimTab, chiffre) &&
			uniqueColonne(i, tab, dimTab, chiffre);
}

bool uniqueCarre(int i, int j, vector<vector<Case>>& tab, int dimCarre, int chiffre) {

	int ligne = i - (i % dimCarre);
	int col;
	int k = 0;
	int l;
	bool existeDeja = false;
	
	while (k < dimCarre && !existeDeja) {
		l = 0;
		col = j - (j % dimCarre);
		while (l < dimCarre && !existeDeja) {
			if (tab[ligne][col].getValeur() == chiffre) existeDeja = true;
			l ++;
			col ++;
		}
		k ++;
		ligne ++;
	}
	return !existeDeja;

}

bool uniqueLigne(int j, vector<vector<Case>>& tab, int dimTab, int chiffre) {

	int ligne = 0;
	bool existeDeja = false;
	while (ligne < dimTab && !existeDeja) {
		if (tab[ligne][j].getValeur() == chiffre) existeDeja = true;
		ligne ++;
	}
	return !existeDeja;
}

bool uniqueColonne(int i, vector<vector<Case>>& tab, int dimTab, int chiffre) {

	int col = 0;
	bool existeDeja = false;
	while (col < dimTab && !existeDeja) {
		if (tab[i][col].getValeur() == chiffre) existeDeja = true; 
		col ++;
	}
	return !existeDeja;
}