function [S] = mediane(s, n)

S = s;
for i=n:length(s)
	S(i) = median(s(i-n+1:i));
end

end
