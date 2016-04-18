function [ fft_s ] = vis_fft( s , dt, n ,s_name)
fft_s = fft(s);
%imagesc(abs(fft_s), [0 std(abs(fft_s))]);
%colormap gray;
L = length(s);
Fs = 1 / dt;
f = Fs*L*(1:L);
figure
%plot(f(2:n), abs(fft_s(2:n)));
plot(f(2:n), abs(fft_s(2:n)));
title(strcat('fft.',s_name))
xlabel('Hz')
ylabel('fft de s')
end