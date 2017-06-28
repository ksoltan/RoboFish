function error = root_mean_square_error(base_pt, end_pt)
    % SHOULD INCLUDE REFERENCE TO WHICH POSTURE
    % If the joint is vertical, return infinitely high error because
    % posture is a function, it cannot be vertical
    if(abs(base_pt(1) - end_pt(1)) < 0.001)
        error = inf; 
    else
        x = base_pt(1) : 0.01 : end_pt(1);
        % y = mx+b is the straight joint
        joint = (end_pt(2) - base_pt(2)) / (end_pt(1) - base_pt(1)) .* (x - base_pt(1)) + base_pt(2);
        posture = get_posture(x);

        error = 0;
        for i = 1 : length(x)
           error = error + sqrt((joint(i) - posture(i))^2); 
        end
    end
    disp(error)
end