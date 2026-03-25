import numpy as np

def read_matrix(filepath):
    with open(filepath, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]
    
    try:
        # 根據錯誤訊息客製化解析：前三行是單一數字，第四行開始是 3 個數字的連線
        n = int(lines[0].split()[0])
        m = int(lines[1].split()[0])
        
        # 尋找第一行有大於 1 個數字的行（尋找連線資料的起點）
        start_idx = 0
        for i, line in enumerate(lines):
            if len(line.split()) > 1:
                start_idx = i
                break
        
        vn_to_cn = []
        for i in range(n):
            # 讀取連線，並過濾掉可能的 0 (如果檔案是用 0 補齊空位的格式)
            cns = [int(x) for x in lines[start_idx + i].split() if int(x) != 0]
            vn_to_cn.append(cns)
            
        # 自動偵測是 1-based 還是 0-based (如果最小值為 1，就全部減 1 轉成 0-based)
        min_idx = min([min(cns) for cns in vn_to_cn if cns])
        if min_idx == 1:
            vn_to_cn = [[x - 1 for x in cns] for cns in vn_to_cn]
            
        cn_to_vn = [[] for _ in range(m)]
        for vi, cns in enumerate(vn_to_cn):
            for ca in cns:
                cn_to_vn[ca].append(vi)
                
        return n, m, vn_to_cn, cn_to_vn
        
    except Exception as e:
        print(f"解析失敗: {e}")
        print("請打開 408.3.854.dat，貼上前 10 行讓我看看確切格式！")
        return None, None, None, None

def analyze_4cycles(filepath):
    n, m, vn_to_cn, cn_to_vn = read_matrix(filepath)
    if n is None:
        return
        
    print(f"✅ 成功讀取矩陣: {m} (校驗節點 CN) x {n} (變數節點 VN)")

    vn_degrees = [len(cns) for cns in vn_to_cn]
    print(f"📊 變數節點平均原始連線數 (Degree): {np.mean(vn_degrees):.2f}")

    lost_branches_per_vn = np.zeros(n, dtype=int)
    total_4cycles = 0

    # 開始對每個變數節點 (主角) 進行分析
    for vi in range(n):
        cns = vn_to_cn[vi]
        lost_branches = 0
        cycles_for_this_vi = 0

        # 檢查該變數節點的每一條連線 (分支)
        for ca in cns:
            branch_has_cycle = False
            for vj in cn_to_vn[ca]:
                if vj == vi:
                    continue
                # 尋找共同的 CN (也就是形成 4-cycle 的另一條路徑)
                common_cns = set(vn_to_cn[vj]).intersection(set(cns))
                common_cns.discard(ca)

                if len(common_cns) > 0:
                    branch_has_cycle = True
                    cycles_for_this_vi += len(common_cns)

            # 如果這條連線被捲入 4-cycle，在無差別防禦中就會被「跳過」不採納
            if branch_has_cycle:
                lost_branches += 1

        lost_branches_per_vn[vi] = lost_branches
        total_4cycles += cycles_for_this_vi // 2  # 每對 (vj, cb) 算一次

    actual_total_4cycles = total_4cycles // 2  # 除以 2 避免重複計算無向圖的環
    print(f"🔄 整個矩陣的獨立 4-cycle 總數: {actual_total_4cycles}")

    # 計算防禦後的「有效連線數」
    effective_degrees = np.array(vn_degrees) - lost_branches_per_vn

    print("\n=== 🩸 殘酷真相分析 (無差別消除 4-cycle 的後果) ===")
    print(f"總變數節點數量: {n}")
    print(f"🟢 防禦後，有效 degree 剩 3 的節點數: {np.sum(effective_degrees == 3):3d} (完全健康)")
    print(f"🟡 防禦後，有效 degree 剩 2 的節點數: {np.sum(effective_degrees == 2):3d} (輕度飢荒)")
    print(f"🟠 防禦後，有效 degree 剩 1 的節點數: {np.sum(effective_degrees == 1):3d} (重度飢荒)")
    print(f"🔴 防禦後，有效 degree 剩 0 的節點數: {np.sum(effective_degrees <= 0):3d} (完全癱瘓，資訊孤島!)")

if __name__ == '__main__':
    # 確認檔名是否為 408.3.854.dat
    analyze_4cycles('408.3.854.dat')