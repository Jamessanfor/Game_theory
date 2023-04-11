hold on 
grid on

hawks1= table2array(DovesHawks1(:,2));
doves2= table2array(DovesHawks1(:,1));
len= length(hawks1)
plot(1:len, hawks1+doves2,'b')
plot(1:len, hawks1,'r',1:len, doves2,'g')
xlabel('Days')
ylabel('Number of Actors')
title('Doves and Hawks sim1')
legend('Both','Hawks','Doves')

%%
hold on 
grid on
hawks1= table2array(DovesHawks2(:,2));
doves2= table2array(DovesHawks2(:,1));
len= length(hawks1)
plot(1:len, hawks1+doves2)
plot(1:len, hawks1,'r',1:len, doves2,'g')

xlabel('Days')
ylabel('Number of Actors')
title('Doves and Hawks sim2')
legend('Both','Hawks','Doves')
