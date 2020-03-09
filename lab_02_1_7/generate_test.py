from random import randint

N = int(input("Number of elements:\n"))

print(N, end=" ")
for i in range(N):
    print(randint(-100, 100), end=" \n"[i == N - 1])
