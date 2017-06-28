function joint_points = discretize_posture(joint_lengths, t)
% Given a posture (a time and the tail function) and the lengths of joints, 
% return a list of points that define the base and end points of the joints
% SHOULD INCLUDE REFERENCE TO WHICH POSTURE IT WANTS
    

%% May need to take this out if calling in joint_deflection and it also initializes globals
joint_variables; % Initialize global variables

%%
joint_points = zeros(K + 1, 2); % K joints, K end points + 1 base point (0, 0)

j = 1; % Current joint
base_pt = [0, 0];
error = inf;
end_pt_best = [0, 0];
while j <= K % Loop through every joint. Could write this recursively
    length_j = joint_lengths(j);
    x_cross = base_pt(1);
    y_cross = get_posture(x_cross, t);
    while get_distance(base_pt, [x_cross, y_cross]) <= length_j
       % for each possible cross point, calculate the end point
       end_pt = get_end_point(base_pt, [x_cross, y_cross], length_j);
       % determine the error that this end point produces. If it is less
       % than the previous one, save this as best end pt
       error_pt = root_mean_square_error(base_pt, end_pt, t);
       if(error_pt < error)
           end_pt_best = end_pt; 
       end
       % Increment x_cross and update y_cross to get next cross point
       x_cross = x_cross + 0.01;
       y_cross = get_posture(x_cross, t);
    end
    % Add the best end_pt to the list of points and set it as the base pt.
    joint_points(j + 1, :) = end_pt_best;
    base_pt = end_pt_best;
    j = j + 1;
end
% Plot the approximation and curve
% figure
% hold on
% plot(joint_points(:, 1), joint_points(:, 2), 'r*-');
% xs = 0 : 0.001 : joint_points(end, 1);
% plot(xs, get_posture(xs, t), 'b');

end