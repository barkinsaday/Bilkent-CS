clear all;
t = -4:4;
y = (-1).^t;
t = t-1;
t = 2*t;
y = y+1;

plot(t, y);
pbaspect([4, 1, 1]);
hold on;

%ak = [0, -16/(9*((pi)^2)), 0, -16/(((pi)^2)), 0, -16/(((pi)^2)), 0, -16/(9*((pi)^2)), 0];

yy = zeros(1, length(t));
n = 2;
for k = 1:n
    ak = (8 / ( (pi^2)* k^2 )) * (pi*k*sin(pi*k) + cos(pi*k) -1);
    yy = yy + k*cos(k*pi*t/4);
end


yy = yy/4;
yy = yy + 1;

plot(t-2, yy, 'red');

%{
%FORMAT will be:
total = 0
for n = 1 : 2 : NN
    total = total + some formula involving n
end
%}


