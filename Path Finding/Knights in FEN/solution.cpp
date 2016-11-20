/*
 * UVa Online Judge - Knights in FEN
 * Path Finding in AI - Search Tree
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1363
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <bitset>

#define LOG(x) std::cout << x << std::endl;

struct Position
{
    int x;
    int y;
    Position() { }
    Position(int x, int y) : x(x), y(y) { }
    Position(int index) : x(index % 5), y(index / 5) { }
    int index() { return 5 * y + x; }
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

class Chessboard
{
public:
    int level{0};
    int board{0};
    size_t hash{0};
    Position slot;

    Chessboard() = delete;

    Chessboard(const Chessboard& other) : level(other.level), board(other.board), hash(other.hash), slot(other.slot) { }

    Chessboard(Position slot, const char pieces[]) : slot(slot)
    {
        for (int i = 24; i >= 0; --i)
        {
            if (pieces[i] != '0')
            {
                board |= (1 << i);
            }
        }
        hash = board | (slot.x << 25) | (slot.y << 28);
    }

    bool operator==(const Chessboard& other) const
    {
       return hash == other.hash;
    }

    bool operator!=(const Chessboard& other) const
    {
        return !operator==(other);
    }

    void dump()
    {
        std::bitset<32> b1(board);
        std::bitset<32> b2(slot.x);
        std::bitset<32> b3(slot.y);
        std::bitset<32> b4(hash);
        LOG("X: " << slot.x);
        LOG("Y: " << slot.y);
        LOG("Board: " << b1.to_string());
        LOG("X:     " << b2.to_string());
        LOG("Y:     " << b3.to_string());
        LOG("Hash:  " << b4.to_string());
        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                Position p(x, y);
                if (p == slot)
                {
                    std::cout << " ";
                }
                else if (board & (1 << p.index()))
                {
                    std::cout << "1";
                }
                else
                {
                    std::cout << "0";
                }
            }
            std::cout << std::endl;
        }
    }

    std::vector<Position> moves()
    {
        std::vector<Position> moves;
        int mx[] = {  2,  2, -2, -2,  1,  1, -1, -1 };
        int my[] = { -1,  1, -1,  1, -2,  2, -2,  2 };
        for (int i = 0; i < 8; ++i)
        {
            if (slot.x + mx[i] >= 0 && slot.x + mx[i] < 5 && slot.y + my[i] >= 0 && slot.y + my[i] < 5)
            {
                moves.emplace_back(slot.x + mx[i], slot.y + my[i]);
            }
        }
        return moves;
    }

    void move(Position move)
    {

        if (board & (1 << move.index()))
        {
            board |= (1 << slot.index());
            board &= ~(1 << move.index());
        }
        slot = move;
        hash = board | (slot.x << 25) | (slot.y << 28);
    }
};

namespace std
{
    template<>
    struct hash<Chessboard>
    {
        size_t operator()(const Chessboard& board) const
        {
            return board.hash;
        }
    };
}

int main(int argc, char **argv)
{
    int N = 0;
    scanf("%d", &N);
    std::vector<Chessboard> chessboards;
    chessboards.reserve(N);
    Chessboard base(Position(12), "1111101111000110000100000");
    for (int i = 0; i < N; ++i)
    {
        Position slot;
        char pieces[25];
        int count = 0;
        while (count < 25)
        {
            char c = fgetc(stdin);
            switch (c)
            {
                case '0':
                    pieces[count++] = '0';
                    break;
                case '1':
                    pieces[count++] = '1';
                    break;
                case ' ':
                    slot = Position(count);
                    pieces[count++] = '0';
                    break;
            };
        }
        chessboards.emplace_back(slot, pieces);
    }
    for (int i = 0; i < N; ++i)
    {
        std::unordered_set<Chessboard> visited;
        std::queue<Chessboard> queue;
        queue.push(chessboards[i]);
        bool found = false;
        while (queue.size() > 0)
        {
            Chessboard& cb = queue.front();
            visited.insert(cb);
            if (base == cb)
            {
                std::cout << "Solvable in " << cb.level << " move(s)." << std::endl;
                found = true;
                break;
            }
            if (cb.level < 10)
            {
                for (auto move : cb.moves())
                {
                    Chessboard ncb(cb);
                    ncb.move(move);
                    if (visited.find(ncb) == visited.end())
                    {
                        ncb.level = cb.level + 1;
                        queue.push(ncb);
                    }
                }
            }
            queue.pop();
        }
        if (!found)
        {
            std::cout << "Unsolvable in less than 11 move(s)." << std::endl;
        }
    }
}
