#include "Board.hpp"
#include <string>

using namespace ariel;

Board::Board() {
    b = nullptr;
    min_row = min_col = row_size = col_size = 0;
}

Board::~Board() {
    if(b != nullptr) {
        for (int i = 0; i < row_size; i++) {
            delete[] b[i];
        }
        delete[] b;
    }
}
void Board::post(u_int r,u_int c,Direction d,std::string m) {
    u_int m_size = m.size();
    resize(r,c,d,m_size);
    u_int row = r-min_row , col = c-min_col;
    for (unsigned long i = 0; i < m_size; i++) {
        b[row][col] = m[i]; 
        if(d == Direction::Horizontal) {
            col++;
        }
        else {
            row++;
        }
    }
}

void Board::resize(u_int r, u_int c, Direction d, u_int l) {
    u_int row_step = 0 , col_step = 0;
    if(d == Direction::Vertical) {
        row_step = 1;
    }
    else {
        col_step = 1;
    }
    if(r >= min_row && c >= min_col && (c+l*col_step < min_col + col_size) && (r+l*row_step < min_row + row_size)) {
        return;
    }
    if(b == nullptr) {
        min_row = r;
        min_col = c;
    }
    u_int new_min_row = min(min_row,r) , new_min_col = min(min_col,c);
    u_int new_max_row = max(min_row + row_size, r+l*row_step) , new_max_col = max(min_col + col_size, c + l*col_step);
    u_int new_row_size = new_max_row - new_min_row + 1;
    u_int new_col_size = new_max_col - new_min_col + 1;
    char** temp = new char*[new_row_size];
    for (int i = 0; i < new_row_size; i++) {
        temp[i] = new char[new_col_size];
    }
    for (int i = 0; i < new_row_size; i++) {
        for (int j = 0; j < new_col_size; j++) {
            temp[i][j] = '_';
        }
    }
    if(b != nullptr) {
        for (u_int i = 0; i < row_size; i++) {
            for (u_int j = 0; j < col_size; j++) {
                temp[min_row - new_min_row + i][min_col - new_min_col + j] = b[i][j];
            }
        }
        for (int i = 0; i < row_size; i++) {
            delete[] b[i];
        }
        delete[] b;
    }
    min_row = new_min_row;
    min_col = new_min_col;
    row_size = new_row_size;
    col_size = new_col_size;
    b = temp;
}

u_int Board::min(u_int x, u_int y) {
    if(x < y) {return x; }
    return y;
}

u_int Board::max(u_int x, u_int y) {
    if(x > y) {return x; }
    return y;
}

std::string Board::read(u_int r,u_int c,Direction d,u_int l) {
    std::string ans;
    ans = "";
    u_int row = r-min_row , col = c-min_col;
    while(l > 0) {
        if(row < row_size && row >= 0 && col < col_size && col >= 0) {
            ans += b[row][col];
        }
        else {
            ans += "_";
        }
        if(d == Direction::Horizontal) {
            col++;
        }
        else {
            row++;
        }
        l--;
    }
    return ans;
}
void Board::show() {
    for (u_int i = 0; i < row_size; i++) {
        std::cout << (i+min_row) << ": "; 
        for (int j = 0; j < col_size; j++) {
            std::cout << b[i][j];
        }
        std::cout << std::endl;
    }
}

// int main() {
//     Board b;
//     b.post(80,40,Direction::Vertical, "abcde");
//     b.post(75,30,Direction::Horizontal, "abcde");
//     b.post(84,35,Direction::Horizontal, "xyzwqzzz");
//     b.show();
//     return 0;
// }