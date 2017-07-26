% Angle is in degrees
% Get deflection of joint relative to previous joint. Angle is defined
% with respect to the line of the previous joint.
% Relative angles salculated wrt +x axis, so if joint at (-2, 2), will
% assume rotation from 1st to 2nd quadrant instead of from 1st to 4th to
% 3rd to 2nd.
function res = get_deflection_angle(prev_base_pt, base_pt, cross_pt)
    prev_joint_angle = get_angle(prev_base_pt, base_pt); % Base_pt is the same as prev_end_pt
    joint_angle = get_angle(base_pt, cross_pt);
    res = joint_angle - prev_joint_angle;
end