function [y] = prevision(X, methode)
% prevoit la nouvelle valeur y en fonction des anciennes X.

y = 0;
N = length(X);

% methode 1: regression lineaire d'ordre 1
if (methode==1)
	Y = X(:);
	X = [ones(N,1) (1:N)'];
	A = X\Y;
	y = [1 N+1]*A;
end

% methode 2: regression lineaire d'ordre 2
if (methode==2)
	p = polyfit([1:N]', X(:), 2);
	y = polyval(p, N+1);
end

end
