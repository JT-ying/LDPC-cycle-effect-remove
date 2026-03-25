% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)

% 定義LDPC方案1的迭代次數值
costTime1_SNR0 = 67.23;
costTime1_SNR1 = 64.07;
costTime1_SNR2 = 61.61;
costTime1_SNR3 = 59.35;
costTime1_SNR4 = 56.32;
costTime1_SNR5 = 52.00;
costTime1_SNR6 = 48.10;

% 定義LDPC方案2的迭代次數值
costTime2_SNR0 = 87.28;
costTime2_SNR1 = 84.67;
costTime2_SNR2 = 82.58;
costTime2_SNR3 = 81.01;
costTime2_SNR4 = 79.12; 
costTime2_SNR5 = 77.26;
costTime2_SNR6 = 74.25;

% 定義LDPC方案3的迭代次數值
costTime3_SNR0 = 40.976;
costTime3_SNR1 = 40.872;
costTime3_SNR2 = 40.373;
costTime3_SNR3 = 39.336;
costTime3_SNR4 = 38.408;
costTime3_SNR5 = 37.299;
costTime3_SNR6 = 36.142;

% 定義LDPC方案4的迭代次數值
costTime4_SNR0 = 71.487;
costTime4_SNR1 = 69.280;
costTime4_SNR2 = 66.822;
costTime4_SNR3 = 64.190;
costTime4_SNR4 = 60.921;
costTime4_SNR5 = 58.345;
costTime4_SNR6 = 55.459;

% 定義LDPC方案5的迭代次數值
costTime5_SNR0 = 38.439;
costTime5_SNR1 = 38.194;
costTime5_SNR2 = 37.066;
costTime5_SNR3 = 35.450;
costTime5_SNR4 = 34.577;
costTime5_SNR5 = 32.961;
costTime5_SNR6 = 30.839;

% 將迭代次數值組合成向量
costTime1 = [costTime1_SNR0, costTime1_SNR1, costTime1_SNR2, costTime1_SNR3, costTime1_SNR4, costTime1_SNR5, costTime1_SNR6];
costTime2 = [costTime2_SNR0, costTime2_SNR1, costTime2_SNR2, costTime2_SNR3, costTime2_SNR4, costTime2_SNR5, costTime2_SNR6];
costTime3 = [costTime3_SNR0, costTime3_SNR1, costTime3_SNR2, costTime3_SNR3, costTime3_SNR4, costTime3_SNR5, costTime3_SNR6];
costTime4 = [costTime4_SNR0, costTime4_SNR1, costTime4_SNR2, costTime4_SNR3, costTime4_SNR4, costTime4_SNR5, costTime4_SNR6];
costTime5 = [costTime5_SNR0, costTime5_SNR1, costTime5_SNR2, costTime5_SNR3, costTime5_SNR4, costTime5_SNR5, costTime5_SNR6];

% 呼叫繪圖函數
plot_costTime_vs_SNR(snr, costTime1, costTime2, costTime3, costTime4, costTime5);

% 繪圖函數
function plot_costTime_vs_SNR(snr, costTime1, costTime2, costTime3, costTime4, costTime5)
    figure;

    % 使用 plot 繪製點線圖
    plot(snr, costTime1, 'b--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    plot(snr, costTime2, 'k--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    plot(snr, costTime3, 'r--^', 'LineWidth', 0.5, 'MarkerSize', 6);
    plot(snr, costTime4, 'm--diamond', 'LineWidth', 0.5, 'MarkerSize', 6);
    plot(snr, costTime5, 'g--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('Total Cost Time', 'FontSize', 12);
    title('96.33.964 (Girth = 6, Simulation times = 10000)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([10 90]);
    xticks(snr);
       
    % 添加圖例
    legend('Fix2(SPA) (Im = 50)', 'Proposed Method (Im = 50)', 'Proposed Method (Im = 25)', 'Proposed Method (pow = 1, Im = 50)', 'Proposed Method (pow = 1, Im = 25)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end