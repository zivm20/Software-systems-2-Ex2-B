#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace ariel;


#pragma region Line
    Line::Line():content(){
        content.fill('_');
    }
    void Line::write(int col, string txt){
        for(size_t i = 0; i<txt.length(); i++){
            content.at(i+size_t(col)) = txt[i];
        }
    }
    string Line::read(int col, int len){
        string out;
        for(size_t i = 0; i<len; i++){
            out+=content.at(size_t(col)+i);
        }
        return out;
    }
    void Line::erase(int col, int len){
        for(size_t i = 0; i<len; i++){
            content.at(i+size_t(col)) = '~';
        }
    }
    void Line::show(){
        cout<<read(0,MAX_LINE_LEN);
    }
    void Line::validWrite(int col, int len){
        for(size_t i = 0; i<len; i++){
            if(content.at(i+size_t(col)) != '_'){
                throw std::invalid_argument("Invalid Write");
            }
        }
    }
    Line::~Line(){
       
    }
#pragma endregion Line


#pragma region Page
    
    void Page::write(int row, int col, Direction dir, string txt){
        generateRows(row,col,dir,txt.length());
        for(char c:txt){
            if(c < MIN_CHAR_VAL || c > MAX_CHAR_VAL){
                throw std::invalid_argument("Invalid character Write");
            }
        }

        //handle writing
        if(Direction::Vertical == dir){
            //check if we are allowed to write in this area
            for(size_t i=0; i<txt.length(); i++){
                lines.at(i+size_t(row)).validWrite(col,1);
            }
            //write vertically
            for(size_t i=0; i<txt.length(); i++){
                lines.at(i+size_t(row)).write(col,string(1, txt[i]));
            }
        }
        else{
            //check if we are allowed to write in this area
            lines.at(size_t(row)).validWrite(col,txt.length());
            //write horizontally
            lines.at(size_t(row)).write(col,txt);
        }
    }

    string Page::read(int row, int col,Direction dir, int len){
        generateRows(row,col,dir,len);

        //handle read
        string out;
        if(Direction::Vertical == dir){
            //read vertically
            for(size_t i=0; i<len; i++){
                out += lines.at(i+size_t(row)).read(col,1);
            }
            
        }
        else{
            //read horizontally
            out = lines.at(size_t(row)).read(col,len);
        }
        return out;
    }

    void Page::erase(int row, int col, Direction dir, int len){
        generateRows(row,col,dir,len);

        //handle erase
        if(Direction::Vertical == dir){
            //erase vertically
            for(size_t i=0; i<len; i++){
                lines.at(i+size_t(row)).write(col,"~");
            }
        }
        else{
            //erase horizontally
            lines.at(size_t(row)).write(col,string(size_t(len),'~'));
        }

    }

    void Page::show(){
        for (auto i = lines.begin(); i != lines.end(); ++i) {
            cout << i->second.read(0,MAX_LINE_LEN) << endl;
        }
    }

    void Page::generateRows(int row, int col, Direction dir, int len){
        //make sure we are not out of row bounds
        if(dir == Direction::Horizontal && col+len>MAX_LINE_LEN){
            throw std::invalid_argument("Out of row bounds!");
        }

        for(int i=0; (i < len && Direction::Vertical == dir) || (i<1 && Direction::Horizontal == dir); i++ ){
            lines.insert(pair<int,Line>(i+row,Line()));
        }
    }
    Page::~Page(){

    }

#pragma endregion page


#pragma region Notebook

    void Notebook::write(int page, int row, int col,Direction dir, string txt){
        generatePages(page);
        pages.at(page).write(row,col,dir,move(txt));
    }
    
    string Notebook::read(int page, int row, int col, Direction dir, int len){
        generatePages(page);
        return pages.at(page).read(row,col,dir,len);
    }
    void Notebook::erase(int page, int row, int col, Direction dir, int len){
        generatePages(page);
        pages.at(page).erase(row,col,dir,len);
    }
    void Notebook::show(int page){
        generatePages(page);
        pages.at(page).show();
    }
    void Notebook::generatePages(int page){
        pages.insert(pair<int,Page>(page,Page()));
    }
    Notebook::~Notebook(){

    }

#pragma endregion Notebook










