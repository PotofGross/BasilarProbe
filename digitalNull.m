function NulledZ = digitalNull(Needle, NoNeedle, AmpRef, stimFrequency, sampleRate)
          %moves probe to zero DC and runs a long no signal 
          disp('nulling...')
          AmpCpx = fftpoint_cpx3(AmpRef,  sampleRate, stimFrequency);
          NCpx = fftpoint_cpx3(Needle, sampleRate, stimFrequency);
          NNCpx = fftpoint_cpx3(NoNeedle, sampleRate, stimFrequency);
          outCpx = fftpoint_cpx3(data(:,1),  BM.sampleRate,BM.stimFrequency); 
          inCpx = fftpoint_cpx3(data(:,2),  BM.sampleRate,BM.stimFrequency); 
          digitalNulledSignal = NCpx + NNCpx; %they are out of phase from the probe thus adition negates
          stackVelocity = -2i*pi* stimFrequency * AmpCpx(end); %a discrete frequency differentiation         
          NulledZ = digitalNulledSignal ./ stackVelocity;
          disp('nulled!')
       
