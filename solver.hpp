#ifndef HEADER_SOLVER
#define HEADER_SOLVER

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <string>
# include <cmath>

using namespace std;

class Case {

private:

	bool reserve_;
	int valeur_;

public:
	Case(bool reserve, int valeur) {
		reserve_ = reserve;
		valeur_ = valeur;
	}
	bool getReserve() {
		return reserve_;
	}
	int getValeur() const {
		return valeur_;
	}
	void setValeur(int valeur) {
		valeur_ = valeur;
	}
};

bool uniqueCarre(int i, int j, vector<vector<Case>>& tab, int dimCarre, int chiffre);
bool uniqueLigne(int j, vector<vector<Case>>& tab, int dimTab, int chiffre);
bool uniqueColonne(int i, vector<vector<Case>>& tab, int dimTab, int chiffre);
bool estValide(int i, int j, vector<vector<Case>>& tab, int dimCarre, int dimTab, int chiffre);
bool remplir(int i, int j, int dimCarre, vector<vector<Case>>& tab, int dimTab);
bool sudoku(vector<vector<Case>>& tab, int dimCarre, int dimTab);

#endif
