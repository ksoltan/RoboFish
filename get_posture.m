function y = get_posture(x, t)
    c1 = 0.1; % Amplitude of oscillation. The highe c1 is, the more wide the sweep is of the function
    c2 = 0; % When not 0, introduces quadratic term. Motion is more steep and tightly curved
    k = 0.05; % Frequency of oscillation. The higher k is, the more zig-zaggy the motion is
    omega = 20; % Speed of oscillation. The higher omega is, the faster the body moves
    y = (c1 .* x + c2 .* x.^2) .* sin(k .* x + omega .* t) - c1 .* x .* sin(omega .* t);
end