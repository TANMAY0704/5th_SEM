import sys

sys.setrecursionlimit(10**6)  # Set the recursion limit to a higher value

def largestAlligator(n, W):
    def dfs(node, min_width):
        nonlocal ans
        if node == n - 1:  # Reached the destination pond
            ans = max(ans, min_width)
            return
        for i in range(n):
            if W[node][i] > 0:  # There is a channel
                new_min_width = min(min_width, W[node][i])
                dfs(i, new_min_width)

    ans = 0
    dfs(0, float('inf'))
    return ans


# Example usage
n = 5
W = [
    [0, 0, 10, 6, 0],
    [0, 0, 8, 0, 9],
    [10, 8, 0, 0, 7],
    [6, 0, 0, 0, 0],
    [0, 9, 7, 0, 0]
]

print(largestAlligator(n, W))
