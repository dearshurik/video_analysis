using System;
using System.Threading;
using VideoAnalysis;

public class AudioCB : AudioCallback {

    public override void putSamples(byte ch, short samples, uint size, double timestamp) {
    }
    
    public override void finishMsg() {
    }
}

public class Test {
	public static void Main(String[] args) {
        AudioCB cb = new AudioCB();

	}
}
