function [S] = mixe(s, coef_mesure, coef_prevision, nb)
% 0.15, 0.15, 10 semble bien

S = s;
for i=nb+1:length(s)
	S_prev = prevision(s(i-nb:i-1), 1);
	S(i) = coef_mesure*s(i) + coef_prevision*S_prev + (1-coef_mesure-coef_prevision)*S(i-1);
end

end

