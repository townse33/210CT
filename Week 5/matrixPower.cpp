#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
	vector<vector<float>> data; //Matrices will be defined as 2D vectors of floats for flexibility

	void print() {
		//Matrix print method

		for (int row = 0; row < this->data.size(); row++) { //Using the 'this' pointer will access the current matrix instance
			cout << "("; //Brackets printed at the start and end of each row
			for (int col = 0; col < this->data[0].size(); col++) {
				cout << this->data[row][col]; 
				if (col < this->data[row].size()) {
					cout << ", "; //If element is not the final element in the row, comma is printed to separate values
				}
			}
			cout << ")" << endl; //New line is printed for each row
		}
	}
};

Matrix mul(Matrix *A, Matrix *B) { 
	//Matrix multiplication function
	//Function uses pointers to matrices as parameters, to be in line with question spec, all element accesses are via pointers
		Matrix result;

		for (int row = 0; row < B->data.size(); row++) {
			//As per question 1, three loops are required for multiplication: row, column, and B's columns

			result.data.push_back({}); //New row in resultant matrix initialised

			for (int col = 0; col < A->data[0].size();col++) {
				float accum = 0; //Variable to accumulate multiplications

				for (int col2 = 0; col2 < B->data[0].size(); col2++) {
					//As usual, element is multiplied by iterating over A's row and B's columns
					accum += A->data[row][col2] * B->data[col2][col];
				}

				result.data[row].push_back(accum);
			}
		}

		return result;
}

Matrix pow(Matrix *M, int k) {
	//Class to bring matrix M to the kth power and return it as a new matrix by repeated multiplication
	Matrix result;
	for (int i = 0; i < k; i++) {
		result = mul(M, M);
	}
	return result;
}

int main() {
	//Example method
	Matrix M, result;
	M.data = { {1,2,3},
			   {4,5,6},
			   {7,8,9} };

	result = pow(&M, 3); //Reference of M is used to pass as a pointer
	result.print();

	system("pause");
	return 0;
}