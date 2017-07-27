function wave_chars = generate_deflection_sequence()
    joint_variables();
    fs = 1 / 0.007; % how many points are we getting per second
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
        % Use Fourier Transform to get frequency spectrum. The frequency
        % with highest amplitude is the driving frequency. For our rough
        % approximation, it is enough to use this frequency to generate a
        % cos curve and approximate the higher order function as such.
        head_ft = fft(all_deflection_angles(:, j));
        % frequencies from 0 to fs/2. Making an array from 0 to fs also works
        % because the second mirrored image of the transform goes the other parts of it
        f = 0 : fs / length(head_ft) : fs;
%         f = linspace(0, fs, length(head_ft));
        half_len = length(f) / 2;
        figure(j);
        subplot(3, 1, 1); plot(f(1 : half_len), abs(head_ft(1 : half_len)), 'LineWidth', 1.5) % Plot the amplitude
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        xlabel('Frequency (Hz)', 'FontSize', 14);
        ylabel('Amplitude', 'FontSize', 14);
        title('Joint Frequency Analysis', 'FontSize', 20);
        
        subplot(3, 1, 2); plot(f(1 : half_len), angle(head_ft(1 : half_len)), 'LineWidth', 1.5) % Plot the phase
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        xlabel('Frequency (Hz)', 'FontSize', 14);
        ylabel('Phase (rad)', 'FontSize', 14);
        
        % Find the index at which maximum amplitude of frequency occurs
        [M, I] = max(abs(head_ft(1 : half_len))); %https://www.mathworks.com/matlabcentral/answers/100813-how-do-i-find-the-indices-of-the-maximum-or-minimum-value-of-my-matrix
        % Get the driving frequency
        freq = 2 * pi * f(I) % https://en.wikipedia.org/wiki/Sine_wave
        phase = angle(head_ft(I)) % Use cos for this phase shift. If you want to use a sine wave, add +pi/2 to the phase.
        % Get height of the wave from original angular deflection data
        amplitude = max(all_deflection_angles(:, j));
        
        wave_chars(j, :) = [amplitude, freq, phase];
        
        subplot(3, 1, 3);
        reconstructed = plot(time, amplitude * cos(freq * time + phase), 'DisplayName', 'Reconstructed Cos Wave', 'LineWidth', 1.5); % Plot reconstructed wave
        set(gca,'FontSize',12, 'FontName', 'Times'); % Set axis to times, 12
        hold on
        original = plot(time, all_deflection_angles(:, j), 'DisplayName', 'Original Wave', 'LineWidth', 1.5);
        legend([reconstructed, original])
        xlabel('Time (s)', 'FontSize', 14);
        ylabel('Deflection (deg)', 'FontSize', 14);
        title('Joint Motion Reconstruction vs Original Approximation', 'FontSize', 18)
    end
    
    figure(K);
    hold on;
    plot(time, wave_chars(1, 1) * cos(wave_chars(1, 2) * time + wave_chars(1, 3)), 'b')
    plot(time, all_deflection_angles(:, 1),'y')
    plot(time, wave_chars(2, 1) * cos(wave_chars(2, 2) * time + wave_chars(2, 3)), 'm')
    plot(time, all_deflection_angles(:, 2),'g')
    plot(time, wave_chars(3, 1) * cos(wave_chars(3, 2) * time + wave_chars(3, 3)), 'r')
    plot(time, all_deflection_angles(:, 3))
end