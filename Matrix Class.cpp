#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

class MATRIX
{
	vector<vector<double>> mat;
	int n;					// no of rows
	int m;					// no of columns
	const vector<vector<double>> invalid = { {INT_MIN} };	// this matrix is returned in case of any error

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
	string matShape();
	string sqMatType();
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

MATRIX::MATRIX()
{
	// input from user in the console

	cout << "\nEnter the number of rows and columns: ";
	cin >> n >> m;
	mat.resize(n, vector<double>(m));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cout << "Enter element (" << i << ',' << j << ") : ";
			cin >> mat[i][j];
		}
}

MATRIX::MATRIX(vector<vector<double>> mat2)
{
	// matrix elements are taken from parameter
	mat = mat2;
	m = 0, n = mat.size();

	for (vector<double> i : mat)
		m = max(m, (int)i.size());

	for (vector<double>& i : mat)
		while (i.size() < m)
			i.push_back(0);
}

MATRIX::MATRIX(int a, int b)
{
	// a and b are row and column, respectively
	if (b == -1)
		b = a;
	// in case only a is provided, b automatically is initialized to a, producing a square matrix

	n = a;
	m = b;
	mat.resize(n, vector<double>(m));
}



void MATRIX::print()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (trunc(mat[i][j]) != mat[i][j])
				cout << fixed << setprecision(2) << mat[i][j] << '\t';
			else
				cout << static_cast<int>(mat[i][j]) << '\t';
		cout << '\n';
	}
	cout << '\n';
}

MATRIX MATRIX::generateUnit(int k)
{
	MATRIX ans(k, k);
	for (int i = 0; i < k; i++)
		ans.mat[i][i] = 1;
	return ans;
}



pair<int, int> MATRIX::order()
{
	return { n, m };
}

string MATRIX::matShape()
{
	if (n == 1 && m == 1)
		return "cell";
	if (n == m)
		return "square";
	if (n == 1)
		return "row";
	if (m == 1)
		return "column";
	if (n > m)
		return "vertical";
	else
		return "horizontal";
}

bool MATRIX::isSquare()
{
	return n == m;
}

string MATRIX::sqMatType()
{
	if (!isSquare())
		return "not a square matrix";

	bool a = 1, b = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (mat[i][j] != 0 && i > j)
				a = 0;
			if (mat[i][j] != 0 && i < j)
				b = 0;
		}

	bool hasSameElts = 1;
	if (a && b) {
		for (int i = 1; i < n; i++)
			if (mat[i][i] != mat[i - 1][i - 1])
				hasSameElts = 0;
		if (hasSameElts)
			return (mat[0][0] == 1) ? "unit" : "scalar";
		return "diagonal";
	}
	if (a)
		return "upper triangle";
	if (b)
		return "lower triangle";
	return "unclassified";
}

bool MATRIX::isNull()
{
	// checks if matrix is a null matrix
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (mat[i][j])
				return 0;
	return 1;
}

string MATRIX::symmetry()
{
	if (!isSquare())
		return "not a square matrix";
	if (*this == transpose())
		return "symmetric";
	if (*this == transpose() * -1)
		return "skew-symmetric";
	return "no symmetry";
}

string MATRIX::commutativity(MATRIX mat2)
{
	MATRIX
		mat1(*this),
		prod1(mat1 * mat2),
		prod2(mat2 * mat1),
		negProd1(mat1 * mat2 * -1);

	if (prod1 == invalid || prod2 == invalid)
		return "invalid";
	if (prod1 == prod2)
		return "commutative";
	else if (prod1 == negProd1)
		return "anti-commutative";
	return "no commutativity";
}

string MATRIX::poweredMatTypes()
{
	MATRIX
		mat1(*this),
		mat2(mat1 ^ 2),
		unit(generateUnit(mat.size()));

	if (!isSquare())
		return "invalid";
	if (mat2 == mat1)
		return "idempotent";
	if (mat2 == unit)
		return "involutary";
	if (mat2 * mat1 == unit)
		return "orthogonal";

	for (int i = 3; i < 10; i++) {
		mat2 = mat2 * mat1;
		if (mat2 == unit)
			return "periodic";
		if (mat2 == *new MATRIX(mat2.n, mat2.m));
		return "nilpotent";
	}
	return "none";
}

bool MATRIX::isElem()
{
	MATRIX tmpMat(*this - generateUnit(n));
	int cnt{};
	int cnt2{};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (cnt > 1)
				return 0;
			if (tmpMat.mat[i][j])
				cnt++;
			cnt2 += tmpMat.mat[i][j];
		}
	if (cnt2 && cnt != 1)
		return 0;
	return 1;
}



MATRIX MATRIX::operator+(MATRIX mat2)
{
	if (n != mat2.n || m != mat2.m)
		return invalid;

	MATRIX ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] + mat2.mat[i][j];
	return ans;
}

MATRIX MATRIX::operator-(MATRIX mat2)
{
	if (n != mat2.n || m != mat2.m)
		return invalid;

	MATRIX ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] - mat2.mat[i][j];
	return ans;
}

MATRIX MATRIX::operator*(MATRIX mat2)
{
	if (m != mat2.n)
		return invalid;

	MATRIX ans(n, mat2.m);
	for (size_t i = 0; i < ans.n; i++)
		for (size_t j = 0; j < ans.m; j++)
			for (size_t k = 0; k < m; k++)
				ans.mat[i][j] += mat[i][k] * mat2.mat[k][j];
	return ans;
}

MATRIX MATRIX::operator*(double k)
{
	// matrix multiplication with scalar
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat[i][j] *= k;
	return mat;
}

MATRIX MATRIX::operator%(MATRIX mat2)
{
	// element-wise multiplication
	if (n != mat2.n || m != mat2.m)
		return invalid;
	MATRIX ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] * mat2.mat[i][j];
	return ans;
}

MATRIX MATRIX::operator/(MATRIX mat2)
{
	// element-wise division
	if (n != mat2.n || m != mat2.m)
		return invalid;
	MATRIX ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] / mat2.mat[i][j];
	return ans;
}

MATRIX MATRIX::operator^(int k)
{
	// matrix power
	if (!isSquare())
		return invalid;
	for (int i = 1; i < k; i++)
		*this = *this * *this;
	return *this;
}

MATRIX MATRIX::operator=(MATRIX mat2)
{
	// assignment operator
	mat = mat2.mat;
	n = mat2.n;
	m = mat2.m;
	return *this;
}

bool MATRIX::operator==(MATRIX mat2)
{
	// matrix equality
	if (n != mat2.n || m != mat2.m)
		return 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (mat[i][j] != mat2.mat[i][j])
				return 0;
	return 1;
}

double MATRIX::operator[](pair<int, int> p)
{
	return mat[p.first][p.second];
}



int MATRIX::trace()
{
	if (!isSquare())
		return INT_MIN;
	int sum{};
	for (int i = 0; i < min(n, m); i++)
		sum += mat[i][i];
	return sum;
}

MATRIX MATRIX::transpose()
{
	MATRIX ans(m, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[j][i] = mat[i][j];
	return ans;
}

double MATRIX::determinant(vector<vector<double>> a)
{
	// when called by user, argument is kept blank
	if (a.empty())
		a = mat;
	if (!isSquare())
		return INT_MIN;

	if (n == 1)
		return mat[0][0];
	double det = 0;

	for (int i = 0; i < n; i++) {
		MATRIX subMat(mat);
		subMat.rowDel(0);
		subMat.colDel(i);
		det += ((i % 2 == 0) ? 1 : -1) * a[0][i] * subMat.determinant();
	}
	return det;
}

MATRIX MATRIX::cofactorMat()
{
	vector<vector<double>> ans(n, vector<double>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			MATRIX subMat(mat);
			subMat.rowDel(i);
			subMat.colDel(j);
			ans[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * subMat.determinant();
		}
	return ans;
}

MATRIX MATRIX::adjoint()
{
	return cofactorMat().transpose();
}

MATRIX MATRIX::inverse()
{
	return (!determinant()) ? invalid : adjoint() * (1.0 / determinant());
}

int MATRIX::rank()
{
	int rank = m;

	for (int row = 0; row < n; row++) {
		int leading = row;
		while (leading < m && !mat[row][leading])
			leading++;

		if (leading < m) {
			if (leading != row)
				opSwapRows(row, leading);

			for (int i = 0; i < n; i++)
				if (i != row)
					opRowAdd(i, row, -mat[i][leading] / mat[row][leading]);
		}
		else
			rank--;
	}
	return rank;
}

MATRIX MATRIX::rref()
{
	MATRIX rrefMatrix = mat;

	int lead = 0;
	for (int r = 0; r < n; r++, lead++) {
		if (m <= lead)
			break;

		int i = r;
		while (!abs(rrefMatrix.mat[i][lead])) {
			i++;
			if (i == n) {
				i = r;
				lead++;
				if (m == lead)
					return rrefMatrix;
			}
		}
		opSwapRows(i, r);

		for (int j = 0; j < m; j++)
			rrefMatrix.mat[r][j] /= rrefMatrix.mat[r][lead];

		for (i = 0; i < n; i++)
			if (i != r)
				opRowAdd(i, r, -rrefMatrix.mat[i][lead]);
	}
	return rrefMatrix;
}



void MATRIX::opRowAdd(int r1, int r2, int k = 1)
{
	if (r1 == r2 && !k)
		return;
	for (int i = 0; i < m; i++)
		mat[r1][i] += mat[r2][i] * k;
}

void MATRIX::opSwapRows(int r1, int r2)
{
	swap(mat[r1], mat[r2]);
}

void MATRIX::opRowMultiply(int r, double k)
{
	if (k)
		for (int i = 0; i < m; i++)
			mat[r][i] *= k;
}

void MATRIX::opColAdd(int c1, int c2, int k = 1)
{
	for (int i = 0; i < n; i++)
		mat[i][c1] += mat[i][c2] * k;
}

void MATRIX::opSwapCols(int c1, int c2)
{
	for (int i = 0; i < n; i++)
		swap(mat[i][c1], mat[i][c2]);
}

void MATRIX::opColMultiply(int c, double k)
{
	if (k)
		for (int i = 0; i < n; i++)
			mat[i][c] *= k;
}



void MATRIX::rowDel(int r)
{
	mat.erase(mat.begin() + r);
	n--;
}

void MATRIX::colDel(int c)
{
	for (int i = 0; i < n; i++)
		mat[i].erase(mat[i].begin() + c);
	m--;
}

void MATRIX::insertRow(double r[], int pos)
{
	n++;
	vector<double> v;
	for (int i = 0; i < m; i++)
		v.push_back(r[i]);
	mat.insert(mat.begin() + pos, v);
}

void MATRIX::insertCol(double c[], int pos)
{
	m++;
	for (int i = 0; i < n; i++)
		mat[i].insert(mat[i].begin() + pos, c[i]);
}

MATRIX MATRIX::joinRows(MATRIX mat2)
{
	if (m != mat2.m)
		return invalid;
	MATRIX ans(mat);
	for (int i = 0; i < mat2.n; i++)
		ans.mat.push_back(mat2.mat[i]);
	ans.n = n + mat2.n;
	return ans;
}

MATRIX MATRIX::joinCols(MATRIX mat2)
{
	if (n != mat2.n)
		return invalid;
	MATRIX ans(mat);
	for (int i = 0; i < mat2.n; i++)
		for (int j = 0; j < mat2.m; j++)
			ans.mat[i].push_back(mat2.mat[i][j]);
	ans.m = m + mat2.m;
	return ans;
}