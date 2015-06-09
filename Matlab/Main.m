%clearvars;
clear all;
close all;
 
% General settings
num_Rep = 100;
NumStar_Generated = 0;
NumStar_Indentified = 0;

Camera = 2;  % 1=Kodak, 2=OV7670
GenerateCatalog = 1;
GenerateImage = 1;
% Centroding
Ithresh = 100;
aRoi = 11; % Must to be odd values  %11

% Camera Settings
switch (Camera)
    case 1  % 1=Kodak
        FOV = 60;           % deg
        Mag_limit = 3.75;
        focal =6;           % mm
        pixel_size =0.0075; % mm
        Resolution_y = 648; % Pixels
        Resolution_x = 488; % Pixels
        d = 6000;           % Aperture diameter (6 mm)
    case 2  % 2=OV7670
        FOV = 45;         % deg
        Mag_limit = 3.5;
        focal = 3.6;        % mm
        pixel_size =0.0036; % mm 
        Resolution_y = 640; % Pixels
        Resolution_x = 480; % Pixels
        d = 6000;           % Aperture diameter (6 mm)
   end

% Read Catalog
if (GenerateCatalog == 1)
    [ Cat_starPairs, Cat_Uvect, Cat_StarsID] = catinit( 'hygfull.csv', FOV, Mag_limit);
else
    [ Cat_starPairs, Cat_Uvect, Cat_StarsID] = catinit( 'cat_hyg.mat');
end

for rep=1:num_Rep

    if (GenerateImage == 1)
        [IMG, RIC, Original_StarsID, h_1]  = Generate_Image( Resolution_x, Resolution_y, pixel_size, FOV, focal, d );
    end
    NumStar_Generated = NumStar_Generated + size(Original_StarsID,2);
    % Load Image
    Image = loading( 'Fotos/Imagen_1.bmp' );

    % Calculate Centroides
    Star_Centers = centroid( Image, Ithresh, aRoi );
    h_2 = figure; imshow(Image); title('Original + Estrellas localizadas');
    hold on;
    for i=1:(size(Star_Centers,1))
        plot(Star_Centers(i,2) ,Star_Centers(i,1),'o'); 
    end
    hold off;

    % Calculate Unit Vectors of image stars
    Image_Unit_Vectors = uvec( Star_Centers, focal, pixel_size );

    % Star Matching: Voting method
    diagonal = sqrt(Resolution_x^2 + Resolution_y^2);
    tol = FOV / diagonal;
    [ Candidate_Uvectors, Catalog_Uvectors, Catalog_Star_IDs ] = starid( Image_Unit_Vectors, Cat_starPairs, Cat_Uvect, Cat_StarsID, FOV, pixel_size, tol );
    NumStar_Indentified = NumStar_Indentified + size(Catalog_Star_IDs,2);
    
    % Attitude Determination
    A = adet( Candidate_Uvectors, Catalog_Uvectors );

    % Error Calculation
    Attitude_Error = inv(A)*RIC; 
    Err_x = abs(3600*(90 - rad2deg(acos(Attitude_Error(3,2))))); % arcseconds
    Err_y = abs(3600*(90 - rad2deg(acos(Attitude_Error(3,1))))); % arcseconds
    Err_z = abs(3600*(90 - rad2deg(acos(Attitude_Error(2,1))))); % arcseconds

    % Save Data
    Original_StarsID = sort(Original_StarsID);
    Catalog_Star_IDs = sort(Catalog_Star_IDs);
    Err = [Err_x Err_y Err_z];
    ERROR_TOTAL(rep,:) = Err;
    Path = sprintf('Results/Results_%i',rep);
    mkdir(Path);
    img_orig = strcat(Path, sprintf('/Original_%i',rep),'.jpg');
    img_fin = strcat(Path, sprintf('/Final_%i',rep),'.jpg');
    print(h_1, img_orig,'-djpeg');
    print(h_2, img_fin,'-djpeg');
    close all;

    File =strcat(Path, sprintf('/Result_%i.txt',rep));
    fid = fopen(File,'wt');
    fprintf(fid,'Original:   \t');fprintf(fid,'%i\t',Original_StarsID); fprintf(fid,'\n');
    fprintf(fid,'Calculated:  \t');fprintf(fid,'%i\t',Catalog_Star_IDs); fprintf(fid,'\n');
    fprintf(fid,'Error X-Y-Z: \t');fprintf(fid,'%i\t',Err); fprintf(fid,'\n');
    fclose(fid);

end

% Errores
Total_OK = 0;
File =sprintf('Results/ERROR.txt');
fid = fopen(File,'wt');
fprintf(fid,'Error X-Y-Z: \n');
 for i=1:(size(ERROR_TOTAL,1))
     fprintf(fid,'%i\t',ERROR_TOTAL(i,:)); fprintf(fid,'\n'); 
     if ( ERROR_TOTAL(i,1)<100 && ERROR_TOTAL(i,2)<100 &&ERROR_TOTAL(i,3)<100 )
         Total_OK = Total_OK+1;
     end
 end
fclose(fid); 

% Otros datos
File =sprintf('Results/Results.txt');
fid = fopen(File,'wt');
fprintf(fid,'Estrellas Generadas:   %i\n', NumStar_Generated);
fprintf(fid,'Estrellas Localizadas: %i\n', NumStar_Indentified);
fprintf(fid,'Error Medio X: %d\n', mean(ERROR_TOTAL(:,1)));
fprintf(fid,'Error Medio Y: %d\n', mean(ERROR_TOTAL(:,2)));
fprintf(fid,'Error Medio Z: %d\n', mean(ERROR_TOTAL(:,3)));
fprintf(fid,'Error Medio TOTAL: %d\n', mean([mean(ERROR_TOTAL(:,1)) mean(ERROR_TOTAL(:,2)) mean(ERROR_TOTAL(:,3))] ));
fprintf(fid,'TOTAL Imágenes OK: %d\n', Total_OK);
fclose(fid);

