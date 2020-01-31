clear
clc

L = 100;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Obtain a discretized model of the system %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Solve for mu_k & beta_k & alpha_k
N_Mode = 1;
Wanted_N_Mode = 3;
Solutions_Check_Point = 1;
Resolution = 0.01;
mu_k = zeros(Wanted_N_Mode,1);
alpha_k = zeros(Wanted_N_Mode,1);
beta_k = zeros(Wanted_N_Mode,1);

% Solve for the pictural solution of mu_k
mu = linspace(0,100,100);
y = cos(mu).*cosh(mu);
z = 1;
subplot(1,2,1);
plot(mu,y,'-r',mu,z,'*b');
xlim([0 50]);
xlabel('mu_k')
ylim([-10 10]);
ylabel('y')

% Solve for the numerical solution of mu_k
format short e
y = @(mu_k) cos(mu_k)*cosh(mu_k)-1; % mu_k Equation
mu_k(N_Mode,1) = fzero(y,Solutions_Check_Point); % 1st mu_k
N_Mode = N_Mode + 1;
Solutions_Check_Point = Solutions_Check_Point + 1;

while N_Mode <= Wanted_N_Mode
    y = @(mu_k) cos(mu_k)*cosh(mu_k)-1; % mu_k Equation
    mu_k(N_Mode,1) = fzero(y,Solutions_Check_Point); % Solve for mu_k
    
    if mu_k(N_Mode,1) - mu_k(N_Mode-1,1) < Resolution % Filter mu_k, avoid the influence from resolution
        Solutions_Check_Point = Solutions_Check_Point + 1;
    else
        N_Mode = N_Mode + 1;
        Solutions_Check_Point = Solutions_Check_Point + 1;
    end
end

alpha_k = (cosh(mu_k) + cos(mu_k))./(sinh(mu_k) + sin(mu_k));  % Solve for alpha_k
beta_k = mu_k./L; % Solve for beta_k

% Admissible Function
subplot(1,2,2);
Resolution = 500;
x = linspace(0,L,Resolution);
phi = zeros(Wanted_N_Mode,Resolution);

for i = 1:Wanted_N_Mode;
    phi(i,:) = cosh(beta_k(i)*x) - cos(beta_k(i)*x) - alpha_k(i)*(sinh(beta_k(i)*x) - sin(beta_k(i)*x));
    plot(x,phi(i,:),'-b');
    %hold on;
    ylim([-2 2]);
    xlabel('x');
    ylabel('Phi_k');
end
plot(x,phi(1,:),x,phi(2,:),x,phi(3,:));
xlabel('x');
ylabel('Phi_k');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Discretized EigenValue & EigenVector %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
syms x t
T_of_t = sym('T(t)');
Rho_0 = 10;
EI_0 = 3*10^6;
L = 2;
xe = 0.7*L;
epsilon = 0.25;
M = 3*Rho_0*L;
k = 3*10^5;
c = sqrt(k*M)/5;

Rho = Rho_0*(1-(epsilon*x/L));
EI_x = EI_0*(1-(epsilon*x/L)^2);
phi_k = cosh(beta_k*x) - cos(beta_k*x) - alpha_k.*(sinh(beta_k*x) - sin(beta_k*x));
omega_xt = phi_k * T_of_t;

% PointsOfMesh = 100;
LocationOfFocus = 1; % Where to put focus on for Eigen-Values & Eigen-Vectors
[V,D] = Eigens(Rho,L,phi_k,EI_x,x,LocationOfFocus);

%Beam_Eq = diff(EI_x*diff(omega_xt,x,2),x,2)+Rho*x*diff(omega_xt,t,2);
% pretty(Beam_Eq)


