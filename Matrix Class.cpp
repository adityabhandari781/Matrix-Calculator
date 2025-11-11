#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

class Matrix
{
	vector<vector<double>> mat;
	int n;					// no of rows
	int m;					// no of columns
	const vector<vector<double>> invalid = { {INT_MIN} };	// this matrix is returned in case of any error

public:
	// constructors
	Matrix(int a = -1, int b = -1);
	Matrix(vector<vector<double>> mat1);

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
	string matShape();
	string sqMatType();
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

Matrix::Matrix(int n, int m) : n(n), m(m)
{
	if (n == -1) {
		cout << "\nEnter the number of rows and columns: ";
		while (n < 0 || m < 0) {
			cin >> n >> m;
			if (n < 0 || m < 0)
				cout << "Invalid values, try again.\n";
		}
		mat.resize(n, vector<double>(m));
	
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				cout << "Enter element (" << i << ',' << j << ") : ";
				cin >> mat[i][j];
			}
	}
	else {
		if (m == -1)
			m = n;
		mat.resize(n, vector<double>(m));
	}
}

Matrix::Matrix(vector<vector<double>> mat) : mat(mat), m(0), n(mat.size())
{
	for (vector<double> v : mat)
		m = max(m, (int)v.size());

	for (vector<double>& v : mat)
		while (v.size() < m)
			v.push_back(0);
}



void Matrix::print()
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

Matrix Matrix::generateUnit(int k)
{
	Matrix ans(k);
	for (int i = 0; i < k; i++)
		ans.mat[i][i] = 1;
	return ans;
}



pair<int, int> Matrix::order()
{
	return { n, m };
}

string Matrix::matShape()
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
	return "horizontal";
}

bool Matrix::isSquare()
{
	return n == m;
}

string Matrix::sqMatType()
{
	if (!isSquare())
		return "not a square matrix";

	bool a = 1, b = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mat[i][j] && )
				if (i > j)
					a = 0;
				else if (i < j)
					b = 0;

	if (a && b) {
		int i;
		for (i = 1; i < n; i++)
			if (mat[i][i] != mat[i - 1][i - 1])
				break;
		if (i == n)
			return (mat[0][0] == 1) ? "unit" : "scalar";
		return "diagonal";
	}
	if (a)
		return "upper triangle";
	if (b)
		return "lower triangle";
	return "unclassified";
}

bool Matrix::isNull()
{
	// checks if matrix is a null matrix
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (mat[i][j])
				return 0;
	return 1;
}

string Matrix::symmetry()
{
	if (!isSquare())
		return "not a square matrix";
	if (*this == transpose())
		return "symmetric";
	if (*this == transpose() * -1)
		return "skew-symmetric";
	return "no symmetry";
}

string Matrix::commutativity(Matrix mat2)
{
	Matrix
		prod1(mat * mat2),
		prod2(mat2 * mat);

	if (prod1 == invalid || prod2 == invalid)
		return "invalid";
	if (prod1 == prod2)
		return "commutative";
	else if (prod1 == -prod1)
		return "anti-commutative";
	return "no commutativity";
}

string Matrix::poweredMatTypes()
{
	Matrix
		mat2(mat1 ^ 2),
		unit(generateUnit(mat.size()));

	if (!isSquare())
		return "invalid";
	if (mat2 == mat)
		return "idempotent";
	if (mat2 == unit)
		return "involutary";
	if (mat2 * mat == unit)
		return "orthogonal";

	for (int i = 3; i < 10; i++) {
		mat2 = mat2 * mat;
		if (mat2 == unit)
			return "periodic";
		if (mat2 == *new Matrix(n, m))
			return "nilpotent";
	}
	return "none";
}

bool Matrix::isElem()
{
	Matrix tmpMat(*this - generateUnit(n));
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



Matrix Matrix::operator+(Matrix mat2)
{
	if (n != mat2.n || m != mat2.m)
		return invalid;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat2.mat[i][j] += mat[i][j];
	return mat2;
}

Matrix Matrix::operator-(Matrix mat2)
{
	if (n != mat2.n || m != mat2.m)
		return invalid;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat2.mat[i][j] += mat[i][j];
	return mat2;
}

Matrix Matrix::operator*(Matrix mat2)
{
	if (m != mat2.n)
		return invalid;

	Matrix ans(n, mat2.m);
	for (int i = 0; i < ans.n; i++)
		for (int j = 0; j < ans.m; j++)
			for (int k = 0; k < m; k++)
				ans.mat[i][j] += mat[i][k] * mat2.mat[k][j];
	return ans;
}

Matrix Matrix::operator*(double k)
{
	// matrix multiplication with scalar
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat[i][j] *= k;
	return mat;
}

Matrix Matrix::operator%(Matrix mat2)
{
	// element-wise multiplication
	if (n != mat2.n || m != mat2.m)
		return invalid;

	Matrix ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] * mat2.mat[i][j];
	return ans;
}

Matrix Matrix::operator/(Matrix mat2)
{
	// element-wise division
	if (n != mat2.n || m != mat2.m)
		return invalid;

	Matrix ans(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[i][j] = mat[i][j] / mat2.mat[i][j];
	return ans;
}

Matrix Matrix::operator^(int k)
{
	// matrix power
    if (!isSquare() || k < 0)
        return invalid;

    Matrix ans = generateUnit(n);  // identity matrix of same size
    Matrix base = *this;

    while (k > 0) {
        if (k & 1)
            ans = ans * base;
        base *= base;
        k >>= 1;
    }

    return ans;
}

Matrix Matrix::operator=(Matrix mat2) : mat = mat2.mat, n = mat2.n, m = mat2.m
{
	// assignment operator
	return *this;
}

bool Matrix::operator==(Matrix mat2)
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

double Matrix::operator[](pair<int, int> p)
{
	return mat[p.first][p.second];
}



int Matrix::trace()
{
	if (!isSquare())
		return INT_MIN;
	int sum{};
	for (int i = 0; i < min(n, m); i++)
		sum += mat[i][i];
	return sum;
}

Matrix Matrix::transpose()
{
	Matrix ans(m, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans.mat[j][i] = mat[i][j];
	return ans;
}

double Matrix::determinant(vector<vector<double>> a)
{
	// when called by user, argument is kept blank
	if (a.empty())
		a = mat;
	if (!isSquare())
		return INT_MIN;

	if (n == 1)
		return mat[0][0];
	double ans = 0;

	for (int i = 0; i < n; i++) {
		Matrix subMat(mat);
		subMat.rowDel(0);
		subMat.colDel(i);
		ans += ((i & 1) ? -1 : 1) * a[0][i] * subMat.determinant();
	}
	return ans;
}

Matrix Matrix::cofactorMat()
{
	vector<vector<double>> ans(n, vector<double>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			Matrix subMat(mat);
			subMat.rowDel(i);
			subMat.colDel(j);
			ans[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * subMat.determinant();
		}
	return ans;
}

Matrix Matrix::adjoint()
{
	return cofactorMat().transpose();
}

Matrix Matrix::inverse()
{
	return (!determinant()) ? invalid : adjoint() * (1.0 / determinant());
}

int Matrix::rank()
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

Matrix Matrix::rref()
{
	Matrix rrefMatrix = mat;

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



void Matrix::opRowAdd(int r1, int r2, int k = 1)
{
	if (r1 == r2 && !k)
		return;
	for (int i = 0; i < m; i++)
		mat[r1][i] += mat[r2][i] * k;
}

void Matrix::opSwapRows(int r1, int r2)
{
	swap(mat[r1], mat[r2]);
}

void Matrix::opRowMultiply(int r, double k)
{
	if (k)
		for (int i = 0; i < m; i++)
			mat[r][i] *= k;
}

void Matrix::opColAdd(int c1, int c2, int k = 1)
{
	for (int i = 0; i < n; i++)
		mat[i][c1] += mat[i][c2] * k;
}

void Matrix::opSwapCols(int c1, int c2)
{
	for (int i = 0; i < n; i++)
		swap(mat[i][c1], mat[i][c2]);
}

void Matrix::opColMultiply(int c, double k)
{
	if (k)
		for (int i = 0; i < n; i++)
			mat[i][c] *= k;
}



void Matrix::rowDel(int r)
{
	mat.erase(mat.begin() + r);
	n--;
}

void Matrix::colDel(int c)
{
	for (int i = 0; i < n; i++)
		mat[i].erase(mat[i].begin() + c);
	m--;
}

void Matrix::insertRow(double r[], int pos)
{
	n++;
	vector<double> v;
	for (int i = 0; i < m; i++)
		v.push_back(r[i]);
	mat.insert(mat.begin() + pos, v);
}

void Matrix::insertCol(double c[], int pos)
{
	m++;
	for (int i = 0; i < n; i++)
		mat[i].insert(mat[i].begin() + pos, c[i]);
}

Matrix Matrix::joinRows(Matrix mat2)
{
	if (m != mat2.m)
		return invalid;
	Matrix ans(mat);
	for (int i = 0; i < mat2.n; i++)
		ans.mat.push_back(mat2.mat[i]);
	ans.n = n + mat2.n;
	return ans;
}

Matrix Matrix::joinCols(Matrix mat2)
{
	if (n != mat2.n)
		return invalid;
	Matrix ans(mat);
	for (int i = 0; i < mat2.n; i++)
		for (int j = 0; j < mat2.m; j++)
			ans.mat[i].push_back(mat2.mat[i][j]);
	ans.m = m + mat2.m;
	return ans;
}
