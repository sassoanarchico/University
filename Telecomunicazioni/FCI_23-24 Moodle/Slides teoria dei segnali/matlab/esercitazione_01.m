clc
close all
clear


% Creare una sinusoide
A = 5; % Amplitude
T= 2; % Periodo
phi=0;

n = 0:0.05:2*T; % Intervallo di tempo da 0 a 2*T
x = A * cos(2*pi*n/T +phi);

% Grafico della sinusoide originale
subplot(2, 1, 1);
plot(n, x);
xlim([0 10])

title('Segnale Originale');
xlabel('Tempo');
ylabel('Amplitude');

% Definizione segnale xx
%a = 1/2;
b= 3;

xx = A * cos(2*pi*n/T +phi)+b;



subplot(2, 1, 2);
plot(n, xx);
title('Segnale modificato');
xlim([0 10])
xlabel('Tempo');
ylabel('Amplitude');

% vettore per scegliere se si vuole calcolare valore medio su segnale
% originario o modificato 
choice_vect = 'transformed';% original, transformed

if strcmp(choice_vect,'original')==1
    x_chosen = x;
    mean_val = mean(x_chosen);
    E_chosen = sum(abs(x_chosen).^2); % Calcolo dell'energia utilizzando una sommatoria

 elseif strcmp(choice_vect,'transformed')==1
        x_chosen = xx;
        mean_val = mean(x_chosen);
        E_chosen = sum(abs(x_chosen).^2); % Calcolo dell'energia utilizzando una sommatoria

end

titlefig = strcat("Figure with ",choice_vect, " signal with mean value");
figure('Name', titlefig)
stem(n,x_chosen);
hold on
yline(mean_val,'-.b','Mean Value','LineWidth',3);
text(0.2,7,strcat('Energy=',num2str(E_chosen)));

phi_vector =[1, 1.25, 1.5, 1.75,2];
matrix_signals = zeros(numel(x), numel(phi_vector));
%T_matrix = 3;


for i=1:numel(phi_vector)
    matrix_signals(:,i) = A * cos(2*pi*n/T + phi_vector(i));
    crosscorr(:,i) =xcorr(x,matrix_signals(:,i))';
    autocorr(:,i) = xcorr(matrix_signals(:,i)',matrix_signals(:,i))';
    correlationcoefficient_matrix=corrcoef(x,matrix_signals(:,i))';
    correlationcoefficient(i)= correlationcoefficient_matrix(1,2);
end


figure;
imagesc(correlationcoefficient);

% definizione filtri
%h_1 = zeros(size(t));
%h_1(t == 3) = 1; 

h= zeros(size(n));
h(n >= 1 & n <= 2) = 1;

y = conv(x, h,'full');



% Plottare il segnale di ingresso
subplot(3,1,1);
plot(n, x);
title('Segnale in Ingresso x(t)');
xlabel('Tempo');
ylabel('Amplitude');

% Plottare la risposta impulsiva del filtro
subplot(3,1,2);
plot(n, h);
title('Risposta Impulsiva del Filtro h(t)');
xlabel('Tempo');
ylabel('Amplitude');

% Plottare il segnale filtrato
subplot(3,1,3);
plot(y);
title('Segnale Filtrato y(t)');
xlabel('Tempo');
ylabel('Amplitude');






