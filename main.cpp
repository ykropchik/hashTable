#include "src/hash.h"

using namespace std;

int main() {
    //HashTable seancesList = HashTable(11, 80);

    /*seancesList.add({"Переводчики", 4, 15, 45});
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
    seancesList.print();*/

//    //// TEST ADD
//
//    TableRec seance = {"AAAA", 1,00, 00};
//
//    for (int i = 1; i < 20; i++) {
//        seancesList.add(seance);
//        seancesList.print();
//        cout << "\n";
//        seance.key.hallNumber += 1;
//        seance.key.time.hour += 1;
//        if (seance.key.time.minute + 20 >= 60){
//            seance.key.time.minute = seance.key.time.minute + 13 - 60;
//        } else {
//            seance.key.time.minute += 13;
//        }
//
//    }
//
////// TEST REMOVE
//
//    seance = {"AAAA", 1,00, 00};
//
//    for (int i = 1; i < 20; i++) {
//        seancesList.remove(seance);
//        seancesList.print();
//        cout << "\n";
//        seance.key.hallNumber += 1;
//        seance.key.time.hour += 1;
//        if (seance.key.time.minute + 20 >= 60){
//            seance.key.time.minute = seance.key.time.minute + 13 - 60;
//        } else {
//            seance.key.time.minute += 13;
//        }
//
//    }

//    TableRec seance = {"AAAAA", 100, 00, 00};
//
//    for (int i = 1; i < 6; i++) {
//        seancesList.add(seance);
//        seance.name[0]++;
//        seance.key.hallNumber -= 1;
//        seance.key.time.hour += 1;
//    }
//    seancesList.print();
//    cout << "\n";

    //// TEST ADD
    HashTable seancesList = HashTable(10, 80);
    TableRec seance = {"AAAA", 120,00, 00};
    TableRec seance1 = {"BBBB", 113,00, 00};

    for (int i = 1; i < 10; i++) {

        seancesList.add(seance);
        seance.key.hallNumber -= 1;
        //   seance.key.time.hour += 1;
        seancesList.add(seance1);
        seance1.key.hallNumber += 1;
        //    seance1.key.time.hour += 1;

//        seancesList.print();
//        cout << "\n";

    }

    seancesList.print();
    cout << "\n";
//// TEST REMOVE


    seance = {"AAAA", 120,00, 00};
    seance1 = {"BBBB", 113,00, 00};

    for (int i = 1; i < 10; i++) {
        seancesList.remove(seance);
        seance.key.hallNumber -= 2;
        //   seance.key.time.hour += 1
        seancesList.remove(seance1);
        seance1.key.hallNumber += 2;
        //    seance1.key.time.hour += 1;

//        seancesList.print();
//        cout << "\n";

    }

    seancesList.print();
    cout << "\n";



}