function [ Image_Unit_Vectors ] = uvec( image_coordinates, focal, Pixel_Size )

Resolution_y = 648;
Resolution_x = 488;
offset_x = Resolution_x/2;
offset_y = Resolution_y/2;

cont_CM = size(image_coordinates,1);

% Create centroides Image
Image_Unit_Vectors = zeros(cont_CM,3);
 for u=1:cont_CM  
   vector = [ Pixel_Size*(image_coordinates(u,1)-offset_x) Pixel_Size*(image_coordinates(u,2)-offset_y) focal];
   Image_Unit_Vectors(u,:) = (vector' / norm(vector));
 end

end

