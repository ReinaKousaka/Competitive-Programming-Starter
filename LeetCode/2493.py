from typing import *
from collections import deque, defaultdict

class UF:
    def __init__(self, size: int) -> None:
        self.size = size
        self.parent = list(range(size))
        self.rank = [1] * size
    
    def find(self, x: int) -> int:
        while x != self.parent[x]:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x
    
    def union(self, x: int, y: int) -> None:
        x, y = self.find(x), self.find(y)
        if x == y: return
        if self.rank[x] <= self.rank[y]:
            self.parent[x] = y
        else:
            self.parent[y] = x
        if self.rank[x] == self.rank[y]:
            self.rank[y] += 1
    

class Solution:
    def magnificentSets(self, n: int, edges: List[List[int]]) -> int:
        # 1. the result = the sum of magnificentSets() on each connected components
        # 2. return -1 if and only if any component contains an odd cycle,
        # which is equivalent to not 2-colorable (bipartite graph)
        # 3. for each component, compute the diameter
        # i.e. longest shortest path between any two vertices
        dsu = UF(n)
        adjacent = [[] for _ in range(n)]
        for a, b in edges:
            adjacent[a - 1].append(b - 1)
            adjacent[b - 1].append(a - 1)
            dsu.union(a - 1, b - 1)
        
        # check if the graph is bipartite by coloring with dfs
        def dfs(vertex: int, colors: List[int], color=1) -> bool:
            colors[vertex] = color
            for w in adjacent[vertex]:
                if not colors[w]:
                    # dye any vertex when first meet
                    if not dfs(w, colors, -color): return False
                else:
                    # odd cycle detected
                    if colors[vertex] == colors[w]: return False
            return True

        # calculate diameter
        def bfs(vertex: int) -> int:
            visited = set([vertex])
            q = deque([vertex])
            depth = 0
            while len(q):
                size = len(q)
                for _ in range(size):
                    v = q.popleft()
                    for w in adjacent[v]:
                        if w in visited: continue
                        visited.add(w)
                        q.append(w)
                depth += 1
            return depth

        colors = [0] * n
        diameters = defaultdict(int)
        for i, color in enumerate(colors):
            if not color and not dfs(i, colors): return -1
            diameters[dsu.find(i)] = max(diameters[dsu.find(i)], bfs(i))
        return sum(diameters.values())
