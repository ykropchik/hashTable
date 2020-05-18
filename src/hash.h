//
// Created by YKROPCHIK on 14.02.2020.
//
#include <iostream>

#define FREE false
#define BUSY true
#define SUCCESS true
#define FAIL false
#define DECREASE 0
#define INCREASE 1
#define EXIST 1
#define NEXIST 0
#define REMOVED 1
#define PERCENTDECREASE (percentIncrease / 2)
#define SIZEINCREASE (100 + ((float) percentIncrease / 2))
#define SIZEDECREASE (100 + ((float) percentIncrease / 4))

struct Key {
    uint8_t hallNumber;
    struct Time {
        uint8_t hour;
        uint8_t minute;
    } time;
};


struct TableRec {
    std::string name;
    Key key;
};

class HashTable {
private:
    uint32_t maxSize;                               // max size of the table
    uint32_t currentSize;                           // current size of the table
    uint8_t percentIncrease;                        // percentage of the table fullness at which it will increase
    TableRec *table;                                // link on the "head" of table
    bool *status;                                   // FREE or BUSY

    uint32_t hashFun_first(const Key &key);
    uint32_t hashFun_second(const uint32_t &hashCode, const uint32_t &counter);
    void resize(const bool &mode);
    void reHash(uint32_t position, uint32_t posTry);

public:
    HashTable(uint32_t maxSize, uint8_t percentIncrease);
    ~HashTable();
    bool add(const TableRec &record);
    bool remove(const TableRec &record);
    bool find(const TableRec &record);
    void print();
    void printStatus();
};

inline bool operator==(const Key &firstArg, const Key &secondArg) {
    return ((firstArg.time.minute == secondArg.time.minute)
            && (firstArg.time.hour == secondArg.time.hour)
            && (firstArg.hallNumber == secondArg.hallNumber));
}

inline bool operator==(const TableRec &firstArg, const TableRec &secondArg) {
    return ((firstArg.name == secondArg.name)
            && (firstArg.key.time.minute == secondArg.key.time.minute)
            && (firstArg.key.time.hour == secondArg.key.time.hour)
            && (firstArg.key.hallNumber == secondArg.key.hallNumber));
}