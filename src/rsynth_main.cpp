
#include <iostream>
#include <unistd.h> // for sleep

#ifdef __arm__
#include <wiringPi.h>
#endif

#include "../include/JackClient.h"
#include "../include/mcp3008Spi.h"
#include "../include/Oscillator.h"
#include "../include/Sequencer.h"
#include "../include/RPIgpio.h"

#define GPIO_WIN_INTERVAL 11025
using namespace std;

Oscillator osc;
Sequencer seq;
RPIgpio *gpio;

int processCount = 0;

int analogChannels[5] = { 0, 1, 2, 3, 4 };
std::vector<int> rgbLedPins = { 0, 2, 3 };
std::vector<int> buttonPins = { 5, 6, 10 };

#ifdef __arm__
// This jack client will play back what it captures
class JackFullDuplex : public JackClient 
{
    int processAudio(jack_nframes_t nframes) 
    {
	//FIX ME different thread..
        if(++processCount > GPIO_WIN_INTERVAL)
        {
            processCount = 0;

      //      int gPot1 = readAnalogChannel(0);
//            int gPot2 = readAnalogChannel(1);
  //          int gPot3 = readAnalogChannel(2);
    //        int gPot4 = readAnalogChannel(3);

            // int gButon1 = 
            // int gButton2_left = 
            // int gButton2_righgt = 
        }

        if (outputPorts.size() != inputPorts.size()){
            cout<<"Different input and output port count, don't know how to copy. In port cnt="<<inputPorts.size()<<" output port count="<<outputPorts.size()<<endl;
            return -1;
        }

        for (uint i = 0; i < outputPorts.size(); i++) 
        { // for each channel of audio, copy input to output
            jack_default_audio_sample_t *out = ( jack_default_audio_sample_t* ) jack_port_get_buffer ( outputPorts[i], nframes ); // the output sample buffer
//            jack_default_audio_sample_t *in = ( jack_default_audio_sample_t* ) jack_port_get_buffer ( inputPorts[i], nframes ); // the inputs sample buffer
            for (uint j = 0; j < nframes; j++)
            {
                out[j] = osc.tick() * (seq.tick() * 0.9f);
            }
        }
        return 0;
    }
};
#endif

int main(int argc, char *argv[])
{
   // default gpio settings

    #ifdef __arm__
    gpio = new RPIgpio(rgbLedPins, buttonPins);
    #endif

    // default synth params
    float freq = 220.0f;
    int   tempo = 120;
    // adsr default
    float attPercent = 0.1;
    float decPercent = 0.1;
    float susLevel = 0.7;
    float relPercent = 0.1;

    // set envelope defaults
    seq._adsr.setAttack(attPercent);
    seq._adsr.setDecay(decPercent);
    seq._adsr.setSustain(susLevel);
    seq._adsr.setRelease(relPercent);

    // command line arguments
    if (argc > 1){
        freq = float(atof(argv[1]));
        osc.setFreq(freq);
    }
    if (argc > 2){
        freq = float(atof(argv[1]));
        tempo = int(atof(argv[2]));
        osc.setFreq(freq);
        seq.setTempo(tempo);
    }

    #ifdef __arm__
    // init the full duplex jack client
    JackFullDuplex jackClient;

    // connect to the jack server
    int res = jackClient.connect("jack full duplex client");
    if (res != 0)
    {
        return JackDebug().evaluateError(res);
    }

    // display Jack setup params
    cout << "Jack : sample rate set to : " << jackClient.getSampleRate() << " Hz" << endl;
    cout << "Jack : block size set to : " << jackClient.getBlockSize() << " samples" << endl;
    cout << "tempo: " << tempo << " " << "freq: " << freq << endl;

    // set oscillator defaults
    osc.setSampleRate(jackClient.getSampleRate());

    // set sequencer default
    seq.setSampleRate(jackClient.getSampleRate());
    seq.setSeqLength(5);
    seq.randomPattern();

    // create the ports
    res = jackClient.createPorts("in ", 1, "out ", 1);
    if (res != 0)
    {
        return JackDebug().evaluateError(res);
    }

    // start the client connecting ports to system ports
    res = jackClient.startClient(1, 1, true);
    if (res != 0)
    {
        return JackDebug().evaluateError(res);
    }
    #endif

    // main loop -- sleep forever
    while (1)
    {
        sleep(10);
    }
    return 0;
}
