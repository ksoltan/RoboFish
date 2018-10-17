% /*
%    Function: get_angle
% 
%    Calculates angle of vector defined by two points with respect to the
%    +x axis.
% 
%    Parameters:
% 
%        pt1 - Coordinates defining initial point of vector
%        pt2 - Coordinates defining terminal point of vector
% 
%    Returns:
% 
%       Angle between vector defined by pt1 and pt2 from horizontal.
%       -180 < theta < 180
% 
%    See Also:
% 
%       <atan2d>
% */
function angle = get_angle(pt1, pt2)
    pt1_x = pt1(1);
    pt1_y = pt1(2);
    pt2_x = pt2(1);
    pt2_y = pt2(2);
    angle = atan2d((pt2_y - pt1_y),(pt2_x - pt1_x)); % atan2d returns -180 < theta < 180 and takes care of vertical alignment
end