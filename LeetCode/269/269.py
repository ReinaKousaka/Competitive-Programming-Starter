from typing import *
from collections import deque

class Queue(deque):
    enqueue = deque.append
    dequeue = deque.popleft
    def front(self):
        return self[-1]
    def size(self):
        return len(self)

class Solution:
    def alienOrder(self, words: List[str]) -> str:
        indegree = {}   # char -> int
        neighbors = {}  # char -> [char]

        for word in words:
            for ch in word:
                if ch not in indegree:
                    indegree[ch] = 0
                    neighbors[ch] = []
        
        for i in range(len(words) - 1):
            curr, next = words[i], words[i + 1]
            diff = False
            for j in range(min(len(curr), len(next))):
                if curr[j] != next[j]:
                    diff = True
                    neighbors[curr[j]].append(next[j])
                    break
            if diff and len(curr) > len(next):
                return ""
        
        q = deque()



