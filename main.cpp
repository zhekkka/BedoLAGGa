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
    std::cout<<"������� �������  **help"<<std::endl;
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
                std::cout
                        << "clear- �������� ������| load <filename> - �������� ������ �� �����| save <filename> - ��������� ������ � �����"<< std::endl << "add  <filename> ��� console- �������� �������| sort- �������������"<<std::endl<< "find- ������� �� ����� ��������, ��������������� ��������| delete- ������� ��������, ��������������� ��������"<<std::endl<< "resources- ������� �� �����, ������� �������� ����� ��� ������� ��������� ������ � ������� ��� ����������| exit- �����"
                        << std::endl;
                connect(x,xArg);
                break;
            }
            case 1: {//clear
                if (UnitListFlag){
                    List->clear();
                    UnitListFlag=false;
                    std::cout<<"������ ������!"<<std::endl;
                }
                else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x ,xArg);
                break;
            }
            case 2: {//load �������� � ������
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
                        std::cout<<"������ ������������� ������"<<std::endl;
                    }
                    in.close();
                } else{
                    std::cout<<"������������ ����!"<<std::endl;
                }
                connect(x, xArg);
                break;
            }
            case 3: {//save ��������� ������
                if (UnitListFlag){
                    std::ofstream out;          // ����� ��� ������
                    out.open(xArg); // �������� ���� ��� ������
                    if (out.is_open())
                    {
                        List->save(out);
                        out.close();
                        std::cout<<"������ ������ �������!"<<std::endl;
                    } else{
                        std::cout<<"����������� ����!"<<std::endl;
                    }
                } else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x, xArg);
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
                    std::cout<<"������������ ����!"<<std::endl;
                }
                connect(x, xArg);
                break;
            }
            case 5: {//sort ��������
                if (UnitListFlag){
                    List->sort();
                    std::cout<<"������ ������������!"<<std::endl;
                }
                else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x, xArg);
                break;
            }
            case 6: {//find
                if (UnitListFlag){
                    List->write();
                }
                else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x, xArg);
                break;
            }
            case 7: {//delete
                if (UnitListFlag){
                    List->remove();
                    if(List->getNumber()==0){
                        UnitListFlag= false;
                    }
                }
                else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x,xArg);
                break;
            }
            case 8: {//resources
                if (UnitListFlag){
                    List->resources();
                }
                else{
                    std::cout<<"������ ����!"<<std::endl;
                }
                connect(x,xArg);
                break;
            }
            case 9: {//exit
                Flag = false;
                break;
            }
            case 10:{//writeAll
                if (UnitListFlag){
                    std::cout<<*List;
                }
                connect(x,xArg);
                break;
            }
        }
    }
    return 0;
}