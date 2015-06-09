clear all;
load 'Results/ERROR.txt';

figure; hist( ERROR(:,1),40);
figure; hist( ERROR(:,2),40);
figure; hist( ERROR(:,3),40);
figure; hist( ERROR,40);


NumeroEstrellas = zeros(1,100);

for i=1:100
    num = num2str(i);
    f = strcat('Results/Results_',num, '/Result_', num, '.txt');
    fid1 = fopen(f,'r');
    line = fgets(fid1); line = fgets(fid1); 
    cont = size(strfind(line, 9),2) - 1; % 9 = tabulador
    NumeroEstrellas(i) = cont;
    fclose(fid1);
end

% Eliminamos la tercera fila por error muy grande
%NumeroEstrellas = NumeroEstrellas([1:2, 4:100]);
figure; hist( NumeroEstrellas,40);

maxim = max(NumeroEstrellas);
AcErr= zeros(3,maxim+1);
AcNum = zeros(1,maxim+1);
for (i=1:maxim+1)
    AcNum(i) = i-1;
end
for (i=1:100)
    AcErr(1,NumeroEstrellas(i)) = (AcErr(1,NumeroEstrellas(i)) + ERROR(i,1))/2;
    AcErr(2,NumeroEstrellas(i)) = (AcErr(2,NumeroEstrellas(i)) + ERROR(i,2))/2;
    AcErr(3,NumeroEstrellas(i)) = (AcErr(3,NumeroEstrellas(i)) + ERROR(i,3))/2;
end

figure; plot (AcNum,AcErr);
kk = mean(AcErr,1);

figure; plot (AcNum,mean(AcErr,1));
