function [ x ] = import_data(filename)
tmp = csvread(filename,0,1);
x = tmp(:,1);
end

