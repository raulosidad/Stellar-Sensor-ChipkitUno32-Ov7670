function [ IMG, R_I_C, Stars_ID, hand ] = Generate_Image( Resolution_x, Resolution_y, pixel_size, FOV, focal, Aperture_diameter )

% Camera Parameters: 
pixel_size_x = pixel_size;     
pixel_size_y = pixel_size;     
tau = 1;            % Transmittance
lammda = 0.6;       % Spectral range (0.6um)600nm
l_sat = 13500;      % Saturation limit (photons)
np = 50;
b = 0.015; 
t_exp = 0.15;     % Exposure Time

% Random Attitude
alpha = [rand rand rand];
theta = (alpha - [0.5 0.5 0.5]) * (180);
theta = deg2rad(theta);

% Direction cosine matrix
R_1 = [ cos(theta(1))    sin(theta(1))    0;
       -sin(theta(1))    cos(theta(1))    0;
        0                0                1];
R_2 = [ cos(theta(2))    0               -sin(theta(2));
        0                1                0;
        sin(theta(2))    0                cos(theta(2))];
R_3 = [ 1                0                0;
        0                cos(theta(3))    sin(theta(3));
        0                -sin(theta(3))   cos(theta(3))];
R_I_C = R_1 * R_2 * R_3;
u_bore = R_I_C' * [0 0 1]';

% Image Generation
IMG = zeros(Resolution_x,Resolution_y);
IMG_Size_X = Resolution_x * pixel_size_x;
IMG_Size_Y = Resolution_y * pixel_size_y;

cat_hyg_load = load ('cat_hyg.mat');
num_cat = size(cat_hyg_load.Unit_vectors,1);
u_hyg = cat_hyg_load.Unit_vectors; % Unit vector for catalog stars
Mag = cat_hyg_load.Magnitudes;

cont = 1;
for k=1:num_cat
   dist = u_bore' * u_hyg(k,:)';
   dist_deg = acos(dist)*180/pi; 
   if ( dist_deg < (FOV/2) )
       star(cont) = cat_hyg_load.Cat_StarsID(k);
       u_star_C  = R_I_C * u_hyg(k,:)';
       u(cont) = focal*(u_star_C(1)/u_star_C(3));
       v(cont) = focal*(u_star_C(2)/u_star_C(3));
       S = t_exp * (pi*(Aperture_diameter^2)/4) * tau * lammda * (10^(-0.4*Mag(k)));
       for j=1:np
           [u_prima(j),v_prima(j)] = rand_circ(1,u(cont),v(cont),b);
           x = round((u_prima(j)/pixel_size_x)+(Resolution_x/2));
           y = round((v_prima(j)/pixel_size_y)+(Resolution_y/2));
           if (x>0 && x<Resolution_x && y>0 && y<Resolution_y)
               IMG(x,y) = IMG(x,y) + (S/np);
           end

       end
       cont = cont +1;
   end;
    
end

for i=1:Resolution_x
    for j=1:Resolution_y
       if((IMG(i,j)/l_sat) <= 1)
           IMG(i,j) = IMG(i,j)/l_sat;
       end
       if((IMG(i,j)/l_sat) > 1)
           IMG(i,j) = 1;
       end
    end
end
hand = figure; imshow(IMG); title('Original + Centroides');
hold on;

cont_2= 1;
for i=1:cont-1
    xx = round((u(i)/pixel_size_x)+(Resolution_x/2));
    yy = round((v(i)/pixel_size_y)+(Resolution_y/2));
    if (xx<Resolution_x && xx>0 && yy<Resolution_y && yy>0)
        Stars_ID(cont_2) = star(i);
%         plot(yy ,xx,'o'); 
%         text(yy+5 ,xx+5, num2str(star(i)),'FontSize',10,'Color',[0 1 1]);
         cont_2 = cont_2 + 1;
    end    
end
hold off;

imwrite(IMG,'Fotos/Imagen_1.bmp','bmp');
