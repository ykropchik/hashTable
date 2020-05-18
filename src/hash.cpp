//
// Created by YKROPCHIK on 14.02.2020.
//

#include "hash.h"

HashTable::HashTable(uint32_t maxSize, uint8_t percentIncrease) {
    this->currentSize = 0;
    this->table = new TableRec[maxSize];
    this->status = new bool[maxSize];

    if (maxSize > 0) {
        this->maxSize = maxSize;
    } else {
        this->maxSize = 20;
    }

    if ((percentIncrease < 20) || (percentIncrease > 80)) {
        this->percentIncrease = 70;
    } else {
        this->percentIncrease = percentIncrease;
    }

    for (uint32_t i = 0; i < maxSize; ++i) {
        status[i] = FREE;
    }
}

HashTable::~HashTable() {
    delete[] this->table;
    delete[] this->status;
}

uint32_t HashTable::hashFun_first(const Key &key) {
    return (key.time.hour + key.time.minute + key.hallNumber) % maxSize;
}

uint32_t HashTable::hashFun_second(const uint32_t &hashCode, const uint32_t &counter) {
    return (hashCode + counter * counter) % maxSize;
}

void HashTable::resize(const bool &mode) {
    TableRec *oldTable = table;
    bool *oldStatus = status;
    uint32_t oldSize = maxSize;
    currentSize = 0;

    if (mode == INCREASE) {
        maxSize = (uint32_t) ((float) maxSize * ((float) SIZEINCREASE / 100));
    } else {
        maxSize = (uint32_t) ((float) maxSize / ((float) SIZEDECREASE / 100));
    }

    table = new TableRec[maxSize];
    status = new bool[maxSize];

    for (uint32_t i = 0; i < maxSize; ++i) {
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

void HashTable::reHash(uint32_t position, uint32_t posTry) {
    position = hashFun_second(position, ++posTry);
    while (status[position] != FREE) {
        status[position] = FREE;
        --currentSize;
        add(table[position]);
        position = hashFun_second(position, ++posTry);
    }
}

bool HashTable::add(const TableRec &record) {
    uint32_t hashCode = hashFun_first({record.key.hallNumber, record.key.time.hour, record.key.time.minute});

    if (status[hashCode] == BUSY) {
        if (record.key == table[hashCode].key) {
            return FAIL;
        }

        bool success = false;
        for (uint32_t i = 1; !success; ++i) {
            hashCode = hashFun_second(hashCode, i);

            if ((status[hashCode] == BUSY) && (record.key == table[hashCode].key)) {
                return FAIL;
            }

            if (i > maxSize / 4) {
                resize(INCREASE);
                add(record);
                return SUCCESS;
            }

            if (status[hashCode] == FREE) {
                table[hashCode] = record;
                status[hashCode] = BUSY;
                currentSize++;
                success = true;
            }
        }
    } else {
        table[hashCode] = record;
        status[hashCode] = BUSY;
        currentSize++;

        if ((currentSize * 100 / maxSize) >= percentIncrease) {
            resize(INCREASE);
        }
    }

    return SUCCESS;
}

bool HashTable::remove(const TableRec &record) {
    uint32_t position = hashFun_first({record.key.hallNumber, record.key.time.hour, record.key.time.minute});
    bool isExist(NEXIST);
    uint32_t posTry(0);

    if (table[position] == record) {
        isExist = EXIST;
    } else {
        for (uint32_t i = 1; (isExist == NEXIST) && (i < maxSize / 3); ++i) {
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

        if ((currentSize * 100 / maxSize) <= PERCENTDECREASE) {
            resize(DECREASE);
        }

        return REMOVED;
    } else {
        return NEXIST;
    }
}

bool HashTable::find(const TableRec &record) {
    uint32_t position = hashFun_first({record.key.hallNumber, record.key.time.hour, record.key.time.minute});
    if (table[position] == record) {
        return EXIST;
    } else {
        for (uint32_t i = 1; (status[position] = BUSY) && (position < maxSize); ++i) {
            position = hashFun_second(position, i);
            if (table[position] == record) {
                return EXIST;
            }
        }
    }
    return NEXIST;
}

void HashTable::print() {
    for (uint32_t i = 0; i < maxSize; ++i) {
        if (status[i] == BUSY) {
            std::cout << i << " | "
                      << table[i].name << " | "
                      << (unsigned) table[i].key.hallNumber << " | "
                      << (unsigned) table[i].key.time.hour << ":"
                      << (unsigned) table[i].key.time.minute << " | "
                      << hashFun_first({table[i].key.hallNumber,table[i].key.time.hour, table[i].key.time.minute}) << "\n";
        } else {
            std::cout << i << " | "
                      << "------------" << " | "
                      << "0" << " | "
                      << "0" << ":"
                      << "0" << " | " //<< hashFun_first({table[i].key.hallNumber,table[i].key.time.hour, table[i].key.time.minute})
                      << "\n";
        }
    }
}

void HashTable::printStatus() {
    for (uint32_t i = 0; i < maxSize; ++i) {
        std::cout << status[i] << " ";
    }
    std::cout << "\n";
}
