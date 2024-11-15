import heapq
from collections import defaultdict

def find_project_order(n, m, groups, dependencies):
    adj = defaultdict(list)
    indegree = [0] * n

    for a, b in dependencies:
        adj[a].append(b)
        indegree[b] += 1

    pq = []
    for i in range(n):
        if indegree[i] == 0:
            heapq.heappush(pq, (groups[i], i))

    result = []
    while pq:
        group_id, project_id = heapq.heappop(pq)
        result.append(project_id + 1)
        for neighbor in adj[project_id]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                heapq.heappush(pq, (groups[neighbor], neighbor))

    if len(result) != n:
        return [-1]
    
    return result

n, m = map(int, input().split())
groups = list(map(int, input().split()))
dependencies = [tuple(map(lambda x: int(x) - 1, input().split())) for _ in range(m)]

order = find_project_order(n, m, groups, dependencies)
print(" ".join(map(str, order)))

#100% marks