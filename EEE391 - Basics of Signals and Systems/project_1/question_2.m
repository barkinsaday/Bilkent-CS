%Provided frequencies and not lengths
fs = 8000;
n1 = 2;
t8 = 1/fs: 1/fs : n1/8;
t2 = 1/fs: 1/fs : n1/2;
sd = zeros(1,round(length(t8)/10));
rest = zeros(1,length(t8));

%Signals
s_1 = cos( 2*pi*220*(2^(10/12))* t8 );
s_2 = cos( 2*pi*220*(2^(6/12))* t2 );
s_3 = cos( 2*pi*220*(2^(8/12))* t8 );
s_4 = cos( 2*pi*220*(2^(5/12))* t2 );

%Signals as an array in the given form
arr = [s_1 sd s_1 sd s_1 sd s_2 sd rest sd s_3 sd s_3 sd s_3 sd s_4];

%Sound command to listen the signal
sound(arr);








