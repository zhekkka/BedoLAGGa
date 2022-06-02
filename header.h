//
// Created by zhest on 26.02.2022.
//

#ifndef CLASS_HEADER_H
#define CLASS_HEADER_H

#include <string>
#include "iostream"

class Unit {
    std::string name;//название
    double x, y;
    char prod;// произоводимый ресурс
    /*
   m - дениги
   e - энергия
   w - труд
   t - земля
   n - ничего
    */
    double prodNum;// количество производимого ресурса
    double prodReq[4]{};//вектор требуемых ресурсов
    /*
   первый - деньги
   второй - энергия
   третий - труд
   четвертый - земля
   */
public:
    Unit();

    ~Unit();

    void read();

    void print();

    std::string getName();

    int compare(Unit &scnd);

    bool check(double r, double x0, double y0, std::string name);

    friend bool operator>(Unit &a, Unit &b);

    friend bool operator>=(Unit &a, Unit &b);

    friend bool operator==(Unit &a, Unit &b);

    friend bool operator<(Unit &a, Unit &b);

    friend bool operator<=(Unit &a, Unit &b);

    friend std::ostream &operator<<(std::ostream &out, const Unit &unit);

    friend std::istream &operator>>(std::istream &in, Unit& unit);

    void getProd(double mas[4]);

    void getReq(double mas[4]);
};

class UnitList {
private:
    struct UnitNode {
        Unit unit;
        UnitNode *next= nullptr;
        UnitNode *prev= nullptr;
    };
    UnitNode *first = nullptr;
    UnitNode *last = nullptr;
    int UnitListNumber = 0;
public:

    UnitList();

    void add();

    void addFile(std::ifstream &in);

    UnitList operator=(const UnitList &a);

    void sort();

    void addToSorted();

    void write();

    void removeNode(UnitList::UnitNode* Node);

    void remove();

    void clear();

    void addToEnd(Unit &Unit);

    friend std::ostream &operator<<(std::ostream &out, const UnitList &unitList);

    friend std::istream &operator>>(std::istream &in, UnitList& unitList);

    void save(std::ostream& file);

    int getNumber();

    void resources();

    UnitList::UnitNode *merge(UnitNode *first, UnitNode *second);

    UnitList::UnitNode *mergeSort(UnitNode *head);

    UnitList::UnitNode *split(UnitNode *head);

    };

#endif //CLASS_HEADER_H