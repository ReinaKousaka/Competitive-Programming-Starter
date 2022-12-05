from typing import *
from bisect import bisect_left

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def closestKValues(self, root: Optional[TreeNode], target: float, k: int) -> List[int]:
        nums = self.inorder_traverse(root)
        r = bisect_left(nums, target)   # first place >= target
        l = r - 1
        res = []
        for _ in range(k):
            if l < 0 or (r < len(nums) and abs(nums[r] - target) < abs(nums[l] - target)):
                res.append(nums[r])
                r += 1
            else:
                res.append(nums[l])
                l -= 1
        return res

    
    def inorder_traverse(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        else:
            return self.inorder_traverse(root.left) + \
                [root.val] + self.inorder_traverse(root.right)