% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)

% 定義LDPC方案1的迭代次數值
iter1_SNR0 = 436152 * 96 * (3+5+5+5);
iter1_SNR1 = 417968 * 96 * (3+5+5+5);
iter1_SNR2 = 396178 * 96 * (3+5+5+5);
iter1_SNR3 = 372671 * 96 * (3+5+5+5);
iter1_SNR4 = 344466 * 96 * (3+5+5+5);
iter1_SNR5 = 318147 * 96 * (3+5+5+5);
iter1_SNR6 = 292733 * 96 * (3+5+5+5);

% 定義LDPC方案2的迭代次數值
iter2_SNR0 = 487418 * 96 * (1+5+5+5);
iter2_SNR1 = 483293 * 96 * (1+5+5+5);
iter2_SNR2 = 475772 * 96 * (1+5+5+5);
iter2_SNR3 = 463648 * 96 * (1+5+5+5);
iter2_SNR4 = 452395 * 96 * (1+5+5+5);
iter2_SNR5 = 437397 * 96 * (1+5+5+5);
iter2_SNR6 = 414354 * 96 * (1+5+5+5);

% 定義LDPC方案3的迭代次數值
iter3_SNR0 = 244569 * 96 * (1+5+5+5);
iter3_SNR1 = 241579 * 96 * (1+5+5+5);
iter3_SNR2 = 237519 * 96 * (1+5+5+5);
iter3_SNR3 = 233081 * 96 * (1+5+5+5);
iter3_SNR4 = 226690 * 96 * (1+5+5+5);
iter3_SNR5 = 219492 * 96 * (1+5+5+5);
iter3_SNR6 = 209910 * 96 * (1+5+5+5);

% 定義LDPC方案4的迭代次數值
iter4_SNR0 = 235963 * 96 * (1+5+5+5);
iter4_SNR1 = 230845 * 96 * (1+5+5+5);
iter4_SNR2 = 223474 * 96 * (1+5+5+5);
iter4_SNR3 = 214156 * 96 * (1+5+5+5);
iter4_SNR4 = 205495 * 96 * (1+5+5+5);
iter4_SNR5 = 194489 * 96 * (1+5+5+5);
iter4_SNR6 = 181068 * 96 * (1+5+5+5);

% 將迭代次數值組合成向量
iter1 = [iter1_SNR0, iter1_SNR1, iter1_SNR2, iter1_SNR3, iter1_SNR4, iter1_SNR5, iter1_SNR6];
iter2 = [iter2_SNR0, iter2_SNR1, iter2_SNR2, iter2_SNR3, iter2_SNR4, iter2_SNR5, iter2_SNR6];
iter3 = [iter3_SNR0, iter3_SNR1, iter3_SNR2, iter3_SNR3, iter3_SNR4, iter3_SNR5, iter3_SNR6];
iter4 = [iter4_SNR0, iter4_SNR1, iter4_SNR2, iter4_SNR3, iter4_SNR4, iter4_SNR5, iter4_SNR6];

% 呼叫繪圖函數
plot_iterations_vs_SNR(snr, iter1, iter2, iter3, iter4);

% 繪圖函數
function plot_iterations_vs_SNR(snr, iter1, iter2, iter3, iter4)
    figure;

    % 使用 plot 繪製點線圖
    plot(snr, iter1, 'b--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    plot(snr, iter2, 'k--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    plot(snr, iter3, 'r--^', 'LineWidth', 0.5, 'MarkerSize', 6);
    plot(snr, iter4, 'm--diamond', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('Edge', 'FontSize', 12);
    title('96.33.964 (Girth = 6, Simulation times = 10000)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0 800000000]);
    xticks(snr);
       
    % 添加圖例
    legend('Fix2(SPA) (Im = 50)', 'Proposed Method (Im = 50)', 'Proposed Method (Im = 25)', 'Proposed Method (pow = 1, Im = 25)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end