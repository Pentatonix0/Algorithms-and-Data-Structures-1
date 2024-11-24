import matplotlib.pyplot as plt

N_vals = []
S_vals = []

with open('monte_carlo_results.txt', 'r') as f:
    for line in f:
        N, S = map(float, line.split())
        N_vals.append(N)
        S_vals.append(S)

exact_area = 0.944517185899

plt.plot(N_vals, S_vals, label='Приближенная площадь', color='blue')

plt.axhline(y=exact_area, color='red', linestyle='--', label=f'Точное значение: {exact_area:.5f}')

plt.xlabel('Количество точек (N)')
plt.ylabel('Приближенная площадь')
plt.title('Зависимость приближенной площади от количества точек')
plt.grid(True)
plt.legend()
plt.show()
