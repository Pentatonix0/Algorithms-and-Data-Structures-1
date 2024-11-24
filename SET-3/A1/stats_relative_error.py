import matplotlib.pyplot as plt

exact_area = 0.944517185899

N_vals = []
S_vals = []
relative_errors = []

with open('monte_carlo_results.txt', 'r') as f:
    for line in f:
        N, S = map(float, line.split())
        N_vals.append(N)
        S_vals.append(S)

        relative_error = abs(S - exact_area) / exact_area
        relative_errors.append(relative_error)

plt.plot(N_vals, relative_errors, label='Относительное отклонение', color='green')


plt.xlabel('Количество точек (N)')
plt.ylabel('Относительное отклонение')
plt.title('Зависимость относительного отклонения от количества точек')
plt.grid(True)
plt.legend()
plt.show()
