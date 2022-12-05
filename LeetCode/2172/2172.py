from typing import *
import numpy as np
from scipy.optimize import linear_sum_assignment

class Solution:
    def maximumANDSum(self, nums: List[int], numSlots: int) -> int:
        cost = []
        for slot in range(1, numSlots + 1):
            row = [num & slot for num in nums]
            cost.append(row)
            cost.append(row)
        cost = np.array(cost)
        row_idx, col_idx = linear_sum_assignment(cost, maximize=True)
        return cost[row_idx, col_idx].sum()
