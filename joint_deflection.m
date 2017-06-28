function joint_deflection()
% The tail function Ft(x, t) defines the position of each point along the
% tail at any point in time.
% To discretize: the tail function is broken up into i = 0...M postures.
% j = 0...K joints in the tail
% Base point is start of linkage, cross point wher eit intersects tail func
% End point is end of linkage and the base point of the next linkage
% Base point of 0th linkage is 0
%% 
    figure()
    hold on
%     xs = 0 : 0.01 : 0.8;
    for t = 0 : 0.2: 1
%         plot(xs, get_posture(xs, t))
        joint_points = discretize_posture([0.3, 0.3, 0.3, 0.3], t)
        plot(joint_points(:, 1), joint_points(:, 2), 'r*-');
        xs = 0 : 0.001 : joint_points(end, 1)
        plot(xs, get_posture(xs, t), 'b');
    end
end