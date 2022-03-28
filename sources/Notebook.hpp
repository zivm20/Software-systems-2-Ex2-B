#pragma once
#include "Direction.hpp"
#include <map>
#include <array>
#include <string>



namespace ariel{
    const int MAX_LINE_LEN = 100;
    const int MAX_CHAR_VAL = 126, MIN_CHAR_VAL = 32;
    class Line{
        private:
            std::array<char,MAX_LINE_LEN> content;
            
        public:
            Line();
            void write(int col, std::string txt);
            std::string read(int col, int len);
            void erase(int col, int len);
            void show();
            void validWrite(int col, int len);
            ~Line();
            
    };

    class Page{
        private:
            std::map<int,Line> lines;
            
        public:
            void write(int row, int col, ariel::Direction dir, std::string txt);
            std::string read(int row, int col, ariel::Direction dir, int len);
            void erase(int row, int col, ariel::Direction dir, int len);
            void show();
            //expand the page if needed, handle row out of bounds
            void generateRows(int row, int col, ariel::Direction dir, int len);
            ~Page();
            
    };

    class Notebook{
        private:
            std::map<int,Page> pages;
            
        public:
            void write(int page, int row, int col, ariel::Direction dir, std::string txt);
            std::string read(int page, int row, int col, ariel::Direction dir, int len);
            void erase(int page, int row, int col, ariel::Direction dir, int len);
            void show(int page);
            //makes the page if it doesnt exist
            void generatePages(int page);
            ~Notebook();


    };
}
