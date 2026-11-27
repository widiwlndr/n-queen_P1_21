#include "nqueens.h"
#include <vector>
#include <cstdint>

using namespace std;

int getBitIndex(uint32_t bit) {
    int index = 0;

    while ((bit & 1u) == 0) {
        bit >>= 1;
        index++;
    }

    return index;
}

vector<vector<int>> solveNQueens(int n) {
    vector<vector<int>> solutions;
    vector<int> pos(n, -1);

    uint32_t mask = (1u << n) - 1u;

    auto dfs = [&](auto&& self,
                   int row,
                   uint32_t cols,
                   uint32_t diagL,
                   uint32_t diagR) -> void {

        if (row == n) {
            solutions.push_back(pos);
            return;
        }

        uint32_t available =
            mask & ~(cols | diagL | diagR);

        while (available != 0) {
            uint32_t bit = available & (~available + 1u);

            available ^= bit;

            int col = getBitIndex(bit);

            pos[row] = col;

            self(self,
                 row + 1,
                 cols | bit,
                 ((diagL | bit) << 1) & mask,
                 (diagR | bit) >> 1);

            pos[row] = -1;
        }
    };

    dfs(dfs, 0, 0, 0, 0);

    return solutions;
}
