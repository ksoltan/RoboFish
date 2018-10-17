% /*
%    Function: get_deflection_angle
% 
%    Calculates angle of vector defined by two points with respect to the
%    +x axis.
% 
%    Parameters:
% 
%      prev_base_pt - Coordinates of initial point of previous joint
%           base_pt - Coordinates of initial point of current joint,
%                     also the terminal point of previous joint
%          cross_pt - Coordinates of terminal point of current joint that
%                     defines its vector.
% 
%    Returns:
% 
%       Angle in degrees between two joints, defined with respect to the
%       line of the previous (preceeding) joint.
%       Relative angles calculated wrt +x axis, so if joint at (-2, 2), will
%       assume rotation from 1st to 2nd quadrant instead of from 1st to 4th
%       to 3rd to 2nd.
% 
%    See Also:
% 
%       <atan2d>
% */
function res = get_deflection_angle(prev_base_pt, base_pt, cross_pt)
    prev_joint_angle = get_angle(prev_base_pt, base_pt); % Base_pt is the same as prev_end_pt
    joint_angle = get_angle(base_pt, cross_pt);
    res = joint_angle - prev_joint_angle;
end