//
// Created by YKROPCHIK on 14.02.2020.
//
#include <iostream>

#define FREE false
#define BUSY true
#define SUCCESS 0
#define FAIL 1
#define OVERFLOW 2
#define DECREASE 0
#define INCREASE 1
#define EXIST 1
#define NEXIST 0
#define REMOVED 1

/*TODO Пересмотреть выбор типов данных*/
struct TableRec{
    std::string name;
    uint8_t hallNumber;
    struct Time{
        uint8_t hour;
        uint8_t minute;
    } time;
};

class HashTable{
private:
    int maxSize;                                // max size of the table
    int currentSize;                            // current size of the table
    uint8_t percentIncrease;                    // percentage of the table fullness at which it will increase
    uint8_t percentDecrease;                    // percentage of the table emptiness at which it will decrease
    uint8_t sizeIncrease;                       // size of a new increased table (in percentage)
    uint8_t sizeDecrease;                       // size of a new decreased table (in percentage)
    TableRec *table;                            // link on the "head" of table
    bool *status;                               // FREE or BUSY

    int hashFun_first(const uint8_t &key);
    int hashFun_second(const uint8_t &key, const int &counter);
    void resize(const bool &mode);
    void reHash(int position, int posTry);

public:
    HashTable(const int &maxSize, const int &percentIncrease);
    ~HashTable();

    uint8_t add(const TableRec& record);
    uint8_t remove(const TableRec& record);
    bool find(const TableRec& record);
    void print();
    void printStatus();
};  


inline bool operator ==(const TableRec& firstArg, const TableRec &secondArg){
    return ((firstArg.time.minute == secondArg.time.minute)
           && (firstArg.time.hour == secondArg.time.hour)
           && (firstArg.hallNumber == secondArg.hallNumber));
}