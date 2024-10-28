// 录音业务的实现

package Student;

import javax.sound.sampled.*;
import javax.swing.filechooser.FileSystemView;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;

public class MyRecorder {
    private AudioFormat af;
    private boolean flag;
    private ByteArrayOutputStream baos = null;      //数据写入字节数组的输出流
    private DataLine.Info targetinfo,sourceinfo;    //DataLine对象有关的行信息
    public static String path = null;
    private TargetDataLine td;
    private SourceDataLine sd;

    public MyRecorder(){
        try {
            af = getAudioFormat();      //获取Audio字节组织顺序
            targetinfo = new DataLine.Info(TargetDataLine.class, af);
            td = (TargetDataLine) (AudioSystem.getLine(targetinfo));
            sourceinfo = new DataLine.Info(SourceDataLine.class, af);
            sd = (SourceDataLine) (AudioSystem.getLine(sourceinfo));
        } catch (Exception e) {
            e.printStackTrace();        //打印异常信息
        }
    }

    public static AudioFormat getAudioFormat() {
        //Encoding类命名用于音频流的特定数据表示类型
        AudioFormat.Encoding encoding = AudioFormat.Encoding.PCM_SIGNED;
        float rate = 8000f;
        int sampleSize = 16;
        boolean bigEndian = false;
        int channels = 1;
        /*AudioFormat各个参数的意思为:
            encoding - 音频编码技术
            sampleRate - 每秒采样数
            sampleSizeInBits - 每个样本中的位数
            channels - 通道数（1为mono，2为立体声等）
            frameSize - 每个帧中的字节数
            frameRate - 每秒的帧数
            bigEndian - 指示单个样本的数据是否以大字节顺序存储(false表示小尾数)
        */
        return new AudioFormat(encoding, rate, sampleSize, channels, (sampleSize / 8) * channels, rate, bigEndian);
    }

    public void play(String fileName){      //播放文件
        try{
            File file = new File(fileName);
            AudioInputStream ais = AudioSystem.getAudioInputStream(file);   //字节输入流
            //AudioFormat是指定声音流中数据的特定排列的类
            AudioFormat af = AudioSystem.getAudioFileFormat(file).getFormat();
            DataLine.Info dataLineInfo = new DataLine.Info(SourceDataLine.class, af);   //有关行信息
            SourceDataLine sd = (SourceDataLine) AudioSystem.getLine(dataLineInfo); //源数据线

            sd.open();
            sd.start();

            byte buf[] = new byte[0xFF];    //一次最大写256个字节
            int len;                        //一次写入长度
            while ((len = ais.read(buf, 0, buf.length)) != -1) {
                sd.write(buf, 0, len);
            }
            sd.drain();  //drain方法通过持续的数据I/O从排队排出数据，直到数据线的内部缓冲区被清空。
            sd.close();  //关闭数据流
            ais.close();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    class Recorder implements Runnable {        //录音类

        public void run() {
            try {
                System.out.println("Begin record");
                td.open(af);
                td.start();
                byte bts[] = new byte[10000];
                baos = new ByteArrayOutputStream();
                flag = true;
                while (flag) {
                    int cnt = td.read(bts, 0, bts.length);
                    if (cnt > 0) {
                        baos.write(bts, 0, cnt);
                    }
                }

                td.drain();
                td.close();
                baos.close();

            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }

    public void start(){        //开始录音
        Thread t = new Thread(new Recorder());
        t.start();
    }

    public void stop(){         //结束录音
        System.out.println("Record ended");
        flag = false;
        td.close();             //TargetDataLine最后还要关闭，以便下一次录音
        save();
    }

    public void save() {        //保存录音文件
        AudioFormat af = getAudioFormat();
        byte audioData[] = baos.toByteArray();      //转为字节数组
        //输入到文件流
        ByteArrayInputStream bais = new ByteArrayInputStream(audioData);
        AudioInputStream ais = new AudioInputStream(bais, af, audioData.length / af.getFrameSize());
        try {
            File filePath = new File(FileSystemView.getFileSystemView().getHomeDirectory().getAbsolutePath());   //保存在桌面
            path = filePath.getPath() + "\\" + System.currentTimeMillis() + ".mp3";
            File file = new File(path);
            AudioSystem.write(ais, AudioFileFormat.Type.WAVE, file);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
