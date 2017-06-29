%% Main function to generate tests
function tests = joint_deflection_tests
    tests = functiontests(localfunctions);
end

%% Test Deflections Angle Greater
function testIsDeflectionAngleGreaterFalseSin(testCase)
    ss = @(x, t) sin(x);
    actSolution = is_deflection_angle_greater(50, [0, 0], [pi/2, 1], 1, ss);
    verifyFalse(testCase, actSolution);
end

function testIsDeflectionAngleGreaterFalseOnLine(testCase)
    ss = @(x, t) x;
    actSolution = is_deflection_angle_greater(50, [0, 0], [55, 55], 1, ss);
    verifyFalse(testCase, actSolution);
end

function testIsDeflectionAngleGreaterTrueOnLine(testCase)
    ss = @(x, t) x;
    actSolution = is_deflection_angle_greater(40, [0, 2], [2, 2], 1, ss);
    verifyTrue(testCase, actSolution);
end

% Set K in joint_variables to 1
% function testMeanErrorGetOneHorizHinge(testCase)
%     ss = @(x, t) sin(x);    
%     joints = discretize_posture([2*pi], 1, @mean_error, ss);
%     verifyLessThan(testCase, abs(joints - [0, 0; 2*pi,0]), 0.002);
% end

function testMeanErrorZero(testCase)
    tt = linspace(0, 2*pi, 100);
    ss = @(x, t) sin(x) + 1;
    yy = tt * 0 + 1;
    verifyLessThan(testCase, mean_error([tt(1), yy(1)], [tt(end), yy(end)], 1, ss), 0.001);
end

function testMeanErrorAreaUnderHalfOfSine(testCase)
    tt = linspace(0, pi, 100);
    ss = @(x, t) sin(x);
    yy = tt * 0;
    verifyLessThan(testCase, abs(mean_error([tt(1), yy(1)], [tt(end), yy(end)], 1, ss) - 2), 0.001);
end

function testRootMeanSquareErrorAreaUnderHalfOfSine(testCase)
    tt = linspace(0, pi, 100);
    ss = @(x, t) sin(x) + 1;
    yy = tt * 0 + 1;
    verifyLessThan(testCase, abs(root_mean_square_error([tt(1), yy(1)], [tt(end), yy(end)], 1, ss) - 2), 0.001);
end

% 
%% Discretize Posture Test Lengths
function testDiscretizePostureLengths(testCase)
    joint_points = discretize_posture([0.3, 0.3, 0.3, 0.3], 1.8, @mean_error, @get_posture);
    base = joint_points(1, :);
    for i = 2 : length(joint_points)
        disp(i)
        end_pt = joint_points(i, :);
        mag = sqrt((base(1) - end_pt(1))^2 + (base(2) - end_pt(2))^2);
        base = end_pt;
       verifyLessThan(testCase, abs(mag - 0.3), 0.0001);
    end
end

function testDiscretizePostureLengthsAll(testCase)
    for t = 0 : 0.01 : 1.4
        joint_points = discretize_posture([0.3, 0.3, 0.3, 0.3], t, @mean_error, @get_posture);
        base = joint_points(1, :);
        for i = 2 : length(joint_points)
            disp(i)
            end_pt = joint_points(i, :);
            mag = sqrt((base(1) - end_pt(1))^2 + (base(2) - end_pt(2))^2);
            base = end_pt;
           verifyLessThan(testCase, abs(mag - 0.3), 0.0001);
        end
    end
end
        
        
%% Mean Error Tests
function testMeanErrorBetterThanVertical(testCase)
    vertical = root_mean_square_error([1, 1], [1, 5], 1, @get_posture);
    diagonal = root_mean_square_error([1, 1], [1 + 4/sqrt(2), 1 + 4/sqrt(2)], 1, @get_posture);
    verifyLessThan(testCase, diagonal, vertical)
end

% PASSES WHEN GET_POSTURE IS SIN(X)
function testMeanErrorBetterThanHorizontal(testCase)
    ss = @(x, t) sin(x);
    better = root_mean_square_error([0, 0], [pi/2, 1], 1, ss);
    worse = root_mean_square_error([0, 0], [sqrt(1 + pi^2 / 4), 0], 1, ss);
    verifyLessThan(testCase, better, worse)
end

function testSquareMeanError(testCase)
    worse = root_mean_square_error([0, 0], [pi/2, 1], 1, @get_posture);
    best = root_mean_square_error([0, 0], [sqrt(1/2 + pi^2/8), sqrt(1/2 + pi^2/8)], 1, @get_posture);
    verifyLessThan(testCase, best, worse)
end

%% RMS Error Tests
function testRootMeanSquareErrorBetterThanVertical(testCase)
    vertical = root_mean_square_error([1, 1], [1, 5], 1, @get_posture);
    diagonal = root_mean_square_error([1, 1], [1 + 4/sqrt(2), 1 + 4/sqrt(2)], 1, @get_posture);
    verifyLessThan(testCase, diagonal, vertical)
end

% PASSES WHEN GET_POSTURE IS SIN(X)
function testRootMeanSquareErrorBetterThanHorizontal(testCase)
    ss = @(x, t) sin(x);
    better = root_mean_square_error([0, 0], [pi/2, 1], 1, ss);
    worse = root_mean_square_error([0, 0], [sqrt(1 + pi^2 / 4), 0], 1, ss);
    verifyLessThan(testCase, better, worse)
end

function testRootMeanSquareError(testCase)
    worse = root_mean_square_error([0, 0], [pi/2, 1], 1, @get_posture);
    best = root_mean_square_error([0, 0], [sqrt(1/2 + pi^2/8), sqrt(1/2 + pi^2/8)], 1, @get_posture);
    verifyLessThan(testCase, best, worse)
end

%% Get End Point Tests
function testGetEndPointLength(testCase)
    actSolution = norm(get_end_point([0, 0], [1, 1], sqrt(8)));
    expSolution = sqrt(8);
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointLength2(testCase)
    % size of the linkage is measured from base point not the origin
    actSolution = norm(get_end_point([4.9, -2.2], [-5.7, 0.4], 10*sqrt(7)) - [4.9, -2.2]);
    expSolution = 10 * sqrt(7);
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointLength2OtherDir(testCase)
    % size of the linkage is measured from base point not the origin
    actSolution = norm(get_end_point([-5.7, 0.4], [4.9, -2.2], 10*sqrt(7)) - [-5.7, 0.4]);
    expSolution = 10 * sqrt(7);
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPoint45(testCase)
    actSolution = get_end_point([0, 0], [1, 1], sqrt(8));
    expSolution = [2, 2];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointNeg45(testCase)
    actSolution = get_end_point([0, 0], [-1, -1], sqrt(8));
    expSolution = [-2, -2];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointSlopeZero(testCase)
    actSolution = get_end_point([3, 3], [5, 3], 4);
    expSolution = [7, 3];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointNotOrigin(testCase)
    actSolution = get_end_point([-3, 3], [13/3, 1], sqrt(130));
    expSolution = [8, 0];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointCrossIsEnd(testCase)
    actSolution = get_end_point([1, 1], [2, 2], sqrt(2));
    expSolution = [2, 2];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointVertical(testCase)
    actSolution = get_end_point([1, 1], [1, 2], 4);
    expSolution = [1, 5];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

function testGetEndPointNegVertical(testCase)
    actSolution = get_end_point([1, 1], [1, -2], 4);
    expSolution = [1, -3];
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001)
end

%% Get Distance Tests
% 3-4-5 Triangle
function testGetDistance345(testCase)
    actSolution = get_distance([0, 0], [3, 4]);
    expSolution = 5;
    verifyEqual(testCase,actSolution,expSolution)
end

% 0 distance
function testGetDistance0(testCase)
    actSolution = get_distance([1, 1], [1, 1]);
    expSolution = 0;
    verifyEqual(testCase,actSolution,expSolution)
end

% 45-45-90 Triangle
function testGetDistance45(testCase)
    actSolution = get_distance([0, 0], [2, 2]);
    expSolution = 2 * sqrt(2);
    verifyEqual(testCase,actSolution,expSolution) % assume no rounding, works
    verifyLessThan(testCase, abs(actSolution - expSolution), 0.0001) % use tolerancing, works
end