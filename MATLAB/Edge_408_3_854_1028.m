% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)

% 定義LDPC方案1的迭代次數值
iter1_SNR0 = 499280 * 408 * (3+5+5+5);
iter1_SNR1 = 497952 * 408 * (3+5+5+5);
iter1_SNR2 = 495472 * 408 * (3+5+5+5);
iter1_SNR3 = 490134 * 408 * (3+5+5+5);
iter1_SNR4 = 481267 * 408 * (3+5+5+5);
iter1_SNR5 = 462987 * 408 * (3+5+5+5);
iter1_SNR6 = 437988 * 408 * (3+5+5+5);

% 定義LDPC方案2的迭代次數值
iter2_SNR0 = 500000 * 408 * (1+5+5+5);
iter2_SNR1 = 500000 * 408 * (1+5+5+5);
iter2_SNR2 = 500000 * 408 * (1+5+5+5);
iter2_SNR3 = 499945 * 408 * (1+5+5+5);
iter2_SNR4 = 499856 * 408 * (1+5+5+5);
iter2_SNR5 = 499761 * 408 * (1+5+5+5);
iter2_SNR6 = 499425 * 408 * (1+5+5+5);

% 定義LDPC方案3的迭代次數值
iter3_SNR0 = 250000 * 408 * (1+5+5+5);
iter3_SNR1 = 250000 * 408 * (1+5+5+5);
iter3_SNR2 = 250000 * 408 * (1+5+5+5);
iter3_SNR3 = 249979 * 408 * (1+5+5+5);
iter3_SNR4 = 249957 * 408 * (1+5+5+5);
iter3_SNR5 = 249954 * 408 * (1+5+5+5);
iter3_SNR6 = 249637 * 408 * (1+5+5+5);

% 定義LDPC方案4的迭代次數值
iter4_SNR0 = 250000 * 408 * (1+5+5+5);
iter4_SNR1 = 249980 * 408 * (1+5+5+5);
iter4_SNR2 = 249819 * 408 * (1+5+5+5);
iter4_SNR3 = 249804 * 408 * (1+5+5+5);
iter4_SNR4 = 249291 * 408 * (1+5+5+5);
iter4_SNR5 = 248331 * 408 * (1+5+5+5);
iter4_SNR6 = 246248 * 408 * (1+5+5+5);

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
    title('408.3.854 (Girth = 4, Simulation times = 10000)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0 4000000000]);
    xticks(snr);
       
    % 添加圖例
    legend('Fix2(SPA) (Im = 50)', 'Proposed Method (Im = 50)', 'Proposed Method (Im = 25)', 'Proposed Method (pow = 1, Im = 25)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end