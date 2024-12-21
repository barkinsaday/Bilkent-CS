clear all;
%SQUARE WAVE SIGNAL
N = 1000; %Lower this to 1 to get figure 2 (Triangular Wave Signal)
x = linspace(-4, 4, 8*N);
y = [ -ones(1, N) ones(1, N) -ones(1, N) ones(1, N)  -ones(1, N) ones(1, N) -ones(1, N) ones(1, N)];



% FOURIER SERIES
% ak coeffecients are fount by hand such that:
% a-4:a4 = [0, -2j/3pi, 0, -2j/pi, 0, 2j/3pi, 0, 2j/pi];

%Just give the proper yy ()
yy = zeros(1, length(x));
n = 4;
for k = 1:2:n
    yy = yy + 4/(pi*k)*sin(x*k);
end

plot(x, y, 'b: ', 'LineWidth', 3);
hold on;
x = x / pi;
xx = linspace(-4, 4, 8*N);
xx = xx/pi;
xx2 = xx-2;
xx3 = xx+2;
yy = -yy;
plot(xx, yy, 'red', 'LineWidth', 2);
plot(xx2, yy, 'red', 'LineWidth', 2);
plot(xx3, yy, 'red', 'LineWidth', 2);
%pbaspect([8 1 1])
xlabel('t'); ylabel('x(t)');
set(gca, "FontSize", 8);




