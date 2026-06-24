import pandas as pd
import folium
from pathlib import Path

RESULTS = Path("../results")

# -------------------------------------------------
# Configuration
# -------------------------------------------------

ALGORITHMS = {
    "Dijkstra": {
        "route": "dijkstra_route.csv",
        "frontier": "dijkstra_frontier.csv",
        "path_color": "#0066ff",
        "frontier_color": "#87cefa"
    },
    "A*": {
        "route": "astar_route.csv",
        "frontier": "astar_frontier.csv",
        "path_color": "#00aa44",
        "frontier_color": "#7CFC00"
    },
    "Bidirectional": {
        "route": "bidirectional_route.csv",
        "frontier": "bidirectional_frontier.csv",
        "path_color": "#8A2BE2",
        "frontier_color": "#DDA0DD"
    },
    "Weighted A* (ε=1.2)": {
        "route": "weighted_route.csv",
        "frontier": "weighted_frontier.csv",
        "path_color": "#ff8800",
        "frontier_color": "#ffd54f"
    }
}

# -------------------------------------------------
# Load reference route
# -------------------------------------------------

reference = pd.read_csv(
    RESULTS / "dijkstra_route.csv"
)

center = [
    reference["lat"].mean(),
    reference["lon"].mean()
]

m = folium.Map(
    location=center,
    zoom_start=14,
    tiles="CartoDB Positron"
)

# -------------------------------------------------
# Draw every algorithm
# -------------------------------------------------

for name, cfg in ALGORITHMS.items():

    route = pd.read_csv(
        RESULTS / cfg["route"]
    )

    frontier = pd.read_csv(
        RESULTS / cfg["frontier"]
    )

    # -------------------------------
    # Route Layer
    # -------------------------------

    route_layer = folium.FeatureGroup(
        name=f"{name} Path",
        show=True
    )

    coords = list(
        zip(
            route["lat"],
            route["lon"]
        )
    )

    folium.PolyLine(
        coords,
        color=cfg["path_color"],
        weight=6,
        opacity=0.95,
        tooltip=name
    ).add_to(route_layer)

    route_layer.add_to(m)

    # -------------------------------
    # Frontier Layer
    # -------------------------------

    frontier_layer = folium.FeatureGroup(
        name=f"{name} Frontier",
        show=False
    )

    for _, row in frontier.iterrows():

        folium.CircleMarker(
            location=[
                row["lat"],
                row["lon"]
            ],
            radius=1,
            color=cfg["frontier_color"],
            fill=True,
            fill_color=cfg["frontier_color"],
            fill_opacity=0.25,
            opacity=0.25,
            weight=0
        ).add_to(frontier_layer)

    frontier_layer.add_to(m)

# -------------------------------------------------
# Start & End markers
# -------------------------------------------------

start = [
    reference.iloc[0]["lat"],
    reference.iloc[0]["lon"]
]

end = [
    reference.iloc[-1]["lat"],
    reference.iloc[-1]["lon"]
]

folium.Marker(
    start,
    popup="Source",
    icon=folium.Icon(
        color="green",
        icon="play"
    )
).add_to(m)

folium.Marker(
    end,
    popup="Destination",
    icon=folium.Icon(
        color="red",
        icon="stop"
    )
).add_to(m)

# -------------------------------------------------
# Legend
# -------------------------------------------------

legend = """
<div style="
position: fixed;
bottom: 40px;
left: 40px;
width: 240px;
background: white;
z-index:9999;
padding:15px;
border:2px solid grey;
border-radius:10px;
font-size:14px;
">

<b>Algorithm Colors</b><br><br>

<span style="color:#0066ff;">■</span> Dijkstra<br>
<span style="color:#00aa44;">■</span> A*<br>
<span style="color:#8A2BE2;">■</span> Bidirectional<br>
<span style="color:#ff8800;">■</span> Weighted A*<br><br>

Turn frontier layers ON
using the control panel.

</div>
"""

m.get_root().html.add_child(
    folium.Element(legend)
)

# -------------------------------------------------
# Layer Control
# -------------------------------------------------

folium.LayerControl(
    collapsed=False
).add_to(m)

m.fit_bounds(
    [
        start,
        end
    ]
)

m.save(
    RESULTS / "comparison.html"
)

print("\nGenerated:")
print("results/comparison.html")