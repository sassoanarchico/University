
load gong
%sound (y, Fs)
% Display the sound signals from chirp and train

subplot(2,1,1)
load chirp
plot(y)
ylabel ('Amplitude')
title ('Chirp')
subplot(2 ,1 ,2)


load train
plot(y)
ylabel ('Amplitude')
title ('Train')

L = numel(y);
fft_signal = fft(y);
figure;
plot(Fs/L*(0:L-1),abs(fft_signal));

figure;
spectrogram(y);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


