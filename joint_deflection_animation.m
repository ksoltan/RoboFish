function joint_deflection_animation()
% The tail function Ft(x, t) defines the position of each point along the
% tail at any point in time.
% To discretize: the tail function is broken up into i = 0...M postures.
% j = 0...K joints in the tail
% Base point is start of linkage, cross point wher eit intersects tail func
% End point is end of linkage and the base point of the next linkage
% Base point of 0th linkage is 0
%% Courtesy of Image Analyst https://www.mathworks.com/matlabcentral/answers/154659-how-to-create-animation-of-matlab-plotting-points-on-a-graph
% Clear space
clear all;
clc;
% Length and resolution of animation
time = 0 : 0.007: 2;
hFigure = figure;
numberOfFrames = length(time);

saveMovie = true;% Set to true if you want to save an avi file. Don't forget to change name of file
movie_file_name = 'tail_with_quiver.avi';

% Set up the movie structure.
% Preallocate recalledMovie, which will be an array of structures.
% First get a cell array with all the frames.
allTheFrames = cell(numberOfFrames,1);
vidHeight = 344;
vidWidth = 446;
allTheFrames(:) = {zeros(vidHeight, vidWidth, 3, 'uint8')};
% Next get a cell array with all the colormaps.
allTheColorMaps = cell(numberOfFrames,1);
allTheColorMaps(:) = {zeros(256, 2)};
% Now combine these to make the array of structures.
myMovie = struct('cdata', allTheFrames, 'colormap', allTheColorMaps);
if(saveMovie)
    % Create a VideoWriter object to write the video out to a new, different file.
    writerObj = VideoWriter(movie_file_name);
    open(writerObj);
end

% Need to change from the default renderer to zbuffer to get it to work right.
% openGL doesn't work and Painters is way too slow.
set(gcf, 'renderer', 'zbuffer');
	
for frameIndex = 1 : numberOfFrames
	t = time(frameIndex);
	joint_points = discretize_posture([6.28, 4.796, 4.28, 7.219], t, @mean_error, @get_posture);
%     joint_points2 = discretize_posture([6.28, 4.796, 4.28, 7.219], t, @root_mean_square_error, @get_posture);
    xs = 0 : 0.001 : 20;
    cla reset;
	% Enlarge figure to full screen.
% 	set(gcf, 'Units', 'Normalized', 'Outerposition', [0, 0, 1, 1]);
    hold on;
    plot(xs, get_posture(xs, t), 'b')
    
    % Plot normal lines along motion function, from 
    % https://stackoverflow.com/questions/17324936/how-to-find-the-normal-vector-at-a-point-on-a-curve-in-matlab
    x = 0 : 3 : 20;
    y = get_posture(x, t);
    dy = gradient(y);
    dx = gradient(x);
    quiver(x, y, -dy, dx);

    %Plot normal line for each joint
    for joint = 1 : length(joint_points) - 1
        num_points = 11;
        xj = linspace(joint_points(joint, 1), joint_points(joint + 1, 1), num_points);
        yj = linspace(joint_points(joint, 2), joint_points(joint + 1, 2), num_points);
        dyj = 4*gradient(yj);
        dxj = 4*gradient(xj);
        middle_vec_idx = round(num_points / 2); % Only display the middle normal vector
        quiver(xj(middle_vec_idx), yj(middle_vec_idx), -dyj(middle_vec_idx), dxj(middle_vec_idx), 'r', 'LineWidth', 2, 'MaxHeadSize', 1);
    end
    plot(joint_points(:, 1), joint_points(:, 2), 'r*-');
    
%     plot(joint_points2(:, 1), joint_points2(:, 2), 'g*-');
    axis([0, 40, -20, 20])
	caption = sprintf('Frame #%d of %d, t = %.1f', frameIndex, numberOfFrames, time(frameIndex));
	title(caption, 'FontSize', 15);
	drawnow;
	thisFrame = getframe(gca);
	% Write this frame out to a new video file.
    if(saveMovie)
     	writeVideo(writerObj, thisFrame);
    end
	myMovie(frameIndex) = thisFrame;
end

if(saveMovie)
    close(writerObj);
end

message = sprintf('Done creating movie\nDo you want to play it?');
button = questdlg(message, 'Continue?', 'Yes', 'No', 'Yes');
drawnow;	% Refresh screen to get rid of dialog box remnants.
close(hFigure);
if strcmpi(button, 'No')
   return;
end
hFigure = figure;
% Enlarge figure to full screen.
% set(gcf, 'Units', 'Normalized', 'Outerposition', [0, 0, 1, 1]);
title('Playing the movie we created', 'FontSize', 15);
% Get rid of extra set of axes that it makes for some reason.
axis off;
% Play the movie.
movie(myMovie);
uiwait(helpdlg('Done with demo!')); 
close(hFigure);

end