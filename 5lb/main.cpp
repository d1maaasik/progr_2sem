#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Перечисление для типа носителя
enum MediaType {
    VINYL,      // грампластинка
    CASSETTE,   // аудиокассета
    CD          // лазерный диск
};

// Структура музыкального товара
struct MusicProduct {
    MediaType media;     // тип носителя
    string title;        // название
    string artist;       // исполнитель
    int catalogNumber;   // порядковый номер в каталоге
    double duration;     // время звучания (в минутах)
    double price;        // цена
};

// Глобальные переменные
vector<MusicProduct*> catalog;  // каталог товаров (используем vector для удобства)

// Функции
void displayMenu();
void loadFromFile();
void saveToFile();
void displayAll();
void searchByField();
void addProduct();
void deleteProduct();
void clearMemory();

// Вспомогательные функции
MediaType selectMediaType();
string mediaTypeToString(MediaType type);
void printProduct(const MusicProduct* product);

int main() {
    setlocale(LC_ALL, "Russian");
    
    int choice;
    do {
        displayMenu();
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: loadFromFile(); break;
            case 2: displayAll(); break;
            case 3: searchByField(); break;
            case 4: addProduct(); break;
            case 5: deleteProduct(); break;
            case 6: saveToFile(); break;
            case 0: cout << "Выход из программы.\n"; break;
            default: cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
    clearMemory();
    return 0;
}

void displayMenu() {
    cout << "\n=== Меню управления каталогом музыкальных товаров ===\n";
    cout << "1. Загрузить каталог из файла\n";
    cout << "2. Показать все товары\n";
    cout << "3. Поиск товара\n";
    cout << "4. Добавить новый товар\n";
    cout << "5. Удалить товар\n";
    cout << "6. Сохранить каталог в файл\n";
    cout << "0. Выход\n";
}

void loadFromFile() {
    string filename;
    cout << "Введите имя файла для загрузки: ";
    getline(cin, filename);
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }
    
    // Очищаем текущий каталог
    clearMemory();
    catalog.clear();
    
    MusicProduct* product;
    int media;
    while (file >> media) {
        product = new MusicProduct();
        product->media = static_cast<MediaType>(media);
        file.ignore();
        getline(file, product->title);
        getline(file, product->artist);
        file >> product->catalogNumber;
        file >> product->duration;
        file >> product->price;
        file.ignore();
        
        catalog.push_back(product);
    }
    
    file.close();
    cout << "Загружено " << catalog.size() << " товаров.\n";
}

void saveToFile() {
    if (catalog.empty()) {
        cout << "Каталог пуст. Нечего сохранять.\n";
        return;
    }
    
    string filename;
    cout << "Введите имя файла для сохранения: ";
    getline(cin, filename);
    
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка создания файла!\n";
        return;
    }
    
    for (const auto& product : catalog) {
        file << product->media << endl;
        file << product->title << endl;
        file << product->artist << endl;
        file << product->catalogNumber << endl;
        file << product->duration << endl;
        file << product->price << endl;
    }
    
    file.close();
    cout << "Каталог сохранен (" << catalog.size() << " товаров).\n";
}

void displayAll() {
    if (catalog.empty()) {
        cout << "Каталог пуст.\n";
        return;
    }
    
    cout << "\n=== Полный каталог музыкальных товаров ===\n";
    cout << left << setw(5) << "№" << setw(15) << "Тип" << setw(25) << "Название" 
         << setw(25) << "Исполнитель" << setw(10) << "Каталог" 
         << setw(10) << "Длит." << setw(10) << "Цена" << endl;
    cout << string(100, '-') << endl;
    
    for (size_t i = 0; i < catalog.size(); ++i) {
        cout << setw(5) << i+1;
        printProduct(catalog[i]);
    }
}

void searchByField() {
    if (catalog.empty()) {
        cout << "Каталог пуст. Нечего искать.\n";
        return;
    }
    
    cout << "\nПоиск по:\n";
    cout << "1. Типу носителя\n";
    cout << "2. Названию\n";
    cout << "3. Исполнителю\n";
    cout << "4. Номеру в каталоге\n";
    cout << "5. Времени звучания\n";
    cout << "6. Цене\n";
    cout << "Выберите поле для поиска: ";
    
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    bool found = false;
    switch (choice) {
        case 1: {
            MediaType type = selectMediaType();
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->media == type) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        case 2: {
            string title;
            cout << "Введите название: ";
            getline(cin, title);
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->title.find(title) != string::npos) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        case 3: {
            string artist;
            cout << "Введите исполнителя: ";
            getline(cin, artist);
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->artist.find(artist) != string::npos) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        case 4: {
            int number;
            cout << "Введите номер в каталоге: ";
            cin >> number;
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->catalogNumber == number) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        case 5: {
            double duration;
            cout << "Введите время звучания: ";
            cin >> duration;
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->duration == duration) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        case 6: {
            double price;
            cout << "Введите цену: ";
            cin >> price;
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i]->price == price) {
                    if (!found) {
                        cout << "\nРезультаты поиска:\n";
                        found = true;
                    }
                    cout << i+1 << ". ";
                    printProduct(catalog[i]);
                }
            }
            break;
        }
        default:
            cout << "Неверный выбор.\n";
            return;
    }
    
    if (!found) {
        cout << "Товары не найдены.\n";
    }
}

void addProduct() {
    MusicProduct* product = new MusicProduct();
    
    cout << "\nДобавление нового товара:\n";
    product->media = selectMediaType();
    
    cout << "Введите название: ";
    getline(cin, product->title);
    
    cout << "Введите исполнителя: ";
    getline(cin, product->artist);
    
    cout << "Введите номер в каталоге: ";
    cin >> product->catalogNumber;
    
    cout << "Введите время звучания (в минутах): ";
    cin >> product->duration;
    
    cout << "Введите цену: ";
    cin >> product->price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    catalog.push_back(product);
    cout << "Товар добавлен в каталог.\n";
}

void deleteProduct() {
    if (catalog.empty()) {
        cout << "Каталог пуст. Нечего удалять.\n";
        return;
    }
    
    displayAll();
    cout << "Введите номер товара для удаления (1-" << catalog.size() << "): ";
    int index;
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (index < 1 || index > static_cast<int>(catalog.size())) {
        cout << "Неверный номер.\n";
        return;
    }
    
    delete catalog[index-1];
    catalog.erase(catalog.begin() + index - 1);
    cout << "Товар удален.\n";
}

void clearMemory() {
    for (auto& product : catalog) {
        delete product;
    }
    catalog.clear();
}

MediaType selectMediaType() {
    int choice;
    cout << "Выберите тип носителя:\n";
    cout << "1. Грампластинка\n";
    cout << "2. Аудиокассета\n";
    cout << "3. Лазерный диск\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: return VINYL;
        case 2: return CASSETTE;
        case 3: return CD;
        default:
            cout << "Неверный выбор. Установлен тип по умолчанию (грампластинка).\n";
            return VINYL;
    }
}

string mediaTypeToString(MediaType type) {
    switch (type) {
        case VINYL: return "Грампластинка";
        case CASSETTE: return "Аудиокассета";
        case CD: return "Лазерный диск";
        default: return "Неизвестно";
    }
}

void printProduct(const MusicProduct* product) {
    cout << left << setw(15) << mediaTypeToString(product->media)
         << setw(25) << product->title
         << setw(25) << product->artist
         << setw(10) << product->catalogNumber
         << setw(10) << fixed << setprecision(2) << product->duration
         << setw(10) << product->price << endl;
}