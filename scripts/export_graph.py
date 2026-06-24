import osmnx as ox
import pandas as pd

G = ox.load_graphml("../data/raw/delhi.graphml")

nodes = []
mapping = {}

for idx, node in enumerate(G.nodes()):
    mapping[node] = idx

for node in G.nodes(data=True):
    osm_id = node[0]

    nodes.append([
        mapping[osm_id],
        node[1]["y"],
        node[1]["x"]
    ])

edges = []

for u, v, data in G.edges(data=True):
    edges.append([
        mapping[u],
        mapping[v],
        data.get("length", 1.0)
    ])

pd.DataFrame(
    nodes,
    columns=["id", "lat", "lon"]
).to_csv(
    "../data/processed/nodes.csv",
    index=False
)

pd.DataFrame(
    edges,
    columns=["source", "target", "weight"]
).to_csv(
    "../data/processed/edges.csv",
    index=False
)

print("Export complete")