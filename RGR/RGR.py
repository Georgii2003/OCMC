import crcmod
import matplotlib.pyplot as plt
import numpy as np
from scipy.fftpack import fft, fftfreq, fftshift

# CRC - Задание 3
def calculate_crc(bit_array):
    polinom = [1, 0, 1, 1, 1, 1, 1, 1]
    bit_array = bit_array + [0]*7 
    for i in range(len(bit_array)-8): 
        if bit_array[i] == 1 : 
            bit_array[i:i+8] = [bit_array[j] ^ polinom[j] for j in range(8)] 
    return bit_array[-7:]

# Генерация последовательности Голда - Задание 4
def generate_gold_sequence(G):
    x = [0, 0, 0, 0, 1]
    y = [0, 1, 0, 0, 0]
    gold_sequence = np.zeros(G)
    #original = np.zeros(G)
    #shifted = np.zeros(G)
    for i in range(G):
        gold_sequence[i] = x[4] ^ y[4]
        #original[i] = gold_sequence[i]
        #shifted[i] = gold_sequence[i]

        temp = x[3] ^ x[4]
        x = np.roll(x, -1)
        x[0] = temp

        temp = y[1] ^ y[4]
        y = np.roll(y, -1)
        y[0] = temp
    return np.array(gold_sequence) #, original, shifted

# Корреляционный прием - Задание 8
def cor_tech(bit_array, code_gold):
    code_gold = np.repeat(code_gold, 5)
    correlation = np.correlate(bit_array, code_gold, "valid")
    correlation /= correlation[np.argmax(correlation)]
    max_arg = np.argmax(correlation)
    plt.title('Корреляция')
    plt.plot(correlation)
    plt.show()
    return max_arg

# Функция декодирования - Задание 9
def decoding(bit_array): 
    decoding = [] 
    for bit in bit_array: 
        if bit > 0.5: 
            decoding.append(1) 
        else: 
            decoding.append(0) 
    return decoding

# Функция проверки корректности приема бит - Задание 11
def crc_rec(bit_array):
    polinom = [1, 0, 1, 1, 1, 1, 1, 1]
    bit_array = np.array(bit_array, dtype=int)
    for i in range(len(bit_array)-8):
        if bit_array[i] == 1 :
            bit_array[i:i+8] ^= polinom
    return bit_array[-7:]

# Ввод имени и фамилии - Задание 1
name = input("Введите ваше имя: ")
surname = input("Введите вашу фамилию: ")

# Преобразование имени и фамилии в бинарный формат - Задание 2
L_array = []
for char in name + surname:
    ascii_code = ord(char)
    binary_representation = format(ascii_code, '08b')
    L_array.extend([int(bit) for bit in binary_representation])

# Визуализация последовательности - Задание 2
plt.figure(figsize=(10,5))
plt.plot(L_array)
plt.title('Последовательность имени и фамилии')
plt.ylabel('Бит')
plt.show()

# Вычисление и преобразование CRC - Задание 3
crc = calculate_crc(L_array) 
print( "CRC = ", crc)
M_array = crc
M = len(M_array)

# Данные для последовательности Голда - Задание 4
G = 31
gold_sequence = generate_gold_sequence(G)
G_array = gold_sequence.astype(int).tolist()
L = len(L_array)

print("Длина массива L = ", L, "Длина массива M = ", M, " Длина массива G = ", G)
LMG = L + M + G
print("Длина общего массива LMG = ", LMG)
LMG_array = np.concatenate((G_array, L_array, M_array, ))

# Визуализация массива с битами данных, CRC и синхронизацией - Задание 4
plt.figure(figsize=(10,5))
plt.title('Последовательность массива с битами данных, CRC и синхронизацией')
plt.plot(LMG_array)
plt.show()

# Преобразование битов с данными во временные отсчёты - Задание 5
N = 5
Timings = np.repeat(LMG_array, N)
#Timings = np.pad(LMG_array, (N, N), 'constant')
T = len(Timings)
print('Длина общего массива с преобразованными битами данных T: ', T)

# Визуализация временных отсчётов - Задание 5
plt.figure(figsize=(10,5))
plt.subplot(2,1,1)
plt.stem(LMG_array)
plt.title('Временные отсчеты сигнала')
plt.ylabel('Амплитуда')

plt.subplot(2,1,2)
plt.plot(LMG_array)
plt.xlabel('Время')
plt.ylabel('Амплитуда')
plt.show()

# Визуализация нулевого и обработанного сигнала - Задание 6
Timings_crushx2 = np.zeros(len(Timings)*2)
start = int(input(f"Введите число (Диапазон в значениях: 0 - {len(Timings_crushx2)}) старта передачи: "))
Timings_crushx2[start:start + len(Timings)] = Timings
plt.figure(figsize=(10,5))
plt.title('Полученный сигнал')
plt.plot(Timings_crushx2)
plt.show()

# Визуализация массива отсчетов зашумленного принятого сигнала - Задание 7
second = float(input("Введите параметр σ для нормального закона распределения: "))
noise = np.random.normal(0, second, len(Timings_crushx2))
Timings_crushx2_noise = noise + Timings_crushx2
plt.figure(figsize=(10,5))
plt.title('Полученный сигнал вместе с шумом')
plt.plot(Timings_crushx2_noise)
plt.show()

# Визуализация корреляционного приёма - Задание 8
correlation = cor_tech(Timings_crushx2_noise, G_array) 
if correlation is not None:
    print('Начиная с отсчёта (семпла) ', correlation, ' начинается синхросигнал')
    Timings_with_noise = Timings_crushx2_noise[correlation:]
    plt.figure(figsize=(10,5))
    plt.title('Полученный сигнал, начинающийся с синхронизации')
    plt.plot(Timings_with_noise)
    plt.show()

# Визуализация декодирования - Задание 9
Timings_with_noise = Timings_with_noise[:len(Timings)] 
Timings_with_noise = Timings_with_noise[::5] 
decoding_bits = decoding(Timings_with_noise) 
print('Полученные данные:', decoding_bits) 
plt.figure(figsize=(10,5))
plt.title('Полученный сигнал начиная с синхронизации') 
plt.plot(Timings_with_noise) 
plt.show()

# Удаление из полученного массива последовательности синхронизации - Задание 10
decoding_bits = decoding_bits[len(G_array):]
print('Полученный данные без синхронизации', decoding_bits)

# Проверка корректности приема бит - Задание 11
decoding_bits_crc = crc_rec(decoding_bits)
error = 0
print('Проверка CRC: ', ''.join(str(i) for i in decoding_bits_crc))
for i in range(len(decoding_bits_crc)):
    if decoding_bits_crc[i] == 1:
         error = 1
if error == 0:
    print('Предача прошла безошибочно!')
else:
    print('Произошли ошибки в количестве: ', error)

# Восстановлени посимвольно введёного текста - Задание 12
decoding_bits = decoding_bits[:-7]
L_array = ''.join(str(b) for b in decoding_bits) 
n = int(L_array, 2) 
decoded_words = n.to_bytes((n.bit_length() + 7) // 8, 'big').decode()
print(decoded_words)

# Визуализация спектров сигналов - 13 задание
tx_signal = fftshift(fft(LMG_array))
rx_signal = fftshift(fft(Timings_with_noise))
spectrum = np.repeat(LMG_array, 2)
spectrum_1 = np.repeat(spectrum, 5)
spectrum_2 = np.repeat(spectrum, 10)
spectrum_1 = spectrum_1[:len(spectrum)]
spectrum_2 = spectrum_2[:len(spectrum)]
spectrum = fftshift(fft(spectrum))+80
spectrum_1 = fftshift(fft(spectrum_1))+40
spectrum_2 = fftshift(fft(spectrum_2))
plt.title('Спектры полученного и переданного сигнала')
plt.plot(tx_signal)
plt.plot(rx_signal)
plt.show()

plt.title('Спектры 3 разных по длительности сигналов')
plt.plot(spectrum)
plt.plot(spectrum_1)
plt.plot(spectrum_2)
plt.show()
