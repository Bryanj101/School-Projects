import timeit
from statistics import mean


def binomial_bottomup(n, k):
    arr = [[0 for _ in range(k + 1)] for _ in range(n + 1)]

    for i in range(n + 1):
        for j in range(min(i, k) + 1):
            if j == 0 or j == i:
                arr[i][j] = 1
            else:
                arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1]
    return arr[n][k]


def binomial_memo(n, k, mem):
    if mem[n][k] != -1:
        return mem[n][k]
    elif k == 0 or k == n:
        mem[n][k] = 1
        return mem[n][k]
    mem[n][k] = (binomial_memo(n - 1, k, mem) + binomial_memo(n - 1, k - 1, mem))
    return mem[n][k]


def memo_setup(n, k):
    mem = [[-1 for _ in range(k + 1)] for _ in range(n + 1)]
    return binomial_memo(n, k, mem)


if __name__ == '__main__':
    n = 100
    k = 90

    print(mean(timeit.repeat("binomial_bottomup(n, k)",
                             globals=globals(),
                             number=1, repeat=10000)))
    print(mean(timeit.repeat("memo_setup(n, k)",
                             globals=globals(),
                             number=1, repeat=10000)))
    