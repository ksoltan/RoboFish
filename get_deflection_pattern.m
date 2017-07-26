% Get the periodic pattern of angular deflection for a certain joint.
function get_deflection_pattern(fs, deflection_angles)
    figure;
    time = (0:length(deflection_angles) - 1)/fs;
    plot(time, deflection_angles);
    [autocor,lags] = xcorr(deflection_angles, 'coeff');
    
    figure;
    plot(lags/fs,autocor)
    xlabel('Lag (days)')
    ylabel('Autocorrelation')
%     axis([-21 21 -0.4 1.1])
end