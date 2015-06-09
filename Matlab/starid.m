function [ Candidate_Uvectors, Catalog_Uvectors, Catalog_Star_IDs ] = starid( Image_UnitVectors, Catalog_StarPairs, Catalog_UnitVectors, Cat_StarsID, FOV, Pixel_Size, tol )

% **************************************************************************************
% ************** CANDIDATE MATCHING ****************************************************
% **************************************************************************************
num_candidates = size(Image_UnitVectors,1);
num_stars_catalog = size(Catalog_UnitVectors,1);
num_catalog_starspairs = size(Catalog_StarPairs,1);
matches = zeros(num_candidates,num_stars_catalog);
matches_2 = zeros(num_candidates,num_stars_catalog);

for i=1:num_candidates-1
   for j=(i+1):num_candidates % Symetric distance a->b and b->a
        dist = Image_UnitVectors(i,1:3)*Image_UnitVectors(j,1:3)';
        dist_deg = acos(dist)*180/pi;
        if (dist_deg <= FOV)
             start_index = BinarySearch(Catalog_StarPairs(:,3),(dist_deg - tol));
             for h=uint32(start_index):uint32(num_catalog_starspairs)
                 dist_catalog = Catalog_StarPairs(h,3);
                 if ( (dist_deg - tol)<=dist_catalog && dist_catalog<=(dist_deg + tol) )
                     matches(i,Catalog_StarPairs(h,1)) =  matches(i,Catalog_StarPairs(h,1))+1;
                     matches(i,Catalog_StarPairs(h,2)) =  matches(i,Catalog_StarPairs(h,2))+1;
                     matches(j,Catalog_StarPairs(h,1)) =  matches(j,Catalog_StarPairs(h,1))+1;
                     matches(j,Catalog_StarPairs(h,2)) =  matches(j,Catalog_StarPairs(h,2))+1;
                 end  
                 if ( dist_catalog>(dist_deg + tol) )
                    break;
                 end  
             end   
        end    
  end % For j
end % For i


% En matches tenemos para cada estrella candidata un array con la cantidad
% de veces que ha dado positivo el algoritmo de matching por cada estrella
% del catálogo. Cada posición de este array representa la posición de
% estrella en el array de estrellas del catálogo Para conocer el ID de la
% estrella se debe recuperar el valor de stars
final_matching_stars = zeros(1,num_candidates); % ID de la estrella en el catálogo
final_matching_index = zeros(1,num_candidates); % Índice de la estrella en el catálogo
for k=1:num_candidates
    uu= max(matches(k,:));
    uuu = find(matches(k,:)==uu);
    index = find(matches(k,:)== max(matches(k,:)), 1,'first');
    final_matching_stars(1,k) = Cat_StarsID(1,index);
    final_matching_index(1,k) = index;
end

% **************************************************************************************
% *************** VERIFICATION AND FINAL RESULT ****************************************
% **************************************************************************************
for i=1:num_candidates
  for j=(i+1):num_candidates % Symetric distance a->b and b->a
    dist_cat = Catalog_UnitVectors(final_matching_index(i),1:3)*Catalog_UnitVectors(final_matching_index(j),1:3)';
    dist_cat = acos(dist_cat)*180/pi;
    dist = Image_UnitVectors(i,1:3)*Image_UnitVectors(j,1:3)';
    dist = acos(dist)*180/pi;
    if ( (dist - tol)<=dist_cat && dist_cat<=(dist + tol) )
         matches_2(i,final_matching_index(i)) =  matches_2(i,final_matching_index(i))+1;
         matches_2(i,final_matching_index(j)) =  matches_2(i,final_matching_index(j))+1;
         matches_2(j,final_matching_index(i)) =  matches_2(j,final_matching_index(i))+1;
         matches_2(j,final_matching_index(j)) =  matches_2(j,final_matching_index(j))+1;
    end  
  end % For j
end % For i


cont=0;
T = max(matches_2(:)) -1;
for k=1:num_candidates
    if (sum(matches_2(k,:)) >  T)
         cont = cont +1;
         Catalog_Star_IDs(cont) =  final_matching_stars(1,k);
         FINAL_index(cont) =  final_matching_index(1,k);
         Candidate_Uvectors(cont,:) = Image_UnitVectors(k,:);
         Catalog_Uvectors(cont,:) = Catalog_UnitVectors(FINAL_index(cont),1:3);
    end
end

end

