%% Creates an angular displacement plot vs time of single joint from .avi video.
% Red base and yellow tip marker centroids are filtered and tracked to
% generate trajectory. Anglular displacement is relative to vertical line
% through red base marker centroid.
function getJointTrajectory()
    getFilePlot();
    
    %% Select single .avi video file to create angular displacement plot of.
    function getFilePlot()
        [myFile, myDir] = uigetfile({'*.avi'}); %gets file
        myDir_split = strsplit(myDir, '\');
        baseDir = myDir_split{end - 1};
        fprintf(1, 'Now reading %s\n', strcat(myDir, '/', myFile));
        makeAngularDisplacementPlot(strcat(myDir, '/', myFile));
    end
    
    %% Select folder of .avi video files to create angular displacement plots of.
    function getDirectoryPlots()
        myDir = uigetdir; %gets directory
        myDir_split = strsplit(myDir, '\');
        baseDir = myDir_split{end};
        myFiles = dir(fullfile(myDir,'*.avi')); %gets all avi files in struct
        for k = 1:length(myFiles)
            try
                baseFileName = myFiles(k).name;
                fullFileName = fullfile(myDir, baseFileName);
                fprintf(1, 'Now reading %s\n', fullFileName);
                makeAngularDisplacementPlot(strcat(baseDir, '/', baseFileName));
            catch
                warning('Could not read %s\n', baseFileName);
            end
        end
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
    
    %% Saves angular displacement vs time plot with appropriate name to Trajectories/ file.
    % Angle is relative to vertical axis through centroid of red base
    % marker at each point in the video.
    function makeAngularDisplacementPlot(filename)
        centroid_data = getAllCentroidData(filename);
        angles = atand((centroid_data.tip(:, 1) - centroid_data.base(:, 1)) ./ (centroid_data.base(:, 2) - centroid_data.tip(:, 2)));
        % Center angles around 0. Subtract out mean, which averages data
        % points (filters out outliers if enough data points).
        meanA = mean(angles);
        angles = angles - meanA;
        figure(1);
        clf;
        plot(centroid_data.time, angles, '.-');
        params = getTestParameters(filename);
        title(sprintf('Angular Displacement over Time of Single Joint\n %d%% Duty Cycle, %d%% Deadzone, %dHz Frequency', params.duty, params.deadzone, params.freq))
        xlim([1, floor(centroid_data.time(end))])
        xlabel('Time (s)')
        ylabel('Angular Displacement (deg)')
%         saveFigure(filename, 1)
    end

    %% Parses file name to extract settings for duty cycle, deadzone, and frequency.
    function res = getTestParameters(filename)
        s = strsplit(filename, '/');
        res.duty = str2double(s{2}(1:2));
        res.deadzone = str2double(s{2}(5:6));
        res.freq = str2double(s{2}(10));
    end

    %% Deconstructs filename into name and extension
    function res = decomposeFilename(filename)
        s = strsplit(filename, '/');
        actual_filename = s{2};
        deliminator_pos = strfind(actual_filename, '.');
        if isempty(deliminator_pos)
            error('ArgError:NoDot', 'Check your filename. It does not have an extension.');
        end
        res.name = actual_filename(1 : deliminator_pos(1) - 1); % Name before first dot
        res.extension = actual_filename(deliminator_pos(end) : end); % Extension including last dot
    end

    %% Saves specific figure to given filename in Trajectories/ folder as a .fig.
    % TODO: Currently harcoded save path! Will not work!
    function saveFigure(filename, fig_num)
        decomposed = decomposeFilename(filename);
        new_file_name = strcat('TrajectoriesMore/', decomposed.name, '.fig');
        saveas(fig_num, new_file_name);
    end

    %% Reads video frames and generates list of centroids of base and tip at all points in time.
    function centroids = getAllCentroidData(filename)
        v = VideoReader(filename);
        base_centroids = [];
        tip_centroids = [];
        time = [];
        i = 1;
        idx = 1;
        frameRate = v.FrameRate;
        while hasFrame(v)
            vidFrame = readFrame(v);
%             imshow(getBinaryJointTip(vidFrame));
            try
                base_centroids(idx, :) = getCentroid(getBinaryJointBase(vidFrame));
                tip_centroids(idx, :) = getCentroid(getBinaryJointTip(vidFrame));
                time(idx) = i / frameRate;
                idx = idx + 1;
            catch
                warning('Could not get centroid.') % RGB mask does not deal well with light glare.
            end
            i = i + 1;
        end
        centroids.base = base_centroids;
        centroids.tip = tip_centroids;
        centroids.time = time;
    end

    %% Returns binary image of marker on base of joint (red).
    function res = getBinaryJointBase(image)
        [BW,maskedRGBImage] = createRedMask(image);
        res = BW;
    end

    %% Returns binary image of marker on tip of joint (yellow).
    function res = getBinaryJointTip(image)
        [BW,maskedRGBImage] = createYellowMask(image);
        res = BW;
    end

    %% Returns centroid of a binary image.
    function res = getCentroid(bw_image)
        stats = regionprops(bw_image,'centroid');
        res = stats.Centroid;
    end
end