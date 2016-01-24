function traitementgeneral

close all

% pour les descripteurs de Fourier
cmax=15;
N=200;

liste=dir('*.pgm');
%liste = dir('resultat2_avance1.pgm');

tabcontfil=zeros(N+1,2*length(liste));
vecteurs=zeros(2*(2*cmax+1),2*length(liste));
for n=1:length(liste)
    nom=liste(n).name;
    BW~=imread(nom, 'PGM');

    zliste=bwboundaries(BW,8,'noholes');
    longmax=0;
    for num=1:length(zliste)
        longueur=size(zliste{num},1);
        if longueur>longmax
            longmax=longueur;
            z=zliste{num};
	    disp('zliste{num}'), disp('length:'),disp(length(zliste));
 	    disp('longueur'),disp(longueur);
	    disp(z);
        end
    end
    z=z(:,1)+1i*z(:,2);
   %    figure, image(255*BW),axis equal,colormap(gray(256))
    %set(title([listenoms{2*n} ' : ' nom]),'Interpreter','none')
   % hold on
   % plot(imag(z),real(z),'b')
   % axis equal
   %      drawnow
    coeff=dfdir(z,cmax);
    coeffpi=dfdir(-z,cmax);
    contfil=dfinv(coeff,N,cmax);
    contfilpi=dfinv(coeffpi,N,cmax);
    tabcontfil(:,2*n-1)=contfil;
    tabcontfil(:,2*n)=contfilpi;
    vecteurs(:,2*n-1)=[real(coeff);imag(coeff)];
    vecteurs(:,2*n)=[real(coeffpi);imag(coeffpi)];
end
figure
h=plot(real(tabcontfil),imag(tabcontfil));
%set(legend(h,listenoms),'Interpreter','none');
title('contours associés aux coefficients normalisés')
axis equal
grid on
print -djpg contours_reconstruits.jpg

figure
plot(-cmax:cmax,vecteurs(1:2*cmax+1,:))
title('partie réelle des coefficients normalisés')
grid on
axis([-cmax cmax -0.2 1.2])
drawnow


figure
plot(-cmax:cmax,vecteurs(2*cmax+2:end,:))
title('partie imaginaire des coefficients normalisés')
grid on
axis([-cmax cmax -0.2 1.2])
drawnow

































































