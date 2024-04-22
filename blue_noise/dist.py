
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import matplotlib.animation as animation
import matplotlib.cm as cm

csv = pd.read_csv("mitchels_bn_64x64.csv", delimiter=',', header=None)
a = np.array(csv)
x = a.T[0]
y = a.T[1]

fig, ax = plt.subplots(figsize=(8, 8))
plt.title("mitchels_bn_64x64")
plt.xlim(0, 1)
plt.ylim(0, 1)
plt.grid(True, color="grey", linewidth=1, alpha=0.1)
sc = ax.scatter([], [], c='red', s=20)

colors = cm.rainbow(np.linspace(0, 1, a.shape[0]))
colors = cm.viridis(np.linspace(0, 1, a.shape[0]))

def update(frame):
    sc.set_offsets(a[:frame])
    sc.set_color(colors[:frame])
    return sc,

ani = FuncAnimation(fig, update, frames=range(1, a.shape[0]+1), interval=70, blit=True)
	
ani.save('myanimation.mp4') 