#include <iostream>
#include <chrono>
#include <conio.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string leftUpCorner = "\u2554";
const string doubleHorizontal = "\u2550";
const string sideUp = "\u2564";
const string rightUpCorner = "\u2557";
const string doubleVertical = "\u2551";
const string leftDoubleSide = "\u255F";
const string normalHorizontal = "\u2500";
const string normalVertical = "\u2502";
const string plusChar = "\u253C";
const string rightDoubleSide = "\u2562";
const string rightDownCorner = "\u255D";
const string leftDownCorner = "\u255A";
const string sideDown = "\u2567";
const string inputSpaces_4 = "								  			 	 ";
const string inputSpaces_6 = "								  			     ";
const string inputSpaces_8 = "								  			 ";
const string inputSpaces_10 = "								  		     ";
const string inputSpaces_12 = "								  		  ";

struct Players
{
	string playerName;
	char symbol;
	int numberOfNuts = 0;
};

Players player1;
Players player2;

void newGame(char table_element[][12], int &currentRow, int &currentCol);
void print_table(char table[][12], int dimension_length, int current_row, int current_col, bool whose_turn);
string returnTotalSpaces(int dimension);
void cheking_is_allowed_and_change_pieces(char table[][12], int currentRow, int currentCol, bool &whose_turn, int table_dimension);
bool checking_x_is_allowed(char table[][12], int table_dimension);
bool checking_o_is_allowed(char table[][12], int table_dimension);
void printOthello();
void OXCounter(Players &player1, Players &player2, char table_element[][12]);
void guidlineFunction();
void saveGame(char table[][12], Players player1, Players player2, int table_dimension, bool whose_turn);
void loadGame(char table_element[][12], int currentRow, int currentCol);
void menu(char table_element[][12], int &currentRow, int &currentCol);
void menuTitle();
void saveRanks(string winner);
void loadRank();
void game(char table_element[][12], int currentRow, int currentCol, int tableDimension, bool turn);

int main()
{
	player1.symbol = 'x';
	player2.symbol = 'o';
	char table_element[12][12];
	int current_row = 1;
	int current_column = 1;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << " 				            							     " << "Loading...";
	_sleep(2300);
	system("CLS");
	menu(table_element, current_row, current_column);
	cout << "Press any key to exit ";
	getch();
	return 0;
}


void menuTitle()
{
	printOthello();           //print OTHELLO title
	_sleep(1000);
	cout << "Please Select Something..." << endl << endl;
	_sleep(700);
	cout << "1) New Game" << endl << endl;
	_sleep(400);
	cout << "2) Load Game" << endl << endl;
	_sleep(400); 
	cout << "3) Ranking" << endl << endl;
	_sleep(400); 
	cout << "4) Exit" << endl << endl;
}


void menu(char table_element[][12], int &currentRow, int &currentCol)
{
	while (true)
	{
		menuTitle();
		char charMenu;
		charMenu = getch();
		switch (charMenu)
		{
			case '1' :
			{
				system("ClS");
				printOthello();
				cout << endl << "Note! The First Player's Symbol Is X " << endl << endl;
				cout << "Please Enter The First Player's Name : ";
				getline(cin, player1.playerName);
				cout << "Please Enter The Second Player's Name : ";
				getline(cin, player2.playerName);
				newGame(table_element, currentRow, currentCol);
				break;
			}
			case '2' :
			{
				system("CLS");
				printOthello();
				loadGame(table_element, currentRow, currentCol);
				break;
			}
			case '3' : 
			{
				system("CLS");
				printOthello();
				cout << "Names" << "\t\t\t\t\t\t\t\t\t" << ' ' << "Number Of Games" << "\t\t\t" << ' ' << "Number Of Wins" << endl;
				cout << "---------------------------------------------------------------------------------------------------------------------------------------" << endl;
				loadRank();
				cout << endl << "Press anykey to exit ..." << endl;
				getch();
				system("CLS");
				break;
			}
			case '4' :
			{
				system("ClS");
				printOthello();
				cout << "You Have Chosen \"Exit\", See You :)" << endl << endl;
				return;
			}
			default :
			{
				cout << "Invalid Entrance! Please Just Select A Number!" << endl << endl;
				_sleep(1200);
				system("CLS");
			}
		}
	}
}


void guidlineFunction()
{
	cout << endl << endl << endl << endl << endl << endl;
	cout << "		 					          " << "__________________________________________________________________________________";
	cout << endl;
	cout << "								  ";
	cout << "W : Up" << "    " << "A : Left" << "    " << "S : Down" << "    " << "D : Right" << "    " << "Exit : P" << "    ";
	cout << "Put : Enter" << "    " << "Save : M";
}


void OXCounter(Players &player1, Players &player2, char table_element[][12])
{
	int answerP1 = 0;
	int answerP2 = 0;
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			if (table_element[i][j] == 'x')
			{
				answerP1++;
			}
			else if (table_element[i][j] == 'o')
			{
				answerP2++;
			}
		}
	}
	player1.numberOfNuts = answerP1;
	player2.numberOfNuts = answerP2;
}


void newGame(char table_element[][12], int &currentRow, int &currentCol)
{
	int tableDimension;
	bool turn = true;
	currentRow = 1;
	currentCol = 1;
	system("CLS");
	printOthello();
	cout << "Please Enter The Dimension : ";
	while (true)
	{
		cin >> tableDimension;
		if (tableDimension >= 4 && tableDimension <= 12 && tableDimension % 2 == 0)
		{
			cin.ignore(1, '\n');
			break;
		}
		else
		{
			cout << "Wrong Input!! Please Enter An Even Number Between 4 to 12!" << endl;
		}
		cin.clear();
		cin.ignore(1000, '\n');
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			table_element[i][j] = ' ';
		}
	}
	table_element[tableDimension - 1 - tableDimension/2][tableDimension - 1 - tableDimension/2] = 'o';
	table_element[tableDimension - tableDimension/2][tableDimension - 1 - tableDimension/2] = 'x';
	table_element[tableDimension - 1 - tableDimension/2][tableDimension - tableDimension/2] = 'x';
	table_element[tableDimension - tableDimension/2][tableDimension - tableDimension/2] = 'o';
	game(table_element, currentRow, currentCol, tableDimension, turn);
}


void print_table(char table[][12], int dimension_length, int current_row, int current_col, bool whose_turn)
{
	printOthello();
	cout << endl;
	// define total spaces before print table
	string totalInputSpaces = returnTotalSpaces(dimension_length);
	
	//print top of the table
	cout << totalInputSpaces << leftUpCorner;
	for (int i = 1; i < dimension_length; i++)
	{
		cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << sideUp;
	}
	cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << rightUpCorner;
	cout << endl;
		
	//print middle of the table
	int t = 1;               							 // t is array index
	for (int j = 1; j <= 2 * dimension_length - 1; ++j)
	{
		if (j % 2 == 0)
		{
			cout << totalInputSpaces << leftDoubleSide;
		}
		else 
		{
			cout << totalInputSpaces << doubleVertical;
		}
		if (j % 2 == 0)
		{
			if (j != 2 * current_row - 1 && j != 2 * current_row && j != 2 * current_row - 2)
			{
				for (int i = 1; i < dimension_length; ++i)
				{
					cout << normalHorizontal << normalHorizontal << normalHorizontal << plusChar;
				}
				cout << normalHorizontal << normalHorizontal << normalHorizontal << rightDoubleSide;
			}
			else
			{
				for (int i = 1; i < dimension_length; ++i)
				{
					if (i != current_col)
					{
						cout << normalHorizontal << normalHorizontal << normalHorizontal << plusChar;
					}
					else 
					{
						cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << plusChar;
					}
				}
				if (current_col != dimension_length)
				{
					cout << normalHorizontal << normalHorizontal << normalHorizontal << rightDoubleSide;
				}
				else 
				{
					cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << rightDoubleSide;
				}
			}		
		}
		else 
		{
			for (int i = 1; i <= dimension_length; ++i)
			{
				if (i != dimension_length)
				{
					if (i != current_col && i != current_col - 1 || j != 2 * current_row - 1)
					{
						cout << ' ' << table[t - 1][i - 1] << ' ' << normalVertical;
					}
					else if (j == 2 * current_row - 1)
					{
						cout << ' ' << table[t - 1][i - 1] << ' ' << doubleVertical;
					}
				}
				else
					cout << ' ' << table[t - 1][i - 1] << ' ' << doubleVertical;
			}
			t++;
		}
		cout << endl;
	}
		
	//print bottom of the table
	cout << totalInputSpaces << leftDownCorner;
	for (int i = 1; i < dimension_length; ++i)
	{
		cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << sideDown;
	}
	cout << doubleHorizontal << doubleHorizontal << doubleHorizontal << rightDownCorner;
	//print informations
	OXCounter(player1, player2, table);
	cout << endl << endl << endl << endl << "					  							     ";
	cout << player1.playerName << " : " << player1.numberOfNuts << "       " << player1.symbol << endl;
	cout << "												     ";
	cout << player2.playerName << " : " << player2.numberOfNuts << "       " << player2.symbol << endl;
	cout << "												     ";
	if (whose_turn)
		cout << "Turn :" << ' ' << player1.playerName;
	else
		cout << "Turn :" << ' ' << player2.playerName;
}


string returnTotalSpaces(int dimension)
{
	string totalSpaces;
	if (dimension == 4)
		totalSpaces = inputSpaces_4;
	else if (dimension == 6)
		totalSpaces = inputSpaces_6;
	else if (dimension == 8)
		totalSpaces = inputSpaces_8;
	else if (dimension == 10)
		totalSpaces = inputSpaces_10;
	else                                            // Dimension is 12
		totalSpaces = inputSpaces_12;
	return totalSpaces;
}


void printOthello()            // print OTHELLO title function
{
	cout << " 												+++++++++++++++++++" << endl;
	cout << "												<<<<<         >>>>>" << endl;
	cout << "												<<<<< OTHELLO >>>>>" << endl;
	cout << "												<<<<<         >>>>>" << endl;
	cout << " 												+++++++++++++++++++" << endl << endl;
}


void cheking_is_allowed_and_change_pieces(char table[][12], int currentRow, int currentCol, bool &whose_turn, int table_dimension)
{
	if (table[currentRow - 1][currentCol - 1] == ' ')
	{
		char put;
		char other;
		bool temp = whose_turn;
		if (whose_turn)
		{
			put = 'x';
			other = 'o';
		}
		else
		{
			put = 'o';
			other = 'x';
		}
		//checking up
		if (currentRow != 1 && table[currentRow - 2][currentCol - 1] == other)
		{
			for (int i = currentRow - 2; i >= 0; i--)
			{
				if (table[i][currentCol - 1] == ' ')
					break;
				else if (table[i][currentCol - 1] == put)
				{
					for (i; i <= currentRow - 1; i++)
					{
						table[i][currentCol - 1] = put;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
			}
		}
		//checking down
		if (currentRow != table_dimension && table[currentRow][currentCol - 1] == other)
		{
			for (int i = currentRow; i < table_dimension; i++)
			{
				if (table[i][currentCol - 1] == ' ')
					break;
				else if (table[i][currentCol - 1] == put)
				{
					for (i; i >= currentRow - 1; i--)
					{
						table[i][currentCol - 1] = put;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
			}
		}
		//checking right
		if (currentCol != table_dimension && table[currentRow - 1][currentCol] == other)
		{
			for (int i = currentCol; i < table_dimension; i++)
			{
				if (table[currentRow - 1][i] == ' ')
					break;
				else if (table[currentRow - 1][i] == put)
				{
					for (i; i >= currentCol - 1; i--)
					{
						table[currentRow - 1][i] = put;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
			}
		}
		//checking left
		if (currentCol != 1 && table[currentRow - 1][currentCol - 2] == other)
		{
			for (int i = currentCol - 2; i >= 0; i--)
			{
				if (table[currentRow - 1][i] == ' ')
					break;
				else if (table[currentRow - 1][i] == put)
				{
					for (i; i <= currentCol - 1; i++)
					{
						table[currentRow - 1][i] = put;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
			}
		}
		//checking down-left
		if (currentRow != table_dimension && currentCol != 1 && table[currentRow][currentCol - 2] == other)
		{
			int i = currentRow, j = currentCol - 2;
			while (i < table_dimension && j >= 0)
			{
				if (table[i][j] == ' ')
					break;
				else if (table[i][j] == put)
				{
					while (i >= currentRow - 1 && j <= currentCol - 1)
					{
						table[i][j] = put;
						j++;
						i--;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
				j--;
				i++;
			}
		}
		//checking up-right
		if (currentCol != table_dimension && currentRow != 1 && table[currentRow - 2][currentCol] == other)
		{
			int i = currentRow - 2, j = currentCol;
			while (i >= 0 && j < table_dimension)
			{
				if (table[i][j] == ' ')
					break;
				else if (table[i][j] == put)
				{
					while (i <= currentRow - 1&& j >= currentCol - 1)
					{
						table[i][j] = put;
						j--;
						i++;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
				j++;
				i--;
			}
		}
		//checking up-left
		if (currentRow != 1 && currentCol != 1 && table[currentRow - 2][currentCol - 2] == other)
		{
			int i = currentRow - 2, j = currentCol - 2;
			while (j >= 0 && i >= 0)
			{
				if (table[i][j] == ' ')
					break;
				else if (table[i][j] == put)
				{
					while (i <= currentRow - 1 && j <= currentCol - 1)
					{
						table[i][j] = put;
						i++;
						j++;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
				i--;
				j--;
			}
		}
		//checking down-right
		if (currentRow != table_dimension && currentCol != table_dimension && table[currentRow][currentCol] == other)
		{
			int i = currentRow, j = currentCol;
			while (i < table_dimension && j < table_dimension)
			{
				if (table[i][j] == ' ')
					break;
				else if (table[i][j] == put)
				{
					while (i >= currentRow - 1 && j >= currentCol - 1)
					{
						table[i][j] = put;
						i--;
						j--;
					}
					if (temp)
					{
						whose_turn = false;
						break;
					}
					else
					{
						whose_turn = true;
						break;
					}
				}
				j++;
				i++;
			}
		}
	}
}


bool checking_x_is_allowed(char table[][12], int table_dimension)
{
	for (int i = 0; i < table_dimension; i++)
	{
		for (int j = 0; j < table_dimension; j++)
		{
			if (table[i][j] == ' ')
			{
				//checking up
				if (i != 0)
				{
					if (table[i - 1][j] == 'o')
					{
						for (int t = i - 1; t >= 0; t--)
						{
							if (table[t][j] == ' ')
								break;
							else if (table[t][j] == 'x')
								return true;
						}
					}
				}
				//checking down
				if (i != table_dimension - 1)
				{
					if (table[i + 1][j] == 'o')
					{
						for (int t = i + 1; t < table_dimension; t++)
						{
							if (table[t][j] == ' ')
								break;
							else if (table[t][j] == 'x')
								return true;
						}
					}
				}
				//checking right
				if (j != table_dimension - 1)
				{
					if (table[i][j + 1] == 'o')
					{
						for (int t = j + 1; t < table_dimension; t++)
						{
							if (table[i][t] == ' ')
								break;
							else if (table[i][t] == 'x')
								return true;
						}
					}
				}
				//checking left
				if (j != 0)
				{
					if (table[i][j - 1] == 'o')
					{
						for (int t = j - 1; t >= 0; t--)
						{
							if (table[i][t] == ' ')
								break;
							else if (table[i][t] == 'x')
								return true;
						}
					}
				}
				//checking up-right
				if (j != table_dimension - 1 && i != 0)
				{
					if (table[i - 1][j + 1] == 'o')
					{
						for (int t = i - 1, q = j + 1; t >= 0 && q < table_dimension; t--, q++)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'x')
								return true;
						}
					}
				}
				//checking up-left
				if (i != 0 && j != 0)
				{
					if (table[i - 1][j - 1] == 'o')
					{
						for (int t = i - 1, q = j - 1; t >= 0 && q >= 0; t--, q--)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'x')
								return true;
						}
					}
				}
				//checking down-right
				if (i != table_dimension - 1 && j != table_dimension - 1)
				{
					if (table[i + 1][j + 1] == 'o')
					{
						for (int t = i + 1, q = j + 1; t < table_dimension && q < table_dimension; q++, t++)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'x')
								return true;
						}
					}
				}
				//checking down-left
				if (i != table_dimension - 1 && j != 0)
				{
					if (table[i + 1][j - 1] == 'o')
					{
						for (int t = i + 1, q = j - 1; t < table_dimension && q >= 0; t++, q--)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'x')
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}


bool checking_o_is_allowed(char table[][12], int table_dimension)
{
	for (int i = 0; i < table_dimension; i++)
	{
		for (int j = 0; j < table_dimension; j++)
		{
			if (table[i][j] == ' ')
			{
				//checking up
				if (i != 0)
				{
					if (table[i - 1][j] == 'x')
					{
						for (int t = i - 1; t >= 0; t--)
						{
							if (table[t][j] == ' ')
								break;
							else if (table[t][j] == 'o')
								return true;
						}
					}
				}
				//checking down
				if (i != table_dimension - 1)
				{
					if (table[i + 1][j] == 'x')
					{
						for (int t = i + 1; t < table_dimension; t++)
						{
							if (table[t][j] == ' ')
								break;
							else if (table[t][j] == 'o')
								return true;
						}
					}
				}
				//checking right
				if (j != table_dimension - 1)
				{
					if (table[i][j + 1] == 'x')
					{
						for (int t = j + 1; t < table_dimension; t++)
						{
							if (table[i][t] == ' ')
								break;
							else if (table[i][t] == 'o')
								return true;
						}
					}
				}
				//checking left
				if (j != 0)
				{
					if (table[i][j - 1] == 'x')
					{
						for (int t = j - 1; t >= 0; t--)
						{
							if (table[i][t] == ' ')
								break;
							else if (table[i][t] == 'o')
								return true;
						}
					}
				}
				//checking up-right
				if (j != table_dimension - 1 && i != 0)
				{
					if (table[i - 1][j + 1] == 'x')
					{
						for (int t = i - 1, q = j + 1; t >= 0 && q < table_dimension; t--, q++)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'o')
								return true;
						}
					}
				}
				//checking up-left
				if (i != 0 && j != 0)
				{
					if (table[i - 1][j - 1] == 'x')
					{
						for (int t = i - 1, q = j - 1; t >= 0 && q >= 0; t--, q--)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'o')
								return true;
						}
					}
				}
				//checking down-right
				if (i != table_dimension - 1 && j != table_dimension - 1)
				{
					if (table[i + 1][j + 1] == 'x')
					{
						for (int t = i + 1, q = j + 1; t < table_dimension && q < table_dimension; q++, t++)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'o')
								return true;
						}
					}
				}
				//checking down-left
				if (i != table_dimension - 1 && j != 0)
				{
					if (table[i + 1][j - 1] == 'x')
					{
						for (int t = i + 1, q = j - 1; t < table_dimension && q >= 0; t++, q--)
						{
							if (table[t][q] == ' ')
								break;
							else if (table[t][q] == 'o')
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}


void saveGame(char table[][12], Players player1, Players player2, int table_dimension, bool whose_turn)
{
	string filename;
	cout << endl << endl;
	cout << "Please enter the file name : ";
	getline(cin, filename);
	ofstream file(filename+".txt");
	file << player1.playerName << endl << player2.playerName << endl;
	file << whose_turn << endl << table_dimension << endl;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (table[i][j] == ' ')
			{
				file << '$' << ' ';
			}
			else
				file << table[i][j] << ' ';
		}
		file << endl;
	}
	file.close();
}


void loadGame(char table_element[][12], int currentRow, int currentCol)
{
	cout << "Please write full name of your game : " << endl;
	string strNamefile;
	while (true)
	{
		getline(cin, strNamefile);
		strNamefile += ".txt";
		if (strNamefile == "exit")
		{
			system("CLS");
			return;
		}
		ifstream file(strNamefile);
		if (file.is_open())
		{
			file.close();
			break;
		}
		else
		{
			cout << "Invalid name! Enter the name again or write \"exit\" to return to menu : " << endl;
			file.close();
		}
	}
	int tableDimension;
	bool turn = true;
	currentRow = 1;
	currentCol = 1;
	ifstream file(strNamefile);
	getline(file, player1.playerName);
	getline(file, player2.playerName);
	file >> turn;
	file >> tableDimension;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			file >> table_element[i][j];
			if (table_element[i][j] == '$')
				table_element[i][j] = ' ';
		}
	}
	file.close();
	game(table_element, currentRow, currentCol, tableDimension, turn);
}


void saveRanks(string winner)
{
	ifstream file("Rank.txt");
	int arraySize = 0;
	string testStr;
	bool isOpen = false;
	if (file.is_open())
	{
		while (getline(file, testStr))
		{
			arraySize++;
		}
		isOpen = true;
	}
	arraySize /= 3;
	string *names = new string[arraySize + 2];
	int *numberOfPlayes = new int[arraySize + 2];
	int *numberOfWins = new int[arraySize + 2];
	for (int i = 0; i < arraySize + 2; ++i)
	{
		numberOfWins[i] = 0;
		numberOfPlayes[i] = 0;
	}
	string temp;
	file.clear();
	file.seekg(0);
	if (isOpen)
	{
		for (int i = 0; i < arraySize; ++i)
		{
			getline(file, temp);
			names[i] = temp;
			getline(file, temp);
			numberOfPlayes[i] = stoi(temp);
			getline(file, temp);
			numberOfWins[i] = stoi(temp);
		}
		file.close();
	}
	bool checkPlayer1 = false;
	bool checkPlayer2 = false;
	int len = arraySize;
	if (winner == "draw")
	{
		for (int i = 0; i < arraySize; ++i)
		{
			if (names[i] == player1.playerName)
			{
				checkPlayer1 = true;
				numberOfPlayes[i]++;
			}
			if (names[i] == player2.playerName)
			{
				checkPlayer2 = true;
				numberOfPlayes[i]++;
			}
		}
		if (!checkPlayer1)
		{
			names[len] = player1.playerName;
			numberOfPlayes[len]++;
			len++;
		}
		if (!checkPlayer2)
		{
			names[len] = player2.playerName;
			numberOfPlayes[len]++;
			len++;
		}
	}
	else 
	{
		for (int i = 0; i < arraySize; ++i)
		{
			if (names[i] == player1.playerName)
			{
				checkPlayer1 = true;
				if (winner == player1.playerName)
				{
					numberOfWins[i]++;
				}
				numberOfPlayes[i]++;
			}
			if (names[i] == player2.playerName)
			{
				checkPlayer2 = true;
				if (winner == player2.playerName)
				{
					numberOfWins[i]++;
				}
				numberOfPlayes[i]++;
			}
		}
		if (!checkPlayer1)
		{
			names[len] = player1.playerName;
			if (winner == player1.playerName)
			{
				numberOfWins[len]++;
			}
			numberOfPlayes[len]++;
			len++;
		}
		if (!checkPlayer2)
		{
			names[len] = player2.playerName;
			if (winner == player2.playerName)
			{
				numberOfWins[len]++;
			}
			numberOfPlayes[len]++;
			len++;
		}
	}
	ofstream file1("Rank.txt");
	for (int i = 0; i < len; ++i)
	{
		file1 << names[i] << endl << numberOfPlayes[i] << endl << numberOfWins[i] << endl;
	}
	file1.close();
	delete[] names;
	delete[] numberOfPlayes;
	delete[] numberOfWins;
}


void loadRank()
{
	ifstream file("Rank.txt", ios::in);
	int arraySize = 0;
	string testStr;
	while (getline(file, testStr))
	{
		arraySize++;
	}
	arraySize /= 3;
	string *name = new string[arraySize];
	int *numberOfPlayes = new int[arraySize];
	int *numberOfWin = new int[arraySize];
	string temp;
	file.clear();
	file.seekg(0);
	for (int i = 0; i < arraySize; i++)
	{
		getline(file, temp);
		name[i] = temp;
		getline(file, temp);
		numberOfPlayes[i] = stoi(temp);
		getline(file, temp);
		numberOfWin[i] = stoi(temp);
	}
	string nameTemp;
	int winTemp;
	int gameTemp;
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize - i - 1; j++)
		{
			if (numberOfWin[j] < numberOfWin[j + 1])
			{
				winTemp = numberOfWin[j];
				numberOfWin[j] = numberOfWin[j + 1];
				numberOfWin[j + 1] = winTemp;
				gameTemp = numberOfPlayes[j];
				numberOfPlayes[j] = numberOfPlayes[j + 1];
				numberOfPlayes[j + 1] = gameTemp;
				nameTemp = name[j];
				name[j] = name[j + 1];
				name[j + 1] = nameTemp;
			}
		}
	}
	for (int i = 0; i < arraySize; i++)
	{
		cout << left << setw(79) << name[i];
		cout << left << setw(40) << numberOfPlayes[i];
		cout << left << setw(30) << numberOfWin[i] << endl;
	}
	delete [] name;
	delete [] numberOfPlayes;
	delete [] numberOfWin;
}


void game(char table_element[][12], int currentRow, int currentCol, int tableDimension, bool turn)
{
	system("CLS");
	print_table(table_element, tableDimension, currentRow, currentCol, turn);
	guidlineFunction();
	cout << endl;
	char control;
	while (checking_o_is_allowed(table_element, tableDimension) || checking_x_is_allowed(table_element, tableDimension))
	{
		do 
		{
			control = getch();
		}
		while (control != 'a' && control != 's' && control != 'd' && control != 'w' && control != '\r' && control != 'm' && control != 'p');
		
		switch (control)
		{
			case 'p' :
			{
				system("CLS");
				return;
			}
			case 'a' :
			{
				if (currentCol != 1)
					currentCol--;
				else
					currentCol = tableDimension;
			}
			break;
			case 's' :
			{
				if (currentRow != tableDimension)
					currentRow++;
				else
					currentRow = 1;
			}
			break;
			case 'd' :
			{
				if (currentCol != tableDimension)
					currentCol++;
				else
					currentCol = 1;
			}
			break;
			case 'w' :
			{
				if (currentRow != 1)
					currentRow--;
				else
					currentRow = tableDimension;
			}
			break;
			case '\r' :
			{
				cheking_is_allowed_and_change_pieces(table_element, currentRow, currentCol, turn, tableDimension);
				if (turn)
				{
					if (!checking_x_is_allowed(table_element, tableDimension))
						turn = false;
				}
				else
				{
					if (!checking_o_is_allowed(table_element, tableDimension))
						turn = true;
				}
			}
			break;
			case 'm' :
			{
				saveGame(table_element, player1, player2, tableDimension, turn);
			}
			break;
		}
		system("CLS");
		print_table(table_element, tableDimension, currentRow, currentCol, turn);
		guidlineFunction();
		cout << endl;
	}
	system("CLS");
	print_table(table_element, tableDimension, currentRow, currentCol, turn);
	cout << endl << endl;
	string winnerStr;
	if (player1.numberOfNuts > player2.numberOfNuts)
	{
		cout << "												     " << player1.playerName << ' ' << "WON!";
		winnerStr = player1.playerName;
		saveRanks(winnerStr);
	}
	else if (player1.numberOfNuts < player2.numberOfNuts)
	{
		cout << "												     " << player2.playerName << ' ' << "WON!";
		winnerStr = player2.playerName;
		saveRanks(winnerStr);
	}
	else
	{
		cout << "												     " << "DRAW!!!";
		saveRanks("draw");
	}
	guidlineFunction();
	cout << endl;
	while (true)
	{
		control = getch();
		if (control == 'p')
		{
			system("CLS");
			return;
		}
	}
}