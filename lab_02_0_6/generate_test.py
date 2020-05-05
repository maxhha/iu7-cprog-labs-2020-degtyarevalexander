from random import randint

H, R, N = map(int, input("Header, repeats and array length:\n").split())

print(H, R, N, end=" ")

for i in range(N):
    print(randint(-100, 100), end=" \n"[i+1==N])
