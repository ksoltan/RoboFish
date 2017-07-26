function wave_chars = generate_deflection_sequence()
    joint_variables();
    fs = 1 / 0.007;
    time = 0 : 1 / fs: 1;
    len_time = length(time);
    all_deflection_angles = zeros(len_time, K - 1);
    wave_chars = zeros(K - 1, 3); % Amplitude, frequency, phase
    % Get all deflection angles
    for i = 1 : len_time
        t = time(i);
        joint_points = discretize_posture([6.28, 4.796, 4.28, 7.219], t, @mean_error, @get_posture);
        all_deflection_angles(i, :) = get_all_deflection_angles(joint_points);
    end
    for j = 1 : K - 1
        head_ft = fft(all_deflection_angles(:, j));
        % frequencies from 0 to fs/2. Making an array from 0 to fs also works
        % because the second mirrored image of the transform goes the other parts of it 
        f = 0 : fs / length(head_ft) : fs;
%         f = linspace(0, fs, length(head_ft));
        figure(j); % Make figure with white background
        
        subplot(3, 1, 1); plot(f(1 : length(f)/2), abs(head_ft(1 : length(f)/2)), 'LineWidth', 1.5) % Plot the amplitude
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        xlabel('Frequency (Hz)', 'FontSize', 14);
        ylabel('Amplitude', 'FontSize', 14);
        title('Joint Frequency Analysis', 'FontSize', 20);
        
        subplot(3, 1, 2); plot(f(1 : length(f)/2), angle(head_ft(1 : length(f)/2)), 'LineWidth', 1.5) % Plot the phase
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        xlabel('Frequency (Hz)', 'FontSize', 14);
        ylabel('Phase (rad)', 'FontSize', 14);
        
        [M, I] = max(abs(head_ft(1 : length(f)/2))); %https://www.mathworks.com/matlabcentral/answers/100813-how-do-i-find-the-indices-of-the-maximum-or-minimum-value-of-my-matrix
        freq = 2 * pi * f(I); % https://en.wikipedia.org/wiki/Sine_wave
        phase = angle(head_ft(I)) + pi/2; % Added pi/2 shift because fits the line better. I don't know what causes that problem, wrapping?
        amplitude = max(all_deflection_angles(:, j));
        wave_chars(j, :) = [amplitude, freq, phase];
        subplot(3, 1, 3);
        reconstructed = plot(time, amplitude * sin(freq * time + phase), 'DisplayName', 'Reconstructed Wave', 'LineWidth', 1.5); % Plot reconstructed wave
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        hold on
        original = plot(time, all_deflection_angles(:, j), 'DisplayName', 'Original Wave', 'LineWidth', 1.5);
        legend([reconstructed, original])
        xlabel('Time (s)', 'FontSize', 14);
        ylabel('Deflection (deg)', 'FontSize', 14);
        title('Joint Motion Reconstruction vs Original Approximation with Adjusted Phase (+\pi/2)', 'FontSize', 18)
%         title('Joint Motion Reconstruction vs Original Approximation with Adjusted Phase (+', 'FontSize', 18);
    end
%     figure(K);
%     hold on;
%     plot(time, wave_chars(1, 1) * sin(wave_chars(1, 2) * time + wave_chars(1, 3)), 'b')
%     plot(time, wave_chars(2, 1) * sin(wave_chars(2, 2) * time + wave_chars(2, 3)), 'm')
%     plot(time, wave_chars(3, 1) * sin(wave_chars(3, 2) * time + wave_chars(3, 3)), 'r')
end