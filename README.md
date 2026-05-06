# Langton's Ant Simulation

このリポジトリは、C++で実装した Langton's Ant（ラングトンのアリ）のシミュレーションです。

シミュレーション本体はC++で実行し、その結果をCSVファイルとして保存します。  
その後、PythonでCSVファイルを読み込み、アニメーションとして可視化します。

## 概要

Langton's Ant は、2次元グリッド上を移動する単純なエージェントシミュレーションです。

アリは現在いるマスの色に応じて、向きを変え、マスの色を反転させ、1マス前に進みます。

この実装では、以下の流れで処理を行います。

```text
C++でシミュレーションを実行
↓
各ステップの結果をCSVに保存
↓
PythonでCSVを読み込む
↓
アニメーションを作成・保存
```

## Langton's Ant のルール

アリの行動ルールは以下の通りです。

### 現在のマスが白の場合

```text
右に90度回転する
現在のマスを黒に変える
1マス前に進む
```

### 現在のマスが黒の場合

```text
左に90度回転する
現在のマスを白に変える
1マス前に進む
```

## 目的

このプログラムの目的は、エージェントベースシミュレーションの基本構造を理解することです。

特に、以下の流れを学ぶことを目的としています。

```text
エージェントが環境を見る
↓
ルールに従って行動を決める
↓
環境を書き換える
↓
エージェントが移動する
↓
結果を記録する
↓
記録した結果を解析・可視化する
```

この構造は、シロアリシミュレーションや群ロボットシミュレーションの基礎にもつながります。

## ファイル構成

```text
Langtons_ant.cpp          Langton's Ant のC++シミュレーション本体
animate_langtons_ant.py   CSVを読み込み、アニメーションを作成するPythonコード
Dockerfile                Docker環境を作成するための設定ファイル
compose.yml               Docker Composeで実行するための設定ファイル
README.md                 この説明ファイル
.gitignore                Gitで管理しないファイルを指定するファイル
```

実行時に生成されるファイルは以下です。

```text
Langtons_ant.exe              C++の実行ファイル
langtons_ant_result.csv       C++で出力されるシミュレーション結果
langtons_ant_animation.gif    Pythonで作成されるアニメーション
```

これらの生成ファイルは、必要に応じて `.gitignore` でGit管理対象から外します。

## C++プログラムの役割

C++側では、Langton's Ant のシミュレーションを実行します。

主な処理は以下です。

```text
グリッド環境を作成する
アリの位置と向きを管理する
現在のマスの状態を確認する
ルールに従って向きを変える
現在のマスの色を反転する
アリを1マス進める
各ステップの結果をCSVに保存する
```

出力されるCSVファイルには、各ステップごとのアリの状態が保存されます。

CSVの形式は以下の通りです。

```csv
step,row,col,direction,cell
```

各列の意味は以下です。

| 列名 | 意味 |
|---|---|
| `step` | シミュレーションのステップ数 |
| `row` | アリの行位置 |
| `col` | アリの列位置 |
| `direction` | アリの向き |
| `cell` | アリがいたマスの状態 |

`cell` は以下の意味を持ちます。

```text
0 = 白マス
1 = 黒マス
```

## Pythonプログラムの役割

Python側では、C++で出力されたCSVファイルを読み込み、アニメーションを作成します。

主な処理は以下です。

```text
CSVファイルを読み込む
各ステップのアリの位置を取得する
マスの色の変化を再現する
アリの位置を赤い点で表示する
アニメーションをGIFとして保存する
```

出力されるアニメーションファイルは以下です。

```text
langtons_ant_animation.gif
```

## 実行方法

## 1. C++でシミュレーションを実行する

まず、C++コードをコンパイルします。

```powershell
g++ Langtons_ant.cpp -o Langtons_ant.exe
```

次に、実行します。

```powershell
.\Langtons_ant.exe
```

実行後、以下のCSVファイルが生成されます。

```text
langtons_ant_result.csv
```

## 2. Pythonでアニメーションを作成する

必要なPythonライブラリをインストールします。

```powershell
pip install pandas numpy matplotlib pillow
```

Pythonコードを実行します。

```powershell
python animate_langtons_ant.py
```

実行後、以下のGIFファイルが生成されます。

```text
langtons_ant_animation.gif
```

## 出力結果

C++の実行結果として、以下のCSVファイルが作成されます。

```text
langtons_ant_result.csv
```

Pythonの実行結果として、以下のアニメーションファイルが作成されます。

```text
langtons_ant_animation.gif
```

アニメーションでは、以下のように表示されます。

```text
白いマス：白状態のセル
黒いマス：黒状態のセル
赤い点：アリの現在位置
```

## Dockerで実行する場合

Dockerが使用できる環境では、以下のコマンドで実行できます。

```powershell
docker compose up --build
```

ただし、Dockerを使用するには Docker Desktop などのDocker実行環境が必要です。

## GitHubへの反映方法

コードを変更した後は、以下の流れでGitHubに反映します。

```powershell
git status
git add .
git commit -m "Save simulation results as CSV and add Python animation"
git push
```

研究室のリポジトリにも反映する場合は、以下を実行します。

```powershell
git push fujisawa main
```

個人リポジトリと研究室リポジトリの両方に反映する場合は、以下を実行します。

```powershell
git push origin main
git push fujisawa main
```

## .gitignoreについて

このリポジトリでは、実行によって生成されるファイルは基本的にGit管理しない方針です。

例：

```gitignore
*.exe
*.bmp
*.ppm
*.csv
*.gif
```

ただし、README上でアニメーション例を表示したい場合は、GIFファイルをGitHubに含めることもあります。

## 今後の拡張予定

今後の拡張として、以下が考えられます。

```text
コードを関数に分割する
複数のアリに拡張する
CSVにより詳細な情報を保存する
Pythonで移動距離やパターンを解析する
シロアリシミュレーション用の構造体を作る
グリッドの状態を WHITE / BLACK から EMPTY / SOIL / PHEROMONE に拡張する
C++でシミュレーション、Pythonで解析する構成をシロアリsimにも応用する
```



## 補足

今回の実装では、アリそのものを画像として直接持っているわけではありません。

内部では、以下のような数値でアリの状態を管理しています。

```text
ant.row        アリの行位置
ant.col        アリの列位置
ant.direction  アリの向き
```

Pythonで可視化するときに、`ant.row` と `ant.col` の位置に赤い点を描画することで、アリの動きをアニメーションとして表示しています。