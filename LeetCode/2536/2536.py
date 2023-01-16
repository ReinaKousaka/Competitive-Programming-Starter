from typing import *

class Solution:
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        diff = [[0 for _ in range(n + 1)] for _ in range(n + 1)]
        # adding 1 to diff[i][j] means adding 1 to the bottom-right rectangle in mat
        # 2d differnce matrix template
        
        for i1, j1, i2, j2 in queries:
            diff[i1][j1] += 1
            diff[i2 + 1][j2 + 1] += 1
            diff[i1][j2 + 1] -= 1
            diff[i2 + 1][j1] -= 1
        
        res = [[0 for _ in range(n)] for _ in range(n)]        
        for i in range(n):
            for j in range(n):
                if i == 0 and j == 0:
                    res[0][0] = diff[0][0]
                elif i == 0:
                    res[i][j] = res[i][j - 1] + diff[i][j]
                elif j == 0:
                    res[i][j] = res[i - 1][j] + diff[i][j]
                else:
                    res[i][j] = res[i - 1][j] + res[i][j - 1] - res[i - 1][j - 1] + diff[i][j]
        return res
