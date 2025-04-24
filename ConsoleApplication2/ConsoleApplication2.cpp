#include <iostream>
#include <fstream> 
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>
using namespace std;

int CheckForInt() {
    int value;
    while (true) {
        string str;
        cin >> str;
        istringstream temp(str);
        temp >> value;
        if (temp.fail() || !temp.eof()) {
            cout << "Некорректый тип данных.\n";
            cout << "Попробуйте снова: ";
            continue;
        }
        return value;
    }
}
int CheckFlightNumber(const string& filename) {
    ifstream file(filename);
    vector<int> existingNumbers;

    // Считываем существующие номера рейсов
    if (file.is_open()) {
        string line;
        char delimiter;
        while (getline(file, line)) {
            istringstream iss(line);
            int number;
            if (iss >> number >> delimiter) {
                existingNumbers.push_back(number);
            }
        }
        file.close();
    }

    while (true) {
        int input;
        input = CheckForInt();

        // Проверка длины и цифр
        if (input > 9999 || input < 1000) {
            cout << "Номер должен состоять ровно из 4 цифр. Попробуйте снова.\n";
            continue;
        }

        // Проверка на уникальность
        if (find(existingNumbers.begin(), existingNumbers.end(), input) != existingNumbers.end()) {
            cout << "Рейс с таким номером уже существует. Попробуйте снова.\n";
            continue;
        }

        return input;
    }
}
string CheckTypePlane() {
    while (true) {
        string type;
        cin >> type;
        if (type != "Грузовой" && type != "Пассажирский") {
            cout << "Некорректый тип данных.\n";
            cout << "Попробуйте снова: ";
            continue;
        }
        return type;
    }
}
string CheckCity() {
    // Список городов с аэропортами
    vector<string> validCities = {
        "Москва", "Санкт-Петербург", "Минск", "Новосибирск", "Екатеринбург",
        "Казань", "Сочи", "Адлер", "Краснодар", "Париж",
        "Лондон", "Токио", "Берлин", "Рим", "Нью-Йорк"
    };

    while (true) {
        string city;
        cin >> city;

        // Проверяем, есть ли город в списке допустимых
        if (find(validCities.begin(), validCities.end(), city) == validCities.end()) {
            cout << "Некорректный город.\nПопробуйте снова: ";
            continue;
        }
        return city;
    }
}
string CheckDepatureTime() {
    while (true) {
        regex timeFormat(R"(^([01][0-9]|2[0-3]):([0-5][0-9])$)");
        string time;
        cin >> time;
        if (!regex_match(time, timeFormat)) {
            cout << "Некорректый тип данных.\n";
            cout << "Попробуйте снова: ";
            continue;
        }
        return time;
    }
}


struct Information {
    int Number;
    string Type;
    string Point_Fly;
    string Departure_Time; // Время вылета
};

void createFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        cout << "Файл успешно создан." << endl;
        file << "1023 | Грузовой | Дублин | 12:00" << endl;
        file << "1152 | Пассажирский | Турция | 13:30" << endl;
        file << "8405 | Грузовой | Рим | 15:00" << endl;
        file << "2037 | Пассажирский | Москва | 16:45" << endl;
        file << "3043 | Грузовой | Нью-Йорк | 18:20" << endl;
        file << "4054 | Пассажирский | Лондон | 20:00" << endl;
        file << "5068 | Грузовой | Рим | 21:15" << endl;
        file << "6079 | Пассажирский | Берлин | 22:30" << endl;
        file << "7082 | Грузовой | Рим | 23:45" << endl;
        file << "8091 | Пассажирский | Сидней | 01:00" << endl;
        file << "9104 | Грузовой | Рим | 02:15" << endl;
        file << "1014 | Пассажирский | Мадрид | 03:30" << endl;
        file << "1113 | Грузовой | Рим | 04:45" << endl;
        file << "1219 | Пассажирский | Чикаго | 06:00" << endl;
        file << "1310 | Грузовой | Вашингтон | 07:15" << endl;
        file << "1415 | Пассажирский | Ванкувер | 08:30" << endl;
        file << "1516 | Грузовой | Рим | 09:45" << endl;
        file << "1617 | Пассажирский | Копенгаген | 11:00" << endl;
        file << "1718 | Грузовой | Стокгольм | 12:15" << endl;
        file << "1819 | Пассажирский | Гонконг | 13:30" << endl;
        file << "1918 | Грузовой | Шанхай | 14:45" << endl;
        file << "2015 | Пассажирский | Сеул | 16:00" << endl;
    }
    else {
        cout << "Не удалось создать файл." << endl;
        return;
    }
    file.close();
    // введены исходные данные
}

void viewFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        char ch;
        while (file.get(ch)) { cout << ch; }
        file.close();
    }
    else {
        cout << "Не удалось открыть файл." << endl;
        return;
    }
}

void Add(string filename) {
    ofstream file(filename, ofstream::app);
    if (file.is_open()) {
        Information Plain;
        cout << "Введите номер рейса: ";
        Plain.Number = CheckFlightNumber(filename);
        cout << "Введите тип самолета: ";
        Plain.Type = CheckTypePlane();
        cout << "Введите пункт прибытия: ";
        Plain.Point_Fly = CheckCity();
        cout << "Введите время вылета: ";
        Plain.Departure_Time = CheckDepatureTime();

        file << Plain.Number << " | "
            << Plain.Type << " | "
            << Plain.Point_Fly << " | "
            << Plain.Departure_Time << endl;

        cout << "Запись добавлена." << endl;
        file.close();
    }
    else {
        cout << "Не удалось открыть файл." << endl;
    }
}

void Redact(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    ofstream temp("temp.txt");
    int number;
    cout << "Введите номер рейса для редактирования: ";
    number = CheckForInt();

    string line;
    bool found = false;

    while (getline(file, line)) {
        istringstream Destroy(line);
        Information Plain;
        char delimiter;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            if (Plain.Number != number) {
                temp << Plain.Number << " | "
                    << Plain.Type << " | "
                    << Plain.Point_Fly << " | "
                    << Plain.Departure_Time << endl;
            }
            else {
                found = true;
                cout << "Введите номер рейса: ";
                Plain.Number = CheckFlightNumber(filename);
                cout << "Введите тип самолета: ";
                Plain.Type = CheckTypePlane();
                cout << "Введите пункт прибытия: ";
                Plain.Point_Fly = CheckCity();
                cout << "Введите время вылета: ";
                Plain.Departure_Time = CheckDepatureTime();

                temp << Plain.Number << " | "
                    << Plain.Type << " | "
                    << Plain.Point_Fly << " | "
                    << Plain.Departure_Time << endl;
            }
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Запись отредактирована." << endl;
    }
    else {
        remove("temp.txt");
        cout << "Запись не найдена." << endl;
    }
}

void Delete(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    ofstream temp("temp.txt");
    int number;
    cout << "Введите номер рейса для удаления: ";
    number = CheckForInt();

    string line;
    bool found = false;

    while (getline(file, line)) {
        istringstream Destroy(line);
        Information Plain;
        char delimiter;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            if (Plain.Number != number) {
                temp << Plain.Number << " | "
                    << Plain.Type << " | "
                    << Plain.Point_Fly << " | "
                    << Plain.Departure_Time << endl;
            }
            else {
                found = true;
            }
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Запись удалена." << endl;
    }
    else {
        remove("temp.txt");
        cout << "Запись не найдена." << endl;
    }
}

// Функция QuickSort
void QuickSort(int low, int high, Information arr[], const string& aimOfSort) {
    if (low < high) {
        int i = low;
        int j = high;

        // Определение пивота на основе aimOfSort
        string pivot;
        if (aimOfSort == "Departure_Time") pivot = arr[(low + high) / 2].Departure_Time;
        else if (aimOfSort == "Point_Fly") pivot = arr[(low + high) / 2].Point_Fly;
        else if (aimOfSort == "Type") pivot = arr[(low + high) / 2].Type;
        else pivot = to_string(arr[(low + high) / 2].Number);

        while (i <= j) {
            while ((aimOfSort == "Departure_Time" && arr[i].Departure_Time < pivot) ||
                (aimOfSort == "Point_Fly" && arr[i].Point_Fly < pivot) ||
                (aimOfSort == "Type" && arr[i].Type < pivot) ||
                (aimOfSort == "Number" && to_string(arr[i].Number) < pivot)) {
                i++;
            }

            while ((aimOfSort == "Departure_Time" && arr[j].Departure_Time > pivot) ||
                (aimOfSort == "Point_Fly" && arr[j].Point_Fly > pivot) ||
                (aimOfSort == "Type" && arr[j].Type > pivot) ||
                (aimOfSort == "Number" && to_string(arr[j].Number) > pivot)) {
                j--;
            }

            if (i <= j) {
                if (i != j) {
                    swap(arr[i], arr[j]); // Обмен элементов
                }
                i++;
                j--;
            }
        }

        QuickSort(low, j, arr, aimOfSort); // Рекурсивная сортировка левой части
        QuickSort(i, high, arr, aimOfSort); // Рекурсивная сортировка правой части
    }
}
// Функция для сортировки рейсов в файле
bool SortFileWithQuickSort(const string& filename) {
    ifstream inFile(filename);
    bool sortByNumber = false;
    if (!inFile.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return false;
    }

    // Чтение данных из файла в массив
    Information Plains[100];
    int count = 0;
    string line;
    char delimiter;

    while (getline(inFile, line)) {
        istringstream Destroy(line);
        Information Plain;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            Plains[count++] = Plain;
        }
    }
    inFile.close();

    // Ввод цели сортировки
    string aimOfSort;
    while (true) {
        cout << "Введите цель сортировки (Number, Type, Point_Fly, Departure_Time): ";
        cin >> aimOfSort;

        // Проверка корректности ввода
        if (aimOfSort == "Number" || aimOfSort == "Type" ||
            aimOfSort == "Point_Fly" || aimOfSort == "Departure_Time") {
            if (aimOfSort == "Number") sortByNumber = true;
            break;
        }
        cout << "Некорректная цель сортировки. Попробуйте снова." << endl;
    }

    // Сортировка данных
    QuickSort(0, count - 1, Plains, aimOfSort);

    // Запись отсортированных данных обратно в файл
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Не удалось записать в файл." << endl;
        return false;
    }

    for (int i = 0; i < count; i++) {
        outFile << Plains[i].Number << " | "
            << Plains[i].Type << " | "
            << Plains[i].Point_Fly << " | "
            << Plains[i].Departure_Time << endl;
    }
    outFile.close();

    cout << "Файл успешно отсортирован по полю: " << aimOfSort << endl;
    return sortByNumber;
}

// Функция ShellSort
void ShellSort(Information arr[], int size, const string& aimOfSort) {
    // Начальная длина шага (gap)
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Итерация по каждому элементу массива
        for (int i = gap; i < size; i++) {
            Information temp = arr[i]; // Элемент для вставки
            int j = i;

            // Динамическое сравнение элементов в зависимости от aimOfSort
            while (j >= gap && (
                (aimOfSort == "Departure_Time" && arr[j - gap].Departure_Time > temp.Departure_Time) ||
                (aimOfSort == "Point_Fly" && arr[j - gap].Point_Fly > temp.Point_Fly) ||
                (aimOfSort == "Type" && arr[j - gap].Type > temp.Type) ||
                (aimOfSort == "Number" && arr[j - gap].Number > temp.Number))) {
                arr[j] = arr[j - gap]; // Сдвигаем элемент вправо
                j -= gap;             // Уменьшаем индекс на размер промежутка
            }

            // Вставка элемента на его правильную позицию
            arr[j] = temp;
        }
    }
}
// Функция для сортировки рейсов в файле
bool SortFileWithShellSort(const string& filename) {
    bool sortByNumber = false;
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return false;
    }

    // Чтение данных из файла в массив
    Information Plains[100];
    int count = 0;
    string line;
    char delimiter;

    while (getline(inFile, line)) {
        istringstream Destroy(line);
        Information Plain;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            Plains[count++] = Plain;
        }
    }
    inFile.close();

    // Ввод цели сортировки
    string aimOfSort;
    while (true) {
        cout << "Введите цель сортировки (Number, Type, Point_Fly, Departure_Time): ";
        cin >> aimOfSort;

        // Проверка корректности ввода
        if (aimOfSort == "Number" || aimOfSort == "Type" ||
            aimOfSort == "Point_Fly" || aimOfSort == "Departure_Time") {
            if (aimOfSort == "Number") sortByNumber = true;
            break;
        }
        cout << "Некорректная цель сортировки. Попробуйте снова." << endl;
    }

    // Сортировка данных
    ShellSort(Plains, count, aimOfSort);

    // Запись отсортированных данных обратно в файл
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Не удалось записать в файл." << endl;
        return false;
    }

    for (int i = 0; i < count; i++) {
        outFile << Plains[i].Number << " | "
            << Plains[i].Type << " | "
            << Plains[i].Point_Fly << " | "
            << Plains[i].Departure_Time << endl;
    }
    outFile.close();

    cout << "Файл успешно отсортирован по полю: " << aimOfSort << endl;
    return sortByNumber;
}

void LinearSearch(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    cout << "Введите номер рейса для поиска информации: ";
    int number;
    number = CheckForInt();

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream Destroy(line);
        Information Plain;
        char delimiter;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            if (Plain.Number == number) {
                cout << line << endl;
                found = true;
            }
        }
    }
    if (found != true) {
        cout << "Запись не найдена." << endl;
    }
}
void BinarySearch(string filename) {
    ifstream inFile(filename);
    bool sortByNumber = false;
    if (!inFile.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    // Чтение данных из файла в массив
    Information Plains[100];
    int count = 0;
    string line;
    char delimiter;

    while (getline(inFile, line)) {
        istringstream Destroy(line);
        Information Plain;
        if (Destroy >> Plain.Number >> delimiter
            >> Plain.Type >> delimiter
            >> Plain.Point_Fly >> delimiter
            >> Plain.Departure_Time) {
            Plains[count++] = Plain;
        }
    }
    inFile.close();

    int searchNumber;
    cout << "Введите номер рейса который хотите найти: ";
    searchNumber = CheckForInt();

    int low = 0;
    int high = count - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (Plains[mid].Number == searchNumber) {
            cout << "Найден рейс: "
                << Plains[mid].Number << " | "
                << Plains[mid].Type << " | "
                << Plains[mid].Point_Fly << " | "
                << Plains[mid].Departure_Time << endl;
            found = true;
            break;
        }
        else if (Plains[mid].Number < searchNumber) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Рейс с номером " << searchNumber << " не найден." << endl;
    }
}


void run()
{
    SetConsoleCP(1251); // Установка кодовой страницы ввода
    SetConsoleOutputCP(1251); // Установка кодовой страницы вывода
    setlocale(LC_ALL, "Russian");
    string filename = "Airoport.txt";
    int choice = 0;
    bool binaryIsOk = false;
    do {
        cout << "=========================================\n";
        cout << "|                 МЕНЮ                  |\n";
        cout << "=========================================\n";
        cout << "|  0. Создание/Пересоздание             |\n";
        cout << "|  1. Просмотр                          |\n";
        cout << "|  2. Добавление                        |\n";
        cout << "|  3. Редактирование                    |\n";
        cout << "|  4. Удаление                          |\n";
        cout << "|  5. QuickSort                         |\n";
        cout << "|  6. ShellSort                         |\n";
        cout << "|  7. LinearSearch                      |\n";
        cout << "|  8. BinarySearch                      |\n";
        cout << "|  9. Найти рейсы                       |\n";
        cout << "|  10. Выход                            |\n";
        cout << "=========================================\n";
        cout << "Выберите опцию: ";
        choice = CheckForInt();

        switch (choice) {
        case 0:
            createFile(filename);
            cout << "\n";
            break;
        case 1:
            viewFile(filename);
            cout << "\n";
            break;
        case 2:
            Add(filename);
            cout << "\n";
            break;
        case 3:
            Redact(filename);
            cout << "\n";
            break;
        case 4:
            Delete(filename);
            cout << "\n";
            break;
        case 5:
            binaryIsOk = SortFileWithQuickSort(filename);
            cout << "\n";
            break;
        case 6:
            binaryIsOk = SortFileWithShellSort(filename);
            cout << "\n";
            break;
        case 7:
            LinearSearch(filename);
            cout << "\n";
            break;
        case 8:
            if (binaryIsOk) BinarySearch(filename);
            else cout << "Массив не отсортирован.";
            cout << "\n";
            break;
        case 9:
            exception;
            cout << "\n";
            break;
        case 10:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    } while (choice != 10);
    // выполнение задания	
    cout << "xui";
}

int main()
{
    run();
    return 0;
}

//void Sort(string filename) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Не удалось открыть файл." << endl;
//        return;
//    }
//
//    ofstream temp("temp.txt");
//    Information Plains[100];
//    int count = 0;
//    Information Plain;
//    string line;
//    char delimiter;
//
//    cout << "Пункт назначения: ";
//    string point;
//    point = CheckCity();
//    while (getline(file, line)) {
//        istringstream Destroy(line);
//        if (Destroy >> Plain.Number >> delimiter
//            >> Plain.Type >> delimiter
//            >> Plain.Point_Fly >> delimiter
//            >> Plain.Departure_Time && Plain.Point_Fly == point) {
//            Plains[count++] = Plain;
//        }
//    }
//    file.close();
//
//    int choice;
//    cout << "Выберите параметр для сортировки:\n";
//    cout << "1. Методом прямого выбора.\n";
//    cout << "2. QuickSort\n";
//    choice = CheckForInt();
//
//    switch (choice) {
//    case 1:
//        for (int i = 0; i < count - 1; i++) {
//            int m = i;
//            for (int j = i + 1; j < count; j++)
//                if (Plains[j].Departure_Time < Plains[m].Departure_Time) m = j;
//            Information r = Plains[m]; // Переставляем элементы
//            Plains[m] = Plains[i];
//            Plains[i] = r;
//        }
//        break;
//    case 2:
//        QuickSort(0, count - 1, Plains);
//        break;
//    default:
//        cout << "Некорректный выбор.";
//    }
//
//    for (int i = 0; i < count; i++) {
//        temp << Plains[i].Number << " | "
//            << Plains[i].Type << " | "
//            << Plains[i].Point_Fly << " | "
//            << Plains[i].Departure_Time << endl;
//    }
//    temp.close();
//
//    cout << "Вот возможные рейсы: " << endl;
//    ifstream show("temp.txt");
//    if (show.is_open()) {
//        char ch;
//        while (show.get(ch)) { cout << ch; }
//        show.close();
//    }
//
//    string searchTime;
//    cout << "Введите время вылета для поиска: ";
//    searchTime = CheckDepatureTime();
//
//    int index = BinarySearch(Plains, count, searchTime);
//    if (index != -1) {
//        cout << "Рейс найден: " << Plains[index].Number << " | "
//            << Plains[index].Type << " | "
//            << Plains[index].Point_Fly << " | "
//            << Plains[index].Departure_Time << endl;
//    }
//    else {
//        cout << "Рейс с таким временем вылета не найден." << endl;
//    }
//    //remove("temp.txt");
//}
