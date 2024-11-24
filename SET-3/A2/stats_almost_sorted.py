import matplotlib.pyplot as plt

N_vals = []
T_vals = []

with open('mergeSort_almost_sorted.txt', 'r') as f:
    for line in f:
        N, S = map(float, line.split())
        N_vals.append(N)
        T_vals.append(S)

plt.plot(N_vals, T_vals, label='mergeSort', color='red')


N_vals = []
T_vals = []

with open('hybridSort_almost_sorted_threshold30.txt', 'r') as f:
    for line in f:
        N, S = map(float, line.split())
        N_vals.append(N)
        T_vals.append(S)

plt.plot(N_vals, T_vals, label='hybridSort', color='green')

plt.xlabel('Размер массива (N)')
plt.ylabel('Время (мс)')
plt.title('Массив со почти отсортированными данными')
plt.grid(True)
plt.legend()
plt.show()
