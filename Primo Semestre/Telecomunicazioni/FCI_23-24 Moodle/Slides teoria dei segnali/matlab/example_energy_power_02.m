clc
close all
clear

close all
clear
clc



% Creare una sinusoide
t = 0:0.05:2*pi; % Intervallo di tempo da 0 a 2*pi
A = 1; % Amplitude
f = 1; % Frequenza
phi = 0; % Fase
x = A * sin(2*pi*f*t + phi);

% Grafico della sinusoide originale
subplot(2, 1, 1);
stem(t, x);
title('Sinusoide Originale');
xlabel('Tempo');
ylabel('Amplitude');

% Trasla la sinusoide
t_shifted = t + 2; % Trasla di 1 secondo (puoi cambiare il valore a tuo piacimento)
x_shifted = A * sin(2*pi*f*t_shifted + phi);





% Grafico della sinusoide traslata
subplot(2, 1, 2);
plot(t_shifted, x_shifted);
title('Sinusoide Traslata');
xlabel('Tempo');
ylabel('Amplitude');



% Calcolo dell'energia
E = sum(abs(x).^2); % Calcolo dell'energia utilizzando una sommatoria
E_shifted = sum(abs(x_shifted).^2); % Calcolo dell'energia utilizzando una sommatoria

%calcolo valore medio
%aggiungere al grafico


% Calcolo della potenza
N = length(x); % Lunghezza del segnale
% DA implementare
%%%

% Visualizzazione dei risultati
fprintf('Energia del segnale: %.4f\n', E);
fprintf('Potenza del segnale: %.4f\n', P);

% Plot del segnale
%subplot(2, 1, 1);
stem(n, x);
title('Segnale x[n]');
xlabel('n');
ylabel('Amplitude');

