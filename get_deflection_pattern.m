% Get the timing and amplitude patterns for a function defined within
% generate_deflection_sequence (change when needed)
% pattern is an array of length of number of propulsors (joints) in order
% of which joint to move, the timing from the previous joint, and amplitude
% The timing for the first joint should be from the last joint.
% Timing is to next critical point (both trough and peak)
function pattern = get_deflection_pattern(joint_lengths)
    wave_chars = generate_deflection_sequence(joint_lengths); % (amplitude, frequency, phase shift)
    num_joints = length(wave_chars);
    % Assume frequecy is the same for all
    freq = wave_chars(1, 2);
    % Augment wave_chars with the number of the joint as the first column
    % Adjust the phase shift to all be positive (mod 2pi) and divide by
    % freq to get true shift
    wave_chars_aug = [(1:num_joints)', wave_chars(:, 1 : 2), mod(wave_chars(:, 3), 2*pi) / freq];
    % Wave chars augments is: joint_num(idx=1), amplitude(idx=2), freq(idx=3), phase shift(idx=4)
    % Sort using the fourth column (magnitude of phase_shifts) and
    % negative means in descending order.
    sorted_wave_chars_aug = sortrows(wave_chars_aug, -4);
    
    pattern = zeros(num_joints, 3); % Joint number, timing from prev joint, amplitude
    wait_time = 0;
    for j = 2 : num_joints
        time_change = sorted_wave_chars_aug(j - 1, 4) - sorted_wave_chars_aug(j, 4);
        wait_time = wait_time + time_change;
        pattern(j, :) = [sorted_wave_chars_aug(j, 1), time_change, sorted_wave_chars_aug(j, 2)]; % (joint_num, timing from prev joint, amplitude)
    end
    % Update the timing for the first joint which takes half the period
    % (pi/f) minus the time taken between all of the previous joints.
    pattern(1, :) = [sorted_wave_chars_aug(1, 1), pi / freq - wait_time, sorted_wave_chars_aug(1, 2)]; 
end