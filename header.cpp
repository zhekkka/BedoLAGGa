//
// Created by zhest on 11.03.2022.
//
#include "header.h"
#include <iostream>
#include <string>
#include "cmath"
#include <sstream>
#include <fstream>
#include "cctype"
#include <climits>

Unit::Unit() {
    name = "";
    x = 0;
    y = 0;
    prod = 'n';
    prodNum = 0;
    for (double &i: prodReq) {
        i = 0;
    }
}

Unit::~Unit() {}

void Unit::read() {
    std::cout << "Введите название " << std::endl;
    std::cin >> name;
    while (true) {
        std::cout << "Введите координаты по x и у" << std::endl;
        std::cin >> x >> y;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    while (true) {
        std::cout << "Введите ресурс\n" << "m - дениги\ne - энергия\nw - труд\nt - земля\nn - ничего" << std::endl;
        std::string vvod;
        std::cin >> vvod;

        if ((!std::cin) |
            !((vvod[0] == 'm') | (vvod[0] == 'e') | (vvod[0] == 't') | (vvod[0] == 'n') | (vvod[0] == 'w')) |
            !(isalpha(vvod[0])) | vvod.length() != 1) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            prod = vvod[0];
            std::cin.clear();
            break;
        }
    }
    while (true) {
        std::cout << "Введите количество ресурса " << std::endl;
        std::cin >> prodNum;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    while (true) {
        std::cout
                << "Введите четырёхмерный вектор требуемых ресурсов\nпервый - деньги\nвторой - энергия\nтретий - труд\nчетвертый - земля"
                << std::endl;
        std::cin >> prodReq[0] >> prodReq[1] >> prodReq[2] >> prodReq[3];
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
}

void Unit::print() {
    std::cout << "Название ";
    std::cout << name << std::endl;
    std::cout << "Координата по x и y ";
    std::cout << x << " " << y << std::endl;
    std::cout << "Ресурс ";
    std::cout << prod << std::endl;
    std::cout << "Количество ресурса ";
    std::cout << prodNum << std::endl;
    std::cout << "Вектор требуемых ресурсов ";
    std::cout << prodReq[0] << " " << prodReq[1] << " " << prodReq[2] << " " << prodReq[3] << std::endl;
}

std::string Unit::getName() {
    return name;
}

int Unit::compare(Unit &scnd) {
    if ((this->x) > scnd.x) {
        return 1;
    } else {
        if ((this->x) == scnd.x) {
            if ((this->y) > scnd.y) {
                return 1;
            } else {
                if ((this->y) == scnd.y) {
                    if ((this->name) > scnd.name) {
                        return 1;
                    } else {
                        if ((this->name) == scnd.name) {
                            return 0;
                        } else {
                            return -1;
                        }
                    }
                } else {
                    return -1;
                }
            }
        } else {
            return -1;
        }
    }
}

bool Unit::check(double r, double x0, double y0, std::string name) {
    if (((pow((this->x - x0), 2) + pow((this->y - y0), 2)) <= pow(r, 2)) & (((this->name) == name) | (name == "*"))) {
        return true;
    } else {
        return false;
    }
}

bool operator>(Unit &a, Unit &b) {
    if (a.compare(b) == 1) {
        return true;
    } else {
        return false;
    }
}

bool operator<(Unit &a, Unit &b) {
    if (a.compare(b) == -1) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(Unit &a, Unit &b) {
    if (a.compare(b) == (1 | 0)) {
        return true;
    } else {
        return false;
    }
}

bool operator<=(Unit &a, Unit &b) {
    if (a.compare(b) == (-1 | 0)) {
        return true;
    } else {
        return false;
    }
}

bool operator==(Unit &a, Unit &b) {
    if (a.compare(b) == 0) {
        return true;
    } else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &out, const Unit &unit) {
    out << unit.name << "*";
    out << unit.x << "*";
    out << unit.y << "*";
    out << unit.prod << "*";
    out << unit.prodNum << "*";
    for (int i = 0; i < 4; ++i) {
        out << unit.prodReq[i] << "*";
    }
    out << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Unit &unit) {
    std::string str;
    bool Fl = true;
    getline(in, str);
    int y, count;
    count = 0;
    for (int i = 0; i < 9; ++i) {
        y = str.find("*");
        if ((y == -1) | (std::string(str, 0, y).empty())) {
            Fl = false;
        }
        if (Fl) {
            switch (i) {
                case 0: {
                    unit.name = std::string(str, 0, y);
                    str = std::string(str, y + 1, str.length() - 1 - y);
                    break;
                }
                case 1: {
                    for (int j = 0; j < std::string(str, 0, y).length(); ++j) {
                        if (isdigit(str[j]) or (str[j] == ',')) {
                            if (str[j] == ',') {
                                count++;
                            }
                        } else {
                            Fl = false;
                            break;
                        }
                    }
                    if (Fl and ((count == 1) or (count == 0))) {
                        unit.x = std::stod(std::string(str, 0, y));
                        str = std::string(str, y + 1, str.length() - 1 - y);
                        count = 0;
                        break;
                    } else {
                        Fl = false;
                        break;
                    }
                }
                case 2: {
                    for (int j = 0; j < std::string(str, 0, y).length(); ++j) {
                        if (isdigit(str[j]) or (str[j] == ',')) {
                            if (str[j] == ',') {
                                count++;
                            }
                        } else {
                            Fl = false;
                            break;
                        }
                    }
                    if (Fl and ((count == 1) or (count == 0))) {
                        unit.y = std::stod(std::string(str, 0, y));
                        str = std::string(str, y + 1, str.length() - 1 - y);
                        count = 0;
                        break;
                    } else {
                        Fl = false;
                        break;
                    }
                }
                case 3: {
                    if (((std::string(str, 0, y).length()) == 1) &
                        ((str[0] == 'm') or (str[0] == 'e') or (str[0] == 'w') or (str[0] == 't') or (str[0] == 'n'))) {
                        unit.prod = str[0];
                        str = std::string(str, y + 1, str.length() - 1 - y);
                        break;
                    } else {
                        Fl = false;
                        break;
                    }
                }
                case 4: {
                    for (int j = 0; j < std::string(str, 0, y).length(); ++j) {
                        if (isdigit(str[j]) or (str[j] == ',')) {
                            if (str[j] == ',') {
                                count++;
                            }
                        } else {
                            Fl = false;
                            break;
                        }
                    }
                    if (Fl and ((count == 1) or (count == 0))) {
                        unit.prodNum = std::stod(std::string(str, 0, y));
                        str = std::string(str, y + 1, str.length() - 1 - y);
                        count = 0;
                        break;
                    } else {
                        Fl = false;
                        break;
                    }
                }
                default: {
                    for (int j = 0; j < std::string(str, 0, y).length(); ++j) {
                        if (isdigit(str[j]) or (str[j] == ',')) {
                            if (str[j] == ',') {
                                count++;
                            }
                        } else {
                            Fl = false;
                            break;
                        }
                    }
                    if (Fl and ((count == 1) or (count == 0))) {
                        unit.prodReq[i - 5] = std::stod(std::string(str, 0, y));
                        str = std::string(str, y + 1, str.length() - 1 - y);
                        count = 0;
                        break;
                    } else {
                        Fl = false;
                        break;
                    }
                }

            }
        } else {
            break;
        }
    }
    if (!Fl) {
        std::cout << "Неверный формат данных в файле!" << std::endl;
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

void Unit::getProd(double mas[4]) {
    switch (this->prod) {
        case 'm': {
            mas[0] += prodNum;
            break;
        }
        case 'e': {
            mas[1] += prodNum;
            break;
        }
        case 'w': {
            mas[2] += prodNum;
            break;
        }
        case 't': {
            mas[3] += prodNum;
            break;
        }
        default:
            break;
    }
}

void Unit::getReq(double mas[4]) {
    mas[0] += prodReq[0];
    mas[1] += prodReq[1];
    mas[2] += prodReq[2];
    mas[3] += prodReq[3];
}

UnitList::UnitList() {}

UnitList UnitList::operator=(const UnitList &a) {
    UnitNode *NodeF = first;
    UnitNode *NodeS = a.first;
    for (int i = 0; i < (a.UnitListNumber); ++i) {
        if ((NodeF != nullptr) & (NodeS != nullptr)) {
            (*NodeF).unit = (*NodeS).unit;
            NodeF = (*NodeF).next;
            NodeS = (*NodeS).next;
        } else {
            if ((NodeF == nullptr) & (NodeS != nullptr)) {
                Unit newUnit;
                newUnit = (*NodeS).unit;
                this->addToEnd(newUnit);
                NodeS = (*NodeS).next;
            } else {
                if ((NodeF != nullptr) & (NodeS == nullptr)) {
                    NodeS = (*NodeF).next;
                    removeNode(&(*NodeF));
                    NodeF = NodeS;
                    NodeS = nullptr;
                }
            };
        }
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const UnitList &unitList) {
    UnitList::UnitNode *it = unitList.first;
    for (int i = 0; i < (unitList.UnitListNumber); ++i) {
        out << (*it).unit << std::endl;
        it = it->next;
    }
    return out;
}

std::istream &operator>>(std::istream &in, UnitList &unitList) {
    std::string line;
    int i = 0;
    UnitList::UnitNode *it = unitList.first;
    while (in.peek() != EOF) {
        std::getline(in, line);
        std::istringstream inLine(line);
        Unit newUnit;
        unitList.addToEnd(newUnit);
        if ((it == nullptr) & (i == 0)) {
            it = unitList.first;
            i++;
        } else {
            it = it = (*it).next;
        }
        inLine >> (*it).unit;
        if (inLine.fail()) {
            in.setstate(std::ios_base::failbit);
            break;
        }
    }

    return in;
}

void UnitList::addToEnd(Unit &Unit) {
    UnitListNumber++;
    UnitNode *Node = new UnitNode;
    if (first == nullptr) {
        first = Node;
        last = Node;
        (*Node).unit = Unit;
    } else {
        last->next = Node;
        (*Node).prev = last;
        last = Node;
        (*Node).unit = Unit;
    }
}

void UnitList::add() {
    Unit newUnit;
    newUnit.read();
    this->addToEnd(newUnit);
}

void UnitList::addFile(std::ifstream &in) {
    Unit newUnit;
    in >> newUnit;
    this->addToEnd(newUnit);
}

void UnitList::write() {
    std::string name;
    double r, x0, y0;
    std::cout << "Введите название" << std::endl;
    std::cin >> name;
    while (true) {
        std::cout << "Введите расстояние" << std::endl;
        std::cin >> r;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    while (true) {
        std::cout << "Введите координаты по x и у" << std::endl;
        std::cin >> x0 >> y0;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    UnitList::UnitNode *tmpNode = this->first;
    for (int i = 0; i < (this->UnitListNumber); ++i) {
        if (!(*tmpNode).unit.getName().empty()) {
            if ((*tmpNode).unit.check(r, x0, y0, name)) {
                tmpNode->unit.print();
            };
        } else {
            std::cout << "Некорректные данные!" << std::endl;
            break;
        }
        tmpNode = (*tmpNode).next;
    }

};

UnitList::UnitNode *UnitList::merge(UnitNode *First, UnitNode *Second) {
    // If first linked list is empty
    if (!First)
        return Second;

    // If second linked list is empty
    if (!Second)
        return First;

    // Pick the smaller value
    if (First->unit < Second->unit) {
        First->next = merge(First->next, Second);
        First->next->prev = First;
        First->prev = nullptr;
        return First;
    } else {
        Second->next = merge(First, Second->next);
        Second->next->prev = Second;
        Second->prev = nullptr;
        return Second;
    }
}

// Function to do merge sort
UnitList::UnitNode *UnitList::mergeSort(UnitNode *head) {
    if (!head || !head->next)
        return head;
    UnitNode *Second = split(head);

    // Recur for left and right halves
    head = mergeSort(head);
    Second = mergeSort(Second);

    // Merge the two sorted halves
    return merge(head, Second);
}

UnitList::UnitNode *UnitList::split(UnitNode *head) {
    UnitNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    UnitNode *temp = slow->next;
    slow->next = nullptr;
    return temp;
}

void UnitList::sort() {
    this->first = mergeSort(this->first);
    UnitNode *it = this->first;
    for (int i = 0; i < UnitListNumber - 1; ++i) {
        it = (*it).next;
    }
    this->last = it;
}

void UnitList::addToSorted() {
    (*this).add();
    (*this).sort();
}

void UnitList::removeNode(UnitList::UnitNode *Node) {
    if (((*Node).prev == nullptr) & (((*Node).next) == nullptr)) {
        delete Node;
        this->first = nullptr;
        this->last = nullptr;
    } else {
        if (((*Node).prev == nullptr) & (((*Node).next) != nullptr)) {
            ((*Node).next)->prev = nullptr;
            this->first = (*Node).next;
            delete Node;
        } else {
            if (((*Node).prev != nullptr) & (((*Node).next) == nullptr)) {
                ((*Node).prev)->next = nullptr;
                this->last = (*Node).prev;
                delete Node;
            } else {
                ((*Node).prev)->next = ((*Node).next);
                ((*Node).next)->prev = ((*Node).prev);
                delete Node;
            }

        }
    }

}

void UnitList::remove() {
    std::string name;
    double r, x0, y0;
    std::cout << "Введите название" << std::endl;
    std::cin >> name;
    while (true) {
        std::cout << "Введите расстояние" << std::endl;
        std::cin >> r;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    while (true) {
        std::cout << "Введите координаты по x и у" << std::endl;
        std::cin >> x0 >> y0;
        if (!std::cin) {
            std::cout << "Что-то пошло не так!\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        } else {
            std::cin.sync();
            std::cin.clear();
            break;
        }
    }
    UnitList::UnitNode *tmpNode = this->first;
    UnitList::UnitNode *tmpNodeNext = nullptr;
    int s = 0;
    for (int i = 0; i < UnitListNumber; ++i) {
        if (!(*tmpNode).unit.getName().empty()) {
            if (((*tmpNode).unit).check(r, x0, y0, name)) {
                tmpNodeNext = (*tmpNode).next;
                this->removeNode(tmpNode);
                s++;
            }
        }
        tmpNode = tmpNodeNext;
    }
    UnitListNumber -= s;
}

void UnitList::clear() {
    int s = 0;
    UnitList::UnitNode *tmpNode = this->first;
    UnitList::UnitNode *tmpNodeNext = nullptr;
    for (int i = 0; i < UnitListNumber; ++i) {
        if (!(*tmpNode).unit.getName().empty()) {
            tmpNodeNext = (*tmpNode).next;
            this->removeNode(tmpNode);
            s++;
        }
        tmpNode = tmpNodeNext;
    }
    UnitListNumber -= s;
}

void UnitList::save(std::ostream &file) {
    UnitNode *it = this->first;
    for (int i = 0; i < (this->UnitListNumber); ++i) {
        file << (*it).unit;
        it = (*it).next;
    }
}

int UnitList::getNumber() {
    return UnitListNumber;
}

void UnitList::resources() {
    UnitNode *it = this->first;
    double resReq[4] = {0, 0, 0, 0};
    double resProd[4] = {0, 0, 0, 0};
    for (int i = 0; i < (this->UnitListNumber); ++i) {
        (*it).unit.getReq(resReq);
        (*it).unit.getProd(resProd);
        it = it->next;
    }
    std::cout << "Вектор требуемых ресурсов ";
    std::cout << resReq[0] << " " << resReq[1] << " " << resReq[2] << " " << resReq[3] << std::endl;
    std::cout << "Вектор производимых ресурсов ";
    std::cout << resProd[0] << " " << resProd[1] << " " << resProd[2] << " " << resProd[3] << std::endl;
}