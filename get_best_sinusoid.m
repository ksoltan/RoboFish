% Get the best sinusoid function for a set of linkage lengths
    joint_variables;
    all_ks = 1 : 0.5 : 10;
    all_omegas = 1 : 0.5 : 10;

    max_joint_angles = zeros(length(all_ks), length(all_omegas));
    lengths = [0.5, 0.5, 0.5, 0.5];
    
    
    for idx_k = 1 : length(all_ks)
        for idx_omega = 1 : length(all_omegas)
            for t = 0 : 0.01 : 1
%                 c1 = 0.2;
%                 c2 = 0.1;
                k = all_ks(idx_k);
                omega = all_omegas(idx_omega);
                c1 = 0.2;
                c2 = 0.1;
                posture_func = @(x, t) (c1 .* x + c2 .* x.^2).*sin(k .* x + omega .* t) - c1 .* x .* sin(omega .* t);
                
                joint_points = discretize_posture(lengths, t, @mean_error, posture_func);
                base = joint_points(1, :);
                max_angle = -inf;
                for i = 2 : length(joint_points)
                    end_pt = joint_points(i, :);
                    angle = get_angle(base, end_pt);
                    if(angle > max_angle)
                       max_angle = angle;
                    end
                    base = end_pt;
                end
                max_joint_angles(idx_k, idx_omega) = max_angle;
            end
        end
    end
%         
    figure;
%     % plot the height of the ball as a function of angle and speed
    pcolor(all_omegas, all_ks, max_joint_angles);
    hold on
%     % Plot line to show where the ball ends up close to the 12 m height is 
%     %(the wall) and 1 m, close to the ground
    clabel(contour(all_omegas, all_ks, max_joint_angles, [40, 15], 'LineColor', 'w', 'LineWidth', 1))
    xlabel('Omega', 'FontName', 'Times', 'FontSize', 20);
    ylabel('K', 'FontName', 'Times', 'FontSize', 20);
    title_str = ['Maximum Angular Deflection of Equal Length Hinges (0.5) Over Time When Approximating Trajectory Defined by K, Omega, C1 = ', num2str(c1) ,', and C2 = ', num2str(c2)];
    title(title_str, 'FontName', 'Times', 'FontSize', 18)