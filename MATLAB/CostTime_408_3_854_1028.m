% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)

% 定義LDPC方案1的迭代次數值
costTime1_SNR0 = 1006.816;
costTime1_SNR1 = 1000.432;
costTime1_SNR2 = 990.368;
costTime1_SNR3 = 968.579;
costTime1_SNR4 = 926.410;
costTime1_SNR5 = 881.414;
costTime1_SNR6 = 827.120;

% 定義LDPC方案2的迭代次數值
costTime2_SNR0 = 1235.424;
costTime2_SNR1 = 1234.713;
costTime2_SNR2 = 1234.004;
costTime2_SNR3 = 1233.320;
costTime2_SNR4 = 1232.890;
costTime2_SNR5 = 1232.276;
costTime2_SNR6 = 1230.426;

% 定義LDPC方案3的迭代次數值
costTime3_SNR0 = 497.443;
costTime3_SNR1 = 496.828;
costTime3_SNR2 = 496.234;
costTime3_SNR3 = 494.029;
costTime3_SNR4 = 492.937;
costTime3_SNR5 = 491.743;
costTime3_SNR6 = 489.228;

% 定義LDPC方案4的迭代次數值
costTime4_SNR0 = 1013.178;
costTime4_SNR1 = 1011.006;
costTime4_SNR2 = 1007.538;
costTime4_SNR3 = 1002.597;
costTime4_SNR4 = 999.911;
costTime4_SNR5 = 994.720;
costTime4_SNR6 = 989.251;

% 定義LDPC方案5的迭代次數值
costTime5_SNR0 = 460.567;
costTime5_SNR1 = 460.427;
costTime5_SNR2 = 459.313;
costTime5_SNR3 = 458.303;
costTime5_SNR4 = 454.473;
costTime5_SNR5 = 448.656;
costTime5_SNR6 = 446.904;

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
    title('408.3.854 (Girth = 4, Simulation times = 10000)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0 1300]);
    xticks(snr);
       
    % 添加圖例
    legend('Fix2(SPA) (Im = 50)', 'Proposed Method (Im = 50)', 'Proposed Method (Im = 25)', 'Proposed Method (pow = 1, Im = 50)', 'Proposed Method (pow = 1, Im = 25)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end