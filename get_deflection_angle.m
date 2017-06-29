% Angle is in degrees
function res = get_deflection_angle(base_pt, cross_pt, t, posture_func)
    % Estimate instantaneous slope at cross pt in posture func
    cross_x = cross_pt(1);
    cross_y = cross_pt(2);
    pt_x = cross_x + 0.01;
    pt_y = posture_func(pt_x, t);
    
    % Can use slopes to calculate
%     inst_slope = (cross_y - pt_y) / (cross_x - pt_x);
%     joint_slope = (cross_y - base_pt(2)) / (cross_x - base_pt(1));
%     
%     res = abs(atand(inst_slope) - atand(joint_slope));
    res = abs(get_angle(cross_pt, [pt_x, pt_y]) - get_angle(base_pt, cross_pt));
end