clc
close all
clear

% Definizione del segnale
n = 0:100; % Intervallo di campionamento da 0 a 100
x = sin(0.1*pi*n); % Esempio di un segnale sinusoidale discreto

% Calcolo dell'energia
E = sum(abs(x).^2); % Calcolo dell'energia utilizzando una sommatoria

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

