#pragma once
#include <iostream>
#include <vector>
using namespace std;

#ifndef MATRIX_H
#define MATRIX_H

class MATRIX
{
	vector<vector<double>> mat;
	int n;
	int m;
	const vector<vector<double>> invalid = { {INT_MIN} };

public:
	// constructors
	MATRIX();
	MATRIX(vector<vector<double>> mat2);
	MATRIX(int a, int b = -1);

	// utility 
	void print();
	MATRIX generateUnit(int k);

	// properties
	int trace();
	MATRIX transpose();
	double determinant(vector<vector<double>> a = {});
	MATRIX cofactorMat();
	MATRIX adjoint();
	MATRIX inverse();
	int rank();
	MATRIX rref();

	// other properties
	pair<int, int> order();
	string sqMatType();
	string matShape();
	bool isNull();
	bool isSquare();
	string symmetry();
	string commutativity(MATRIX mat2);
	string poweredMatTypes();
	bool isElem();

	// operations
	MATRIX operator+(MATRIX mat2);
	MATRIX operator-(MATRIX mat2);
	MATRIX operator*(MATRIX mat2);
	MATRIX operator*(double k);
	MATRIX operator%(MATRIX mat2);
	MATRIX operator/(MATRIX mat2);
	MATRIX operator^(int k);
	MATRIX operator=(MATRIX mat2);
	bool operator==(MATRIX mat2);
	double operator[](pair<int, int> p);


	// row / col operations
	void opRowAdd(int r1, int r2, int k);
	void opSwapRows(int r1, int r2);
	void opRowMultiply(int r, double k);
	void opColAdd(int c1, int c2, int k);
	void opSwapCols(int c1, int c2);
	void opColMultiply(int c, double k);

	// matrix alter
	void rowDel(int r);
	void colDel(int c);
	void insertRow(double r[], int pos);
	void insertCol(double c[], int pos);
	MATRIX joinRows(MATRIX mat2);
	MATRIX joinCols(MATRIX mat2);
};

#endif // MATRIX_X