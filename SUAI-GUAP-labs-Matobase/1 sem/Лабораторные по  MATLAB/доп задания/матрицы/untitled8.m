clc;clear
str = inputdlg('Вводите данные через пробел и, для разделения на строки, вводите ;');
 A = str2num(str{1});
 str = inputdlg('Вводите данные через пробел и, для разделения на строки, вводите ;');
 B = str2num(str{1});
 [m,n] = size(A);
 [l,k] = size(B); 
 if (n==l)
 else
     error('Не может перемножить')
 end
for c = 1:n
    for r = 1:n
        H(r,c) = A(m,n)*B(k,l)+A(m,n)*B();
        H(r,c) = A(c,r)*B(k,l)+A(m,n)*B();
    end
end
