#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <thread>
#include "pipe.h"
#include "ks.h"
using namespace std;

const int MAX_PIPES = 100;
const int MAX_KS = 50;

void SaveData(pipe pipes[], int pipeCount, ks kss[], int ksCount) {
	cout << "������� ��� ����� ��� ���������� ������: \n";
	string filename;
	getline(cin, filename);

	ofstream outFile(filename);
	if (!outFile) {
		cout << "������ ��� �������� ����� ��� ���������� ������.\n";
		return;
	}


	outFile << "Pipes" << endl;
	for (int i = 0; i < pipeCount; ++i) {
		outFile << pipes[i].GetName() << endl;
		outFile << pipes[i].GetLength() << endl;
		outFile << pipes[i].GetDiameter() << endl;
		outFile << pipes[i].GetInRepair() << endl;
	}

	outFile << "KS" << endl;
	for (int i = 0; i < ksCount; ++i) {
		outFile << kss[i].GetName() << endl;
		outFile << kss[i].GetNumFac() << endl;
		outFile << kss[i].GetNumWorkFac() << endl;
		outFile << kss[i].GetEff() << endl;
	}

	outFile.close();
	cout << "������ ������� ��������� � " << filename << ".\n";
}

void LoadData(pipe pipes[], int& pipeCount, ks kss[], int& ksCount) {
    cout << "������� ��� ����� ��� �������� ������: ";
    string filename;
    getline(cin, filename);

    ifstream inFile(filename);
    if (!inFile) {
        cout << "������ ��� �������� ����� ��� �������� ������.\n";
        return;
    }

    string line;
    getline(inFile, line);

	if (line == "Pipes") {
		while (getline(inFile, line) && line != "KS") {
			string name = line;
			int length, diameter;
			bool inRepair;

			inFile >> length >> diameter >> inRepair;
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			if (pipeCount < MAX_PIPES) {
				pipes[pipeCount++] = pipe(name, length, diameter, inRepair);
			}
		}
	}

	if (line == "KS") {
		while (getline(inFile, line)) {
			string name = line;
			int numFac, numWorkFac, eff;

			inFile >> numFac >> numWorkFac >> eff;
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');

			if (ksCount < MAX_KS) {
				kss[ksCount++] = ks(name, numFac, numWorkFac, eff);
			}
		}
	}

	inFile.close();
	cout << "������ ������� ��������� �� " << filename << ".\n";
}

void LogToFile(const string& message, ofstream& logFile) {
	if (logFile.is_open()) {
		logFile << message << endl; 
	}
}

bool IsInteger(string s) {
	istringstream iss(s);
	int num;
	return (iss >> num) && iss.eof();
}

int GetPositiveNumber(const string& zapros, ofstream& logFile) {
	string input;
	int value;
	std::cout << zapros;
	while (true) {
		getline(cin, input);
		LogToFile(input, logFile);
		if (input.empty()) {
			cout << "���� �� ������ ���� ������. ���������� �����: ";
			LogToFile("Error. Empty insert >:(", logFile);
			continue;
		}
		if (IsInteger(input)) {
			value = stoi(input);
			if (value > 0) return value;
		}
		std::cout << "������� ������������� ����� \n";
		LogToFile("Error. Non-positive number >:(", logFile);
		}

	}

bool GetRepairStatus(const string& zapros, ofstream& logFile) {
	string repairStatus;
	cout << zapros;
	while (true) {
		getline(cin, repairStatus);
		LogToFile(repairStatus, logFile);
		if (repairStatus == "y" || repairStatus == "Y") return true;
		if (repairStatus == "n" || repairStatus == "N") return false;
		cout << "������� y(��) ��� n(���)\n";
		LogToFile("Error. Try y or n >:(", logFile);
	}
}

void SearchPipe(pipe pipes[], int pipeCount, ofstream& logFile) {
	cout << "�������� ������ ��� ������ ����:\n";
	cout << "1. �� ��������\n";
	cout << "2. �� ������� �������\n";

	string choice;
	getline(cin, choice);
	LogToFile(choice, logFile);

	if (choice == "1") {
		string searchName;
		cout << "������� �������� �����: ";
		getline(cin, searchName);
		LogToFile(searchName, logFile);
		for (int i = 0; i < pipeCount; ++i) {
			if (pipes[i].GetName().find(searchName) != string::npos) {
				cout << "������� �����:\n";
				cout << pipes[i].ToString(); 
			}
		}
	}
	else if (choice == "2") {
		string status;
		cout << "������� ������ ������� (y/n): ";
		getline(cin, status);
		LogToFile(status, logFile);
		while (true) {
			if (status == "y" || status == "Y" || status == "n" || status == "N") {
				break;
			}
			cout << "������� ������ ������ (y/n): ";
			LogToFile("Error.Try y or n >:(", logFile);
			getline(cin, status);
			LogToFile(status, logFile);
		}
		bool inRepair = (status == "y" || status == "Y");
		for (int i = 0; i < pipeCount; ++i) {
			if (pipes[i].GetInRepair() == inRepair) {
				cout << "������� �����:\n";
				cout << pipes[i].ToString();
			}
		}
	}
	else {
		cout << "�������� �����.\n";
		LogToFile("Error. Wrong choice >:(", logFile);
	}
}

void SearchKS(ks kss[], int ksCount, ofstream& logFile) {
	cout << "�������� ������ ��� ������ ��:\n";
	cout << "1. �� ��������\n";
	cout << "2. �� �������� ����������������� �����\n";

	string choice;
	getline(cin, choice);
	LogToFile(choice, logFile);

	if (choice == "1") {
		string searchName;
		cout << "������� �������� �� ��� ������: ";
		getline(cin, searchName);
		LogToFile(searchName, logFile);
		for (int i = 0; i < ksCount; ++i) {
			if (kss[i].GetName().find(searchName) != string::npos) {
				cout << "������� ��:\n";
				cout << kss[i].ToString(); 
			}
		}
	}
	else if (choice == "2") {
		int percent;
		cout << "������� ������� ����������������� �����: ";
		cin >> percent;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		LogToFile(to_string(percent), logFile);
		for (int i = 0; i < ksCount; ++i) {
			int unusedPercent = 100 * (kss[i].GetNumFac() - kss[i].GetNumWorkFac()) / kss[i].GetNumFac();
			if (unusedPercent == percent) {
				cout << "������� ��:\n";
				cout << kss[i].ToString();
			}
		}
	}
	else {
		cout << "�������� �����.\n";
		LogToFile("Error. Wrong choice >:(", logFile);
	}
}

void PacEditPipes(pipe pipes[], int pipeCount, ofstream& logFile) {
	cout << "������ ����:\n";
	for (int i = 0; i < pipeCount; ++i) {
		cout << i << ": " << pipes[i].GetName() << endl;
	}

	cout << "������� ������� ���� ��� �������������� (����� �������, ��� ��������): ";
	string input;
	getline(cin, input);
	LogToFile(input, logFile);

	stringstream ss(input);
	string indexStr;
	bool inRepair = GetRepairStatus("��������� �� ����� � �������?: ", logFile);
	while (getline(ss, indexStr, ',')) {
		int index = stoi(indexStr);
		if (index >= 0 && index < pipeCount) {
			pipes[index].SetInRepair(inRepair);
			cout << "������ ������� ����� " << pipes[index].GetName() << " ��������.\n";
		}
		else {
			cout << "�������� ������: " << index << endl;
			LogToFile("Error. Empty index: " + to_string(index), logFile);
		}
	}
}

int main() {
	ofstream logFile("C:/Users/05bla/Downloads/LAB2/LAB2/LAB2/log.txt", ios::app); // ��������� ���� ��� ����������
	if (!logFile) {
		cerr << "������ ��� �������� ����� ��� �����������.\n";
		return 1; // ��������� ��������� � ������ ������
	}
	string choose;
	pipe pipes[MAX_PIPES];
	ks kss[MAX_KS];
	int pipeCount = 0;
	int ksCount = 0;
	while (true) {
		setlocale(LC_ALL, (""));
		cout << "1. ������� �����\n";
		cout << "2. ������� ��\n";
		cout << "3. �������������� ����\n";
		cout << "4. �������������� ��\n";
		cout << "5. �������� ��� �������\n";
		cout << "6. ���������\n";
		cout << "7. ���������\n";
		cout << "8. �����\n";
		cout << "9. �����\n";
		getline(cin, choose);
		LogToFile(choose, logFile);
		while (!IsInteger(choose)) {
			cout << "������� ����� �� 1 �� 9" << endl;
			LogToFile("Error. Try 1 to 9 >:(", logFile);
			getline(cin, choose);
			LogToFile(choose, logFile);
		}

		switch (stoi(choose)) {
		case 1: {
			if (pipeCount >= MAX_PIPES) {
				cout << "��������� �������� ����" << endl;
				break;
			}
			string name;
			cout << "������� �������� �����: ";
			while (true) {
				getline(cin, name);
				LogToFile(name, logFile);
				if (name.empty()) {
					cout << "��� �� ����� ���� ������ �������. ���������� �����: ";
					LogToFile("Error. Name can't be empty >:(", logFile);
				}
				else {
					break;
				}
			}

			int length = GetPositiveNumber("������� ����� �����: ", logFile);
			int diameter = GetPositiveNumber("������� ������� �����: ", logFile);
			bool inRepair = GetRepairStatus("��������� �� ����� � �������? (y/n): ", logFile);

			pipes[pipeCount] = pipe(name, length, diameter, inRepair);
			pipeCount++;
			cout << "����� �������\n";
		}
			  break;
		case 2: {
			if (ksCount >= MAX_KS) {
				cout << "���������� ������������� ���������� ��" << endl;
				break;
			}
			string name;
			cout << "������� �������� K�: ";
			while (true) {
				getline(cin, name);
				LogToFile(name, logFile);
				if (name.empty()) {
					cout << "��� �� ����� ���� ������ �������. ���������� �����: ";
					LogToFile("Error.Name can't be empty >:(", logFile);
				}
				else {
					break;
				}
			}
			int NumFac = GetPositiveNumber("������� ���������� ������: ", logFile);
			int NumWorkFac;
			while (true) {
				NumWorkFac = GetPositiveNumber("������� ���������� ���������� ������: ", logFile);
				if (NumWorkFac <= NumFac) {
					break;
				}
				cout << "���������� ��������� ������ ������ ���� ������ ������\n";
				LogToFile("Error. Ammount of working factories need to be below total >:(", logFile);
			}

			int eff;
			while (true) {
				eff = GetPositiveNumber("������� ������������� �� (0-100): ", logFile);
				if (eff >= 0 && eff <= 100) {
					break;
				}
				cout << "������� ����� �� 0 �� 100\n";
				LogToFile("Error. Try 0 to 100 >:(", logFile);
			}

			kss[ksCount] = ks(name, NumFac, NumWorkFac, eff);
			ksCount++;
			cout << "�� �������\n";
		}
			  break;
		case 3: {
			if (pipeCount == 0) {
				cout << "��� ���� ��� ��������������\n";
				break;
			}
			string choice;
			cout << "1. ������������� ���� �����\n";
			cout << "2. �������� �������������� ����\n";
			getline(cin, choice);
			LogToFile((choice), logFile);


			if (choice == "1") {
				if (pipeCount == 0) {
					cout << "��� ���� ��� ��������������\n";
					break;
				}
				string indexs;
				cout << "������� ������ ����� ��� �������������� (0-" << pipeCount - 1 << "): ";
				getline(cin, indexs);
				LogToFile(indexs, logFile);


				if (IsInteger(indexs)) {
					if (stoi(indexs) < 0 || stoi(indexs) >= pipeCount) {
						cout << "�������� ������.\n";
						break;
					}
					int index = stoi(indexs);
					cout << "1. �������� ������ �������\n";
					cout << "2. ������� �����\n";
					getline(cin, choice);
					LogToFile(choice, logFile);

					if (choice == "1") {
						pipes[index].SetInRepair(GetRepairStatus("��������� �� ����� � �������?: ", logFile));
						cout << "������ ������� ����� ��������.\n";
					}
					else if (choice == "2") {
						for (int i = index; i < pipeCount - 1; ++i) {
							pipes[i] = pipes[i + 1]; // �������� �������� ������� �����
						}
						pipeCount--; // ��������� ������� ����
						cout << "����� �������.\n";
						LogToFile("����� �������", logFile);
					}
					else {
						cout << "�������� �����.\n";
						LogToFile("������: �������� ����� ��� �������������� ����� �����.", logFile);
					}

				}
				}
				else if (choice == "2") {
					PacEditPipes(pipes, pipeCount, logFile);
				}
				else {
					cout << "�������� �����.\n";
					LogToFile("Error. Wrong choice >:(", logFile);
				}
			}
			break;
		case 4: {
			if (ksCount == 0) {
				cout << "��� �� ��� ��������������\n";
				break;
			}
			int index;
			cout << "������� ������ �� ��� �������������� (0-" << ksCount - 1 << "): ";

			while (!(cin >> index) || index < 0 || index >= ksCount) {
				LogToFile(to_string(index), logFile);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "�������� ������. ���������� �����: ";
				LogToFile("Error. Wrong index >:(", logFile);
			}
			LogToFile(to_string(index), logFile);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "1. �������� ���������� ���������� ������\n";
			cout << "2. ������� ��\n";
			string editChoice;
			getline(cin, editChoice);
			LogToFile(editChoice, logFile);

			while (!IsInteger(editChoice) || (stoi(editChoice) < 1 || stoi(editChoice) > 2)) {
				cout << "������� 1 ��� 2: ";
				LogToFile("Error. Try 1 or 2 >:(", logFile);
				getline(cin, editChoice);
				LogToFile(editChoice, logFile);
			}

			int choice = stoi(editChoice);
			if (choice == 1) {
				int newNumWorkFac;
				while (true) {
					newNumWorkFac = GetPositiveNumber("������� ����� ���������� ���������� ������: ", logFile);
					if (newNumWorkFac <= kss[index].GetNumFac()) {
						break;
					}
					cout << "���������� ���������� ������ ������ ���� ������ ��� ����� ������ ���������� ������.\n";
					LogToFile("Error. Ammount of working factories need to be below total >:(", logFile);
				}
				kss[index].SetNumWorkFac(newNumWorkFac);
				cout << "���������� ���������� ������ ���������.\n";
			}
			else if (choice == 2) {
				for (int i = index; i < ksCount - 1; i++) {
					kss[i] = kss[i + 1];
				}
				ksCount--;
				cout << "KC �������\n";
			}
			break;
		}
			  break;
		case 5: {
			if (pipeCount == 0) {
				cout << "��� ��������� ����\n";
			}
			else {
				cout << "������ ����:\n";
				for (int i = 0; i < pipeCount; ++i) {
					cout << "����� " << i << ":\n";
					cout << "  ��������: " << pipes[i].GetName() << "\n";
					cout << "  �����: " << pipes[i].GetLength() << "\n";
					cout << "  �������: " << pipes[i].GetDiameter() << "\n";
					cout << "  � �������: " << (pipes[i].GetInRepair() ? "��" : "���") << "\n";
				}
			}
			if (ksCount == 0) {
				cout << "��� ��������� ��\n";
			}
			else {
				cout << "������ ��:\n";
				for (int i = 0; i < ksCount; ++i) {
					cout << "�� " << i << ":\n";
					cout << "  ��������: " << kss[i].GetName() << "\n";
					cout << "  ���������� ������: " << kss[i].GetNumFac() << "\n";
					cout << "  ���������� ������� ������: " << kss[i].GetNumWorkFac() << "\n";
					cout << "  �������������: " << kss[i].GetEff() << "\n";
				}
			}
			break;
		case 6:
			SaveData(pipes, pipeCount, kss, ksCount);
			break;
		case 7:
			LoadData(pipes, pipeCount, kss, ksCount);
			break;
		case 8:
			cout << "�������� ������ ��� ������:\n";
			cout << "1. �����\n";
			cout << "2. ��\n";
			getline(cin, choose);
			LogToFile(choose, logFile);

			if (choose == "1") {
				SearchPipe(pipes, pipeCount, logFile);
			}
			else if (choose == "2") {
				SearchKS(kss, ksCount, logFile);
			}
			else {
				cout << "�������� �����.\n";
				LogToFile("Error. Wrong choice >:(", logFile);
			}
			break;
		case 9:
			return 0;
			break;
		default:
			cout << "������� ����� �� 1 �� 9" << endl;
			break;
		}

		}
	}
}