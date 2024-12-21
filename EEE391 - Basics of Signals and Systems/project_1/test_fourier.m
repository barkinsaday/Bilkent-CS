x = -24:0.1:24;
n = 10;
ycos = fcos(x,n);
plot(x,ycos),grid
xlabel('x'),ylabel('cos function')
% Define functions
function f = fcos(x,n)
         
         f = zeros(1,numel(x));
         f = 1/2;
         for i = 1:n
             an = -2*sin(i*pi/2)/(i*pi);
             f = f + an*cos(i*pi*x/4);
         end
end