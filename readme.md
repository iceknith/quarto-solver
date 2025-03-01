This is a Quarto solver written in C++

# How to run

# Technical details

### QuartoBoard class

Our way of storing quarto boards. It contains 5 bitboards:
- `occupation` -> the spots occupied by stones
- `circle` -> the spots occupied by circle stones
- `white` -> the spots occupied by white stones
- `tall` -> the spots occupied by tall stones
- `full` -> the spots occupied by full (with no holes) stones

for each property bitboard (the 4 last ones) can obtain its opposite bitboards, by doing an XOR with `occupation`

The class also stores the **available stones**
For that we have an `availableStones` array, that contains maximum 16 items.

A stone is a 4 bit int that is encoded this way:
1) 0 -> is square / 1 -> is circle
2) 0 -> is black / 1 -> is white
3) 0 -> is short / 1 -> is tall
4) 0 -> has hole / 1 -> is full