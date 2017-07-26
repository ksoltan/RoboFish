% Because discretize posture only does one posture at a time,
% get_all_deflection_angles returns the angles for a set of joint_points
% for a posture.
function all_angles = get_all_deflection_angles(joint_points)
    % If there are 4 joints, there are 3 intersection points. Because joint
    % points is 5 points, number of intersection points is
    % len(joint_points) - 2
    all_angles = zeros(1, length(joint_points) - 2);
    for j = 2 : length(joint_points) - 1
        all_angles(j - 1) = get_deflection_angle(joint_points(j - 1, :), joint_points(j, :), joint_points(j + 1, :));
    end
end