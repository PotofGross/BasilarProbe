classdef bmCollectD1 < handle
% bmCollectD is a class that reads data from a data acqusition object and
% saves it to a file. It plots chunks of data to a figure for real time
%viewing of the data. Figure is designed to look like a Tektronix scope 
% screen because it is kewl. Or just intuitive to me.
% Aleks Zosuls Boston University 2016
%THis version is custom tailored for the BM force probe it uses digital
%nulling instead of tha analoge nuller.

    properties
    animalNumber
    maxFileSize    
    end
   properties (SetAccess = private)
       fileName
       fileNameBinary
       fid
       runningFileSize
       fStat
       run
       initDCPos  %initial probe DC position
       lastDCVolts    %last programmed DC probe position
       DCdispCal    %DC stack voltage to displacement cal V/um
       ACdispCal
       runStep
       runInputCpx
       runOutputCpx
       sampleRate
       stimFrequency
       Cimpedance
       mag
       phRad 
       timeStamp
       nullRawNN
       nullRawN
       nullRawAmp
       currentNullCpx
       chargeAMGain
       ampAtten
       runAmpCpx
       runNCpx
       runNNCpx
       continueRun
       freeRunTrue
   end
   
   methods
       function BM = bmCollectD1(animalNumber,s)
           BM.animalNumber =animalNumber;
           BM.runningFileSize = 0;
           BM.run = 0;
           BM.initDCPos = 0;
           BM.DCdispCal = .1429; %in micrometers per volt
           BM.ACdispCal = .085; %um/v
           BM.stimFrequency = 78;
           BM.sampleRate = 21000;
           BM.chargeAMGain = 50;    %this is the charge amp AM502 gain should be matched
           BM.ampAtten = .1;    %this is the norelco output attenuator 10x
           %open warnig box to alert user to clear the probe path for a
           %home operation that move the probe to 0um relative to the DC
           %stack
           f = figure;
           h = uicontrol('Position',[20 20 200 40],'String','Continue',...
                          'Callback','uiresume(gcbf)');
           disp('Clear probe for stack home process');
           uiwait(gcf); 
           disp('homing');
           close(f);
            %move to home
            %initDCPos = 
           %queueOutputData(s,initDCPos);
           startForeground(s);
           BM.lastDCVolts = 0;
          % figure(99) %this is the frequency domain figure
            %init properties
       end
       
       function newFile(BM)
           timeFormat='yyyy-mm-dd-HH-MM-SS';
           BM.timeStamp = datestr(fix(clock),timeFormat);
           BM.fileName = [BM.animalNumber,'-',BM.timeStamp,'run',num2str(BM.run),'.dat']; 
           BM.fileNameBinary = [BM.animalNumber,'-',BM.timeStamp,'BinaryRun',num2str(BM.run),'.mat']; 
           BM.fid = fopen(BM.fileName, 'w');
       end
       
       function close(BM)
            BM.fStat = fclose(BM.fid);
           %delete(FS.fid)
       end
       
       %this is the main loop to run a stiffness series
       function accumulateData(BM, s, startLim,upLim,stepSize,endLim)
           %clear the run incremental datas
           BM.freeRunTrue = 0;
           BM.continueRun = 1;
           BM.runStep = [];
           BM.runInputCpx = [];
           BM.runOutputCpx = [];
           BM.Cimpedance = [];
           BM.mag = [];
           BM.phRad = [];
           BM.run  = BM.run + 1; %increment run number
           BM.newFile();  %make new run file for raw data
           zFig = figure(BM.run+100); %new magPh figure for each run
           %calcualte the steps and put in vector
           stepps = [startLim:stepSize:upLim upLim-stepSize:-stepSize:endLim];
           %for loop that runs through the steps
           for z = 1:length(stepps)
 
              if(BM.continueRun == 1)
               %move to  step position
               moveDC(BM,s, stepps(z))
               %make output buffer for DAC
               DCStackVolts = stepps(z) * BM.DCdispCal;
               queueOutputData(s, DCStackVolts*ones(70000,1));
               data = startForeground(s);   %run the stuff
               %convert to input referred volts
               data(:,1) = data(:,1)/BM.chargeAMGain;
               data(:,2) = data(:,2)/BM.chargeAMGain;
               data(:,3) = data(:,3)* BM.ACdispCal / BM.ampAtten;
               fprintf(BM.fid, 'stepppen\t %6.4f\r\n', stepps(z));
               fprintf(BM.fid,'%6.4f\t %6.4f\t %6.4f\r\n', [data(:,1)'; data(:,2)'; data(:,3)';]);
               %data(:,1) is NEEDLE convereted to volts
               %data(:,2) is the NO NEEDLE out
               %data(:,3) is AC Amp out ref
               figure(88)  %88 is the time domain figure
               cla
               h = gca;
               h.Color = 'black';
               plot(data(1:2000,1),'y')
               hold on
               plot(data(1:2000,2),'b')
               plot(data(1:2000,3),'m')

               displayFreqDomain(BM,zFig, data(:,3), data(:,1), data(:,2), stepps(z))
               figure(88)
               %write the mag and faze of the stepp
               lockinM = uicontrol('Style', 'text','FontSize',16,...
                    'Position', [300 380 120 28],'String',num2str(BM.mag(end)));  
                lockinP = uicontrol('Style', 'text','FontSize',16,...
                    'Position', [450 380 100 28],'String',180*BM.phRad(end)/pi);  
               eval(['dataStep{',num2str(z),'} = data;']) 
               
              end   %end of if not stopped...
           end      %end of DC step loop
           BM.close; %close the ASCII run file
           figure(zFig)
           overr = uicontrol('Style', 'text','FontSize',16,...
                'Position', [450 380 100 28],'String','its over!!');  
               eval(['dataStep{',num2str(z),'} = data;']) 
           save(BM.fileNameBinary, 'dataStep', 'BM')
           %save the FD stuff in a mat file for later viewing
           %matFilename = [BM.animalNumber,'-',BM.timeStamp,'run',num2str(BM.run),'.mat'];
           %save(matFilename, 'BM.runStep', 'BM.runInputCpx', 'BM.runOutputCpx');
       end  %end of step data collection
       
       %this moves the DC stack with the sigmoid smoothing
       function moveDC(BM,s, targetPosUM)
           BM.freeRunTrue = 0;
           timebase = (0:6999)/210000; %make this a property
           endVolts = targetPosUM * BM.DCdispCal;
           rampSignal = sigmoidRamp(BM.lastDCVolts, endVolts, timebase);
           queueOutputData(s, rampSignal');
           data = startForeground(s);
           BM.lastDCVolts = endVolts;
       end
           
       function delete(BM)
           try
               BM.fStat = fclose(BM.fid);
           catch
           end
       end
        
       function closeDAQ(BM, s)
           s.stop
           delete(s)
           clear('s')
       end
       
       function stopRun(BM,s)
           BM.continueRun = 0;
           BM.freeRunTrue = 0;
           disp('stopping run, move to zero')
           wait(s,11)
           moveDC(BM,s, 0) %move to Zero in z axis
       end
       
       function displayFreqDomain(BM,zFig, ampData, NData, NNData, stepp)
          %display and add points at each stepp
          figure(zFig)
          BM.runAmpCpx(end+1) = fftpoint_cpx3(ampData,  BM.sampleRate,BM.stimFrequency);
          BM.runNCpx(end+1) = fftpoint_cpx3(NData, BM.sampleRate, BM.stimFrequency);
          BM.runNNCpx(end+1) = fftpoint_cpx3(NNData, BM.sampleRate, BM.stimFrequency);
          BM.runStep(end+1) = stepp;
          %compute impedance = force( the measured signal) over velocity(drive
          %signal)
          digitalNulledSignal = BM.runNCpx(end) - BM.runNNCpx(end);  %probe 3 5
          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
          %digitalNulledSignal = BM.runNCpx(end) + BM.runNNCpx(end);     %probe2
          stackVelocity = -2i*pi* BM.stimFrequency .* BM.runAmpCpx(end);
          zCCow = digitalNulledSignal ./ stackVelocity
          %zCCow = BM.runOutputCpx(end) / BM.runInputCpx(end);
          zCNow = zCCow - BM.currentNullCpx;
          BM.Cimpedance(end+1) = zCNow;
          BM.mag(end+1) = abs(zCNow);
          BM.phRad(end+1) = angle(zCNow);
          subplot(2,1,1)
          plot(BM.runStep,BM.mag)
          title('Z Magnitude')
          ylabel('Magnitude')
          subplot(2,1,2)
          plot(BM.runStep, 180*BM.phRad/pi)
          title('Z phase')
          ylabel('Phase degrees')
      
       end
        
       function null(BM,s)
          %moves probe to zero DC and runs a long no signal 
          disp('nulling...')
          BM.freeRunTrue = 0;
          moveDC(BM,s, 0) %move to Zero in z axis
          DCStackVolts = 0 * BM.DCdispCal;
          queueOutputData(s, DCStackVolts*ones(70000,1));
          data = startForeground(s);   %run the stuff
          data(:,1) = data(:,1)/BM.chargeAMGain;
          data(:,2) = data(:,2)/BM.chargeAMGain;
          data(:,3) = data(:,3)* BM.ACdispCal / BM.ampAtten;
          BM.nullRawNN = data(:,2);
          BM.nullRawN =  data(:,1);
          BM.nullRawAmp = data(:,3);
          AmpCpx = fftpoint_cpx3(data(:,3),  BM.sampleRate,BM.stimFrequency);
          NCpx = fftpoint_cpx3(data(:,1), BM.sampleRate, BM.stimFrequency);
          NNCpx = fftpoint_cpx3(data(:,2), BM.sampleRate, BM.stimFrequency);
          %outCpx = fftpoint_cpx3(data(:,1),  BM.sampleRate,BM.stimFrequency); 
          %inCpx = fftpoint_cpx3(data(:,2),  BM.sampleRate,BM.stimFrequency); 
          digitalNulledSignal = NCpx - NNCpx;   %probe3 5
          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
          %digitalNulledSignal = NCpx + NNCpx;       %probe2
          stackVelocity = -2i*pi* BM.stimFrequency * AmpCpx;
          zCCow = digitalNulledSignal ./ stackVelocity;
          BM.currentNullCpx = zCCow ;  %outCpx/inCpx; 
          disp('nulled!')
       
       end
       
       function freeRun(BM,s) %free run collects x seconds of data and displays it no saving
          moveDC(BM,s, 0) %move to Zero in z axis
          DCStackVolts = 0 * BM.DCdispCal;
          BM.freeRunTrue = 1;
          
          while(BM.freeRunTrue)
              queueOutputData(s, DCStackVolts*ones(3500,1));
              data = startForeground(s);   %run the stuff
              data(:,1) = data(:,1)/BM.chargeAMGain;
              data(:,2) = data(:,2)/BM.chargeAMGain;
              data(:,3) = data(:,3)* BM.ACdispCal / BM.ampAtten;
              AmpCpx = fftpoint_cpx3(data(:,3),  BM.sampleRate,BM.stimFrequency);
              NCpx = fftpoint_cpx3(data(:,1), BM.sampleRate, BM.stimFrequency);
              NNCpx = fftpoint_cpx3(data(:,2), BM.sampleRate, BM.stimFrequency);
              %outCpx = fftpoint_cpx3(data(:,1),  BM.sampleRate,BM.stimFrequency); 
              %inCpx = fftpoint_cpx3(data(:,2),  BM.sampleRate,BM.stimFrequency); 
              digitalNulledSignal = NCpx - NNCpx;   %probe3 5
              %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
              %digitalNulledSignal = NCpx + NNCpx;   %probe2
              stackVelocity = -2i*pi* BM.stimFrequency * AmpCpx;
              zCCow = digitalNulledSignal ./ stackVelocity;
              zCNow = zCCow - BM.currentNullCpx;
              figure(66)
              lockinM = uicontrol('Style', 'text','FontSize',16,...
                        'Position', [300 380 120 28],'String',num2str(abs(zCNow)));  

              lockinP = uicontrol('Style', 'text','FontSize',16,...
                        'Position', [450 380 100 28],'String',180*angle(zCNow)/pi); 
          
          end
           
       end
   end
end