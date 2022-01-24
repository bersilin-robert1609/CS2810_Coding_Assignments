#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define endl "\n"

class Matrix{
    public:
        Matrix();
        Matrix(int rows, int columns);
        Matrix(int rows, int columns, int** matrix);
        ~Matrix();
        void setValue(int row, int col, int val) { mat[row-1][col-1] = val; }
        int getValue(int row, int col) { return mat[row-1][col-1]; }
        int getNoRows() { return rows; }
        int getNoColumns() { return columns; }

        void printSpiral();
        int trace();
        bool checkTriangular();
        bool isSpecialMatrix();

    private:
        int rows = 0;
        int columns = 0;
        int **mat;
};

Matrix::Matrix(){
    this->rows = 0;
    this->columns = 0;
}

Matrix::Matrix(int rows, int columns){
    this->rows = rows;
    this->columns = columns;

    mat = new int*[rows]; 

    for(int i=0; i<rows; i++){
        mat[i] = new int[columns];
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(int rows, int columns, int** matrix){
    this->rows = rows;
    this->columns = columns;

    mat = new int*[rows]; 

    for(int i=0; i<rows; i++){
        mat[i] = new int[columns];
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            mat[i][j] = matrix[i][j];
        }
    }
}

void Matrix::printSpiral(){

    int i, k=0, l=0, m=rows-1, n=columns-1;

    while(k<=m && l<=n){

        for(i = l; i <= n; i++){
            cout << mat[k][i] << " ";
        }
        k++;

        for(i = k; i <= m; i++){
            cout << mat[i][n] << " ";
        }
        n--;

        if(k<=m){
            for(i = n; i >= l; i--){
                cout << mat[m][i] << " ";
            }
            m--;
        }

        if(l<=n){
            for(i = m; i >= k; i--){
                cout << mat[i][l] << " ";
            }
            l++;
        }
    }

    cout<<endl;
}

int Matrix::trace(){
    if( this->rows != this->columns ) return -1;

    int traceM = 0;
    for(int i=0; i<rows; i++){
        traceM += mat[i][i];
    }

    return traceM;
}

bool Matrix::checkTriangular(){
    if( this->rows != this->columns ) return false;

    int lowerZeroes = 0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<i; j++){
            if(mat[i][j]==0) lowerZeroes++;
            else break;
        }
    }
    if(lowerZeroes == ((rows)*(rows-1))/2) return true;

    int upperZeroes = 0;
    for(int i=0; i<rows; i++){
        for(int j=i+1; j<columns; j++){
            if(mat[i][j]==0) upperZeroes++;
            else break;
        }
    }
    if(upperZeroes == ((rows)*(rows-1))/2) return true;

    return false;
}

bool Matrix::isSpecialMatrix(){

    int sumRows = 0;
    for(int i=0; i<columns; i++) sumRows+= mat[0][i];

    for(int i=1; i<rows; i++){
        int tempSum = 0;
        for(int j=0; j<columns; j++){
            tempSum+=mat[i][j];
        }
        if(tempSum!=sumRows) return false;
    }

    for(int i=0; i<columns; i++){
        int tempSum = 0;
        for(int j=0; j<rows; j++){
            tempSum+=mat[j][i];
        }
        if(tempSum!=sumRows) return false;
    }

    return true;
}

Matrix::~Matrix(){

    for(int i=0; i<rows; i++){
        delete[] *(mat+i);
    }

    delete[] mat;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int rows, columns;
    cin>>rows>>columns;

    int **matrix = new int*[rows]; 

    for(int i=0; i<rows; i++){
        matrix[i] = new int[columns];
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            cin>>matrix[i][j];
        }
    }

    Matrix testMatrix = Matrix(rows, columns, matrix);

    int Q;
    cin>>Q;

    while(Q--){
        int opcode;
        cin>>opcode;

        switch(opcode){
            case 1:{
                testMatrix.printSpiral();
                break;
            }
            case 2:{
                int trace = testMatrix.trace();
                cout<<trace<<endl;
                break;
            }
            case 3:{
                cout<<boolalpha<<testMatrix.checkTriangular()<<endl;
                break;
            }
            case 4:{
                cout<<boolalpha<<testMatrix.isSpecialMatrix()<<endl;
                break;
            }
        }
    }

    for(int i=0; i<rows; i++) free(*(matrix+i));
    free(matrix);

    return 0;
}