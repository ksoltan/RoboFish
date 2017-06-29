function joint_deflection()
% The tail function Ft(x, t) defines the position of each point along the
% tail at any point in time.
% To discretize: the tail function is broken up into i = 0...M postures.
% j = 0...K joints in the tail
% Base point is start of linkage, cross point wher eit intersects tail func
% End point is end of linkage and the base point of the next linkage
% Base point of 0th linkage is 0
    figure;
    hold on;
    axis([0, 1, -0.8, 0.8])
    joint_variables;
    joint_angles = zeros(K, 1);
    
    for t = 0 : 0.01 : 1.4
        joint_points = discretize_posture([0.05, 0.05, 0.05, 0.05], t, @mean_error, @get_posture);
        base = joint_points(1, :);
        for i = 2 : length(joint_points)
            end_pt = joint_points(i, :);
            angle = get_angle(base, end_pt);
            if(angle > joint_angles(i - 1))
               joint_angles(i - 1) = angle; 
            end
            base = end_pt;
        end
        xs = 0 : 0.001 : joint_points(end, 1);
        plot(xs, get_posture(xs, t), 'b')
        plot(joint_points(:, 1), joint_points(:, 2), 'r*-');
    end
    disp(joint_angles)
end