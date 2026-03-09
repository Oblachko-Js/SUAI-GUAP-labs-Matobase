import numpy as np
import random
import matplotlib.pyplot as plt

# Coordinates for dj89.tsp (89 cities)
coordinates = [
    (11511.3889, 42106.3889),
    (11503.0556, 42855.2778),
    (11438.3333, 42057.2222),
    (11438.3333, 42057.2222),
    (11438.3333, 42057.2222),
    (11785.2778, 42884.4444),
    (11785.2778, 42884.4444),
    (11785.2778, 42884.4444),
    (11785.2778, 42884.4444),
    (12363.3333, 43189.1667),
    (11846.9444, 42660.5556),
    (11503.0556, 42855.2778),
    (11963.0556, 43290.5556),
    (11963.0556, 43290.5556),
    (12300.0000, 42433.3333),
    (11973.0556, 43026.1111),
    (11973.0556, 43026.1111),
    (11461.1111, 43252.7778),
    (11461.1111, 43252.7778),
    (11461.1111, 43252.7778),
    (11461.1111, 43252.7778),
    (11600.0000, 43150.0000),
    (12386.6667, 43334.7222),
    (12386.6667, 43334.7222),
    (11595.0000, 43148.0556),
    (11595.0000, 43148.0556),
    (11569.4444, 43136.6667),
    (11310.2778, 42929.4444),
    (11310.2778, 42929.4444),
    (11310.2778, 42929.4444),
    (11963.0556, 43290.5556),
    (11416.6667, 42983.3333),
    (11416.6667, 42983.3333),
    (11595.0000, 43148.0556),
    (12149.4444, 42477.5000),
    (11595.0000, 43148.0556),
    (11595.0000, 43148.0556),
    (11108.6111, 42373.8889),
    (11108.6111, 42373.8889),
    (11108.6111, 42373.8889),
    (11108.6111, 42373.8889),
    (11183.3333, 42933.3333),
    (12372.7778, 42711.3889),
    (11583.3333, 43150.0000),
    (11583.3333, 43150.0000),
    (11583.3333, 43150.0000),
    (11583.3333, 43150.0000),
    (11583.3333, 43150.0000),
    (11822.7778, 42673.6111),
    (11822.7778, 42673.6111),
    (12058.3333, 42195.5556),
    (11003.6111, 42102.5000),
    (11003.6111, 42102.5000),
    (11003.6111, 42102.5000),
    (11522.2222, 42841.9444),
    (12386.6667, 43334.7222),
    (12386.6667, 43334.7222),
    (12386.6667, 43334.7222),
    (11569.4444, 43136.6667),
    (11569.4444, 43136.6667),
    (11569.4444, 43136.6667),
    (11155.8333, 42712.5000),
    (11155.8333, 42712.5000),
    (11155.8333, 42712.5000),
    (11155.8333, 42712.5000),
    (11133.3333, 42885.8333),
    (11133.3333, 42885.8333),
    (11133.3333, 42885.8333),
    (11133.3333, 42885.8333),
    (11133.3333, 42885.8333),
    (11003.6111, 42102.5000),
    (11770.2778, 42651.9444),
    (11133.3333, 42885.8333),
    (11690.5556, 42686.6667),
    (11690.5556, 42686.6667),
    (11751.1111, 42814.4444),
    (12645.0000, 42973.3333),
    (12421.6667, 42895.5556),
    (12421.6667, 42895.5556),
    (11485.5556, 43187.2222),
    (11423.8889, 43000.2778),
    (11423.8889, 43000.2778),
    (11715.8333, 41836.1111),
    (11297.5000, 42853.3333),
    (11297.5000, 42853.3333),
    (11583.3333, 43150.0000),
    (11569.4444, 43136.6667),
    (12286.9444, 43355.5556),
    (12355.8333, 43156.3889)
]

n = len(coordinates)
# Compute distance matrix
dist = np.zeros((n, n))
for i in range(n):
    for j in range(n):
        if i != j:
            dist[i][j] = np.sqrt((coordinates[i][0] - coordinates[j][0])**2 + (coordinates[i][1] - coordinates[j][1])**2)

# ACO parameters
alpha = 1.0
beta = 5.0
rho = 0.5
Q = 100
num_ants = 50
max_iter = 100
initial_pheromone = 1e-6

# Initialize pheromone
tau = np.full((n, n), initial_pheromone)

# Function to choose next city
def choose_next(current, visited, tau, dist):
    probs = []
    candidates = [c for c in range(n) if c not in visited]
    if not candidates:
        return None
    total = 0
    for next_city in candidates:
        if dist[current][next_city] == 0:
            continue
        p = (tau[current][next_city] ** alpha) * ((1.0 / dist[current][next_city]) ** beta)
        probs.append(p)
        total += p
    if total == 0:
        return random.choice(candidates)
    probs = [p / total for p in probs]
    return np.random.choice(candidates, p=probs)

# Main ACO loop
best_tour = None
best_length = float('inf')

for iteration in range(max_iter):
    ant_tours = []
    ant_lengths = []
    for ant in range(num_ants):
        start = random.randint(0, n-1)
        tour = [start]
        visited = set([start])
        current = start
        while len(tour) < n:
            next_city = choose_next(current, visited, tau, dist)
            if next_city is None:
                break
            tour.append(next_city)
            visited.add(next_city)
            current = next_city
        if len(tour) == n:
            # Close the tour
            tour.append(start)
            length = sum(dist[tour[i]][tour[i+1]] for i in range(n))
            ant_tours.append(tour)
            ant_lengths.append(length)
    
    # Update best
    if ant_lengths:
        min_length = min(ant_lengths)
        if min_length < best_length:
            best_length = min_length
            best_tour = ant_tours[ant_lengths.index(min_length)]
    
    # Evaporate pheromone
    tau = (1 - rho) * tau
    
    # Deposit pheromone
    for k in range(len(ant_tours)):
        length = ant_lengths[k]
        tour = ant_tours[k]
        for i in range(n):
            u = tour[i]
            v = tour[i+1]
            tau[u][v] += Q / length
            tau[v][u] += Q / length  # Since undirected

print("Best tour length:", best_length)
print("Best tour:", best_tour)

# Plot the best tour
x = [coordinates[i][0] for i in best_tour]
y = [coordinates[i][1] for i in best_tour]
plt.plot(x, y, 'r-')
plt.scatter(x[:-1], y[:-1], c='b')
plt.show()