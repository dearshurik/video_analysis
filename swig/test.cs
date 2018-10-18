using System;
using System.Threading;
using System.IO;
using VideoAnalysis;

public class AudioCB : AudioCallback {

    public AudioCB() {
        dataOut = new BinaryWriter(new FileStream("res.pcm",FileMode.Create));
    }

    public override void putSamples(AudioFrame frame) {
        if (frame.getChannel() == 1) {
            short[] arr = new short[frame.getSize()];
            frame.getSamples(arr);
            foreach(short it in arr) {
                dataOut.Write(it);
            }
            dataOut.Flush();
        }
    }

    public override void finishMsg() {
        isFinish = true;
    }

    public bool isFinish = false;
    private BinaryWriter dataOut;
}

public class Test {
	public static void Main(String[] args) {
        AudioCB cb = new AudioCB();
        AudioDec dec = new AudioDec("/home/kuznetsov/video/4308.mp4", cb);
        dec.setInterval(0, 300);
        dec.run();
        while(!cb.isFinish) ;
	}
}
