% 定義SNR值
snr = [1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5];  % SNR值(dB)
% 定義LDPC方案1的BER值
BER1_SNR0 = 0.112179;
BER1_SNR1 = 0.098377;
BER1_SNR2 = 0.084908;
BER1_SNR3 = 0.071456;
BER1_SNR4 = 0.059380;
BER1_SNR5 = 0.047317;
BER1_SNR6 = 0.037610;

% 定義LDPC方案2的BER值
BER2_SNR0 = 0.099491;
BER2_SNR1 = 0.089212;
BER2_SNR2 = 0.079162;
BER2_SNR3 = 0.069441;
BER2_SNR4 = 0.059485;
BER2_SNR5 = 0.051428;
BER2_SNR6 = 0.043238;

% 定義LDPC方案3的BER值
BER3_SNR0 = 0.099584;
BER3_SNR1 = 0.088887;
BER3_SNR2 = 0.078872;
BER3_SNR3 = 0.069520;
BER3_SNR4 = 0.060112;
BER3_SNR5 = 0.051541;
BER3_SNR6 = 0.043152;

% 定義LDPC方案4的BER值
BER4_SNR0 = 0.110615;
BER4_SNR1 = 0.103439;
BER4_SNR2 = 0.097025;
BER4_SNR3 = 0.088299;
BER4_SNR4 = 0.081635;
BER4_SNR5 = 0.075449;
BER4_SNR6 = 0.069137;

% 定義LDPC方案5的BER值
BER5_SNR0 = 0.121287;
BER5_SNR1 = 0.113968;
BER5_SNR2 = 0.107078;
BER5_SNR3 = 0.100473;
BER5_SNR4 = 0.093755;
BER5_SNR5 = 0.086380;
BER5_SNR6 = 0.079603;

% 定義LDPC方案6的BER值
BER6_SNR0 = 0.096638;
BER6_SNR1 = 0.085385;
BER6_SNR2 = 0.074512;
BER6_SNR3 = 0.063737;
BER6_SNR4 = 0.053368;
BER6_SNR5 = 0.044940;
BER6_SNR6 = 0.036163;

% 定義LDPC方案7的BER值
BER7_SNR0 = 0.096687;
BER7_SNR1 = 0.085307;
BER7_SNR2 = 0.074055;
BER7_SNR3 = 0.063700;
BER7_SNR4 = 0.054091;
BER7_SNR5 = 0.044408;
BER7_SNR6 = 0.036137;

% 定義LDPC方案8的BER值
BER8_SNR0 = 0.110844;
BER8_SNR1 = 0.097728;
BER8_SNR2 = 0.084272;
BER8_SNR3 = 0.070978;
BER8_SNR4 = 0.058412;
BER8_SNR5 = 0.047098;
BER8_SNR6 = 0.036163;

% 定義LDPC方案9的BER值
BER9_SNR0 = 0.0608063725;
BER9_SNR1 = 0.0439681373;
BER9_SNR2 = 0.0268750000;
BER9_SNR3 = 0.0152303922;
BER9_SNR4 = 0.0067377451;
BER9_SNR5 = 0.0029730392;
BER9_SNR6 = 0.0017622549;

%10 11 12

% 定義LDPC方案13的BER值
BER13_SNR0 = 0.0587500000;
BER13_SNR1 = 0.0393750000;
BER13_SNR2 = 0.0264803922;
BER13_SNR3 = 0.0134705882;
BER13_SNR4 = 0.0076740196;
BER13_SNR5 = 0.0036642157;
BER13_SNR6 = 0.0017671569;

% 定義LDPC方案14的BER值
BER14_SNR0 = 0.0602426471;
BER14_SNR1 = 0.0453088235;
BER14_SNR2 = 0.0263333333;
BER14_SNR3 = 0.0157843137;
BER14_SNR4 = 0.0081299020;
BER14_SNR5 = 0.0038627451;
BER14_SNR6 = 0.0017573529;

% Remove 公式內 v0
BER15_SNR0 = 0.148824;
BER15_SNR1 = 0.130000;
BER15_SNR2 = 0.120380;
BER15_SNR3 = 0.110000;
BER15_SNR4 = 0.095205;
BER15_SNR5 = 0.080000;
BER15_SNR6 = 0.067521;

% 將BER值組合成向量
BER1 = [BER1_SNR0, BER1_SNR1, BER1_SNR2, BER1_SNR3, BER1_SNR4, BER1_SNR5, BER1_SNR6];
%BER2 = [BER2_SNR0, BER2_SNR1, BER2_SNR2, BER2_SNR3, BER2_SNR4, BER2_SNR5, BER2_SNR6];
%BER3 = [BER3_SNR0, BER3_SNR1, BER3_SNR2, BER3_SNR3, BER3_SNR4, BER3_SNR5, BER3_SNR6];
%BER4 = [BER4_SNR0, BER4_SNR1, BER4_SNR2, BER4_SNR3, BER4_SNR4, BER4_SNR5, BER4_SNR6];
%BER5 = [BER5_SNR0, BER5_SNR1, BER5_SNR2, BER5_SNR3, BER5_SNR4, BER5_SNR5, BER5_SNR6];
%BER6 = [BER6_SNR0, BER6_SNR1, BER6_SNR2, BER6_SNR3, BER6_SNR4, BER6_SNR5, BER6_SNR6];
%BER7 = [BER7_SNR0, BER7_SNR1, BER7_SNR2, BER7_SNR3, BER7_SNR4, BER7_SNR5, BER7_SNR6];
BER8 = [BER8_SNR0, BER8_SNR1, BER8_SNR2, BER8_SNR3, BER8_SNR4, BER8_SNR5, BER8_SNR6];
BER9 = [BER9_SNR0, BER9_SNR1, BER9_SNR2, BER9_SNR3, BER9_SNR4, BER9_SNR5, BER9_SNR6];
%10
%11
%12
BER13 = [BER13_SNR0, BER13_SNR1, BER13_SNR2, BER13_SNR3, BER13_SNR4, BER13_SNR5, BER13_SNR6];
BER14 = [BER14_SNR0, BER14_SNR1, BER14_SNR2, BER14_SNR3, BER14_SNR4, BER14_SNR5, BER14_SNR6];
BER15 = [BER15_SNR0, BER15_SNR1, BER15_SNR2, BER15_SNR3, BER15_SNR4, BER15_SNR5, BER15_SNR6];

% 呼叫繪圖函數
plot_BER_vs_SNR(snr, BER1, BER8, BER9, BER13, BER14, BER15);

% 繪圖函數
function plot_BER_vs_SNR(snr, BER1, BER8, BER9, BER13, BER14, BER15)
    figure;
    
    semilogy(snr, BER1, 'b--square', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold on;
    %semilogy(snr, BER2, 'k--o', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER3, 'r--^', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER4, 'm--diamond', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER5, 'g--x', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER6, 'c--*', 'LineWidth', 0.5, 'MarkerSize', 6);
    %semilogy(snr, BER7, 'Color', '#D95319', 'LineStyle', '--','Marker', '.', 'LineWidth', 0.5, 'MarkerSize', 6); % '#D95319' = 橘色
    semilogy(snr, BER8, 'Color', '#EDB120', 'LineStyle', '--','Marker', '*', 'LineWidth', 0.5, 'MarkerSize', 6); % '#EDB120' = 深黃色
    semilogy(snr, BER9, 'Color', '#7E2F8E', 'LineStyle', '--','Marker', '^', 'LineWidth', 0.5, 'MarkerSize', 6); % '#7E2F8E' = 深紫色
    %10
    %11
    %12
    semilogy(snr, BER13, 'r--+', 'LineWidth', 0.5, 'MarkerSize', 6); % 原綠，改紅，好分辨
    semilogy(snr, BER14, 'Color', '#A2142F', 'LineStyle', '--','Marker', 'o', 'LineWidth', 0.5, 'MarkerSize', 6); % '#A2142F' = 深紅色
    semilogy(snr, BER15, 'b--*', 'LineWidth', 0.5, 'MarkerSize', 6);
    hold off;

    grid on;
    xlabel('SNR (dB)', 'FontSize', 12);
    ylabel('BER', 'FontSize', 12);
    title('408.3.854 (Girth = 4)', 'FontSize', 14);

    % 設置軸的範圍和刻度
    xlim([min(snr) max(snr)]);
    ylim([0.0002 0.2]);
    xticks(snr);
       
    ytickformat('%.e');

    % 添加圖例
    legend('Fix2 (Im = 50)', 'Fix2 (Im = 25)', 'SPA (Im = 50)', 'Fix2 (update q, Im = 50)', 'Fix2 (update q, Im = 25)', 'Proposed method (Remove 公式內v_0, Im = 50)', 'Location', 'southwest');

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