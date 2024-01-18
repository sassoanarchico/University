close all
clear
clc

% Creare una sinusoide
t = 0:0.5:2*pi; % Intervallo di tempo da 0 a 2*pi
A = 1; % Amplitude
f = 1; % Frequenza
phi = 0; % Fase
sinusoide = A * sin(2*pi*f*t + phi);

% Grafico della sinusoide originale
subplot(2, 1, 1);
stem(t, sinusoide);
title('Sinusoide Originale');
xlabel('Tempo');
ylabel('Amplitude');

% Trasla la sinusoide
t_shifted = t + 2; % Trasla di 1 secondo (puoi cambiare il valore a tuo piacimento)
sinusoide_shifted = A * sin(2*pi*f*t_shifted + phi);

% Grafico della sinusoide traslata
subplot(2, 1, 2);
plot(t_shifted, sinusoide_shifted);
title('Sinusoide Traslata');
xlabel('Tempo');
ylabel('Amplitude');
