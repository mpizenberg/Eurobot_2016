function [ a ] = acceleration( v, dt )
a = (v(2:end)-v(1:end-1))/dt;
end

