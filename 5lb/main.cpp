#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <windows.h> 
// перечисление типов носителей
enum MediaType {
    VINYL,
    CASSETTE,
    CD
};

// структура музыкального товара
struct MusicProduct {
    MediaType media;      // тип носителя
    std::string title;    // название
    std::string artist;   // исполнитель
    int catalogNumber;    // номер в каталоге
    double duration;      // длительность
    double price;         // цена
};

// глобальный каталог товаров
std::vector<MusicProduct*> catalog;

// прототипы функций
void displayMenu();
void loadFromFile();
void saveToFile();
void displayAll();
void searchByField();
void addProduct();
void deleteProduct();
void clearMemory();
MediaType selectMediaType();
std::string mediaTypeToString(MediaType type);
void printProduct(const MusicProduct* product);

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    do {
        displayMenu(); // вывод меню
        std::cout << "выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: loadFromFile(); break;
            case 2: displayAll(); break;
            case 3: searchByField(); break;
            case 4: addProduct(); break;
            case 5: deleteProduct(); break;
            case 6: saveToFile(); break;
            case 0: std::cout << "выход.\n"; break;
            default: std::cout << "неверный выбор.\n";
        }
    } while (choice != 0);

    clearMemory(); // освобождение памяти
    return 0;
}

void displayMenu() {
    std::cout << "\n=== каталог музыкальных товаров ===\n";
    std::cout << "1. загрузить из файла\n";
    std::cout << "2. показать все\n";
    std::cout << "3. поиск\n";
    std::cout << "4. добавить\n";
    std::cout << "5. удалить\n";
    std::cout << "6. сохранить\n";
    std::cout << "0. выход\n";
}

void loadFromFile() {
    std::string filename;
    std::cout << "имя файла: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file) {
        std::cout << "ошибка открытия файла.\n";
        return;
    }

    clearMemory(); // очистка старых данных

    int media;
    while (file >> media) {
        MusicProduct* p = new MusicProduct();
        p->media = static_cast<MediaType>(media);
        file.ignore();
        std::getline(file, p->title);
        std::getline(file, p->artist);
        file >> p->catalogNumber >> p->duration >> p->price;
        file.ignore();
        catalog.push_back(p); // добавление в каталог
    }

    std::cout << "загружено: " << catalog.size() << "\n";
}

void saveToFile() {
    std::string filename;
    std::cout << "имя файла: ";
    std::getline(std::cin, filename);

    std::ofstream file(filename);
    if (!file) {
        std::cout << "ошибка создания файла.\n";
        return;
    }

    // запись всех товаров
    for (auto p : catalog) {
        file << p->media << "\n"
             << p->title << "\n"
             << p->artist << "\n"
             << p->catalogNumber << "\n"
             << p->duration << "\n"
             << p->price << "\n";
    }

    std::cout << "сохранено.\n";
}

void displayAll() {
    if (catalog.empty()) {
        std::cout << "каталог пуст.\n";
        return;
    }

    // вывод всех элементов
    for (size_t i = 0; i < catalog.size(); i++) {
        std::cout << i + 1 << ". ";
        printProduct(catalog[i]);
    }
}

void searchByField() {
    std::string keyword;
    std::cout << "введите название для поиска: ";
    std::getline(std::cin, keyword);

    // поиск по названию
    for (auto p : catalog) {
        if (p->title.find(keyword) != std::string::npos) {
            printProduct(p);
        }
    }
}

void addProduct() {
    MusicProduct* p = new MusicProduct();

    p->media = selectMediaType();

    std::cout << "название: ";
    std::getline(std::cin, p->title);

    std::cout << "исполнитель: ";
    std::getline(std::cin, p->artist);

    std::cout << "номер в каталоге: ";
    std::cin >> p->catalogNumber;

    std::cout << "длительность: ";
    std::cin >> p->duration;

    std::cout << "цена: ";
    std::cin >> p->price;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    catalog.push_back(p); // добавление в вектор
    std::cout << "добавлено.\n";
}

void deleteProduct() {
    displayAll();
    std::cout << "номер для удаления: ";
    int index;
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (index < 1 || index > (int)catalog.size()) {
        std::cout << "неверный номер.\n";
        return;
    }

    delete catalog[index - 1]; // освобождение памяти
    catalog.erase(catalog.begin() + index - 1);
    std::cout << "удалено.\n";
}

void clearMemory() {
    // удаление всех элементов
    for (auto p : catalog)
        delete p;
    catalog.clear();
}

MediaType selectMediaType() {
    int choice;
    std::cout << "1 - винил\n2 - кассета\n3 - cd\nвыбор: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: return VINYL;
        case 2: return CASSETTE;
        case 3: return CD;
        default: return VINYL;
    }
}

std::string mediaTypeToString(MediaType type) {
    switch (type) {
        case VINYL: return "винил";
        case CASSETTE: return "кассета";
        case CD: return "cd";
        default: return "неизвестно";
    }
}

void printProduct(const MusicProduct* p) {
    // вывод информации о товаре
    std::cout << mediaTypeToString(p->media) << " | "
              << p->title << " | "
              << p->artist << " | "
              << p->catalogNumber << " | "
              << std::fixed << std::setprecision(2)
              << p->duration << " мин | "
              << p->price << " руб\n";
}