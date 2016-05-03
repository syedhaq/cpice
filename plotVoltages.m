function plotVoltages(fileName,numValues,stepSize,timeStart,timeEnd,plotName,xlab,ylab)
%PLOTVOLTAGES plots voltage data from file
%Input:
%fileName: name of text file containing voltage data
voldataID=fopen(fileName,'r');
fscanf(voldataID,'%s',[1,2]);
voltdata=fscanf(voldataID,'%f',[2,numValues])';
figure
hold on
plot(timeStart:stepSize:(timeEnd-stepSize),voltdata(:,1));
plot(timeStart:stepSize:(timeEnd-stepSize),voltdata(:,2));
title(plotName);
xlabel(xlab);
ylabel(ylab);
legend('V_1(t)','V_2(t)','location','best');
hold off
fclose(voldataID);
end



