function pt = get_end_point(base_pt, cross_pt, length_j)
    % IF THE BASE_PT = CROSS_PT, WILL FAIL. DIVIDE BY ZERO. SHOULD INCLUDE
    % EXCEPTION
    % base pt and cross pt make a line.
    base_x = base_pt(1);
    base_y = base_pt(2);
    cross_x = cross_pt(1);
    cross_y = cross_pt(2);
    
    % If vertical line:
    if(abs(base_x - cross_x) < 0.0001)
        pt = [0, length_j];
        % If cross is below base, subtract length. Otherwise, add it
        if(cross_y < base_y)
            pt = base_pt - pt;
        else
            pt = base_pt + pt;
        end
        
    else
        % slope
        m = (cross_y - base_y) / (cross_x - base_x);
        % angle for polar coords
        theta = atan(m);
        % x = r*cos(theta)  y = r*sin(theta)
        % Cross point must be between end and base points. Therefore, if it is
        % in the negative direction, must flip the end_pt.
        pt = length_j * [cos(theta), sin(theta)];
        if(cross_x < base_x)
            pt = -pt;
        end
        pt = pt + base_pt; % pt was calculated as if from origin, now shift to base_pt
    end
end