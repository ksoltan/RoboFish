% The tail function Ft(x, t) defines the position of each point along the
% tail at any point in time.
% To discretize: the tail function is broken up into i = 0...M postures.
% j = 0...K joints in the tail
% Base point is start of linkage, cross point where it intersects tail func
% End point is end of linkage and the base point of the next linkage
% Base point of 0th linkage is 0
M = 2;
i = 0 : 1 : M;
K = 4;
j = 0 : 1 : K;