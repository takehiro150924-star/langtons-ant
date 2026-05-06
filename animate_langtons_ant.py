import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# =========================
# 設定
# =========================
CSV_FILE = "langtons_ant_result.csv"
GRID_SIZE = 201
OUTPUT_GIF = "langtons_ant_animation.gif"

# 何ステップごとに描画するか
FRAME_INTERVAL = 10

# =========================
# CSV読み込み
# =========================
df = pd.read_csv(CSV_FILE)

# グリッドを作成
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)

# 描画対象ステップを間引く
df_frames = df.iloc[::FRAME_INTERVAL].reset_index(drop=True)

# =========================
# 描画準備
# =========================
fig, ax = plt.subplots()

im = ax.imshow(grid, cmap="binary", vmin=0, vmax=1)
ant_plot, = ax.plot([], [], "ro", markersize=4)
title = ax.set_title("Langton's Ant")

ax.set_xticks([])
ax.set_yticks([])

# =========================
# アニメーション更新関数
# =========================
def update(frame_index):
    global grid

    # 前回から今回までの処理を反映する
    start = 0 if frame_index == 0 else (frame_index - 1) * FRAME_INTERVAL
    end = min(frame_index * FRAME_INTERVAL, len(df))

    for i in range(start, end):
        row = int(df.loc[i, "row"])
        col = int(df.loc[i, "col"])
        cell = int(df.loc[i, "cell"])

        # C++側では、cellが白なら黒へ、黒なら白へ反転している
        if cell == 0:
            grid[row, col] = 1
        else:
            grid[row, col] = 0

    # 現在のアリ位置
    current = df_frames.loc[frame_index]
    ant_row = int(current["row"])
    ant_col = int(current["col"])
    step = int(current["step"])

    im.set_data(grid)
    ant_plot.set_data([ant_col], [ant_row])
    title.set_text(f"Langton's Ant Step: {step}")

    return im, ant_plot, title

# =========================
# アニメーション作成
# =========================
animation = FuncAnimation(
    fig,
    update,
    frames=len(df_frames),
    interval=30,
    blit=False
)

# GIFとして保存
animation.save(OUTPUT_GIF, writer=PillowWriter(fps=30))

print(f"Saved animation: {OUTPUT_GIF}")