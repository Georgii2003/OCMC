% Задаём данные
a = [0.3 0.2 -0.1 4.2 -2 1.5 0];
b = [0.3 4 -2.2 1.6 0.1 0.1 0.2];
% Вывод первых двух графиков
figure(1);
plot(a);
title('График a');
xlabel('Индекс элемента');
ylabel('Значение');
figure(2);
plot(b);
title('График b');
xlabel('Индекс элемента');
ylabel('Значение');


format longG;
ab = dot(a, b);
fprintf('%.0f \t',ab)
max_ab = -999 
nofmax = 0
for i = 1:7
    b = circshift(b,1)
    ab = dot(a, b);
    fprintf('------- %.0f ------- \n',ab)
        if (ab > max_ab)
            max_ab = ab
            nofmax = i
        end
end

b = circshift(b,nofmax)

% Вывод последнего графика
figure(3);
plot(b);
title('График b');
xlabel('Индекс элемента');
ylabel('Значение');
