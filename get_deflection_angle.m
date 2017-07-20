% Angle is in degrees
% Get deflection of joint relative to previous joint. Angle is defined
% with respect to the line of the previous joint.
function res = get_deflection_angle(prev_base_pt, base_pt, cross_pt)
    prev_joint_angle = get_angle(prev_base_pt, base_pt); % Base_pt is the same as prev_end_pt
    joint_angle = get_angle(base_pt, cross_pt);
    res = joint_angle - prev_joint_angle;
end