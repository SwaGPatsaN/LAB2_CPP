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
	cout << "Введите имя файла для сохранения данных: \n";
	string filename;
	getline(cin, filename);

	ofstream outFile(filename);
	if (!outFile) {
		cout << "Ошибка при открытии файла для сохранения данных.\n";
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
	cout << "Данные успешно сохранены в " << filename << ".\n";
}

void LoadData(pipe pipes[], int& pipeCount, ks kss[], int& ksCount) {
    cout << "Введите имя файла для загрузки данных: ";
    string filename;
    getline(cin, filename);

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка при открытии файла для загрузки данных.\n";
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
	cout << "Данные успешно загружены из " << filename << ".\n";
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
			cout << "Ввод не должен быть пустым. Попробуйте снова: ";
			LogToFile("Error. Empty insert >:(", logFile);
			continue;
		}
		if (IsInteger(input)) {
			value = stoi(input);
			if (value > 0) return value;
		}
		std::cout << "Введите положительное число \n";
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
		cout << "Введите y(да) или n(нет)\n";
		LogToFile("Error. Try y or n >:(", logFile);
	}
}

void SearchPipe(pipe pipes[], int pipeCount, ofstream& logFile) {
	cout << "Выберите фильтр для поиска труб:\n";
	cout << "1. По названию\n";
	cout << "2. По статусу ремонта\n";

	string choice;
	getline(cin, choice);
	LogToFile(choice, logFile);

	if (choice == "1") {
		string searchName;
		cout << "Введите название трубы: ";
		getline(cin, searchName);
		LogToFile(searchName, logFile);
		for (int i = 0; i < pipeCount; ++i) {
			if (pipes[i].GetName().find(searchName) != string::npos) {
				cout << "Найдена труба:\n";
				cout << pipes[i].ToString(); 
			}
		}
	}
	else if (choice == "2") {
		string status;
		cout << "Введите статус ремонта (y/n): ";
		getline(cin, status);
		LogToFile(status, logFile);
		while (true) {
			if (status == "y" || status == "Y" || status == "n" || status == "N") {
				break;
			}
			cout << "Введите верный статус (y/n): ";
			LogToFile("Error.Try y or n >:(", logFile);
			getline(cin, status);
			LogToFile(status, logFile);
		}
		bool inRepair = (status == "y" || status == "Y");
		for (int i = 0; i < pipeCount; ++i) {
			if (pipes[i].GetInRepair() == inRepair) {
				cout << "Найдена труба:\n";
				cout << pipes[i].ToString();
			}
		}
	}
	else {
		cout << "Неверный выбор.\n";
		LogToFile("Error. Wrong choice >:(", logFile);
	}
}

void SearchKS(ks kss[], int ksCount, ofstream& logFile) {
	cout << "Выберите фильтр для поиска КС:\n";
	cout << "1. По названию\n";
	cout << "2. По проценту незадействованных цехов\n";

	string choice;
	getline(cin, choice);
	LogToFile(choice, logFile);

	if (choice == "1") {
		string searchName;
		cout << "Введите название КС для поиска: ";
		getline(cin, searchName);
		LogToFile(searchName, logFile);
		for (int i = 0; i < ksCount; ++i) {
			if (kss[i].GetName().find(searchName) != string::npos) {
				cout << "Найдена КС:\n";
				cout << kss[i].ToString(); 
			}
		}
	}
	else if (choice == "2") {
		int percent;
		cout << "Введите процент незадействованных цехов: ";
		cin >> percent;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		LogToFile(to_string(percent), logFile);
		for (int i = 0; i < ksCount; ++i) {
			int unusedPercent = 100 * (kss[i].GetNumFac() - kss[i].GetNumWorkFac()) / kss[i].GetNumFac();
			if (unusedPercent == percent) {
				cout << "Найдена КС:\n";
				cout << kss[i].ToString();
			}
		}
	}
	else {
		cout << "Неверный выбор.\n";
		LogToFile("Error. Wrong choice >:(", logFile);
	}
}

void PacEditPipes(pipe pipes[], int pipeCount, ofstream& logFile) {
	cout << "Список труб:\n";
	for (int i = 0; i < pipeCount; ++i) {
		cout << i << ": " << pipes[i].GetName() << endl;
	}

	cout << "Введите индексы труб для редактирования (через запятую, без пробелов): ";
	string input;
	getline(cin, input);
	LogToFile(input, logFile);

	stringstream ss(input);
	string indexStr;
	bool inRepair = GetRepairStatus("Находятся ли трубы в ремонте?: ", logFile);
	while (getline(ss, indexStr, ',')) {
		int index = stoi(indexStr);
		if (index >= 0 && index < pipeCount) {
			pipes[index].SetInRepair(inRepair);
			cout << "Статус ремонта трубы " << pipes[index].GetName() << " обновлен.\n";
		}
		else {
			cout << "Неверный индекс: " << index << endl;
			LogToFile("Error. Empty index: " + to_string(index), logFile);
		}
	}
}

int main() {
	ofstream logFile("C:/Users/05bla/Downloads/LAB2/LAB2/LAB2/log.txt", ios::app); // Открываем файл для добавления
	if (!logFile) {
		cerr << "Ошибка при открытии файла для логирования.\n";
		return 1; // Завершаем программу в случае ошибки
	}
	string choose;
	pipe pipes[MAX_PIPES];
	ks kss[MAX_KS];
	int pipeCount = 0;
	int ksCount = 0;
	while (true) {
		setlocale(LC_ALL, (""));
		cout << "1. Создать трубу\n";
		cout << "2. Создать КС\n";
		cout << "3. Редактирование труб\n";
		cout << "4. Редактирование КС\n";
		cout << "5. Показать все объекты\n";
		cout << "6. Сохранить\n";
		cout << "7. Загрузить\n";
		cout << "8. Поиск\n";
		cout << "9. Выход\n";
		getline(cin, choose);
		LogToFile(choose, logFile);
		while (!IsInteger(choose)) {
			cout << "Введите цифру от 1 до 9" << endl;
			LogToFile("Error. Try 1 to 9 >:(", logFile);
			getline(cin, choose);
			LogToFile(choose, logFile);
		}

		switch (stoi(choose)) {
		case 1: {
			if (pipeCount >= MAX_PIPES) {
				cout << "Достигнут максимум труб" << endl;
				break;
			}
			string name;
			cout << "Введите название трубы: ";
			while (true) {
				getline(cin, name);
				LogToFile(name, logFile);
				if (name.empty()) {
					cout << "Имя не может быть пустой строкой. Попробуйте снова: ";
					LogToFile("Error. Name can't be empty >:(", logFile);
				}
				else {
					break;
				}
			}

			int length = GetPositiveNumber("Введите длину трубы: ", logFile);
			int diameter = GetPositiveNumber("Введите диаметр трубы: ", logFile);
			bool inRepair = GetRepairStatus("Находится ли труба в ремонте? (y/n): ", logFile);

			pipes[pipeCount] = pipe(name, length, diameter, inRepair);
			pipeCount++;
			cout << "Труба создана\n";
		}
			  break;
		case 2: {
			if (ksCount >= MAX_KS) {
				cout << "Достигнуто максималльное количество КС" << endl;
				break;
			}
			string name;
			cout << "Введите название KС: ";
			while (true) {
				getline(cin, name);
				LogToFile(name, logFile);
				if (name.empty()) {
					cout << "Имя не может быть пустой строкой. Попробуйте снова: ";
					LogToFile("Error.Name can't be empty >:(", logFile);
				}
				else {
					break;
				}
			}
			int NumFac = GetPositiveNumber("Введите количество фабрик: ", logFile);
			int NumWorkFac;
			while (true) {
				NumWorkFac = GetPositiveNumber("Введите количество работающих фабрик: ", logFile);
				if (NumWorkFac <= NumFac) {
					break;
				}
				cout << "Количество работаюих фабрик должно быть меньше общего\n";
				LogToFile("Error. Ammount of working factories need to be below total >:(", logFile);
			}

			int eff;
			while (true) {
				eff = GetPositiveNumber("Введите эффективность КС (0-100): ", logFile);
				if (eff >= 0 && eff <= 100) {
					break;
				}
				cout << "Введите число от 0 до 100\n";
				LogToFile("Error. Try 0 to 100 >:(", logFile);
			}

			kss[ksCount] = ks(name, NumFac, NumWorkFac, eff);
			ksCount++;
			cout << "КС создана\n";
		}
			  break;
		case 3: {
			if (pipeCount == 0) {
				cout << "Нет труб для редактирования\n";
				break;
			}
			string choice;
			cout << "1. Редактировать одну трубу\n";
			cout << "2. Пакетное редактирование труб\n";
			getline(cin, choice);
			LogToFile((choice), logFile);


			if (choice == "1") {
				if (pipeCount == 0) {
					cout << "Нет труб для редактирования\n";
					break;
				}
				string indexs;
				cout << "Введите индекс трубы для редактирования (0-" << pipeCount - 1 << "): ";
				getline(cin, indexs);
				LogToFile(indexs, logFile);


				if (IsInteger(indexs)) {
					if (stoi(indexs) < 0 || stoi(indexs) >= pipeCount) {
						cout << "Неверный индекс.\n";
						break;
					}
					int index = stoi(indexs);
					cout << "1. Изменить статус починки\n";
					cout << "2. Удалить трубу\n";
					getline(cin, choice);
					LogToFile(choice, logFile);

					if (choice == "1") {
						pipes[index].SetInRepair(GetRepairStatus("Находится ли труба в ремонте?: ", logFile));
						cout << "Статус ремонта трубы обновлен.\n";
					}
					else if (choice == "2") {
						for (int i = index; i < pipeCount - 1; ++i) {
							pipes[i] = pipes[i + 1]; // Сдвигаем элементы массива влево
						}
						pipeCount--; // Уменьшаем счетчик труб
						cout << "Труба удалена.\n";
						LogToFile("Труба удалена", logFile);
					}
					else {
						cout << "Неверный выбор.\n";
						LogToFile("Ошибка: Неверный выбор при редактировании одной трубы.", logFile);
					}

				}
				}
				else if (choice == "2") {
					PacEditPipes(pipes, pipeCount, logFile);
				}
				else {
					cout << "Неверный выбор.\n";
					LogToFile("Error. Wrong choice >:(", logFile);
				}
			}
			break;
		case 4: {
			if (ksCount == 0) {
				cout << "Нет КС для редактирования\n";
				break;
			}
			int index;
			cout << "Введите индекс КС для редактирования (0-" << ksCount - 1 << "): ";

			while (!(cin >> index) || index < 0 || index >= ksCount) {
				LogToFile(to_string(index), logFile);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Неверный индекс. Попробуйте снова: ";
				LogToFile("Error. Wrong index >:(", logFile);
			}
			LogToFile(to_string(index), logFile);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "1. Изменить количество работающих фабрик\n";
			cout << "2. Удалить КС\n";
			string editChoice;
			getline(cin, editChoice);
			LogToFile(editChoice, logFile);

			while (!IsInteger(editChoice) || (stoi(editChoice) < 1 || stoi(editChoice) > 2)) {
				cout << "Введите 1 или 2: ";
				LogToFile("Error. Try 1 or 2 >:(", logFile);
				getline(cin, editChoice);
				LogToFile(editChoice, logFile);
			}

			int choice = stoi(editChoice);
			if (choice == 1) {
				int newNumWorkFac;
				while (true) {
					newNumWorkFac = GetPositiveNumber("Введите новое количество работающих фабрик: ", logFile);
					if (newNumWorkFac <= kss[index].GetNumFac()) {
						break;
					}
					cout << "Количество работающих фабрик должно быть меньше или равно общему количеству фабрик.\n";
					LogToFile("Error. Ammount of working factories need to be below total >:(", logFile);
				}
				kss[index].SetNumWorkFac(newNumWorkFac);
				cout << "Количество работающих фабрик обновлено.\n";
			}
			else if (choice == 2) {
				for (int i = index; i < ksCount - 1; i++) {
					kss[i] = kss[i + 1];
				}
				ksCount--;
				cout << "KC удалена\n";
			}
			break;
		}
			  break;
		case 5: {
			if (pipeCount == 0) {
				cout << "Нет созданных труб\n";
			}
			else {
				cout << "Список труб:\n";
				for (int i = 0; i < pipeCount; ++i) {
					cout << "Труба " << i << ":\n";
					cout << "  Название: " << pipes[i].GetName() << "\n";
					cout << "  Длина: " << pipes[i].GetLength() << "\n";
					cout << "  Диаметр: " << pipes[i].GetDiameter() << "\n";
					cout << "  В ремонте: " << (pipes[i].GetInRepair() ? "Да" : "Нет") << "\n";
				}
			}
			if (ksCount == 0) {
				cout << "Нет созданных КС\n";
			}
			else {
				cout << "Список КС:\n";
				for (int i = 0; i < ksCount; ++i) {
					cout << "КС " << i << ":\n";
					cout << "  Название: " << kss[i].GetName() << "\n";
					cout << "  Количество фабрик: " << kss[i].GetNumFac() << "\n";
					cout << "  Количество рабочих фабрик: " << kss[i].GetNumWorkFac() << "\n";
					cout << "  Эффективность: " << kss[i].GetEff() << "\n";
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
			cout << "Выберите объект для поиска:\n";
			cout << "1. Труба\n";
			cout << "2. КС\n";
			getline(cin, choose);
			LogToFile(choose, logFile);

			if (choose == "1") {
				SearchPipe(pipes, pipeCount, logFile);
			}
			else if (choose == "2") {
				SearchKS(kss, ksCount, logFile);
			}
			else {
				cout << "Неверный выбор.\n";
				LogToFile("Error. Wrong choice >:(", logFile);
			}
			break;
		case 9:
			return 0;
			break;
		default:
			cout << "Введите цифру от 1 до 9" << endl;
			break;
		}

		}
	}
}