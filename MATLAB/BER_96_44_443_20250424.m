% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% 定義LDPC方案1的BER值 (法1_只刪除level4產生循環之節點)
BER1_SNR0 = 0.1022916667;
BER1_SNR1 = 0.0816666667;
BER1_SNR2 = 0.0737500000;
BER1_SNR3 = 0.0550000000;
BER1_SNR4 = 0.0500000000;
BER1_SNR5 = 0.0339583333;
BER1_SNR6 = 0.0247916667;

% 定義LDPC方案2的BER值 (SPA)
BER2_SNR0 = 0.1041666667;
BER2_SNR1 = 0.0841666667;
BER2_SNR2 = 0.0697916667;
BER2_SNR3 = 0.0522916667;
BER2_SNR4 = 0.0508333333;
BER2_SNR5 = 0.0364583333;
BER2_SNR6 = 0.0231250000;

% 定義LDPC方案3的BER值 (法2_刪除level4產生循環的部分)
BER3_SNR0 = 0.0960416667;
BER3_SNR1 = 0.0939583333;
BER3_SNR2 = 0.0702083333;
BER3_SNR3 = 0.0625000000;
BER3_SNR4 = 0.0450000000;
BER3_SNR5 = 0.0325000000;
BER3_SNR6 = 0.0235416667;

% 定義LDPC方案4的BER值 (SPA iter = 100 觀察)
BER4_SNR0 = 0.1218750000;
BER4_SNR1 = 0.1108333333;
BER4_SNR2 = 0.0820833333;
BER4_SNR3 = 0.0687500000;
BER4_SNR4 = 0.0558333333;
BER4_SNR5 = 0.0462500000;
BER4_SNR6 = 0.0333333333;

% 定義LDPC方案5的BER值 (for PPT result better to look， 需要比較時再開啟)
BER5_SNR0 = 0.1218750000;
BER5_SNR1 = 0.1108333333;
BER5_SNR2 = 0.0820833333;
BER5_SNR3 = 0.0687500000;
BER5_SNR4 = 0.0558333333;
BER5_SNR5 = 0.0462500000;
BER5_SNR6 = 0.0333333333;

% 將BER值組合成向量
BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];
BER4 = [BER4_SNR0, BER4_SNR1, BER4_SNR2, BER4_SNR3, BER4_SNR4, BER4_SNR5, BER4_SNR6];
BER5 = [BER5_SNR0, BER5_SNR1, BER5_SNR2, BER5_SNR3, BER5_SNR4, BER5_SNR5, BER5_SNR6];

% 呼叫繪圖函數
plot_BER_vs_SNR(snr, BER3, BER4);

% 繪圖函數
function plot_BER_vs_SNR(snr, BER3, BER4)
    figure;
    
    %semilogy(snr, BER1, 'r--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    %hold on;
    %semilogy(snr, BER2, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER3, 'g--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    semilogy(snr, BER3, 'r--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    %semilogy(snr, BER4, 'k-->', 'LineWidth', 0.5, 'MarkerSize', 6);
    semilogy(snr, BER4, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER5, 'k--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('96.44.443 (Girth 4)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.01 0.2]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    %legend('SPA eliminate 4-cycle effect (Im = 50)', 'SPA (Im = 50)', 'SPA eliminate 4-cycle effect (parent) (Im = 50)', 'SPA (Im = 100)', 'Location', 'southwest');
    legend('SPA without 4-cycle effect (Imax = 50)', 'SPA (Imax = 100)', 'Location', 'southwest');
    
    % 美化圖形
    set(gca, 'FontSize', 10);
end