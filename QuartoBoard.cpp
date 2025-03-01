#include "QuartoBoard.h"
#include "HashMap.cpp"

QuartoBoard::QuartoBoard() {
    occupation = white = tall = full = circle = 0;
    availableStoneCount = 16;

     for (bool & availableStone : availableStones) availableStone = true;
}

QuartoBoard::QuartoBoard(const QuartoBoard &b) {
    occupation = b.occupation;
    circle = b.circle;
    white = b.white;
    tall = b.tall;
    full = b.full;

    availableStoneCount = b.availableStoneCount;
    for (int i = 0; i < 16; i++) availableStones[i] = b.availableStones[i];
}

bool QuartoBoard::equals(const QuartoBoard &b) const {
    return
        occupation == b.occupation &&
        circle == b.circle &&
        white == b.white &&
        tall == b.tall &&
        full == b.full
    ;
}

void QuartoBoard::print() {

    // Print placed stones
    unsigned int occupation_ite = occupation;
    for (int y = 0; y < height; y++) {
        std::cout << "|";
        for (int x = 0; x < width-1; x++) {
            if (occupation_ite & 1) {
                u_int8_t stone =
                        isFree(full, x, y) << 3 |
                        isFree(tall, x, y) << 2 |
                        isFree(white, x, y) << 1 |
                        isFree(circle, x, y);
                std::cout << " " << stoneToCharTable[stone] << " |";
            }
            else {
                std::cout << "  -  " << "|";
            }
            occupation_ite >>= 1;
        }
        occupation_ite >>= 1;
        std::cout << "\n";
    }

    // Print available Stones
    std::cout << "\nAvailable Stones:\n";
    for (int i = 0; i < 16; i++) if (availableStones[i]) std::cout << stoneToCharTable[i] << " ";
    std::cout << "\n";
}

bool QuartoBoard::isFree(u_int32_t bitBoard, u_int8_t x, u_int8_t y) {
    return (bitBoard >> (y*width + x)) & 1;
}

bool QuartoBoard::isFree(u_int8_t x, u_int8_t y) const {
    return isFree(y*width + x);
}

bool QuartoBoard::isFree(u_int8_t offset) const {
    return !((occupation >> offset) & 1);
}

void QuartoBoard::place(u_int8_t stone, u_int8_t x, u_int8_t y) {
    place(stone, y*width + x);
}

void QuartoBoard::place(u_int8_t stone, u_int8_t offset) {
    // Remove stone from available list
    availableStoneCount--;
    availableStones[stone] = false;

    u_int32_t stonePlacement = 1 << offset;

    // base placement
    occupation |= stonePlacement;

    // circle / square
    if (stone & 1) circle |= stonePlacement;

    // white / black
    stone >>= 1;
    if (stone & 1) white |= stonePlacement;

    // tall / short
    stone >>= 1;
    if (stone & 1) tall |= stonePlacement;

    // full / hole
    stone >>= 1;
    if (stone & 1) full |= stonePlacement;
}

bool QuartoBoard::has4Streak(u_int32_t bitBoard) {
    // horizontal check
    u_int32_t temp_bitBoard = bitBoard >> 2;
    if (bitBoard & bitBoard >> 1 & temp_bitBoard & temp_bitBoard >> 1) return true;

    // vertical check
    temp_bitBoard = bitBoard >> 2*width;
    if (bitBoard & bitBoard >> width & temp_bitBoard & temp_bitBoard >> width) return true;

    // diagonal left check
    u_int8_t offset = width - 1;
    temp_bitBoard = bitBoard >> 2*offset;
    if (bitBoard & bitBoard >> offset & temp_bitBoard & temp_bitBoard >> offset) return true;

    // diagonal right check
    offset = width + 1;
    temp_bitBoard = bitBoard >> 2*offset;
    if (bitBoard & bitBoard >> offset & temp_bitBoard & temp_bitBoard >> offset) return true;

    return false;
}

bool QuartoBoard::hasWin() {
    // Optimisation: check if there is a potential win, if not, we return false
    if (!has4Streak(occupation)) return false;

    if (has4Streak(circle)) return true;
    if (has4Streak(white)) return true;
    if (has4Streak(tall)) return true;
    if (has4Streak(full)) return true;

    if (has4Streak(occupation ^ circle)) return true;
    if (has4Streak(occupation ^ white)) return true;
    if (has4Streak(occupation ^ tall)) return true;
    if (has4Streak(occupation ^ full)) return true;

    return false;
}

u_int32_t QuartoBoard::getKey() const {
    u_int32_t circle_parity = circle<<1;
    circle_parity ^= circle_parity<<1;
    circle_parity ^= circle_parity<<1;
    circle_parity ^= circle_parity<<1;
    return occupation | circle_parity;
}

u_int8_t QuartoBoard::bitboardTransposition(u_int32_t bitBoard, bool high_bits) {
    if (high_bits) bitBoard >>= 10;

    return bitBoard & 0xF | (bitBoard & 0x1E0) >> 1;
}