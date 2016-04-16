function [S] = passe_bas(s, seuil)

fs = fft(s);
fs(seuil+1:end)=0;
S = real(ifft(fs));

end
