function [S] = moyenne(s, coef)

S = s;
for i=2:length(s)
	S(i) = coef*s(i) + (1-coef)*S(i-1);
end

end
