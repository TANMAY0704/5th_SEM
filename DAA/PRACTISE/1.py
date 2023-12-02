import heapq

def dijkstra(graph, start):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    previous_nodes = {node: None for node in graph}
    priority_queue = [(0, start)]
    
    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)
        
        if current_distance > distances[current_node]:
            continue
        
        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_nodes[neighbor] = current_node
                heapq.heappush(priority_queue, (distance, neighbor))
    
    return distances, previous_nodes

def create_graph():
    graph = {}
    num_nodes = int(input("Enter the number of nodes: "))
    
    for _ in range(num_nodes):
        node = input("Enter the name of the node: ")
        graph[node] = {}
        
        num_neighbors = int(input(f"Enter the number of neighbors for node {node}: "))
        
        for _ in range(num_neighbors):
            neighbor = input("Enter the name of the neighbor: ")
            weight = int(input(f"Enter the weight of the edge between {node} and {neighbor}: "))
            graph[node][neighbor] = weight
    
    return graph

def get_path(previous_nodes, start, end):
    path = []
    current_node = end
    while current_node is not None:
        path.insert(0, current_node)
        current_node = previous_nodes[current_node]
    return path

# Example usage:
user_graph = create_graph()
start_node = input("Enter the starting node: ")
end_node = input("Enter the ending node: ")

shortest_distances, previous_nodes = dijkstra(user_graph, start_node)
shortest_path = get_path(previous_nodes, start_node, end_node)

print(f"Shortest distance from {start_node} to {end_node}: {shortest_distances[end_node]}")
print(f"Shortest path: {shortest_path}")
