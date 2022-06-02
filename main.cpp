#include <iostream>
#include "header.h"
#include <string>
#include <fstream>
#include <map>

void connect(std::string &x,std::string &xArg){
    std::string str;
    int y;
    x="";
    xArg="";
    std::cout<<"Введите функцию  **help"<<std::endl;
    getline(std::cin,str);
    std::cin.clear();

    y= str.find(" ");
    if (y!=-1) {
        x = std::string(str,0,y);
        xArg = std::string(str,y+1,str.length()-1-y);
    }
    else{
        x=std::string(str);
        xArg="";
    }
}
void choice(std::string &x, std::string &xArg, int &y){
    std::map <std::string,int> choice={{"help",0},{"clear",1},{"load",2},{"save",3},{"add",4},{"sort",5},{"find",6},{"delete",7},{"resources",8},{"exit",9},{"writeAll",10}};
    std::map<std::string,int>::iterator it;
    it = choice.find(x);
    while (it==choice.end()){
        connect(x,xArg);
        it = choice.find(x);
    }
    y=it->second;
}
int main() {
    setlocale(LC_ALL, "Russian");
    std::string x,xArg;
    bool Flag = true;
    bool UnitListFlag= false;
    int choiceInt;
    //choice(x,xArg, choiceInt);
    UnitList *List= new UnitList;
    while (Flag) {
        connect(x,xArg);
        choice(x, xArg,choiceInt);
        switch (choiceInt) {
            case 0: {//help
                if (xArg=="") {
                    std::cout
                            << "clear- очистить список| load <filename> - добавить список из файла| save <filename> - сохранить список в файле"
                            << std::endl << "add  <filename> или console- добавить элемент| sort- отсортировать"
                            << std::endl
                            << "find- вывести на экран элементы, удовлетровяющие условиям| delete- удалить элементы, удовлетворяющие условиям"
                            << std::endl
                            << "resources- вывести на экран, сколько ресурсов нужно для сожания имеющихся юнитов и сколько они производят| exit- выход"
                            << std::endl;
                }
                break;
            }
            case 1: {//clear
                if (xArg=="") {
                    if (UnitListFlag) {
                        List->clear();
                        UnitListFlag = false;
                        std::cout << "Список очищен!" << std::endl;
                    } else {
                        std::cout << "Список пуст!" << std::endl;
                    }
                }
                break;
            }
            case 2: {//load добавить в список
                std::ifstream in(xArg);
                if (in.is_open()){
                    List->clear();
                    in>>(*List);
                    if (!(in.fail())) {
                        if ((List->getNumber() != 0)) {
                            UnitListFlag = true;
                        } else {
                            UnitListFlag = false;
                        }

                    } else{
                        UnitListFlag=false;
                        List->clear();
                        std::cout<<"Список принудительно очищен"<<std::endl;
                    }
                    in.close();
                } else{
                    std::cout<<"Неправильный путь!"<<std::endl;
                }
                break;
            }
            case 3: {//save сохранить список
                if (UnitListFlag){
                    std::ofstream out;          // поток для записи
                    out.open(xArg); // окрываем файл для записи
                    if (out.is_open())
                    {
                        List->save(out);
                        out.close();
                        std::cout<<"Запись прошла успешно!"<<std::endl;
                    } else{
                        std::cout<<"Неравильный путь!"<<std::endl;
                    }
                } else{
                    std::cout<<"Список пуст!"<<std::endl;
                }
                break;
            }
            case 4: {//add
                bool Fl=false;
                if (xArg=="console"){
                    List->add();
                    UnitListFlag=true;
                    Fl=true;
                }
                std::ifstream in(xArg);
                if (in.is_open()){
                    Fl=true;
                    List->addFile(in);
                    UnitListFlag=true;
                    in.close();
                }
                if (!Fl){
                    std::cout<<"Неправильный ввод!"<<std::endl;
                }
                break;
            }
            case 5: {//sort доделать
                if (xArg=="") {
                    if (UnitListFlag) {
                        List->sort();
                        std::cout << "Список отсортирован!" << std::endl;
                    } else {
                        std::cout << "Список пуст!" << std::endl;
                    }
                }
                break;
            }
            case 6: {//find
                if (xArg=="") {
                    if (UnitListFlag) {
                        List->write();
                    } else {
                        std::cout << "Список пуст!" << std::endl;
                    }
                }
                break;
            }
            case 7: {//delete
                if (xArg=="") {
                    if (UnitListFlag) {
                        List->remove();
                        if (List->getNumber() == 0) {
                            UnitListFlag = false;
                        }
                    } else {
                        std::cout << "Список пуст!" << std::endl;
                    }
                }
                break;
            }
            case 8: {//resources
                if (xArg=="") {
                    if (UnitListFlag) {
                        List->resources();
                    } else {
                        std::cout << "Список пуст!" << std::endl;
                    }
                }
                break;
            }
            case 9: {//exit
                if (xArg=="") {
                    Flag = false;
                    break;
                }
                break;
            }
            case 10:{//writeAll
                if (xArg=="") {
                    if (UnitListFlag) {
                        std::cout << *List;
                    }
                }
                break;
            }
        }
    }
    return 0;
}