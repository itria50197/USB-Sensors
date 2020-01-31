function [V,D] = Eigens(Rho,L,phi_k,EI_x,x,LocationOfFocus)
M_3x1 = Rho * L * phi_k; % Rho(x), Phi_k(x), Alpha(3x1), Beta(3x1)
K_3x1 = (diff(EI_x,x,2) + diff(EI_x,x)) * diff(phi_k,x,2) + (diff(EI_x,x) + EI_x) * diff(phi_k,x,3); % K(x)

M_3x3 = diag(M_3x1);
K_3x3 = diag(K_3x1);

M_Valued = subs(M_3x3,x,LocationOfFocus);
K_Valued = subs(K_3x3,x,LocationOfFocus);
K_Valued = -1*K_Valued;
    
[V,D] = eig(double(K_Valued),double(M_Valued));