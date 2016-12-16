function [r] = limit_float(x,y,z)
    if (x<y)
        r = y;
    elseif (x>z)
        r = z;
    else
        r = x;
    end
end