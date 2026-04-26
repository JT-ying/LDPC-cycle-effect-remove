# Artificial Extreme Error Test Report

## 1. 修改目的

本次修改新增人工極端錯誤測試模式，用來在不使用 AWGN 的情況下，直接測試特定 variable node 的解碼修正能力。

目標節點是 VN 173，因為它在 408.3.854 中的 `4Cycle_Hits = 3`。目前程式內部採用 0-based index，因此設定 `artificial_error_node = 173`。

## 2. 修改檔案

`Configuration.h`

- 新增 `artificial_error_usage`
- 新增 `artificial_error_node`
- 新增 `artificial_error_eps`
- 保留原本 AWGN 相關設定，當 `artificial_error_usage = 0` 時仍可回到原本 AWGN 模擬流程。

`main.cpp`

- 修改機率域 SPA channel initialization。
- 當 `sumproduct_usage == 1 && log_sumproduct_usage == 0 && artificial_error_usage == 1` 時，不呼叫 `gaussian_noise()`，也不對任何節點加入 AWGN。
- 在 soft-decoding while loop 結束後、統計 `errorbit` 前，新增 target node 狀態輸出。

`Decode.cpp`

- 保持不動，未修改 edge-level hotspot neutralization 演算法核心。

## 3. 人工錯誤模式邏輯

Target node:

- 若 `c[artificial_error_node] == 0`，設定 `Pi[target] = 1.0 - artificial_error_eps`，製造極端錯誤 prior。
- 若 `c[artificial_error_node] == 1`，設定 `Pi[target] = artificial_error_eps`，製造極端錯誤 prior。

Non-target nodes:

- 若 `c[ii] == 0`，設定 `Pi[ii] = artificial_error_eps`。
- 若 `c[ii] == 1`，設定 `Pi[ii] = 1.0 - artificial_error_eps`。
- 這代表其他節點不加雜訊，直接給正確且極端可靠的 channel prior。

`yi` 同步設定為 `Pi`，因為原本 hard decoding 統計使用 `yi` 判斷機率域 SPA 的 hard output。

`qij1` 初始化方式維持：

```cpp
qij1[ii][jj] = Pi[R[ii][jj] - 1];
```

並只在 `R[ii][jj] != 0` 時寫入。

## 4. 如何跑兩組實驗

傳統 SPA：

```cpp
const int artificial_error_usage = 1;
const int artificial_error_node = 173;
const int iteration = 100;
const int exam_number = 1; // 或 100
const int sumproduct_usage = 1;
const int log_sumproduct_usage = 0;
const int avoid_SPA_any_cycle_usage = -1;
```

Cycle-neutralization SPA：

```cpp
const int artificial_error_usage = 1;
const int artificial_error_node = 173;
const int iteration = 100;
const int exam_number = 1; // 或 100
const int sumproduct_usage = 1;
const int log_sumproduct_usage = 0;
const int avoid_SPA_any_cycle_usage = 0;
```

## 5. 編譯指令

```powershell
g++ -std=c++17 -O2 -fopenmp main.cpp AWGN.cpp Decode.cpp Encode.cpp Preprocess.cpp decode_MSC.cpp -o ldpc_sim.exe
```

## 6. 執行指令

```powershell
.\ldpc_sim.exe
```

## 7. 預期觀察項目

- `Artificial target node`
- `Original c[target]`
- `Decoded c_[target]`
- `Q1[target]`
- `Pi[target]`
- BER
- total error bit
- total iteration

## 8. 修改後檢查結果

- 編譯成功：`g++ -std=c++17 -O2 -fopenmp main.cpp AWGN.cpp Decode.cpp Encode.cpp Preprocess.cpp decode_MSC.cpp -o ldpc_sim.exe`
- `Decode.cpp` 演算法核心未修改。
- `artificial_error_usage = 1` 時，機率域 SPA initialization 不呼叫 `gaussian_noise()`。
- 只有 `artificial_error_node` 被設為極端錯誤 prior。
- 其他 variable nodes 被設為正確極端 prior。
- `qij1` 仍正常初始化。
- `artificial_error_usage = 0` 時，原本 AWGN 流程仍保留。
