# Decode.cpp Encoding Repair Report

## 1. Mojibake Areas

`Decode.cpp` had mojibake in Chinese comments around these areas:

- File header hotspot comment.
- Temporary-variable and array-initialization comments in SPA functions.
- 2-cycle, q/r message, normalization, and codeword-decision comments.
- Comments inside `SumproductAlgorithm_cycle()` near `sumproduct3()` calls and temporary q/r storage.
- Comments inside the inactive `#if 0` old `sumproduct3()` block.
- Log-domain SPA helper comments, including `sigma`, 2-cycle removal, channel LLR, and codeword-decision comments.
- `logsumproduct_cycle()` comments for sign and magnitude computation.

## 2. Restore Method

- Checked Git history for `Decode.cpp`.
- The older commit `c1b0b5c` had readable Chinese comments for the pre-hotspot sections.
- Used that history as reference where reliable.
- For newer edge-level hotspot-neutralization comments and inactive old-code comments, rewrote concise Traditional Chinese comments from local code context.

## 3. Algorithm Logic

- Confirmed executable code is unchanged after stripping `//` comments.
- The only non-comment difference after stripping line comments is the final newline at end of file.
- No decoding algorithm logic was changed.

## 4. sumproduct3()

- The effective `sumproduct3()` remains the standard SPA check-node product version.
- It still:
  - skips `i == l`
  - skips `R[j][i] == 0`
  - applies `product *= (1.0 - 2.0 * row[i])`
  - assigns `*rji = product`
- The effective `sumproduct3()` does not check hotspot nodes and does not search for 4-cycles.
- The old `#if 0` `sumproduct3()` block remains inactive.

## 5. Hotspot Neutralization

- Confirmed there is no `is_cn_muted`.
- Confirmed no check-node-level muting was introduced.
- `SumproductAlgorithm_cycle()` still uses edge-level hotspot neutralization:
  - CN -> hotspot VN writes `0.5 / 0.5`
  - CN -> non-hotspot VN writes `0.5 + 0.5 * product_rji` and `0.5 - 0.5 * product_rji`
- `HOTSPOT_NODES` was not changed.

## 6. Encoding

- `Decode.cpp` was saved as UTF-8.
- UTF-8 validation passed.
- Search checks found none of:
  - `�`
  - `?��`
  - `�?`
  - `????`

## 7. Build

Compile command:

```powershell
g++ -std=c++17 -O2 -fopenmp main.cpp AWGN.cpp Decode.cpp Encode.cpp Preprocess.cpp decode_MSC.cpp -o ldpc_sim.exe
```

Result: success.
