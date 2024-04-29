#pragma once
#include <iostream>
#include <vector>
using namespace std;

#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

class Matrix
{
	vector<vector<double>> mat;
	int n;
	int m;
	const vector<vector<double>> invalid = { {INT_MIN} };

public:
	// constructors
	Matrix();
	Matrix(vector<vector<double>> mat2);
	Matrix(int a, int b = -1);

	// utility 
	void print();
	Matrix generateUnit(int k);

	// properties
	int trace();
	Matrix transpose();
	double determinant(vector<vector<double>> a = {});
	Matrix cofactorMat();
	Matrix adjoint();
	Matrix inverse();
	int rank();
	Matrix rref();

	// other properties
	pair<int, int> order();
	string sqMatType();
	string matShape();
	bool isNull();
	bool isSquare();
	string symmetry();
	string commutativity(Matrix mat2);
	string poweredMatTypes();
	bool isElem();

	// operations
	Matrix operator+(Matrix mat2);
	Matrix operator-(Matrix mat2);
	Matrix operator*(Matrix mat2);
	Matrix operator*(double k);
	Matrix operator%(Matrix mat2);
	Matrix operator/(Matrix mat2);
	Matrix operator^(int k);
	Matrix operator=(Matrix mat2);
	bool operator==(Matrix mat2);
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
	Matrix joinRows(Matrix mat2);
	Matrix joinCols(Matrix mat2);
};

#endif // Matrix_X