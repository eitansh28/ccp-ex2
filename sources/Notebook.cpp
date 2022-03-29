#include <string>
#include <iostream>
#include "Direction.hpp"
#include "Notebook.hpp"
#include <stdexcept>
#include <unordered_map>
#include <limits.h>
using namespace ariel;
using namespace std;

const int limit = 100;
const int low = 33;
const int high = 126;
const int mugzam = 9000;


    int strlen(const string &s){
        int count=0;
        for(int i=0;i<s.length();i++){
            count++;
        }return count;
    }

// namespace ariel {
    
    Notebook::Notebook(){
        //unordered_map<std::string, char> note;
        this->rowUpLim=0;
        this->rowDownLim=INT_MAX;
    }
    
    Notebook::~Notebook()
    {
        
    }


    void Notebook::write(int page, int row, int col, ariel::Direction dir, string str){
        if(strlen(str)>mugzam){
            return;
        }
        if(Notebook::illegal(page, row, col, dir, str)==0){
            throw invalid_argument{"you can't write here"};
        }
        if(col>limit || col<0 || col>=limit || row<0 || page<0){
            throw invalid_argument{"out of range"};
        }
        if(col+strlen(str)>limit && dir==Direction::Horizontal){
            throw invalid_argument{"out of range"};
        }char c=0;
        for (unsigned int i = 0; i < strlen(str); i++){
            c=str.at(i);
            if((c<low || c>high) && c!=' '){
                throw invalid_argument{"Illegal char"};
            }
        }           
        string tilda="~";
        if (str.find(tilda) != string::npos){
            throw invalid_argument{"Illegal char"};
        }
        if(dir==Direction::Vertical){
            if(row+strlen(str)>this->rowUpLim){
                this->rowUpLim=row+strlen(str);
            }
        }else{
            if(row>this->rowUpLim){
                this->rowUpLim=row+1;
            }
        }
        if(row<this->rowDownLim){
            this->rowDownLim=row;
        }
        char ch=0;
        if(dir==Direction::Horizontal){
            for(unsigned int i=0;i<str.length();i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!=0 && this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!='_'){
                    throw invalid_argument{"you can't write here"};
                }
                ch=str.at(i);
                this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]=ch;
                col++;
                }
        }
        else if(dir==Direction::Vertical){
            for(unsigned int i=0;i<str.length();i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!=0 && this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!='_'){
                    throw invalid_argument{"you can't write here"};
                }
                ch=str.at(i);
                this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]=ch;
                row++;
            }
        }
    }


    string Notebook::read(int page, int row, int col, ariel::Direction dir, int length){
        if(col>limit || col<0 || col>=limit || row<0 || page<0 || length<0){
            throw invalid_argument{"out of range"};
        }
        if((col+length>limit && dir==Direction::Horizontal)){
            throw invalid_argument{"out of range"};
        }
        string textForRead;
        if(dir==Direction::Horizontal){
            for(int i=0;i<length;i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]==0){
                    textForRead+='_';
                    col++;
                    continue;
                }
                textForRead+=this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)];
                col++;
            }
        }
        else if(dir==Direction::Vertical){
            for(int i=0;i<length;i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]==0){
                    textForRead+='_';
                    row++;
                    continue;
                }
                textForRead+=this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)];
                row++;
            }
        }
        return textForRead;
    }


    void Notebook::erase(int page, int row, int col, ariel::Direction dir, int length){
        if(col>limit || col<0 || col>=limit || row<0 || page<0 || length<0){
            throw invalid_argument{"out of range"};
        }
        if((col+length>limit && dir==Direction::Horizontal)){
            throw invalid_argument{"out of range"};
        }
        if(dir==Direction::Vertical){
            if(row+length>this->rowUpLim){
                this->rowUpLim=row+length;
            }
        }else{
            if(row>this->rowUpLim){
                this->rowUpLim=row;
            }
        }
        if(row<this->rowDownLim){
            this->rowDownLim=row;
        }
        if(dir==Direction::Horizontal){
            for(int i=0;i<length;i++){
                this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]='~';
                col++;
            }
        }
        else if(dir==Direction::Vertical){
            for(int i=0;i<length;i++){
                this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]='~';
                row++;
            }
        }
    }
    void Notebook::show(int page){
        if(page<0){
            throw invalid_argument{"This page doesn't exist"};
        }
        string s;
        for(int i=this->rowDownLim-2;i<this->rowUpLim+2;i++){
            if(i<limit){
               s+=""+to_string(i)+":  "; 
            }else{
              s+=""+to_string(i)+": ";  
            }
            for(int j=0;j<=limit;j++){
                if(this->note[""+to_string(page)+","+to_string(i)+","+to_string(j)]==0){
                    s+='_';
                    j++;
                }
                s+=this->note[""+to_string(page)+","+to_string(i)+","+to_string(j)];
            }
            s+='\n';
        }cout<<s<<endl;
    }

    int Notebook::illegal(int page, int row, int col, ariel::Direction dir, const string &str){
        int OK=1;
        if(dir==ariel::Direction::Horizontal){
            for (int i = 0; i < strlen(str); i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]=='_'){
                        OK=1;
                        continue;
                    }
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!=0){// && this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!='_'){
                    OK=0;
                    
                    return OK;
                }col++;
            }
        }
        else{
            for (int i = 0; i < strlen(str); i++){
                if(this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!=0 && this->note[""+to_string(page)+","+to_string(row)+","+to_string(col)]!='_'){
                    OK=0;
                    return OK;
                }row++;
            }
        }return OK;
    }
//}