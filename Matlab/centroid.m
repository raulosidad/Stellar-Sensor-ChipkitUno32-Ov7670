function [ Star_Centers ] = centroid( Image, Ithresh, aRoi )
% Definitions
r_avge = 7; 

[X Y] = size(Image);
cont=1;

for x=1:X
   for y=1:Y
       if ( Image(x, y) > Ithresh)
           % Calculate ROI
            x_start = x - ((aRoi -1)/2);
            y_start = y - ((aRoi -1)/2);
            if (x_start<=0 || y_start<=0 )
                break; % Next pixel
            end
            x_end   = x_start + aRoi;
            y_end   = y_start + aRoi;
            if (x_end>X || y_end>Y )
                break; % Next pixel
            end
            
            % Find the average intensity value of the border pixels Iborder
            I_botton = 0;
            for i=x_start:(x_end-1)
                 I_botton = I_botton + Image(i,y_start);
            end
            I_top = 0;
            for i=(x_start+1):(x_end)
                 I_top = I_top + Image(i,y_end);
            end
            I_left = 0;
            for j=(y_start):(y_end-1)
                 I_left = I_left + Image(x_start,j);
            end
            I_right = 0;
            for j=(y_start+1):(y_end)
                 I_right = I_right + Image(x_end,j);
            end
            Iborder = (I_botton + I_top + I_left + I_right) / (4*(aRoi - 1));
            
           % Normalized light intensity matrix Inorm
           Inorm = zeros(aRoi-2,aRoi-2);
           for i=(x_start+1):(x_end-1)
                for j=(y_start+1):(y_end-1)
                    Inorm(i,j) = Image(i,j) - Iborder;
                end
           end
           
           %Calculate the centroid location (xCM; yCM)
           B =0;
           for i=(x_start+1):(x_end-1)
               for j=(y_start+1):(y_end-1)
                   B = B + Inorm(i,j);
               end
           end
           xCM = 0;
           for i=(x_start+1):(x_end-1)
               for j=(y_start+1):(y_end-1)
                   xCM = xCM + (i * Inorm(i,j) / B);
               end
           end
           yCM = 0;
           for i=(x_start+1):(x_end-1)
               for j=(y_start+1):(y_end-1)
                   yCM = yCM + (j * Inorm(i,j) / B);
               end
           end

            Centroides(cont).xCM = xCM;
            Centroides(cont).yCM = yCM;
            Centroides(cont).processed = 0;
            cont = cont +1;  
                  
       end % if ( I2(x, y) > Ithresh)      
   end % for y
end % for x

cont_CM =1;
for u=1:cont-1
    if ( Centroides(u).processed ==0)
        Centroides_CM(cont_CM) = Centroides(u);
        Centroides(u).processed =1;
        for v=1:cont-1
            if(u~=v)
                 if( (abs(Centroides(v).xCM -  Centroides(u).xCM) <= r_avge) && (abs(Centroides(v).yCM -  Centroides(u).yCM) <= r_avge) )
                  Centroides_CM(cont_CM).xCM = (Centroides_CM(cont_CM).xCM  + Centroides(v).xCM) /2 ;
                  Centroides_CM(cont_CM).yCM = (Centroides_CM(cont_CM).yCM + Centroides(v).yCM) /2 ; 
                  Centroides(v).processed =1;              
                end  
            end
        end %FOR v
        Star_Centers(cont_CM,:) = [Centroides_CM(cont_CM).xCM Centroides_CM(cont_CM).yCM ];
        cont_CM = cont_CM+1;
    end   
end % FOR u

end

