#include <iostream>
#include "Header.h"
#include <fstream>
#include <string> 
#include "Windows.h"

using namespace std;

// ������ ������� ����� ����. �� 2 ������ ��� �� �� �������� �� �������
const int height = 23;
const int width = 23;
// ��� ������� ������� (workspace)
const int wheight = height - 1;
const int wwidth = width - 1;

// ������� ����� ����� �������� �� ����
int aliveCount(char mas[height][width]) {
	int count = 0;
	for (int i = 1; i < wheight; i++) {
		for (int j = 1; j < wwidth; j++) {
			if ((mas[i][j] - '0') > 0) { // ���� ������ ��� ����������� �������
				count++;
			}
		}
	}
	return count;
}

// ����� ������� � �������
void printOut(char arr[height][width]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((arr[i][j] - '0') == -48) { // ���� ��� �������, � �������� �� ����
				cout << "  ";
			}
			if ((arr[i][j] - '0') == 0) { // ���� ���� �� �������, ��� ��������
				cout << "  ";
			}
			else {
				cout << arr[i][j] << " "; // ����� ����� ����������
			}
		}
		cout << endl;
	}
}

// ����������� ������ ������� � ������
void copying(char(&_old)[height][width], char(&_new)[height][width]) {
	for (int i = 1; i < wheight; i++) {
		for (int j = 1; j < wwidth; j++) {
			_new[i][j] = _old[i][j];
		}
	}
}

int LIFE() {
	// ��������� ��������� �������, �������� ������ � �������� �� ��� ������ � ������ ����� fstream
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fdat("work.dat.txt");
	ofstream fout("work.out.txt");
	fdat.close();
	fout.close();
	fstream data("work.dat.txt", fstream::out | fstream::in);
	fstream out("work.out.txt", fstream::out | fstream::in);

	char arr_old[height][width]{}; // ������ �������� 
	char arr_new[height][width]{}; // ������ ��������

	// 1
	// ������������ ������ ����� ��������� �������� (��������, ���������� �� ������� �������� �� ����) � ���� ����������� ��������� (������� ���� ��������)
	int freq = 0;
	while (true) {
		cout << "������� ��������� �������� ����� � ����� dat? (������� ��������)" << endl << "������� ����� [1,26]: ";
		freq = getInt();
		if (freq >= 1 && freq <= 26) {
			break;
		}
		else {
			cout << "������. �������� ����� ������ ���� � �������� [1,26]. ���������� ��� ���" << endl;
		}
	}
	// ���������� ����� dat ���������.
	srand(time(NULL));
	for (int i = 0; i < 21*21; i++) {
		char smvl = 97 + (rand() % freq); // � char ����� ���������� ��������� ������ �� a �� z �� ������� ASCII (����� �� 97 �� 122)
		data << smvl; // ���� � ���� 
	}
	data.seekg(0); // ��������� ������� � ������ ����� ����� ����������

	// 2
	// ���������� �������� �� ����� � ������ ��������
	char microb = 97 + (rand() % freq); // ����� ���������� �������, ������� ����� ���������� �������
	for (int i = 1; i < wheight; i++) {
		for (int j = 1; j < wwidth; j++) {
			char ch;
			data.get(ch);  // ���������� ������� �� �����
			if (ch == microb) { // �������� �������, ���� ������ - ������� � ������ 1
				arr_old[i][j] = '1';
			}
			else { // ���� ��� - 0
				arr_old[i][j] = '0';
			}
		}
	}
	data.close();

	// ������ � ��� ���� ������� ���� � ��������� ������������� �������� � arr_old
	copying(arr_old, arr_new); // ����������� ������� ������� � �����

	int colv_pok;
	while (true) {
		cout << "������� ���������� ���������: ";
		colv_pok = getInt();
		if (colv_pok > 0) {
			break;
		}
		else {
			cout << "������. ���������� ��� ���" << endl;
		}
	}

	int num = 1; // �������� �� ����� ���������
	printOut(arr_old); // ����� � ������� ���������� ��������� ��������

	// ���������� � ���� out, ������ ������
	for (int i = 1; i < wheight; i++) {
		for (int j = 1; j < wwidth; j++) {
			if (arr_old[i][j] == '0') { // ���� ������� ��� ��������� ������
				out << "  ";
			}
			else {
				out << arr_old[i][j] << " ";
			}
		}
		out << endl;
	}
	out << "���������: " << num << endl << "���������� ����� ��������: " << aliveCount(arr_new) << endl << "------------------------------------------" << endl;
	if (aliveCount(arr_old) == 0) { // ���� �������� �� �������� � ����� - �����
		cout << "������ �������� ���..." << endl;
		exit(0);
	}
	cout << "���������: " << num << endl << "���������� ����� ��������: " << aliveCount(arr_new) << endl << "------------------------------------------" << endl;

	// 3
	for (int zzz = 1; zzz < colv_pok; zzz++) {
		for (int i = 1; i < wheight; i++) {
			for (int j = 1; j < wwidth; j++) {
				int sosedi = 0;// ����� �������
				for (int q = i-1; q < i+2; q++) { // ������� �������� � ����������� ���� ��� [i][j] ��������
					for (int w = j-1; w < j+2; w++) {
						if ((arr_new[q][w] - '0') == -48) { // �� ��������� �������
							continue;
						}
						if ((arr_new[q][w] - '0') > 0) { // ���� ������ ���, �� +1 � ������
							sosedi++;
						}
					}
				}
				if ((arr_new[i][j] - '0') > 0) { // �������� [i][j] ������� ��� ��� ��� ������� � ����������� �� �����
					sosedi--;
				}

				// �������� �������. ��������� ���������� � ������ �������, ��� ���� ��� �� ����� ��������� �� ����������� �����
				if ((sosedi == 3) && ((arr_new[i][j] - '0') >= 0)) { // ���� ���� 3 ������ => ���������� ���� ��� ���������
					if (arr_new[i][j] == '9') { // ���� ������� 9 ���, �� �� ��������� ��� ������ ������������ �(�� 16������ ��) 
						arr_old[i][j] += 7; // ����� ������� �� 9 � A, �� ������� ASCII ���������� 8 (���������� 7 � 1 �� ���� ������)
					}
					arr_old[i][j]++; // ���� ������ ����� - ������� ��� ���
					if ((arr_old[i][j]) == 'C') { // ���� ������ ����� �� 12 ��� => �� �������
						arr_old[i][j] = '0';
					}
				}

				if ((sosedi < 2 || sosedi > 3) && (arr_new[i][j] - '0') >= 1) { // ���� � ������� ������ 3 ��� ������ 2 ������� => �� �������
					arr_old[i][j] = '0';
				}

				if ((sosedi == 2) && ((arr_new[i][j] - '0') > 0)) { // ���� ���� 2 ������ => ���������� ���� 
					if (arr_new[i][j] == '9') { // ����� ����� 9 ���� A
						arr_old[i][j] += 7; // ���� ��������� 8
					}
					arr_old[i][j]++;
					if ((arr_old[i][j]) == 'C') { // ���� ������ ����� �� 12 ��� => �� �������
						arr_old[i][j] = '0';
					}
				}
			}
		}


		// ����������� �� ������� ������� � ����� � ����� �������� ���������
		copying(arr_old, arr_new);
		printOut(arr_new); 

		// ������ � ����
		for (int i = 1; i < wheight; i++) {
			for (int j = 1; j < wwidth; j++) {
				if (arr_old[i][j] == '0') {
					out << "  ";
				}
				else {
					out << arr_old[i][j] << " ";
				}
			}
			out << endl;
		}
		num++; // ���������� ������ ���������
		out << "���������: " << num << endl << "���������� ����� ��������: " << aliveCount(arr_new) << endl << "------------------------------------------" << endl;

		// ����� ���������� � �������
		cout << "���������: " << num << endl << "���������� ����� ��������: " << aliveCount(arr_new) << endl << "------------------------------------------" << endl;
		if (aliveCount(arr_new) == 0) {
			cout << endl << "��� ������� ������(" << endl;
			break;
		}
	}

	out.close();
	cout << endl << "�����" << endl;
	return 0;
}