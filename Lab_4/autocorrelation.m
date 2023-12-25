function autocorr = autocorrelation(original, shifted, length)
    matches = 0;
    for i = 1:length
        if original(i) == shifted(i)
            matches = matches + 1;
        end
    end
    autocorr = (matches - (length - matches)) / length;
end