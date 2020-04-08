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
#define PERCENTDECREASE (percentIncrease / 2)
#define SIZEINCREASE (100 + ((float) percentIncrease / 2))
#define SIZEDECREASE (100 + ((float) percentIncrease / 4))


struct TableRec {
    std::string name;
    uint8_t hallNumber;
    struct Time {
        uint8_t hour;
        uint8_t minute;
    } time;
};

class HashTable {
private:
    uint32_t maxSize;                                // max size of the table
    uint32_t currentSize;                            // current size of the table
    uint8_t percentIncrease;                    // percentage of the table fullness at which it will increase
    TableRec *table;                            // link on the "head" of table
    bool *status;                               // FREE or BUSY

    uint32_t hashFun_first(const uint8_t &key);
    uint32_t hashFun_second(const uint8_t &key, const uint32_t &counter);
    void resize(const bool &mode);
    void reHash(uint32_t position, uint32_t posTry);

public:
    HashTable(uint32_t maxSize, uint8_t percentIncrease);
    ~HashTable();
    uint8_t add(const TableRec &record);
    bool remove(const TableRec &record);
    bool find(const TableRec &record);
    void print();
    void printStatus();
};


inline bool operator==(const TableRec &firstArg, const TableRec &secondArg) {
    return ((firstArg.time.minute == secondArg.time.minute)
            && (firstArg.time.hour == secondArg.time.hour)
            && (firstArg.hallNumber == secondArg.hallNumber));
}