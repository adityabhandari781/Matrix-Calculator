#include <iostream>
#include <climits>
#include "Matrix Class.h"
using namespace std;

void appendMatrix(vector<Matrix>& v)
{
	Matrix m;
	v.push_back(m);
	cout << "Matrix " << char(64 + v.size()) << " successfully added\n";
}

void displayMats(vector<Matrix> v)
{
	cout << "\nList of matrices: \n";
	char ch = 'A';
	for (Matrix i : v) {
		cout << '\n' << ch << ":\n";
		i.print();
		ch++;
	}
}

void matrixPrint(Matrix mat)
{
	if (mat.matShape() == "cell" && mat[{0, 0}] == INT_MIN)
		cout << "Invalid operation";
	else
		cout << "The resulting matrix is:\n",
		mat.print();
}

void updateMat(vector<Matrix>& v, int index, Matrix mat)
{
	if (mat.matShape() == "cell" && mat[{0, 0}] == INT_MIN) {
		cout << "Invalid operation!\n";
		return;
	}

	char choice;
	cout << "Update matrix? (Y/N) ";
	cin >> choice;
	switch (choice) {

	case ('Y'):
		v[index] = mat;
		cout << "\nUpdated\n";
		break;

	case ('N'):
		cout << "\nMatrix retained\n";
		break;

	default:
		cout << "\nPlease enter an appropriate value!\n";
		break;
	}
}

int main()
{
	vector<Matrix> v;
	int index;

	cout << "================ MATRIX PROCESSING APP ================";

	while (1) {

		cout << "\n_______________________________________________________\n\n"
			<< "Would you like to: \n"
			<< "1. Create matrix\n"
			<< "2. Select a matrix\n"
			<< "3. Select two matrices\n"
			<< "4. Exit\n\n";

		char choice;
		cin >> choice;
		switch (choice) {

		case ('1'):
			appendMatrix(v);
			break;

		case ('2'):
			if (v.empty()) {
				cout << "\nNo matrices defined yet\n";
				break;
			}
			displayMats(v);
			cout << "\nSelect the matrix (A,B,C...): ";
			cin >> choice;
			index = choice - 'A';

			if (index < 0 || index > v.size() - 1)
				cout << "\nPlease enter an appropriate value!\n";

			else {
				Matrix mat = v[index];
				cout << "\nSelected matrix:\n";
				mat.print();
				cout << "\nWould you like to:\n"
					<< "1. See arithmetic properties\n"
					<< "2. See other properties\n"
					<< "3. Perform matrix operations\n"
					<< "4. Perform row/column operations\n"
					<< "5. Alter matrix\n"
					<< "6. Delete matrix\n\n";
				cin >> choice;

				switch (choice) {

				case ('1'):
					cout << "\nWhich arithmetic property:\n"
						<< "1. Rank\n"
						<< "2. Rref\n";
					if (mat.isSquare())
						cout << "3. Trace\n"
						<< "4. Determinant\n"
						<< "5. Transpose\n"
						<< "6. Cofactor matrix\n"
						<< "7. Adjoint matrix\n"
						<< "8. Inverse matrix\n";
					cin >> choice;
					cout << '\n';
					switch (choice) {

					case ('1'):
						cout << "Rank:\n" << mat.rank();
						break;

					case ('2'):
						cout << "Rref:\n";
						matrixPrint(mat.rref());
						break;

					case ('3'):
						cout << "Trace:\n" << mat.trace();
						break;

					case ('4'):
						cout << "Determinant:\n" << mat.determinant();
						break;

					case ('5'):
						cout << "Transpose:\n";
						matrixPrint(mat.transpose());
						break;

					case ('6'):
						cout << "Cofactor matrix:\n";
						matrixPrint(mat.cofactorMat());
						break;

					case ('7'):
						cout << "Adjoint:\n";
						matrixPrint(mat.adjoint());
						break;

					case ('8'):
						cout << "Inverse:\n";
						matrixPrint(mat.inverse());
						break;

					default:
						cout << "\nPlease enter an appropriate value!\n";
						break;
					}


					break;

				case ('2'):
					cout << "\nProperties:"
						<< "\nOrder: " << mat.order().first << "x" << mat.order().second
						<< "\nShape: " << mat.matShape()
						<< "\nIs null? " << mat.isNull();

					if (mat.isSquare())
						cout
						<< "\nType of square matrix: " << mat.sqMatType()
						<< "\nSymmetry: " << mat.symmetry()
						<< "\nType of powered matrix: " << mat.poweredMatTypes()
						<< "\nIs elementary? " << mat.isElem()
						<< "\n";
					break;

				case ('3'):
					cout << "\nWould you like to operate with:\n"
						<< "1. A scalar\n"
						<< "2. A matrix\n\n";
					cin >> choice;
					switch (choice) {

					case ('1'):
						cout << "\nWould you like to:\n"
							<< "1. Multiply\n"
							<< "2. Power\n";
						cin >> choice;
						cout << '\n';

						switch (choice) {
							int num;

						case ('1'):
							cout << "Multiply with: ";
							cin >> num;
							mat = mat * num;
							break;

						case ('2'):
							cout << "To the power of: ";
							cin >> num;
							mat = mat ^ num;
							break;

						default:
							cout << "\nPlease enter an appropriate value!\n";
							break;
						}

						if (choice == '1' || choice == '2')
							matrixPrint(mat),
							updateMat(v, index, mat);
						break;

					case ('2'):
						cout << "\nWould you like to:\n"
							<< "1. Add to another matrix\n"
							<< "2. Subtract with another matrix\n"
							<< "3. Multiply with\n"
							<< "4. Element-wise multiply\n"
							<< "5. Element-wise divide\n"
							<< "6. Assign another value\n"
							<< "7. Check equality\n";
						cin >> choice;
						cout << "Enter your matrix:\n";
						{
							Matrix mat2;
							switch (choice) {

							case ('1'):
								mat = mat + mat2;
								break;

							case ('2'):
								mat = mat - mat2;
								break;

							case ('3'):
								mat = mat * mat2;
								break;

							case ('4'):
								mat = mat % mat2;
								break;

							case ('5'):
								mat = mat / mat2;
								break;

							case ('6'):
								mat = mat2;
								cout << "\nValue successfully assigned\n";
								break;

							case ('7'):
								cout << "\nThey are " << ((mat == mat2) ? "equal" : "unequal") << '\n';
								break;

							default:
								cout << "\nPlease enter an appropriate value!\n";
								break;
							}

							if (choice >= '1' && choice <= '6')
								cout << '\n';
							updateMat(v, index, mat);
						}
						break;

					default:
						cout << "\nPlease enter an appropriate value!\n";
						break;
					}
					break;

				case ('4'):
					cout << "\nWould you like to:\n"
						<< "1. Add a row onto another\n"
						<< "2. Swap rows\n"
						<< "3. Multiply a row \n"
						<< "4. Add a column onto another\n"
						<< "5. Swap columns\n"
						<< "6. Multiply a column \n";

					cin >> choice;
					cout << '\n';
					switch (choice) {
						int r1, r2, k;

					case ('1'):
						cout << "Enter row number to add, row number to be added onto, and the factor:";
						cin >> r2 >> r1 >> k;
						mat.opRowAdd(r1, r2, k);
						break;

					case ('2'):
						cout << "Enter the row numbers to be swapped: ";
						cin >> r1 >> r2;
						mat.opSwapRows(r1, r2);
						break;

					case ('3'):
						cout << "Enter row number and factor: ";
						cin >> r1 >> k;
						mat.opRowMultiply(r1, k);
						break;

					case ('4'):
						cout << "Enter column number to add, column number to be added onto, and the factor: ";
						cin >> r2 >> r1 >> k;
						mat.opColAdd(r1, r2, k);
						break;

					case ('5'):
						cout << "Enter the row numbers to be swapped: ";
						cin >> r1 >> r2;
						mat.opSwapCols(r1, r2);
						break;

					case ('6'):
						cout << "Enter column number and factor: ";
						cin >> r1 >> k;
						mat.opRowMultiply(r1, k);
						break;

					default:
						cout << "\nPlease enter an appropriate value!\n";
						break;
					}

					if (choice >= '1' && choice <= '6')
						cout << '\n',
						updateMat(v, index, mat);
					break;

				case ('5'):
					cout << "\nWould you like to:\n"
						<< "1. Delete a row\n"
						<< "2. Delete a colums\n"
						<< "3. Insert a row\n"
						<< "4. Insert a column\n";
					cin >> choice;
					cout << '\n';
					switch (choice) {
						int k,
							pos,
							size;
						double* r;

					case ('1'):
						cout << "Enter row number to delete: ";
						cin >> k;
						mat.rowDel(k);
						break;

					case ('2'):
						cout << "Enter column number to delete: ";
						cin >> k;
						mat.colDel(k);
						break;

					case ('3'):
						size = mat.order().second;
						r = new double[size];
						cout << "Enter the " << size << " elements to insert:\n";
						for (int i = 0; i < size; i++)
							cin >> r[i];
						cout << "\nEnter the position to insert these elements: ";
						cin >> pos;
						mat.insertRow(r, pos);
						break;

					case ('4'):
						size = mat.order().first;
						r = new double[size];
						cout << "Enter the " << size << " elements to insert:\n";
						for (int i = 0; i < size; i++)
							cin >> r[i];
						cout << "Enter the position to insert these elements: ";
						cin >> pos;
						mat.insertCol(r, pos);
						break;

					default:
						cout << "Please enter an appropriate value!\n";
						break;
					}

					if (choice >= '1' && choice <= '4')
						cout << '\n',
						matrixPrint(mat),
						cout << '\n',
						updateMat(v, index, mat);
					break;

				case ('6'):
					v.erase(v.begin() + index);
					cout << "\nMatrix successfuly deleted\n";
					break;

				default:
					cout << "\nPlease enter an appropriate value!\n";
					break;
				}
			}

			break;

		case ('3'):
			if (v.empty()) {
				cout << "\nNo matrices defined yet\n";
				break;
			}
			else if (v.size() == 1)
				cout << "\nOnly one matrix exists\n";

			else {
				displayMats(v);
				cout << "\nWhich is the first matrix you would like to select (A,B,C...): ";
				cin >> choice;
				int index1 = choice - 'A';
				cout << "\nWhich is the second matrix you would like to select (A,B,C...): ";
				cin >> choice;
				int index2 = choice - 'A';

				if (index1 < 0 || index1 > v.size() - 1 || index2 < 0 || index2 > v.size() - 1) {
					cout << "\nPlease enter appropriate values\n";
					break;
				}
				Matrix mat1 = v[index1], mat2 = v[index2], ans({});
				cout << "Would you like to:\n"
					<< "1. Check commutativity of matrices\n"
					<< "2. Perform operations\n"
					<< "3. Alter matrices\n";
				cin >> choice;
				cout << '\n';
				switch (choice) {

				case ('1'):
					cout << mat1.commutativity(mat2) << '\n';
					break;

				case ('2'):
					cout << "Which operation to perform:\n"
						<< "1. Addition\n"
						<< "2. Subtraction\n"
						<< "3. Multiplication\n"
						<< "4. Element-wise multiplication\n"
						<< "5. Element-wise division\n"
						<< "6. Assign 2nd matrix's value to the 1st\n"
						<< "7. Check equality\n"
						<< "8. Swap values\n";
					cin >> choice;
					switch (choice) {

					case ('1'):
						ans = mat1 + mat2;
						break;

					case ('2'):
						ans = mat1 - mat2;
						break;

					case ('3'):
						ans = mat1 * mat2;
						break;

					case ('4'):
						ans = mat1 % mat2;
						break;

					case ('5'):
						ans = mat1 / mat2;
						break;

					case ('6'):
						mat1 = mat2;
						cout << "\nValue successfully stored\n";
						break;

					case ('7'):
						cout << "\nThey are " << ((mat1 == mat2) ? " equal\n" : " unequal\n");
						break;

					case ('8'):
						v[index1] = mat2;
						v[index2] = mat1;
						cout << "\nMatrices successfully swapped\n";
						break;

					default:
						cout << "\nPlease enter an appropriate value!\n";
						break;
					}

					if (choice >= '1' && choice <= '5') {
						cout << '\n';
						matrixPrint(ans);

						cout << "Append matrix to the list? (Y/N) ";
						cin >> choice;
						switch (choice) {

						case ('Y'):
							v.push_back(ans);
							cout << "\nMatrix successfully added\n";
							break;

						case ('N'):
							cout << "\nMatrix retained\n";
							break;

						default:
							cout << "\nPlease enter an appropriate value!\n";
							break;
						}
					}
					break;

				case ('3'):
					cout << "Would you like to:\n"
						<< "1. Join rows\n"
						<< "2. Join columns\n";
					cin >> choice;
					switch (choice) {

					case ('1'):
						ans = mat1.joinRows(mat2);
						break;

					case ('2'):
						ans = mat2.joinCols(mat2);
						break;

					default:
						cout << "\nPlease enter an appropriate value!\n";
						break;
					}

					if (choice == '1' || choice == '2') {
						cout << '\n';
						matrixPrint(ans);
						cout << "Append matrix to the list? (Y/N) ";
						cin >> choice;
						switch (choice) {

						case ('Y'):
							v.push_back(ans);
							cout << "\nMatrix successfully added\n";
							break;

						case ('N'):
							cout << "\nMatrix retained\n";
							break;

						default:
							cout << "\nPlease enter an appropriate value!\n";
							break;
						}
					}
					break;

				default:
					cout << "\nPlease enter an appropriate value!\n";
					break;
				}
			}
			break;

		case ('4'):
			cout << "\nExiting...\n";
			return 0;

		default:
			cout << "\nPlease enter an appropriate value!\n";
			break;
		}
	}
}