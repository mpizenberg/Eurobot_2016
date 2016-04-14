function [ fft_s ] = vis_fft( s )
fft_s = fft(s);
imagesc(abs(fft_s), [0 std(abs(fft_s))]);
colormap gray;
end

