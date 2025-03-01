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
For that we have an `availableStones` u_int16, that contains maximum 16 items.
A 0 means that the stone is available, a 1 means that it isn't.

A stone is a 4 bit int that is encoded this way:
1) 0 -> is square / 1 -> is circle
2) 0 -> is black / 1 -> is white
3) 0 -> is short / 1 -> is tall
4) 0 -> has hole / 1 -> is full


### Hash Map class

Temporarly, a HashMap will not store keys, but will store the entire QuartoBoard in each cells

But, to know where to store the HashMap, a temporary, non-unique, key has to be created, it is:
`key = occupation | circle_parity`
With `circle_parity = circle<<1 ^ circle<<2 ^ circle<<3 ^ circle<<4`

It is important to note that `key` is a 32 bit integer, but that its bit over the 20th are all empty
So the HashMap should not be greater than `2^20 = 1048576` items !