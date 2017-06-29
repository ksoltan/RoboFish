function error = mean_error(base_pt, end_pt, t, posture_func)
    % SHOULD INCLUDE REFERENCE TO WHICH POSTURE
    % If the joint is vertical, return infinitely high error because
    % posture is a function, it cannot be vertical
    if(abs(base_pt(1) - end_pt(1)) < 0.001)
        error = inf;
        disp('oops');
    else
        dx = 0.005;
        x = base_pt(1) : dx : end_pt(1);
        % y = mx+b is the straight joint
        joint = (end_pt(2) - base_pt(2)) / (end_pt(1) - base_pt(1)) .* (x - base_pt(1)) + base_pt(2);
        posture = posture_func(x, t);
        
%         figure;
%         plot(x, joint, 'r')
%         hold on
%         plot(x, posture, 'b')
        
        error = 0;
        for i = 1 : length(x)
           error = error + (joint(i) - posture(i))*dx;
        end
    end
    error = abs(error);
%     disp(error)
end