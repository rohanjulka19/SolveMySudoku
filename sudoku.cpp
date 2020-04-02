#include<iostream>
#include<cmath>
#include<stack>

using namespace std;

class Sudoku {

	int mat[9][9] ;
	int unsolved[81][2] ;
	bool isSolved ;
	
	public :

	Sudoku():mat{}, unsolved{}, isSolved(false) {
	}

	void solve() {
		setUnsolved();
		solveUtil(unsolved[0][0],unsolved[0][1] , 0) ;
	}

	void solveUtil(int i, int j, int index) {
		int  n ;
		stack<int> s ;
		
		if(unsolved[index][0] == 0 && unsolved[index][1] == 0 && index != 0) {
			isSolved = true ;
			cout << "TRUE" ;
			return ;
		}

		if(isSolved == true) {
			cout << "TRUE" ;
			return ;
		} 
	
		getRange(i, j, s) ;
		n = s.size() ;
		cout << n << endl ; 
		while(s.size() != 0) { 
			cout <<"INDEX" << index ;
			mat[i][j] = s.top() ;
			cout << "Value " << s.top()  << endl ;
			cout << *this << endl ;

			s.pop();
			cout << "CALL" << endl;
			solveUtil(unsolved[index + 1][0], unsolved[index + 1][1], index + 1) ;
			cout << "NEXT" << endl ;
			if(isSolved != true)
				mat[i][j] = 0 ;
			else
				break ;
		}
		cout << "returning solved" << isSolved << endl ;
		return ;
	}
	
	int getRange(int i, int j, stack<int>& s) {
		int temp[9] = {} ;
		

		for(int k = 0 ; k < 9 ; k++) {
			if(mat[i][k] != 0) {
				int index = mat[i][k] - 1 ;
				temp[index] = -1 ;
			}
			if(mat[k][j] != 0) {
				int index = mat[k][j] - 1 ;
				temp[index] = -1 ;
			}
			int quad = getQuadrant(i, j) ;

			int quad_i = (quad / 3) * 3 ;
			int quad_j = (quad % 3) * 3 ;

			for(int a = quad_i ; a <= quad_i + 2  ; a++) {
				for(int b = quad_j ; b <= quad_j + 2 ; b++) {
					if(mat[a][b] != 0) {
						int index = mat[a][b] - 1 ;
						temp[index] = -1 ;
					}
				}
			}
		}

		for(int k = 0 ; k<9 ; k++) {
			if(temp[k] != -1)
				s.push(k + 1) ;
		}
	}

	int getQuadrant(int i, int j) {

		int quad = floor(i/3) * 3 + floor(j/3) ;

		return quad ;
	}

	int setUnsolved() {
		int index = 0 ;
		for(int i = 0 ; i<9 ; i++) {
			for(int j = 0 ; j<9 ; j++) {
				if(mat[i][j] == 0) {
					unsolved[index][0] = i ;
					unsolved[index][1] = j ;
					index++ ;
				}
			}
		}
		for(int i = 0 ; i<81 ; i++) {
			cout << unsolved[i][0] << unsolved[i][1] << " " ;
		}
	}
	friend istream& operator>>(istream& in, Sudoku& s) ;
	friend ostream& operator<<(ostream& out, Sudoku s) ;

};

istream& operator>>(istream& in, Sudoku& s) {
	for(int i = 0 ; i< 9 ; i++ ) {
		for(int j = 0 ; j<9 ; j++) {
			in >> s.mat[i][j] ;
		}

	}

	return in;
}

ostream& operator<<(ostream& out, Sudoku s) {
	for(int i = 0 ; i<9; i++) {
		if(i % 3 == 0 )
			out << endl ; 
		for(int j = 0 ; j<9 ; j++) {
			if(j % 3 == 0 )
				out << " " ; 
			out << s.mat[i][j] << " ";
		}
		out << '\n' ;
	}
}
int main() {
	Sudoku s ;
	cin >> s ;

	s.solve() ;
	cout << "DONE" ;
	cout << s ;

}

