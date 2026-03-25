# 短循環消除 (Cycle Elimination) 演算法深度稽核報告

## 稽核結論（摘要）

> **本程式碼確實採用「無差別防禦」策略。** 每一次迭代中，演算法都會針對**全部 n 個變數節點**逐一作為「主角」，對**整張二分圖的所有 Check Node** 進行 4-cycle 偵測與消除。沒有任何黑名單、門檻值或選擇性機制來限制消除範圍。這極可能是導致外部資訊大量喪失、BER 反升的根本原因。

---

## 1. 觸發條件 (Detection Logic)

### 機率域版本：`sumproduct3()` (Decode.cpp, Line 603)

```cpp
void sumproduct3(..., int Qnumber, int j, int l, int** R, int** C, int n, int m) {
    for (i = 0; i < maxdegree; i++) {
        if (i == l)
            continue; // 排除自身 (避免 2-cycle)

        if (Qnumber == R[j][i] - 1) {   // ← 關鍵偵測條件
            // 偵測到 4-cycle！
            parent_index = find_parent_index(Qnumber, n, m, R, C, maxdegree);
            product *= (1 - 2 * row[parent_index]);
            break;
        }

        product *= (1 - 2 * row[i]);  // 正常累乘
    }
}
```

**偵測邏輯**：當 Check Node `j` 正在收集鄰居訊息時，逐一檢查每個鄰居 `R[j][i]`。若發現某個鄰居恰好等於目前的主角節點 `Qnumber`（即 `Qnumber == R[j][i] - 1`），就認定此 Check Node 與主角之間存在 4-cycle。

### 對數域版本：`logsumproduct_cycle()` (Decode.cpp, Line 1029)

```cpp
for (i = 0; i < maxdegree; i++) {
    if (i != l && Qnumber != R[j][i] - 1)   // ← 同一偵測條件
    {
        temp_rji += -log(tanh(0.5 * fabs(row[i])));
    }
}
```

**偵測邏輯完全相同**：只有滿足 `Qnumber != R[j][i] - 1` 的鄰居才會被納入運算，與主角形成 4-cycle 的鄰居直接被跳過。

---

## 2. 消除範圍 (Scope of Elimination)

### 呼叫架構 (`SumproductAlgorithm_cycle`, Line 279)

```cpp
for (Qnumber = 0; Qnumber < n; Qnumber++)   // ← 對每一個變數節點
{
    for (j = 0; j < m; j++)                   // ← 對每一個 Check Node
    {
        for (l = 0; l < maxdegree; l++)       // ← 對每一個邊
        {
            sumproduct3(..., Qnumber, j, l, R, C, n, m);
        }
    }
}
```

### 🚨 關鍵發現：完全無差別的全域掃描

| 面向 | 現狀 | 問題 |
|---|---|---|
| **主角節點範圍** | `Qnumber = 0` 到 `n-1`，**每一個**變數節點都當過主角 | 無任何篩選機制 |
| **Check Node 範圍** | `j = 0` 到 `m-1`，**全部** Check Node 都被掃描 | 即使某個 CN 與主角根本不相鄰，也會進入迴圈 |
| **黑名單/白名單** | ❌ 不存在 | 沒有任何陣列記錄「哪些節點真正位於短環上」 |
| **門檻值** | ❌ 不存在 | 沒有「環的嚴重程度」或「可信度」門檻 |
| **選擇性啟動** | ❌ 不存在 | 不管矩陣結構中是否真的有 4-cycle，都一律執行消除 |

**結論**：這是一套 **O(n × m × maxdegree)** 的暴力全掃描。每個迭代中，**所有節點都平等地被防禦**，實際上等於「所有人都在刪訊息」。

---

## 3. 消除手段 (Mechanism of Elimination)

### 機率域版本 (`sumproduct3`)：「用祖先替代」策略

當偵測到 4-cycle 時（`Qnumber == R[j][i] - 1`）：

```cpp
parent_index = find_parent_index(Qnumber, n, m, R, C, maxdegree);
product *= (1 - 2 * row[parent_index]);   // 使用祖先節點的值替代
break;                                     // 立即中斷累乘
```

- 呼叫 `find_parent_index()` 沿著 Tanner Graph 往上回溯，找到主角節點的祖先（上 2 層）
- 用祖先的機率值 `row[parent_index]` 取代原本的 `row[i]`
- **但立即 `break` 跳出迴圈**，後續所有還沒乘到的鄰居全部被拋棄！

> ⚠️ **這個 `break` 是一個嚴重的資訊喪失點**：碰到第一個 4-cycle 鄰居後，剩餘的合法鄰居也全部不被計算了。

### 對數域版本 (`logsumproduct_cycle`)：「靜默跳過」策略

```cpp
if (i != l && Qnumber != R[j][i] - 1)
{
    temp_rji += -log(tanh(0.5 * fabs(row[i])));  // 只累加非 4-cycle 的
}
// else: 什麼都不做，直接跳過
```

- 比機率域版本更溫和：不使用祖先替代，而是單純跳過涉及 4-cycle 的鄰居
- **但 sign（符號）部分仍然累乘了所有 `i != l` 的鄰居**（包含 4-cycle 的），造成 sign 與 magnitude 不一致

### 機制比較

| 版本 | 偵測到 4-cycle 時的行為 | 副作用 |
|---|---|---|
| 機率域 `sumproduct3` | 用祖先值替代 + **break 中斷整個累乘** | 大量合法鄰居資訊被拋棄 |
| 對數域 `logsumproduct_cycle` | magnitude 跳過、sign 保留 | sign/magnitude 不一致 |

---

## 4. 效能惡化根因分析

### 根因一：暴力全掃描導致的計算量爆炸
原始 SPA 的複雜度為 **O(m × maxdegree)**，但啟用 cycle 消除後變成 **O(n × m × maxdegree)**，額外多出 **n 倍**的計算量（每個節點都要輪流當主角）。在 (408,204) 矩陣中，這意味著 **408 倍**的膨脹。

### 根因二：`break` 導致的資訊截斷
`sumproduct3` 中的 `break` 使得一旦遇到第一個 4-cycle 鄰居，後續所有鄰居（即使它們完全合法且不在任何短環上）都不再被乘入 `product`。這導致 Check-to-Variable 訊息嚴重失真。

### 根因三：`find_parent_index` 的錯誤搜尋邏輯
`find_parent_index` 只回傳「第一個找到的」祖先索引，不驗證該祖先是否與當前路徑相關。在高密度矩陣中，這個函式很可能回傳一個與實際 4-cycle 無關的祖先，引入錯誤的替代值。

### 根因四：無差別防禦 = 過度防禦
即使 H 矩陣中只有極少數的 4-cycle，演算法仍然對**每一個節點**、**每一個 Check Node** 進行偵測和替代。對於不存在 4-cycle 的節點對來說，這些額外操作只會引入不必要的誤差，不會帶來任何益處。
