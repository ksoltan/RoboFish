function angle = get_angle(pt1, pt2)
    pt1_x = pt1(1);
    pt1_y = pt1(2);
    pt2_x = pt2(1);
    pt2_y = pt2(2);
    if(abs(pt1_x - pt2_x) < 0.001)
       angle = 90; % vertical joint 
    else
        angle = atand((pt2_y - pt1_y)/(pt2_x - pt1_x));
        % Care about the angle from the horizontal in +x direction
        if(pt2_x <= pt1_x) %
            if(pt2_y < pt1_y)
                angle = -angle;
            else
                angle = 180 - angle;
            end
        end
    end
end