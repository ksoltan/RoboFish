function y = get_posture(x, t)
    c1 = 0.2;
    c2 = 0;
    k = 0.4;
    omega = 20;
    y = (c1 .* x + c2 .* x.^2) .* sin(k .* x + omega .* t) - c1 .* x .* sin(omega .* t);
end