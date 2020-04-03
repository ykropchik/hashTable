//
// Created by YKROPCHIK on 14.02.2020.
//

#include "hash.h"

HashTable::HashTable(const int &maxSize, const int &percentIncrease) {
    this->maxSize = maxSize;
    this->currentSize = 0;
    if ((percentIncrease < 20) || (percentIncrease > 90)){
        this->percentIncrease = 70;
    } else {
        this->percentIncrease = percentIncrease;
    }
    this->table = new TableRec[maxSize];
    this->status = new bool[maxSize];
    this->percentDecrease = percentIncrease / 2;
    this->sizeIncrease = (100 + (percentIncrease / 2));
    this->sizeDecrease = (100 + (percentIncrease / 4));

    for (int i = 0; i < maxSize; ++i){
        status[i] = FREE;
    }
}

HashTable::~HashTable() {
    delete[] this->table;
    delete[] this->status;
}

int HashTable::hashFun_first(const uint8_t &key) {
    return key % maxSize;
}

int HashTable::hashFun_second(const uint8_t &key, const int &counter) {
    return (key + counter * counter) % maxSize;
}

/*TODO Ебаный мусор после в выделенной памяти вестора status*/
void HashTable::resize(const bool &mode) {
    TableRec *oldTable = table;
    bool *oldStatus = status;
    int oldSize = maxSize;
    currentSize = 0;

    if (mode == INCREASE) {
        maxSize = (int) ((float)maxSize * ((float) sizeIncrease / 100));
    } else {
        maxSize = (int) ((float) maxSize / ((float) sizeDecrease / 100));
    }

    table = new TableRec[maxSize];
    status = new bool[maxSize];

    for (int i = 0; i < maxSize; ++i){
        status[i] = FREE;
    }

    for (int i = 0; i < oldSize; ++i) {
        if (oldStatus[i] == BUSY) {
            add(oldTable[i]);
        }
    }
    delete[] oldStatus;
    delete[] oldTable;
}

void HashTable::reHash(int position, int posTry) {
    position = hashFun_second(position, ++posTry);
    while (status[position] != FREE) {
        status[position] = FREE;
        --currentSize;
        add(table[position]);
        position = hashFun_second(position, ++posTry);
    }
}

uint8_t HashTable::add(const TableRec &record) {
    int position = hashFun_first(record.hallNumber + record.time.hour + record.time.minute);

    if (status[position] == BUSY) {
        if (record == table[position]) {
            return FAIL;
        }

        for (int i = 1; status[position] == BUSY; ++i) {
            position = hashFun_second(position, i);

            if (i < maxSize / 4) {
                return OVERFLOW;
            }
        }
    }

    table[position] = record;
    status[position] = BUSY;
    currentSize++;

    if ((currentSize * 100 / maxSize) >= percentIncrease) {
        resize(INCREASE);
    }

    return SUCCESS;
}

uint8_t HashTable::remove(const TableRec &record) {
    int position = hashFun_first(record.hallNumber + record.time.hour + record.time.minute);
    bool isExist(NEXIST);
    int posTry(0);

    if (table[position] == record) {
        isExist = EXIST;
    } else {
        for (int i = 1; (isExist == NEXIST) && (i < maxSize / 4); ++i) {
            position = hashFun_second(position, i);
            if (table[position] == record) {
                isExist = EXIST;
                posTry = i;
            }
        }
    }

    if (isExist) {
        status[position] = FREE;
        --currentSize;
        reHash(position, posTry);

        if ((currentSize * 100 / maxSize) <= percentDecrease) {
            resize(DECREASE);
        }

        return REMOVED;
    } else {
        return NEXIST;
    }
}

bool HashTable::find(const TableRec &record) {
    int position = hashFun_first(record.hallNumber + record.time.hour + record.time.minute);
    if (table[position] == record) {
        return EXIST;
    } else {
        for (int i = 1; (status[position] = BUSY) && (position < maxSize); ++i) {
            position = hashFun_second(position, i);
            if (table[position] == record) {
                return EXIST;
            }
        }
    }
    return NEXIST;
}

void HashTable::print() {
    for (int i = 0; i < maxSize; ++i) {
        if (status[i] == BUSY) {
            std::cout << i << " | "
                      << table[i].name << " | "
                      << (unsigned) table[i].hallNumber << " | "
                      << (unsigned) table[i].time.hour << ":"
                      << (unsigned) table[i].time.minute << " | "
                      << hashFun_first(table[i].hallNumber + table[i].time.hour + table[i].time.minute) << "\n";
        } else {
            std::cout << i << " | "
                      << "------------" << " | "
                      << "0" << " | "
                      << "0" << ":"
                      << "0" << " | " << hashFun_first(table[i].hallNumber + table[i].time.hour + table[i].time.minute)
                      << "\n";
        }
    }
}

void HashTable::printStatus() {
    for (int i = 0; i < maxSize; ++i) {
        std::cout << status[i] << " ";
    }
    std::cout << "\n";
}
