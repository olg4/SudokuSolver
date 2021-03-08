# include "solver.hpp"

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

// Supposé qu'une grille ait les dimensions 9x9
int main(int argc, char** argv) {

	if (argc > 2) cout << "try: ./sudokuSolver <file containing sudoku>" << endl;	
	else {
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
		int number;
		vector<vector<Case>> tab;
		vector<Case> row;
		string line;
		int counterLine = 0;
		while (getline(theFile, line)) {
			if (counterLine == 0) cout << line << " ... "<< endl;
			else {
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