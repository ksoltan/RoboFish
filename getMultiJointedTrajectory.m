% /*
%    Function: getMultiJointedTrajectory
% 
%    Process a video of a multi-jointed fish with blue markers at each
%    joint.
% 
%    Parameters:
% 
%
%    Returns:
% 
%       Graph of angular displacement. Some velocity graphs..?
% 
%    See Also:
% 
%       <createBlueMarkerMask>
% */
function getMultiJointedTrajectory()
    NUM_MARKERS = 5;
    SAVE_MOVIE = false;
%     getDirectoryPlots()
    getFilePlot();
        %% Select folder of .avi video files to create angular displacement plots of.
    function getDirectoryPlots()
        myDir = uigetdir; %gets directory
        myDir_split = strsplit(myDir, '\');
        baseDir = myDir_split{end};
        myFiles = dir(fullfile(myDir,'*.avi')); %gets all avi files in struct
        for k = 1:length(myFiles)
            try
                baseFileName = myFiles(k).name;
%                 fullFileName = fullfile(myDir, baseFileName);
                getTrajectory(baseFileName, myDir)
            catch
                warning('Could not read %s\n', baseFileName);
            end
        end
    end
    
    %% Select single .avi video file to create angular displacement plot of.
    function getFilePlot()
        [myFile, myDir] = uigetfile({'*.avi'}); %gets file
        getTrajectory(myFile, myDir)
    end


    function res = getSinusoidFit(X, Y)
        % Compute fft on the angular deflection data (ydata)
        yfft = fft(Y);
%         m = abs(yfft); % Magnitude
%         p = unwrap(angle(yfft)); % Phase
        % Get maximum peak frequency in spectrum
        f = (0:length(yfft)-1)*29.97/length(yfft);
        half_len = length(f) / 2;
        [M, I] = max(abs(yfft(1 : half_len)));
        res.freq = f(I);
        
        figure(3)
        clf;
        % Get the amplitude by averaging peaks in the data
        [pks,locs] = findpeaks(Y, 'MinPeakDistance', 10); % Don't know why 10 works, but picks out only the top peaks nicely
        hold on
        plot(X(locs),pks,'or')
        axis tight

        res.phase = angle(yfft(I));
        res.amplitude = mean(abs(pks));
        plot(X, res.amplitude .* cos(res.freq * 2 * pi .* X + res.phase), 'm')
        
    end

    function getTrajectory(myFile, myDir)
        fprintf(1, 'Now reading %s\n', strcat(myDir, '/', myFile));
        if(SAVE_MOVIE)
            getCentroidMovie(strcat(myDir, '/', myFile));    
        else
            mCentroids = getAllCentroidData(strcat(myDir, '/', myFile));
    %         angles = getAngularDisplacement(mCentroids);
    %         makeAngularDisplacementPlot(angles, mCentroids.time);
    %         saveFigure(myFile, myDir, 1)
%             vel = getVelocity(mCentroids);
%             avg_speed = vel.avg_speed
%             avg_speed_BL = vel.avg_speed_BL
%             avg_angle = vel.avg_angle
            makeVelocityPlot(mCentroids);
        end
    end

    %% Reads video frames and generates list of centroids of base and tip at all points in time.
    function getCentroidMovie(filename)
        v = VideoReader(filename);
        i = 1;
        clf;
        % Create a VideoWriter object to write the video out to a new, different file.
        movie_file_name = strcat(filename(1:end-4), '_centroids.avi');
        writerObj = VideoWriter(movie_file_name);
        open(writerObj);
        
        while hasFrame(v)
            vidFrame = readFrame(v);
            try
                % Assume head is left of tail (swimming from right to left)
                getMarkerCentroids(vidFrame);
                thisFrame = getframe(gcf);
                % Write this frame out to a new video file.
                writeVideo(writerObj, thisFrame);
            catch
                warning('Could not get centroid.') % RGB mask does not deal well with light glare.
            end
            i = i + 1;
        end
        close(writerObj);
    end
    
    function makeVelocityPlot(centroids)
        velocity = getIncrementalVelocity(centroids);
        time = centroids.time;
        figure(1);
        clf;
        hold on
        plot(time, velocity.j2, 'r.-');
        figure(2)
        plot(time, velocity.avg);
        disp(sum(velocity.j2) / length(velocity.j2))
        disp(max(velocity.j2))
    end
   %% Saves angular displacement vs time plot with appropriate name to Trajectories/ file.
    % Angle is relative to vertical axis through centroid of red base
    % marker at each point in the video.
    function makeAngularDisplacementPlot(angles, time)
        % Center angles around 0. Subtract out mean, which averages data
        % points (filters out outliers if enough data points).
        meanA = mean(angles);
        angles = angles - meanA;
        figure(1);
        clf;
        hold on
        plot(time, angles(:, 1), 'b.-');
        plot(time, angles(:, 2), 'm.-');
        plot(time, angles(:, 3), 'r.-');
%         params = getTestParameters(filename);
%         title(sprintf('Angular Displacement over Time of Single Joint\n %d%% Duty Cycle, %d%% Deadzone, %dHz Frequency', params.duty, params.deadzone, params.freq))
        xlabel('Time (s)')
        ylabel('Angular Displacement (deg)')
    end

    %% Saves specific figure to given filename in Trajectories/ folder as a .fig.
    function saveFigure(filename, directory, fig_num)
        deliminator_pos = strfind(filename, '.');
        if isempty(deliminator_pos)
            error('ArgError:NoDot', 'Check your filename. It does not have an extension.');
        end
        fig_filename = filename(1 : deliminator_pos(1) - 1); % Name before first dot
        new_file_name = strcat(directory, '/Graphs/', fig_filename, '.fig');
        saveas(fig_num, new_file_name);
    end


    function angles = getAngularDisplacement(allCentroids)
        nose_centroids = allCentroids.nose;
        j1_centroids = allCentroids.j1;
        j2_centroids = allCentroids.j2;
        j3_centroids = allCentroids.j3;
        tail_centroids = allCentroids.tail;
        angles = zeros(length(tail_centroids), 3); % We have 3 joints Each column reps one joint.
        for i = 1 : length(tail_centroids)
           angles(i, 1) = get_deflection_angle(nose_centroids(i, :), j1_centroids(i, :), j2_centroids(i, :));
           angles(i, 2) = get_deflection_angle(j1_centroids(i, :), j2_centroids(i, :), j3_centroids(i, :));
           angles(i, 3) = get_deflection_angle(j2_centroids(i, :), j3_centroids(i, :), tail_centroids(i, :));
        end
    end

   function velocity = getIncrementalVelocity(allCentroids)
        nose_centroids = allCentroids.nose;
        j1_centroids = allCentroids.j1;
        j2_centroids = allCentroids.j2;
        j3_centroids = allCentroids.j3;
        tail_centroids = allCentroids.tail;
        dt = (allCentroids.time(end) - allCentroids.time(1)) / length(allCentroids.time);
        v = zeros(length(tail_centroids), 6);
        nose_starting_pos = nose_centroids(1);
        j1_starting_pos = j1_centroids(1);
        j2_starting_pos = j2_centroids(1);
        j3_starting_pos = j3_centroids(1);
        tail_starting_pos = tail_centroids(1);
        j1_to_j2_length_screen = norm(j2_starting_pos - j1_starting_pos);
        j1_to_j2_length_actual = 26; % mm
        full_length = 106.1754 + 17; %mm
        screen_length = full_length * j1_to_j2_length_screen / j1_to_j2_length_actual;
        for i = 2 : length(tail_centroids)
           nose_new_pos = nose_centroids(i);
           j1_new_pos = j1_centroids(i);
           j2_new_pos = j2_centroids(i);
           j3_new_pos = j3_centroids(i);
           tail_new_pos = tail_centroids(i);
           nose_vel = norm(nose_new_pos - nose_starting_pos) / dt;
           j1_vel = norm(j1_new_pos - j1_starting_pos) / dt;
           j2_vel = norm(j2_new_pos - j2_starting_pos) / dt;
           j3_vel = norm(j3_new_pos - j3_starting_pos) / dt;
           tail_vel = norm(tail_new_pos - tail_starting_pos) / dt;
           avg_vel = (j1_vel + j2_vel + j3_vel) / 5;
           v(i,:) = [nose_vel, j1_vel, j2_vel, j3_vel, tail_vel, avg_vel];
           
           nose_starting_pos = nose_new_pos;
           j1_starting_pos = j1_new_pos;
           j2_starting_pos = j2_new_pos;
           j3_starting_pos = j3_new_pos;
           tail_starting_pos = tail_new_pos;
        end
        ratio = 1 / screen_length;
        velocity.nose = v(:, 1) * ratio;
        velocity.j1 = v(:, 2) * ratio;
        velocity.j2 = v(:, 3) * ratio;
        velocity.j3 = v(:, 4) * ratio;
        velocity.tail = v(:, 5) * ratio;
        velocity.avg = v(:, 6) * ratio;
    end

    function velocity = getVelocity(centroids)
       % Assuming that if I average the final - start positions of each
       % joint and divide by time, I should get velocity.
       BL_screen = norm(centroids.nose(1, :) - centroids.tail(1, :));
%        j1_to_j2_length_actual = 26; % mm
       ratio = 1 / BL_screen;
       d_nose = centroids.nose(end, :) - centroids.nose(1, :);
       d_j1 = centroids.j1(end, :) - centroids.j1(1, :);
       d_j2 = centroids.j2(end, :) - centroids.j2(1, :);
       d_j3 = centroids.j3(end, :) - centroids.j3(1, :);
       d_tail = centroids.tail(end, :) - centroids.tail(1, :);
       t = centroids.time(end) - centroids.time(1);
       nose_speed = norm(d_nose) / t;
       j1_speed = norm(d_j1) / t;
       j2_speed = norm(d_j2) / t;
       j3_speed = norm(d_j3) / t;
       tail_speed = norm(d_tail) / t;
       velocity.nose_speed = nose_speed;
       velocity.j1_speed = j1_speed;
       velocity.j2_speed = j2_speed;
       velocity.j3_speed = j3_speed;
       velocity.tail_speed = tail_speed;
       
       velocity.nose_angle = get_angle(centroids.nose(end, :), centroids.nose(1, :));
       velocity.j1_angle = get_angle(centroids.j1(end, :), centroids.j1(1, :));
       velocity.j2_angle = get_angle(centroids.j2(end, :), centroids.j2(1, :));
       velocity.j3_angle = get_angle(centroids.j3(end, :), centroids.j3(1, :));
       velocity.tail_angle = get_angle(centroids.tail(end, :), centroids.tail(1, :));
       
       velocity.avg_speed = (nose_speed + j1_speed + j2_speed + j3_speed + tail_speed) / 5;
       velocity.avg_speed_BL = velocity.avg_speed * ratio;
       velocity.avg_angle = (velocity.nose_angle + velocity.j1_angle + velocity.j2_angle + velocity.j3_angle + velocity.tail_angle) / 5;
    end

    %% Reads video frames and generates list of centroids of base and tip at all points in time.
    function centroids = getAllCentroidData(filename)
        v = VideoReader(filename);
        nose_centroids = [];
        j1_centroids = [];
        j2_centroids = [];
        j3_centroids = [];
        tail_centroids = [];
        time = [];
        i = 1;
        idx = 1;
        frameRate = v.FrameRate;
        while hasFrame(v)
            vidFrame = readFrame(v);
            try
                % Assume head is left of tail (swimming from right to left)
                markerCentroids = getMarkerCentroids(vidFrame);
                nose_centroids(idx, :) = markerCentroids(:, 1);
                j1_centroids(idx, :) = markerCentroids(:, 2);
                j2_centroids(idx, :) = markerCentroids(:, 3);
                j3_centroids(idx, :) = markerCentroids(:, 4);
                tail_centroids(idx, :) = markerCentroids(:, 5);
                time(idx) = i / frameRate;
                idx = idx + 1;
            catch
                warning('Could not get centroid.') % RGB mask does not deal well with light glare.
            end
            i = i + 1;
        end
        centroids.nose = nose_centroids;
        centroids.j1 = j1_centroids;
        centroids.j2 = j2_centroids;
        centroids.j3 = j3_centroids;
        centroids.tail = tail_centroids;
        centroids.time = time;
    end
    
    % Calculate all blobs areas and centroids. Filter out the markers by area. They
    % will be hopefully be clearly larger than the other snippets of
    % color the mask doesn't filter out.
    function markerCentroids = getMarkerCentroids(originalImage)
        blobMeasurements = getBlobMeasurements(originalImage);
        markerCentroids = zeros(2, NUM_MARKERS);
        allBlobAreas = [blobMeasurements.Area];
        sortedBlobAreas = sort(allBlobAreas,'descend');
        jointBlobAreas = sortedBlobAreas(1 : NUM_MARKERS);
        jointBlobIdxs = sort(arrayfun(@(x)find(allBlobAreas==x,1),jointBlobAreas));
        
        allBlobCentroids = [blobMeasurements.Centroid];
        centroidsX = allBlobCentroids(1:2:end-1);
        centroidsY = allBlobCentroids(2:2:end);
        numCentroid = 1;
        
        
        for k = jointBlobIdxs
            if(SAVE_MOVIE)
                hold on
                plot(centroidsX(k), centroidsY(k), 'bx', 'MarkerSize', 10, 'LineWidth', 2);   
                hold off
            end
            
            markerCentroids(:, numCentroid) = [centroidsX(k), centroidsY(k)];
            numCentroid = numCentroid + 1;
        end
%         pause()
    end

    function blobMeasurements = getBlobMeasurements(originalImage)
        % Isolate all blue markers.
        [BW,maskedRGBImage] = createBlueMarkerMask(originalImage);
        % Do a "hole fill" to get rid of any background pixels or "holes" inside the blobs.
        binaryImage = imfill(BW, 'holes');
        figure(1)
        clf;
%         imshow(binaryImage);
        % Label each blob, 8-connectivity means pixels connected in all 8
        % dirs are part of same blob.
        labeledImage = bwlabel(binaryImage, 8);
        blobMeasurements = regionprops(labeledImage, binaryImage, 'Area', 'Centroid');
    end
    
end