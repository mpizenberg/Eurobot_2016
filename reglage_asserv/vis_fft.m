function [ fft_s ] = vis_fft( s )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fft_s = fft(s);
imagesc(abs(fft_s), [0 std(abs(fft_s))]);
colormap gray;

end

