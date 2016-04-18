function [S] = lineaire(s, ordre, nb)

S = s;
for i=nb+1:length(s)
	S(i) = prevision(s(i-nb:i-1), ordre);
end

end
