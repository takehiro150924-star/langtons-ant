#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;

// =========================
// 設定
// =========================
const int GRID_SIZE = 201;
const int STEPS = 20000;

// 方向
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

// =========================
// 整数をリトルエンディアンで書き込む関数
// =========================
void writeInt(ofstream& ofs, int value, int size)
{
    for (int i = 0; i < size; i++) {
        ofs.put(static_cast<char>((value >> (8 * i)) & 0xFF));
    }
}

// =========================
// BMP画像として保存する関数
// =========================
void saveBMP(const vector<vector<int>>& grid, int ant_row, int ant_col, const string& filename)
{
    int height = static_cast<int>(grid.size());
    int width = static_cast<int>(grid[0].size());

    int rowSize = (3 * width + 3) & ~3;  // 4バイト境界にそろえる
    int imageSize = rowSize * height;
    int fileSize = 54 + imageSize;

    ofstream ofs(filename, ios::binary);

    if (!ofs) {
        cerr << "ファイルを開けませんでした: " << filename << endl;
        return;
    }

    // BMPファイルヘッダ
    ofs.put('B');
    ofs.put('M');
    writeInt(ofs, fileSize, 4);
    writeInt(ofs, 0, 2);
    writeInt(ofs, 0, 2);
    writeInt(ofs, 54, 4);

    // DIBヘッダ
    writeInt(ofs, 40, 4);
    writeInt(ofs, width, 4);
    writeInt(ofs, height, 4);
    writeInt(ofs, 1, 2);
    writeInt(ofs, 24, 2);
    writeInt(ofs, 0, 4);
    writeInt(ofs, imageSize, 4);
    writeInt(ofs, 2835, 4);
    writeInt(ofs, 2835, 4);
    writeInt(ofs, 0, 4);
    writeInt(ofs, 0, 4);

    vector<unsigned char> rowData(rowSize, 0);

    // BMPは下の行から保存する
    for (int row = height - 1; row >= 0; row--) {
        int index = 0;

        for (int col = 0; col < width; col++) {
            unsigned char r, g, b;

            // アリの位置は赤
            if (row == ant_row && col == ant_col) {
                r = 255;
                g = 0;
                b = 0;
            }
            // 白マス
            else if (grid[row][col] == 0) {
                r = 255;
                g = 255;
                b = 255;
            }
            // 黒マス
            else {
                r = 0;
                g = 0;
                b = 0;
            }

            // BMPは B, G, R の順番
            rowData[index++] = b;
            rowData[index++] = g;
            rowData[index++] = r;
        }

        ofs.write(reinterpret_cast<char*>(rowData.data()), rowSize);
    }

    ofs.close();
}

// =========================
// メイン処理
// =========================
int main()
{
    vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

    int row = GRID_SIZE / 2;
    int col = GRID_SIZE / 2;

    int direction = UP;

    int drow[4] = {-1, 0, 1, 0};
    int dcol[4] = {0, 1, 0, -1};

    int step;

    for (step = 0; step < STEPS; step++) {

        // 現在のマスが白の場合
        if (grid[row][col] == 0) {
            direction = (direction + 1) % 4;  // 右に曲がる
            grid[row][col] = 1;               // 黒にする
        }
        // 現在のマスが黒の場合
        else {
            direction = (direction + 3) % 4;  // 左に曲がる
            grid[row][col] = 0;               // 白にする
        }

        // 前に進む
        row += drow[direction];
        col += dcol[direction];

        // グリッド外に出たら終了
        if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
            cout << "アリがグリッドの外に出ました。" << endl;
            break;
        }
    }

    cout << "シミュレーション終了: " << step << " steps" << endl;

    saveBMP(grid, row, col, "langtons_ant_result.bmp");

    cout << "画像を保存しました: langtons_ant_result.bmp" << endl;

    return 0;
}