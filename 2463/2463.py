from typing import *
import numpy as np
from scipy.optimize import linear_sum_assignment

class Solution:
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:
        cost = []
        for pos_f, limit in factory:
            row = [abs(pos_r - pos_f) for pos_r in robot]
            for _ in range(limit):
                cost.append(row)
        cost = np.array(cost)
        row_idx, col_idx = linear_sum_assignment(cost)
        return cost[row_idx, col_idx].sum()
