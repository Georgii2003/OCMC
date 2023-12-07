f1 = 1; %Порядковый номер в журнале
f2 = f1 + 4;
f3 = f1 * 2 + 1;

time = (0:100-1)/100; % Задаём время

S1 = cos(2*pi* f1 *time);
S2 = cos(2*pi* f2 *time);
S3 = cos(2*pi* f3 *time);

a = 2*S1 + 4*S2 + S3; % 1 вариант
b = S1 + S2;

format longG;

S1a = sum(S1 .* a);
S1b = sum(S1 .* b);
S1a2 = sum(S1 .* a) / (sqrt(sum(S1 .^ 2)) * sqrt(sum(a .^ 2)));
S1b2 = sum(S1 .* b) / (sqrt(sum(S1 .^ 2)) * sqrt(sum(b .^ 2)));
S2a = sum(S2 .* a);
S2b = sum(S2 .* b);
S2a2 = sum(S2 .* a) / (sqrt(sum(S2 .^ 2)) * sqrt(sum(a .^ 2)));
S2b2 = sum(S2 .* b) / (sqrt(sum(S2 .^ 2)) * sqrt(sum(b .^ 2)));
S3a = sum(S3 .* a);
S3b = sum(S3 .* b);
S3a2 = sum(S3 .* a) / (sqrt(sum(S3 .^ 2)) * sqrt(sum(a .^ 2)));
S3b2 = sum(S3 .* b) / (sqrt(sum(S3 .^ 2)) * sqrt(sum(b .^ 2)));

% Вывод
fprintf(' %.0f\n', S1a)
fprintf(' %.0f\n', S1b)
fprintf(' %.2f\n', S1a2)
fprintf(' %.2f\n', S1b2)
fprintf(' %.0f\n', S2a)
fprintf(' %.0f\n', S2b)
fprintf(' %.2f\n', S2a2)
fprintf(' %.2f\n', S2b2)
fprintf(' %.0f\n', S3a)
fprintf(' %.0f\n', S3b)
fprintf(' %.2f\n', S3a2)
fprintf(' %.2f\n', S3b2)
