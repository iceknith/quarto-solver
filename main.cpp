#include <iostream>
#include "QuartoSolver.cpp"
#include <ctime>
#include <bitset>

int main() {
    auto *b = new QuartoBoard();
    b->place(3, 1, 2);
    b->place(2, 0, 0);
    b->place(4, 2, 3);
    b->place(0, 2, 2);
    b->place(5, 3, 3);
    b->place(6, 3, 1);


    hashMap = new HashMap(10000000);

    u_int8_t stoneint = 1;
    auto start = time(nullptr);
    int place = bestMovePlay(b, stoneint);
    auto end = time(nullptr);


    std::cout << "Best place : (" << place%5 << ";" << place/5 << ")" << "\nFound in " << end - start << "s\n";
    std::cout << "Looked Up Pos : " << lookedUpPos << "\nExplored Pos : " << posExplored << "\nTime Spend with the hash map : " << timer/1000000000 << "s\n";
    b->place(stoneint, place);
    b->print();

    return 0;
}
