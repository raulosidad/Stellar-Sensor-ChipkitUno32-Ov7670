function [ Star_pairs, Unit_vectors, Cat_StarsID] = catinit( starcat, FOV, Mag_limit)

%***************************************************************************************
% Create file
%***************************************************************************************
if (nargin == 3) % Create file
    m_max = Mag_limit;   % Maximun Magnitude

    % Read HYG Catalog
    hygfull = importdata(starcat);
    num_total = size(hygfull,1);

    % Calculate Unit Vectors for stars with magnitude >= m_max
    figure; title('Stars');
    hold on;
    cont = 1;
    for u=1:num_total
        if (hygfull(u,4)<=m_max)
            RA = deg2rad(hygfull(u,2)*15);
            DEC = deg2rad(hygfull(u,3));
            plot(hygfull(u,2)*15,hygfull(u,3), '*');
            text((hygfull(u,2)*15)+1 ,hygfull(u,3), num2str(u),'FontSize',7,'Color',[0 0 0]);
            Unit_vectors(cont,:) = [cos(RA)*cos(DEC) sin(RA)*cos(DEC) sin(DEC) cont]';
            Magnitudes(cont) = hygfull(u,4);
            Cat_StarsID(cont) = u;
            cont = cont+1;
        end 
    end
    hold off;

    % Selection of star pairs
    num_selected=size(Unit_vectors,1);
    cont = 1;
    for i=1:num_selected
        for j=(i+1):num_selected-1 % Symetric distance a->b and b->a
        %for j=1:num2 
            if (i~=j)
                dist = Unit_vectors(i,1:3)*Unit_vectors(j,1:3)';
                dist_deg = acos(dist)*180/pi;
                if (dist_deg <= FOV)
                    Star_pairs(cont,:) = [Unit_vectors(i,4) Unit_vectors(j,4) dist_deg]';
                    cont=cont+1;
                end
            end                
        end % For j
    end % For i
    Star_pairs = sortrows(Star_pairs,3);
    Unit_vectors = Unit_vectors(:,1:3);

    save 'cat_hyg.mat' Star_pairs Unit_vectors Cat_StarsID Magnitudes;

%***************************************************************************************
% Read file
%***************************************************************************************
else % Read file
    cat_hyg_load = load ('cat_hyg.mat');
    Star_pairs = cat_hyg_load.Star_pairs;
    Unit_vectors = cat_hyg_load.Unit_vectors;
    Cat_StarsID = cat_hyg_load.Cat_StarsID;
end
    
end

