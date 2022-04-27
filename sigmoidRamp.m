function rampSignal = sigmoidRamp(y0, y1, timebase)
% Creates a ramp for output to a data acquisition device.  The shape of the
% ramp is a sigmoid function that starts at y0 and ends at y1.  Overshoot
% is used to compensate asymptotic behavior of the sigmoid function. 
% sigmoid function f(t) = y0 + (y1 - y0)/(1 + e^(k(-T/2)))
% Where k is a scaling factor, and T is the duration of the signal

duration = timebase(length(timebase));
T = (duration)/2;
k = 10/duration;
overshoot = (y1-y0) * (1+exp(k*-T)) + y0 - y1;

rampSignal = y0 + (y1 + overshoot - y0)./(1+exp(k*(T-timebase))); 
jump = rampSignal(length(rampSignal)) - y1;  % Difference between end of sigmoid ramp and requested position (y1);
if jump ~= 0
    disp('WARNING Sigmoid ramp may introduce impulses!');
end
%plot(rampSignal);
%rampSignal(1) = rampSignal(length(rampSignal));