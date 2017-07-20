% Get angle between two points that define a vector.
% Angle defined with respect to +x axis. Angles from -180 < theta < 180
function angle = get_angle(pt1, pt2)
    pt1_x = pt1(1);
    pt1_y = pt1(2);
    pt2_x = pt2(1);
    pt2_y = pt2(2);
    angle = atan2d((pt2_y - pt1_y),(pt2_x - pt1_x)); % atan2d returns -180 < theta < 180 and takes care of vertical alignment
end