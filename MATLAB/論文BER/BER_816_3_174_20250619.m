% 定義SNR值
%snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.5];  % SNR for PPT
% 定義LDPC方案1的BER值        % Matirx A
BER1_SNR0 = 0.00668811275;
BER1_SNR1 = 0.00413039216;
BER1_SNR2 = 0.00214975490;
BER1_SNR3 = 0.00087120098;
BER1_SNR4 = 0.00022830882;
%BER1_SNR5 = 0;
BER1_SNR6 = 0.00000562092;

% 定義LDPC方案2的BER值        % 816.3.174
BER2_SNR0 = 0.00644;
BER2_SNR1 = 0.00412;
BER2_SNR2 = 0.00214;
BER2_SNR3 = 0.00084558824;
BER2_SNR4 = 0.00022;
%BER2_SNR5 = 0.0016666667;
BER2_SNR6 = 0.0000053;

% 定義LDPC方案3的BER值        % Matrix B
BER3_SNR0 = 0.00653026961;
BER3_SNR1 = 0.00399644608;
BER3_SNR2 = 0.00204178922;
BER3_SNR3 = 0.00069693627;
BER3_SNR4 = 0.00018688725;
%BER3_SNR5 = 0.0012627451;
BER3_SNR6 = 0.00000360294;

% 定義LDPC方案4的BER值 (SPA iter = 100 觀察)
BER4_SNR0 = 0;
BER4_SNR1 = 0;
BER4_SNR2 = 0;
BER4_SNR3 = 0;
BER4_SNR4 = 0;
BER4_SNR5 = 0;
BER4_SNR6 = 0;

% 將BER值組合成向量
%BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
%BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
%BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];
BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR6];
BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR6];
BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR6];
BER4 = [BER4_SNR0, BER4_SNR1, BER4_SNR2, BER4_SNR3, BER4_SNR4, BER4_SNR5, BER4_SNR6];

% 呼叫繪圖函數
plot_BER_vs_SNR(snr, BER1, BER2, BER3);

% 繪圖函數
function plot_BER_vs_SNR(snr, BER1, BER2, BER3)
    figure;
    
    semilogy(snr, BER1, 'r--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    semilogy(snr, BER2, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    semilogy(snr, BER3, 'g--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('(816, 408) LDPC codes', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.000001 0.01]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    legend('Matrix A (Girth 4)', '816.3.174 (Girth 6)', 'Matrix B (Girth 8)', 'Location', 'southwest');
    %legend('SPA eliminate 4-cycle effect (Imax = 50)', 'SPA (Imax = 100)', 'Location', 'southwest');
    
    % 美化圖形
    set(gca, 'FontSize', 10);
end