% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)

% 定義LDPC方案1的迭代次數值
iter1_SNR0 = 436152;
iter1_SNR1 = 417968;
iter1_SNR2 = 396178;
iter1_SNR3 = 372671;
iter1_SNR4 = 344466;
iter1_SNR5 = 318147;
iter1_SNR6 = 292733;

% 定義LDPC方案2的迭代次數值
iter2_SNR0 = 487418;
iter2_SNR1 = 483293;
iter2_SNR2 = 475772;
iter2_SNR3 = 463648;
iter2_SNR4 = 452395;
iter2_SNR5 = 437397;
iter2_SNR6 = 414354;

% 將迭代次數值組合成向量
iter1 = [iter1_SNR0, iter1_SNR1, iter1_SNR2, iter1_SNR3, iter1_SNR4, iter1_SNR5, iter1_SNR6];
iter2 = [iter2_SNR0, iter2_SNR1, iter2_SNR2, iter2_SNR3, iter2_SNR4, iter2_SNR5, iter2_SNR6];

% 呼叫繪圖函數
plot_iterations_vs_SNR(snr, iter1, iter2);

% 繪圖函數
function plot_iterations_vs_SNR(snr, iter1, iter2)
    figure;

    % 使用 plot 繪製點線圖
    plot(snr, iter1, 'b--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    plot(snr, iter2, 'k--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('Iteration times', 'FontSize', 12);
    title('96.33.964 (Girth = 6, Simulation times = 10000)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([250000 500000]);
    xticks(snr);
       
    % 添加圖例
    legend('Fix2(SPA) (Im = 50)', 'Proposed Method (Im = 50)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end