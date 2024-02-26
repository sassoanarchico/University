clear 
clc
close all

load('C:\Users\DELL-7380\Desktop\corsi\FCI\homework FCI\dati\01_RawData\RawData_Subject_1_task_BL.mat')

x=ECG(1:3000);
figure;
plot(x);

f_pass =10;
y = lowpass(x,f_pass,samplFreq);
figure; plot(y);