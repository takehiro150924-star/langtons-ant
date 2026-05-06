#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// =========================
// 設定
// =========================
const int GRID_SIZE = 201;
const int STEPS = 20000;

// マスの状態
const int WHITE = 0;
const int BLACK = 1;

// 方向
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

// =========================
// アリを表す構造体
// =========================
struct Ant {
    int row;
    int col;
    int direction;
};

int main()
{
    // グリッド環境を作成
    vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, WHITE));

    // アリを作成
    Ant ant;
    ant.row = GRID_SIZE / 2;
    ant.col = GRID_SIZE / 2;
    ant.direction = UP;

    // 方向ごとの移動量
    int drow[4] = {-1, 0, 1, 0};
    int dcol[4] = {0, 1, 0, -1};

    // CSVファイルを作成
    ofstream csv("langtons_ant_result.csv");

    if (!csv) {
        cerr << "Could not open CSV file." << endl;
        return 1;
    }

    // CSVのヘッダー
    csv << "step,row,col,direction,cell\n";

    int step;

    for (step = 0; step < STEPS; step++) {

        // 現在のマスの状態を保存
        int current_cell = grid[ant.row][ant.col];

        // 現在の状態をCSVに出力
        csv << step << ","
            << ant.row << ","
            << ant.col << ","
            << ant.direction << ","
            << current_cell << "\n";

        // 現在アリがいるマスが白の場合
        if (current_cell == WHITE) {
            ant.direction = (ant.direction + 1) % 4;  // 右に曲がる
            grid[ant.row][ant.col] = BLACK;           // 現在地を黒にする
        }
        // 現在アリがいるマスが黒の場合
        else {
            ant.direction = (ant.direction + 3) % 4;  // 左に曲がる
            grid[ant.row][ant.col] = WHITE;           // 現在地を白にする
        }

        // アリを1マス前に進める
        ant.row += drow[ant.direction];
        ant.col += dcol[ant.direction];

        // グリッドの外に出たら終了
        if (ant.row < 0 || ant.row >= GRID_SIZE ||
            ant.col < 0 || ant.col >= GRID_SIZE) {
            cout << "Ant went out of the grid." << endl;
            break;
        }
    }

    csv.close();

    cout << "Simulation finished: " << step << " steps" << endl;
    cout << "Saved CSV: langtons_ant_result.csv" << endl;

    return 0;
}