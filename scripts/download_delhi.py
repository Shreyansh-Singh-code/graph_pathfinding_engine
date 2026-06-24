import osmnx as ox

print("Downloading Delhi road network...")

G = ox.graph_from_place(
    "National Capital Territory of Delhi, India",
    network_type="drive",
    simplify=True
)

ox.save_graphml(
    G,
    "../data/raw/delhi.graphml"
)

print("Saved to data/raw/delhi.graphml")