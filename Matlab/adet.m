function [ A ] = adet( Candidate_Uvectors, Catalog_Uvectors )

% **************************************************************************************
% *************** ATTITUDE determination ****************************************
% **************************************************************************************
cont = size(Candidate_Uvectors,1);
B = zeros(3,3);
for k=1:cont
    B = B + Candidate_Uvectors(k,:)'*Catalog_Uvectors(k,:);
end

[U,S,V] = svd(B);
U_aux = [1  0   0;
         0  1   0;
         0  0   det(U)];
 V_aux = [1  0   0;
     0  1   0;
     0  0   det(V)];
     
U_plus = U * U_aux;
V_plus = V * V_aux;

A = U_plus * V_plus';

end

