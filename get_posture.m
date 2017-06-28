function y = get_posture(x, t)
    % SHOULD INCLUDE WAY TO CHOOSE WHICH POSTURE
    y = sin(x);
    c1 = 0.45;
    c2 = 0;
    k = 5;
    omega = 3;
    y = (c1 .* x + c2 .* x.^2).*sin(k .* x + omega .* t) - c1 .* x .* sin(omega .* t);
end