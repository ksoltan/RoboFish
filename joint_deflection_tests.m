%% Main function to generate tests
function tests = joint_deflection_tests
    tests = functiontests(localfunctions);
end

%% RMS Error Tests
function testRootMeanSquareErrorBetterThanVertical(testCase)
    vertical = root_mean_square_error([1, 1], [1, 5], 1);
    diagonal = root_mean_square_error([1, 1], [1 + 4/sqrt(2), 1 + 4/sqrt(2)], 1);
    verifyLessThan(testCase, diagonal, vertical)
end

% PASSES WHEN GET_POSTURE IS SIN(X)
function testRootMeanSquareErrorBetterThanHorizontal(testCase)
    better = root_mean_square_error([0, 0], [pi/2, 1], 1);
    worse = root_mean_square_error([0, 0], [sqrt(1 + pi^2 / 4), 0], 1);
    verifyLessThan(testCase, better, worse)
end

function testRootMeanSquareError(testCase)
    worse = root_mean_square_error([0, 0], [pi/2, 1], 1);
    best = root_mean_square_error([0, 0], [sqrt(1/2 + pi^2/8), sqrt(1/2 + pi^2/8)], 1);
    verifyLessThan(testCase, best, worse)
end

%% Get End Point Tests
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