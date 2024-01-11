#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

char candy = 219;

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Random_Color_generator() {
	int Colors[6] = { 1,2,3,4,5,6 };
	int random;
	srand(time(NULL) + rand());
	random = Colors[rand() % 6];
	return random;
}

void update(int arr[5][5], int score) {
	system("CLS");
	int number = 1;
	char wall = 177;
	Color(7);
	for (int i = 0; i < 73; i++) {
		cout << wall;
	}
	cout << endl << wall << "									" << wall << endl;
	for (int i = 0; i < 5; i++) {
		cout << wall << "  ";
		for (int j = 0; j < 5; j++) {
			Color(arr[i][j]);
			if (j != 4) {
				cout << candy << candy << number++ << "		";
			}
			if (j == 4) {
				cout << candy << candy << number++ << "	";
				Color(7);
				cout << wall;
			}
			Color(7);
			if (i == 1 && j == 4) {
				cout << "	-------------";
			}
			if (i == 2 && j == 4) {
				Color(7);
				cout << "	| SCORE : " << score << " |";
			}
			if (i == 3 && j == 4) {
				cout << "	-------------";
			}
		}
		Color(7);
		cout << endl << wall << "									" << wall << endl << wall << "									" << wall << endl;
	}
	for (int i = 0; i < 73; i++) {
		cout << wall;
	}
	cout << endl << endl;
}

int check(int arr[5][5], int score) {
	int temp, counter = 0;
	//Generating new candies if 3 Colors are same
	//FOR HORIZONTAL
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
				temp = Random_Color_generator();
				arr[i][j] = temp;
				temp = Random_Color_generator();
				arr[i][j + 1] = temp;
				temp = Random_Color_generator();
				arr[i][j + 2] = temp;
				counter++;
			}
			//FOR VERTICAL
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) {
				temp = Random_Color_generator();
				arr[i][j] = temp;
				temp = Random_Color_generator();
				arr[i + 1][j] = temp;
				temp = Random_Color_generator();
				arr[i + 2][j] = temp;
				counter++;
			}
		}
	}
	update(arr, score);
	Color(7);
	return counter;
}

int numbertoindexrow(int num) {
	return (num / 5);
}
int numbertoindexcol(int num) {
	return ((num - (numbertoindexrow(num) * 5)) - 1);
}

int Title() {
	int option;
	cout << "			---------------------------------------------\n";
	cout << "			|		"; Color(4); cout << candy; Color(7); cout << "CANDY CRUSH"; Color(4); cout << candy; Color(7); cout << "		    | \n";
	cout << "			---------------------------------------------\n\n\n";
	cout << "1.  Start Game\n";
	cout << "2.  Instructions\n";
	cout << "3.  Exit\n\n";
	cin >> option;
	system("CLS");
	return option;
}

void instructions() {
	cout << "			---------------------------------------------\n";
	cout << "			|		"; Color(4); cout << candy; Color(7); cout << "INSTRUCTIONS"; Color(4); cout << candy; Color(7); cout << "		    | \n";
	cout << "			---------------------------------------------\n\n\n";
	cout << "1. You have to combine 3 same colored jellies to destroy them.\n";
	cout << "2. Numbers are allocated to each cell.\n";
	cout << "3. Enter 2 numbers to swap them.\n";
	cout << "4. Score 100 to Win!\n";
	cout << "5. Enjoy!\n";
	system("pause");
	system("CLS");
}

int main() {
	int option;
	do {
		option = Title();
		if (option == 1) {
			//INITIALZING CANDIES
			int temp, number = 1, score = 0;
			int arr[5][5];
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					temp = Random_Color_generator();
					arr[i][j] = temp;
					Color(temp);
					cout << candy << candy << number++ << "		";
				}
				cout << endl << endl;
			}
			check(arr, score);
			//Taking User Input for swapping
			int num1, num2;
			do {
				cout << "Enter Numbers of cells to swap: ";
				cin >> num1 >> num2;
				if (num1 >= 1 && num1 <= 25 && num2 >= 1 && num2 <= 25 && num1 != num2 && (((num1 - 5) == num2) || ((num1 + 1) == num2) || ((num1 + 5) == num2) || ((num1 - 1) == num2))) {
					swap(arr[numbertoindexrow(num1)][numbertoindexcol(num1)], arr[numbertoindexrow(num2)][numbertoindexcol(num2)]);
					if (check(arr, score) == 0) {
						swap(arr[numbertoindexrow(num1)][numbertoindexcol(num1)], arr[numbertoindexrow(num2)][numbertoindexcol(num2)]);
						cout << "Incorrect Combination!\n";
					}
					else {
						score = score + 10;
						Beep(500, 300);
						check(arr, score);
					}

				}
				else {
					cout << "The Numbers you entered are incorrect!\n";
					cout << "1) Both Numbers should not be equal.\n";
					cout << "2) Both Numbers should be between 1 - 25.\n";
					cout << "3) Both Numbers should be next to each other.\n\n";
					cout << "Try Again! ";
				}
			} while (score < 100);
			if (score >= 100) {
				cout << "	C O N G R A T U L A T I O N S! You Won!\n\n";
			}
			return 0;
		}
		if (option == 2) {
			instructions();
		}
		if (option == 3) {
			return 0;
		}
	} while (option == 2);
}