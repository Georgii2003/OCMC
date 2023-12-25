LENGTH = 5;
SEQUENCE_LENGTH = 31;

x = [0, 0, 0, 0, 1];
y = [0, 1, 0, 0, 0];

disp('Массив x: ');
printArray(x, LENGTH);
disp(' ')
disp('Массив y: ');
printArray(y, LENGTH);
disp(' ')

original = zeros(1, SEQUENCE_LENGTH);
shifted = zeros(1, SEQUENCE_LENGTH);

disp('Сгенерированная последовательность Голда: ');

goldSequence = zeros(1, SEQUENCE_LENGTH);
for i = 1:SEQUENCE_LENGTH
    goldSequence(i) = x(5) ~= y(5);

    original(i) = goldSequence(i);
    shifted(i) = goldSequence(i);

    disp(['', num2str(i)]);
    disp('x: ')
    printArray(x, LENGTH);
    disp(' ')
    disp('y: ');
    printArray(y, LENGTH);
    disp(' ')

    temp = xor(x(4), x(5));
    x(2:5) = x(1:4);
    x(1) = temp;

    temp = xor(y(2), y(5));
    y(2:5) = y(1:4);
    y(1) = temp;
end
disp(' ')
disp('Сгенерированная последовательность Голда: ');
printArray(goldSequence, SEQUENCE_LENGTH);
disp(' ');
disp('Shift|                              Bits                            |AutoCorr');

for shift = 1:33
    autocorr = autocorrelation(original, shifted, SEQUENCE_LENGTH);
    disp(['', num2str(shift), '|']);
    printArrayShift(shifted, SEQUENCE_LENGTH);
    disp(['| ', num2str(autocorr)]);

    temp = shifted(SEQUENCE_LENGTH);
    shifted(2:SEQUENCE_LENGTH) = shifted(1:SEQUENCE_LENGTH - 1);
    shifted(1) = temp;
end