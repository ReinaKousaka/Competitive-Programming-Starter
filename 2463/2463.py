from typing import *
import numpy as np
# https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.linear_sum_assignment.html
from scipy.optimize import linear_sum_assignment

class Solution:
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:
        adjacent = []
        for pos_f, limit in factory:
            row = [abs(pos_r - pos_f) for pos_r in robot]
            for _ in range(limit):
                adjacent.append(row)
        adjacent = np.array(adjacent)
        row_idx, col_idx = linear_sum_assignment(adjacent)
        return adjacent[row_idx, col_idx].sum()
