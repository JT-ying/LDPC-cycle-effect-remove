# LDPC 演算法深度程式碼稽核報告 (Algorithm Audit Report)

## 🎯 稽核目標與條件
尋找符合「許銘元學長論文中圖 3.7」之真實 C++ 實作，即【機率域 (Probability Domain) 搭配精準剔除 (Precise Exclusion)】版本的演算法。搜尋依據以下三個嚴格特徵：
1. **【機率域特徵】**：參數與內部變數需使用 `qij0`, `qij1`, `rji0`, `rji1`，且內部運算基於機率連乘積，不可包含 `LLR`、`log` 等對數域運算。
2. **【精準剔除特徵】**：函式內部（通常在 `Qnumber` 迴圈中）必須具備類似 `if (Qnumber != R[j][l] - 1)` 的條件判斷來跳過主角節點。
3. **【排除連坐法特徵】**：內部「絕對不能」呼叫 `sumproduct3` 或 `find_parent_index` 等攜帶矩陣 `C` 進行樹狀分支追蹤的外部函式。

---

## 🔍 搜尋結果摘要

**結論：在目前的原始碼中，並沒有找到完全符合上述三項嚴格特徵的演算法實作。**

程式碼中雖然存在對應機率域運算的程式碼，以及對應精準剔除概念的程式碼，但卻無法在同一個函式內完美交集且不具備「連坐法」追蹤。
- 尋找 `if (Qnumber != R[j][i] - 1)` 的邏輯時，我們在原始碼中只發現它存在於對數域的 `logsumproduct_cycle` 內（違反條件1），或是被實作在一支被註解掉的 `sumproduct3` 舊程式碼中（Line 548 附近）。
- 實際被呼叫的 `sumproduct3` (Line 603) 已經被改寫為會引入矩陣 `C` 並進行深度追蹤的連坐法機制（違反條件3）。

---

## 📊 既有 Probability Domain 函式防禦邏輯分析

針對目前存在的這三支機率域演算法，其目前的實作與防禦邏輯分析如下：

### 1. `SumproductAlgorithm`
- **檔案位置**：`Decode.cpp` 
- **防禦邏輯**：這是最標準傳統的機率域 Sum-Product 演算法。它在 Check Node 收集訊息的迴圈中，僅依靠 `if (q != l)` 排除傳遞給自身的訊息（一般的 Extrinsic Information）。另外配合 `avoid_two_cycle_usage` 的旗標來決定是否保留 2-cycle，並**沒有**針對主角節點 `Qnumber`（4-cycle 以上）進行精準剔除。

### 2. `SumproductAlgorithm2`
- **檔案位置**：`Decode.cpp` 
- **防禦邏輯**：同樣是基本的機率域演算。從原始碼結構來看，它與 `SumproductAlgorithm` 的判斷邏輯幾乎同出一轍（皆使用 `if (q != l)` 來略過節點，並受 `avoid_two_cycle_usage` 限制）。它不包含外圍的 `Qnumber` 即時剔除迴圈，因此也不符合精準剔除的條件。

### 3. `SumproductAlgorithm_cycle`
- **檔案位置**：`Decode.cpp` 
- **防禦邏輯**：這支函式是最接近學長論文機制的實作，它的最外層確實包了一層 `for (Qnumber = 0; Qnumber < n; Qnumber++)` 主角節點迴圈，意圖針對特定節點剔除造成短環的訊息。
- **違失特點（為何不符合需求）**：在 Check Node 更新的關鍵點，它呼叫了 `sumproduct3(temp_row, &rji, maxdegree, Qnumber, j, l, R, C, n, m);`。目前版本生效的 `sumproduct3` 函式將 `C` 矩陣傳入其中，藉此向後追尋分支與 Parent Index。這意味著此版本已經加入了「連坐法（樹狀追蹤）」的機制，而非單純且乾淨的即時 `Qnumber` 條件過濾。

---
**總結**：目前專案內的機率域 SPA 若非僅防禦基本的 2-cycle，就是結合了會進行樹狀分支尋訪的連坐法（`sumproduct3`），您所需的「純淨且只有 `if(Qnumber != R[j][i]-1)` 精準過濾」機制，目前並沒有被獨立實踐在一支啟用的函式中。
