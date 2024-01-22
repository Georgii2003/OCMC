% CRC - Задание 3
function calculate_crc(bit_arr)
    G = [1, 1, 1, 1, 0, 0, 0, 0];
    bit_arr = [bit_arr, zeros(1,7)];
    
    for i = 1:length(bit_arr)-8
        if bit_arr(i) == 1 
            bit_arr(i:i+7) = bitxor(bit_arr(i:i+7), G);
        end
    end
    
    crc = bit_arr(end-6:end);
end