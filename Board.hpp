#pragma once
#include <iostream>
#include "Direction.hpp"

namespace ariel {
    class Board {
        private:
            char** b;
            u_int min_row, min_col, row_size, col_size;
            
            void resize(u_int,u_int,Direction,u_int);
            u_int min(u_int,u_int);
            u_int max(u_int,u_int);
        public:
            Board();
            ~Board();
            void post(u_int,u_int,Direction,std::string);
            std::string read(u_int,u_int,Direction,u_int);
            void show();
    };
};