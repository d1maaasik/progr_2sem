#include <iostream>
#include <windows.h>

class List {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head;

public:
    List() : head(nullptr) {}

    // Добавление в конец
    void push_back(int value) {
        Node* newNode = new Node{value, nullptr};

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next)
            temp = temp->next;

        temp->next = newNode;
    }

    // Удаление третьего положительного с конца
    void removeThirdPositiveFromEnd() {
        int count = 0;

        // Считаем положительные
        Node* temp = head;
        while (temp) {
            if (temp->data > 0)
                count++;
            temp = temp->next;
        }

        if (count < 3) {
            std::cout << "Недостаточно положительных элементов.\n";
            return;
        }

        int target = count - 3 + 1; // какой по счёту положительный удалить

        temp = head;
        Node* prev = nullptr;
        int currentPos = 0;

        while (temp) {
            if (temp->data > 0)
                currentPos++;

            if (currentPos == target) {
                if (prev)
                    prev->next = temp->next;
                else
                    head = temp->next;

                delete temp;
                return;
            }

            prev = temp;
            temp = temp->next;
        }
    }

    void print() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    List list;

    std::cout << "Введите 15 чисел:\n";
    for (int i = 0; i < 15; i++) {
        int x;
        std::cin >> x;
        list.push_back(x);
    }

    std::cout << "\nИсходный список:\n";
    list.print();

    list.removeThirdPositiveFromEnd();

    std::cout << "\nПосле удаления третьего положительного с конца:\n";
    list.print();

    return 0;
}