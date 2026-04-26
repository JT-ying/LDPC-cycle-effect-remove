# Encoding Repair Report

## Files With Mojibake

- `Configuration.h`
- `main.cpp`

The mojibake appeared after the artificial error test changes were previously written with the wrong encoding path.

## Restore Source

- Restored `Configuration.h` and `main.cpp` from Git `HEAD`.
- Commit used: `709fd2e Implement edge-level hotspot neutralization`.
- This commit is the version immediately before the artificial error test mode was added in the working tree.

## Reapplied Artificial Error Test Changes

`Configuration.h`

- Added `const int artificial_error_usage = 1;`
- Added `const int artificial_error_node = 173;`
- Added `const double artificial_error_eps = 1e-10;`

`main.cpp`

- Added artificial mode inside probability-domain SPA channel initialization.
- When `artificial_error_usage == 1`, the code does not call `gaussian_noise()`.
- Added range guard for `artificial_error_node`.
- The target node gets an extreme wrong prior.
- Non-target variable nodes get correct and extremely reliable priors.
- `yi[ii]` is synchronized with `Pi[ii]`.
- `qij1` is initialized from `Pi[R[ii][jj] - 1]`.
- When `artificial_error_usage == 0`, the original AWGN flow remains available.
- Added target-node output after the soft-decoding loop and before `errorbit` statistics.

## Decode.cpp

- Confirmed `Decode.cpp` was not modified during this repair.
- No changes were made to `sumproduct3()`, `SumproductAlgorithm_cycle()`, `LogSumproductAlgorithm()`, or other decoding algorithms.

## Encoding Settings

- `Configuration.h` validated as UTF-8.
- `main.cpp` validated as UTF-8.
- Created `.vscode/settings.json` with:

```json
{
    "files.encoding": "utf8",
    "files.autoGuessEncoding": true
}
```

- Created `.gitattributes` with:

```gitattributes
*.cpp text working-tree-encoding=UTF-8 eol=crlf
*.h text working-tree-encoding=UTF-8 eol=crlf
*.md text working-tree-encoding=UTF-8 eol=crlf
```

## Build Result

Compile command:

```powershell
g++ -std=c++17 -O2 -fopenmp main.cpp AWGN.cpp Decode.cpp Encode.cpp Preprocess.cpp decode_MSC.cpp -o ldpc_sim.exe
```

Result: success.
