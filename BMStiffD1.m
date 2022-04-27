%Basilar membrane stiffness probe runner
%Aleks Zosuls Boston University 2017
% Use NI DAQ to collect three channels of analog data
% and save it to disk. The files are broken into reasonable
% chunks to prevent large file issues.
% relies on fileSplitter.m and stopDAC.m

figure(88)
h = gca;
h.Color = 'black';
subjectID = input('Yo enter the subject ID. ', 's');

%% ni stuff%%%%%%%%%%%%%%%%%%%
v = daq.getVendors();
d = daq.getDevices();
s = daq.createSession('ni');
addAnalogOutputChannel(s,'Dev1', 'ao0', 'Voltage');
% this version has three input channels....
addAnalogInputChannel(s,'Dev1', 3, 'Voltage'); % ch 0 N / Angstrom Resolver
addAnalogInputChannel(s,'Dev1', 1, 'Voltage'); %ch1 NN 
addAnalogInputChannel(s,'Dev1', 2, 'Voltage'); % ampMon / AC signal
nChannelsAD = 3;
%sample rate should enable an integer number of cycles to be collected
%not sure if s.Rate is scan or sample rate because of mux
s.Rate = 21000;
npts = 21000*10;
zerosData = zeros(npts,1);
queueOutputData(s, zerosData); %this is here beacuse the output queue
%determins the input number of samples...
%s.NumberOfScans = npts * nChannelsAD;

%% make data handlers and listeners%%%%%%%%%
BM = bmCollectD1(subjectID, s);

btn1 = uicontrol('Style', 'pushbutton', 'String', 'end DAQ',...
    'Position', [500 20 50 20],...
    'Callback', @(src,eventdata) BM.closeDAQ(s));

rl = uicontrol('Style', 'text',...
           'Position', [170 40 40 20],'String','Retract');  

 retractLimBox = uicontrol('Style', 'edit',...
           'Position', [170 20 40 20]);   
sl = uicontrol('Style', 'text',...
           'Position', [220 40 40 20],'String','Start');  

 startLimBox = uicontrol('Style', 'edit',...
           'Position', [220 20 40 20]);   
       
ul = uicontrol('Style', 'text',...
           'Position', [270 40 40 20],'String','Upper');  

 upperLimBox = uicontrol('Style', 'edit',...
           'Position', [270 20 40 20]);   
       
 stpp = uicontrol('Style', 'text',...
           'Position', [320 40 40 20],'String','Step um');  

 stepSize = uicontrol('Style', 'edit',...
           'Position', [320 20 40 20]);   
   
btn2 = uicontrol('Style', 'pushbutton', 'String', 'stop',...
    'Position', [500 20 50 20],...
    'Callback', @(src,eventdata) BM.stopRun(s));

btn3 = uicontrol('Style', 'pushbutton', 'String', 'null!',...
    'Position', [400 20 50 20],...
    'Callback', @(src,eventdata) BM.null(s));

btn4 = uicontrol('Style', 'pushbutton', 'String', 'FreeRun',...
    'Position', [80 20 50 20],...
    'Callback', @(src,eventdata) BM.freeRun(s));

btn = uicontrol('Style', 'pushbutton', 'String', 'meas ps',...
    'Position', [20 20 50 20],...
    'Callback', @(src,eventdata) BM.accumulateData(s,str2double(startLimBox.String), str2double(upperLimBox.String),str2double(stepSize.String),str2double(retractLimBox.String)));

lockinM = uicontrol('Style', 'text','FontSize',16,...
                    'Position', [300 380 120 28],'String','Mag');  

lockinP = uicontrol('Style', 'text','FontSize',16,...
                    'Position', [450 380 100 28],'String','Ph deg'); 


