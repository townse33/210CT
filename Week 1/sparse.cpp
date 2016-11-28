#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

bool isSparseVec(vector<vector<float>>values) { //Function to verify matrix is sparse
	int zeroCount = 0; 

	for (int row = 0; row < values.size(); row++) { //Two for loops are required to iterate over a matrix, so this is still O(n) time
		for (int col = 0; col < values[0].size(); col++) {
			if (values[row][col] == 0) {
				zeroCount++;
			}
		}
	}

	if (zeroCount < values.size() * values[0].size() / 2 + 1) { 
	//If the number of zeroes is greater than half the matrix size, this is not sparse
		return false;
	}
	else {
		return true;
	}
}

class SparseMatrix { //Class is used as signficant amounts of attributes should be hidden from user
	
	vector<float> matrix;
	vector<int> mRows;
	vector<int> mCols;
	void setShape(int width, int height) { shape[0] = width; shape[1] = height; }
public:
	int shape[2];

	bool isSparseMat() { //This function converts the matrix data so it is readable for the sparsity check
		return isSparseVec(decodeMatrix());
	}

	void encodeMatrix(vector<vector<float>> values) {
	/*
	Matrix is encoded for space efficiency, this is achived by:
	- storing nonzero values in a vector
	- storing their columns per index in another vector
	- storing the number of elements per row in a final vector
	*/

		if (!isSparseVec(values)) {
			//Exception is thrown if matrix data provided is not sparse
			throw invalid_argument("ERROR: Zero elements must outnumber nonzero elements in a Sparse Matrix.");
		}

		for (int row = 0; row < values.size(); row++) {
			mRows.push_back(0); //Row element quantity vector initialisation
			for (int col = 0; col < values[0].size(); col++) {
				if (values[row][col] != 0) {
					matrix.push_back(values[row][col]); //Nonzero element added to matrix vector
					mRows[row] += 1; //Quantity of elements for row is incremented
					mCols.push_back(col); //The column index is added to column vector
				}
			}
		}


	}

	void setValues(vector<vector<float>> values) { 

		if (values.size() < 1 || values[0].size() < 1) { 
		//Matrix shape validity must be checked to avoid less obvious errors later
			throw invalid_argument("ERROR: Matrix shape must be positive");
		}

		encodeMatrix(values); //Matrix is encoded as per the values given as a 2D array

		setShape(values.size(), values[0].size());
		//Shape of matrix is found using the assumption the matrix will have at least one column and subsequent columns must be the same size
	}

	vector<vector<float>> decodeMatrix() { //This function retrieves the matrix as a 2D vector from the compressed version
		vector<vector<float>> actualMatrix;

		for (int row = 0; row < shape[0]; row++) { 
			actualMatrix.push_back({}); //Initialise number of rows to add to 2D vector
			for (int col = 0; col < shape[1]; col++) {
				actualMatrix[row].push_back(0); //Same as above for columns
			}
		}

		int i = 0; //This integer is used to track current location in the matrix data

		for (int row = 0; row < shape[0]; row++) {
			for (int k = 0;  k < mRows[row]; k++) {
				actualMatrix[row][mCols[i]] = matrix[i]; 
				i++;
			//For the number of elements given by the row vector and using the column vector, find each element location and use this to store next matrix item in vector
			}
		}
		return actualMatrix;
	}

	void printMatrix() {
		vector<vector<float>> actualMatrix = decodeMatrix(); //Matrix must be decoded for simple matrix traversal

		for (int row = 0; row < shape[0]; row++) {
			cout << "("; //Rows are enclosed with brackets
			for (int col = 0; col < shape[1]; col++) {
				cout << actualMatrix[row][col]; 
				if (shape[1] - col > 1) {
					cout << ", "; //For listing output, comma is output if it is not the final element in the row
				}
			}
			cout << ")" << endl;
		}

		cout << endl;
	}

};

SparseMatrix sMatrixAdd(SparseMatrix A, SparseMatrix B) {
	vector<vector<float>> decA = A.decodeMatrix(); 
	vector<vector<float>> decB = B.decodeMatrix();
	vector<vector<float>> resultMatrix;

	if (A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]) {
		//Mathematically, matrix addition of different shapes is undefined
		throw invalid_argument("ERROR: Matrices of different shapes cannot be added.");
	}

	for (int row = 0; row < A.shape[0]; row++) {
		resultMatrix.push_back({});
		for (int col = 0; col < A.shape[1]; col++) {
			resultMatrix[row].push_back(decA[row][col] + decB[row][col]); //Simply, the matrix values are added elementwise
		}
	}

	if (!isSparseVec(resultMatrix)) {
	//It is possible this won't result in a sparse matrix, and this cannot be stored as one
		throw invalid_argument("ERROR: Resultant matrix is not sparse.");
	}

	SparseMatrix resultSparseMatrix;
	resultSparseMatrix.setValues(resultMatrix);

	return resultSparseMatrix;
}

SparseMatrix sMatrixSub(SparseMatrix A, SparseMatrix B) {
	//Identical to addition method, except using elementwise subtraction

	vector<vector<float>> decA = A.decodeMatrix();
	vector<vector<float>> decB = B.decodeMatrix();
	vector<vector<float>> resultMatrix;

	if (A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]) {
		throw exception("ERROR: Matrices of different shapes cannot be subtracted.");
	}

	for (int row = 0; row < A.shape[0]; row++) {
		resultMatrix.push_back({});
		for (int col = 0; col < A.shape[1]; col++) {
			resultMatrix[row].push_back(decA[row][col] - decB[row][col]);
		}
	}

	if (!isSparseVec(resultMatrix)) {
		throw invalid_argument("ERROR: Resultant matrix is not sparse.");
	}

	SparseMatrix resultSparseMatrix;
	resultSparseMatrix.setValues(resultMatrix);

	return resultSparseMatrix;
}

SparseMatrix sMatrixMul(SparseMatrix A, SparseMatrix B) {
	//Note that matrix multiplication is not commutative
	vector<vector<float>> decA = A.decodeMatrix();
	vector<vector<float>> decB = B.decodeMatrix();
	vector<vector<float>> resultMatrix;

	int agg= 0; //Integer will be used to store aggregate value of row multiplied by column
	if (A.shape[1] != B.shape[0]) {
	//If the column size of A is not equal to the row size of B, this is undefined
		throw invalid_argument("ERROR: Matrix shapes are not aligned.");
	}


	for (int row = 0; row < A.shape[0]; row++) {
		resultMatrix.push_back({});
		for (int colB = 0; colB < B.shape[1]; colB++) {
			for (int col = 0; col < A.shape[1]; col++) {
				agg += decA[row][col] * decB[col][colB]; //A third iterator is used to iterate over B's columns independantly
			}
			resultMatrix[row].push_back(agg);
			agg = 0;
		}

	}

	if (!isSparseVec(resultMatrix)) {
		throw invalid_argument("ERROR: Resultant matrix is not sparse.");
	}

	SparseMatrix resultSparseMatrix;
	resultSparseMatrix.setValues(resultMatrix);

	return resultSparseMatrix;
}

int main() {
	//Example method to show how the sparse matrix classes may be used

	try { //Try statement is used to throw error if matrices fail sparsity validation
		SparseMatrix M, M2, R;
		M.setValues({ {0,0,0,0},
					  {2.4f,-1.5f,0,0},
					  {0,0,0,4.2f},
					  {1.11f,0,0,0} });

		M2.setValues({ { 0,0,0,9 },
					 { 0,0,0,0 },
					 { 0,0,0,0 },
					 { 3.56f,0,0,1.7f } });

		R = sMatrixMul(M, M2);

		cout << "Matrices multiplied gives: " << endl;

		R.printMatrix();

		R = sMatrixAdd(M, M2);

		cout << "Matrices added gives: " << endl;

		R.printMatrix();

		R = sMatrixSub(M, M2);

		cout << "Matrices subtracted gives: " << endl;

		R.printMatrix();
	}

	catch (invalid_argument& e) {
		cerr << e.what() << endl;
	}

	return 0;
}