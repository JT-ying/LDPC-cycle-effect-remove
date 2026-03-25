% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% 定義LDPC方案1的BER值
BER1_SNR0 = 0.0591176471;
BER1_SNR1 = 0.0372058824;
BER1_SNR2 = 0.0282843137;
BER1_SNR3 = 0.0196078431;
BER1_SNR4 = 0.0060294118;
BER1_SNR5 = 0.0041176471;
BER1_SNR6 = 0.0020098039;

% 定義LDPC方案2的BER值
BER2_SNR0 = 0.0662254902;
BER2_SNR1 = 0.0426470588;
BER2_SNR2 = 0.0291176471;
BER2_SNR3 = 0.0154411765;
BER2_SNR4 = 0.0047549020;
BER2_SNR5 = 0.0016666667;
BER2_SNR6 = 0.0000980392;

% 定義LDPC方案3的BER值
BER3_SNR0 = 0.0550490196;
BER3_SNR1 = 0.0393627451;
BER3_SNR2 = 0.0228431373;
BER3_SNR3 = 0.0123039216;
BER3_SNR4 = 0.0040686275;
BER3_SNR5 = 0.0012627451;
BER3_SNR6 = 0.0001568627;

% 定義LDPC方案4的BER值 (SPA iter = 100 觀察)
BER4_SNR0 = 0.0697549020;
BER4_SNR1 = 0.0471568627;
BER4_SNR2 = 0.0282352941;
BER4_SNR3 = 0.0176470588;
BER4_SNR4 = 0.0114215686;
BER4_SNR5 = 0.0043627451;
BER4_SNR6 = 0.0013235294;

% 定義LDPC方案5的BER值 (for PPT result better to look，需要比較時再開啟)
BER5_SNR0 = 0.0550490196;
BER5_SNR1 = 0.0393627451;
BER5_SNR2 = 0.0228431373;
BER5_SNR3 = 0.0123039216;
BER5_SNR4 = 0.0040686275;
BER5_SNR5 = 0.0012627451;
BER5_SNR6 = 0.0001568627;

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
    semilogy(snr, BER3, 'r-square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    %semilogy(snr, BER4, 'k-->', 'LineWidth', 0.5, 'MarkerSize', 6);
    semilogy(snr, BER4, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER5, 'k--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('408.3.854 (Girth 4)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.00002 0.2]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    %legend('SPA eliminate 4-cycle effect (Im = 50)', 'SPA (Im = 50)', 'SPA eliminate 4-cycle effect (parent) (Im = 50)', 'SPA (Im = 100)', 'Location', 'southwest');
    legend('SPA without 4-cycle effect (Imax = 50)', 'SPA (Imax = 100)', 'Location', 'southwest');
    
    % 美化圖形
    set(gca, 'FontSize', 10);
end