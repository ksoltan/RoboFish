function res = get_distance(A, B)
    Ax = A(1);
    Ay = A(2);
    Bx = B(1);
    By = B(2);
    res = sqrt((Bx - Ax)^2 + (By - Ay)^2);
end