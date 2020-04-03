#include "src/hash.h"

using namespace std;

int main() {
    HashTable seancesList = HashTable(25, 70);
    seancesList.add({"Переводчики", 4, 15, 45});
    seancesList.add({"Джентльмены", 4, 18, 55});
    seancesList.add({"Удивительное путешествие Доктора Дулиттла", 3, 21, 40});
    seancesList.add({"Удивительное путешествие Доктора Дулиттла", 4, 23, 25});
    seancesList.add({"Калашников", 1, 13, 50});
    seancesList.add({"Лёд 2", 1, 19, 00});
    seancesList.add({"Лёд 2", 1, 21, 30});
    seancesList.add({"Джентльмены", 1, 23, 59});
    seancesList.add({"Жадность", 2, 14, 15});
    seancesList.add({"Отель «Маскарад» (53-й фестиваль японского кино)", 2, 19, 00});
    seancesList.add({"Яга. Кошмар тёмного леса", 2, 21, 35});
    seancesList.add({"Яга. Кошмар тёмного леса", 2, 23, 45});
    seancesList.add({"Калашников", 3, 17, 20});
    seancesList.add({"Переводчики", 3, 19, 30});
    seancesList.add({"Жадность", 3, 21, 45});
    seancesList.add({"Переводчики", 3, 23, 59});
    seancesList.print();
    cout << "\n";
    seancesList.remove({"Переводчики", 4, 15, 45});
    seancesList.print();
    seancesList.remove({"Лёд 2", 1, 19, 00});
    cout << "\n";
    seancesList.print();

    return 0;
}
