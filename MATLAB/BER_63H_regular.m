% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% 定義LDPC方案1的BER值
BER1_SNR0 = 0.2066666667;
BER1_SNR1 = 0.1833333333;
BER1_SNR2 = 0.1733333333;
BER1_SNR3 = 0.1700000000;
BER1_SNR4 = 0.1700000000;
BER1_SNR5 = 0.1633333333;
BER1_SNR6 = 0.1566666667;

% 定義LDPC方案2的BER值
BER2_SNR0 = 0.0800000000;
BER2_SNR1 = 0.0733333333;
BER2_SNR2 = 0.0700000000;
BER2_SNR3 = 0.0566666667;
BER2_SNR4 = 0.0500000000;
BER2_SNR5 = 0.0500000000;
BER2_SNR6 = 0.0466666667;

% 定義LDPC方案3的BER值
BER3_SNR0 = 0;
BER3_SNR1 = 0;
BER3_SNR2 = 0;
BER3_SNR3 = 0;
BER3_SNR4 = 0;
BER3_SNR5 = 0;
BER3_SNR6 = 0;

% 將BER值組合成向量
BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];

% 呼叫繪圖函數
plot_BER_vs_SNR(snr, BER1, BER2);

% 繪圖函數
function plot_BER_vs_SNR(snr, BER1, BER2)
    figure;
    
    semilogy(snr, BER1, 'r--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    semilogy(snr, BER2, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER3, 'g--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('(6,3)H', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.002 0.3]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    legend('SPA eliminate 4-cycle effect (Im = 50)', 'SPA (Im = 50)', 'Location', 'southwest');
    %legend('SPA eliminate 4-cycle effect (Im = 50)', 'SPA (Im = 50)', 'SPA 極值化 (Im = 50)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end

