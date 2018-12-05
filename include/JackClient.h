#ifdef __arm__ 
 #ifndef JACKCLIENT_H_
 #define JACKCLIENT_H_

 #include "JackBase.H"


 class JackClient : virtual public JackBase {
     static int processAudioStatic(jack_nframes_t nframes, void *arg) { 
         return reinterpret_cast<JackClient*>(arg)->processAudio(nframes);
     }

     static int bufferSizeChangeStatic(jack_nframes_t nframes, void *arg) { 
         return reinterpret_cast<JackClient*>(arg)->bufferSizeChange(nframes);
     }

 protected:
     virtual int processAudio(jack_nframes_t nframes)=0;

     virtual int bufferSizeChange(jack_nframes_t nframes){
         cout<<"JackClient::bufferSizeChangeStatic : New buffer size = "<<nframes<<endl;
         return 0;
     }

 public:
     JackClient(void) : JackBase() {}

     JackClient(string clientName_) : JackBase(clientName_) {}

     virtual ~JackClient() {
         disconnect(); // if the client is running, then stop the client and disconnect from the server
     }

     virtual int connect(string clientName_) {
         return JackBase::connect(clientName_);
     }

     virtual int connect(const string &clientName_, const string &serverName) {
         JackBase::connect(clientName_, serverName); // get the jack client connected

         if (0 != jack_set_process_callback(client, processAudioStatic, this))
             return JackDebug().evaluateError(JACK_SET_CALLBACK_ERROR);

         if (0 != jack_set_buffer_size_callback(client, bufferSizeChangeStatic, this))
             return JackDebug().evaluateError(JACK_SET_BUFFSIZE_CALLBACK_ERROR);

         return NO_ERROR;
     }

     virtual int getBlockSize() {
         return jack_get_buffer_size (client);
     }


     int setBlockSize(int size) {
         int res=jack_set_buffer_size(client,size);
         if (res!=0)
             return JACK_SET_BUFFER_SIZE_ERROR;
         return NO_ERROR;
     }

     virtual int startClient() {
         /* Tell the JACK server that we are ready to roll.  Our
         * process() callback will start running now. */

         return jack_activate(client);
     }

     virtual int startClient(int inCnt, int outCnt, bool doConnect=true) {

         if (startClient())
             return JackDebug().evaluateError(JACK_ACTIVATE_ERROR);


         if (doConnect) {
             vector<jack_port_t *> inPorts, outPorts; // find the physical ports and auto connect
             int inCntLocal=getPortListAndCount((JackPortFlags)(JackPortIsPhysical|JackPortIsOutput), &inPorts, NULL, NULL);
             if (inCntLocal==0)
                 return JackDebug().evaluateError(JACK_HAS_NO_CAPTURE_PORTS_ERROR);
             if (inCnt<inCntLocal)
                 inCntLocal=inCnt;
             for (int i=0; i<inCntLocal; i++)
                 if (jack_connect(client, jack_port_name(inPorts[i]), jack_port_name(inputPorts[i])))
                     cerr<<"cannot connect input port "<<i<<endl;

             int outCntLocal=getPortListAndCount((JackPortFlags)(JackPortIsPhysical|JackPortIsInput), &outPorts, NULL, NULL);
             if (outCntLocal==0)
                 return JackDebug().evaluateError(JACK_HAS_NO_PLAYBACK_PORTS_ERROR);
             if (outCnt<outCntLocal)
                 outCntLocal=outCnt;
             for (int i=0; i<outCntLocal; i++)
                 if (jack_connect(client, jack_port_name(outputPorts[i]), jack_port_name(outPorts[i])))
                     cerr<<"cannot connect output port "<<i<<endl;
         }
         return 0;
     }
 };
 #endif // JACKCLIENT_H_
#endif
