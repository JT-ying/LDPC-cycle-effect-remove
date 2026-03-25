% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% 定義LDPC方案1的BER值
BER1_SNR0 = 0.0881666667;
BER1_SNR1 = 0.0835000000;
BER1_SNR2 = 0.0785000000;
BER1_SNR3 = 0.0740000000;
BER1_SNR4 = 0.0718333333;
BER1_SNR5 = 0.0711666667;
BER1_SNR6 = 0.0688333333;

% 定義LDPC方案2的BER值
BER2_SNR0 = 0.0618333333;
BER2_SNR1 = 0.0535000000;
BER2_SNR2 = 0.0475000000;
BER2_SNR3 = 0.0401666667;
BER2_SNR4 = 0.0330000000;
BER2_SNR5 = 0.0270000000;
BER2_SNR6 = 0.0211666667;

% 定義LDPC方案3的BER值
BER3_SNR0 = 0.0646666667;
BER3_SNR1 = 0.0565000000;
BER3_SNR2 = 0.0518333333;
BER3_SNR3 = 0.0458333333;
BER3_SNR4 = 0.0383333333;
BER3_SNR5 = 0.0355000000;
BER3_SNR6 = 0.0300000000;

% 將BER值組合成向量
BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];

% 呼叫繪圖函數
plot_BER_vs_SNR(snr, BER1, BER2, BER3);

% 繪圖函數
function plot_BER_vs_SNR(snr, BER1, BER2, BER3)
    figure;
    
    semilogy(snr, BER1, 'r--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    semilogy(snr, BER2, 'b--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    semilogy(snr, BER3, 'k--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('(6,3)H irregular', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.0002 0.2]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    legend('SPA eliminate 4-cycle effect (Im = 50)', 'SPA (Im = 50)', 'SPA 極值化 (Im = 50)', 'Location', 'southwest');

    % 美化圖形
    set(gca, 'FontSize', 10);
end

% % 定義SNR值
% snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% % 定義LDPC方案1的BER值
% BER1_SNR0 = 0.051;
% BER1_SNR1 = 0.037;
% BER1_SNR2 = 0.016;
% BER1_SNR3 = 0.0045;
% BER1_SNR4 = 0.0011;
% BER1_SNR5 = 0;
% BER1_SNR6 = 0;
% 
% % 定義LDPC方案2的BER值
% BER2_SNR0 = 0.102308;
% BER2_SNR1 = 0.098;
% BER2_SNR2 = 0.093928;
% BER2_SNR3 = 0.069;
% BER2_SNR4 = 0.049;
% BER2_SNR5 = 0;
% BER2_SNR6 = 0;
% 
% % 定義LDPC方案3的BER值
% BER3_SNR0 = 0;
% BER3_SNR1 = 0;
% BER3_SNR2 = 0;
% BER3_SNR3 = 0;
% BER3_SNR4 = 0;
% BER3_SNR5 = 0;
% BER3_SNR6 = 0;
% 
% % 定義LDPC方案4的BER值
% BER4_SNR0 = 0;
% BER4_SNR1 = 0;
% BER4_SNR2 = 0;
% BER4_SNR3 = 0;
% BER4_SNR4 = 0;
% BER4_SNR5 = 0;
% BER4_SNR6 = 0;
% 
% % 將BER值組合成向量
% BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
% BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
% BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];
% BER4 = [BER4_SNR0, BER4_SNR1, BER4_SNR2, BER4_SNR3, BER4_SNR4, BER4_SNR5, BER4_SNR6];
% 
% % 呼叫繪圖函數
% plot_BER_vs_SNR(snr, BER1, BER2, BER3, BER4);
% 
% % 繪圖函數
% function plot_BER_vs_SNR(snr, BER1, BER2, BER3, BER4)
%     figure;
%     
%     semilogy(snr, BER1, 'b--square', 'LineWidth', 0.5, 'MarkerSize', 6);
%     hold on;
%     semilogy(snr, BER2, 'g--o', 'LineWidth', 0.5, 'MarkerSize', 6);
%     semilogy(snr, BER3, 'r-square', 'LineWidth', 0.5, 'MarkerSize', 6);
%     semilogy(snr, BER4, 'x--', 'LineWidth', 0.5, 'MarkerSize', 6);
%     hold off;
% 
%     grid on;
%     xlabel('SNR (dB)', 'FontSize', 12);
%     ylabel('BER', 'FontSize', 12);
%     title('(1008,504) regular example', 'FontSize', 14);
% 
%     % 設置軸的範圍和刻度
%     xlim([min(snr) max(snr)]);
%     ylim([0.00001 1]);
%     xticks(snr);
%        
%     ytickformat('%.e');
% 
%     % 添加圖例
%     legend('SPA (Im = 100)', 'Fixed-level (Level = 2, Im = 100)', 'Location', 'southwest');
% 
%     % 美化圖形
%     set(gca, 'FontSize', 10);
% end