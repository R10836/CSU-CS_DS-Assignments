// ¼��ҵ���ʵ��

package Student;

import javax.sound.sampled.*;
import javax.swing.filechooser.FileSystemView;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;

public class MyRecorder {
    private AudioFormat af;
    private boolean flag;
    private ByteArrayOutputStream baos = null;      //����д���ֽ�����������
    private DataLine.Info targetinfo,sourceinfo;    //DataLine�����йص�����Ϣ
    public static String path = null;
    private TargetDataLine td;
    private SourceDataLine sd;

    public MyRecorder(){
        try {
            af = getAudioFormat();      //��ȡAudio�ֽ���֯˳��
            targetinfo = new DataLine.Info(TargetDataLine.class, af);
            td = (TargetDataLine) (AudioSystem.getLine(targetinfo));
            sourceinfo = new DataLine.Info(SourceDataLine.class, af);
            sd = (SourceDataLine) (AudioSystem.getLine(sourceinfo));
        } catch (Exception e) {
            e.printStackTrace();        //��ӡ�쳣��Ϣ
        }
    }

    public static AudioFormat getAudioFormat() {
        //Encoding������������Ƶ�����ض����ݱ�ʾ����
        AudioFormat.Encoding encoding = AudioFormat.Encoding.PCM_SIGNED;
        float rate = 8000f;
        int sampleSize = 16;
        boolean bigEndian = false;
        int channels = 1;
        /*AudioFormat������������˼Ϊ:
            encoding - ��Ƶ���뼼��
            sampleRate - ÿ�������
            sampleSizeInBits - ÿ�������е�λ��
            channels - ͨ������1Ϊmono��2Ϊ�������ȣ�
            frameSize - ÿ��֡�е��ֽ���
            frameRate - ÿ���֡��
            bigEndian - ָʾ���������������Ƿ��Դ��ֽ�˳��洢(false��ʾСβ��)
        */
        return new AudioFormat(encoding, rate, sampleSize, channels, (sampleSize / 8) * channels, rate, bigEndian);
    }

    public void play(String fileName){      //�����ļ�
        try{
            File file = new File(fileName);
            AudioInputStream ais = AudioSystem.getAudioInputStream(file);   //�ֽ�������
            //AudioFormat��ָ�������������ݵ��ض����е���
            AudioFormat af = AudioSystem.getAudioFileFormat(file).getFormat();
            DataLine.Info dataLineInfo = new DataLine.Info(SourceDataLine.class, af);   //�й�����Ϣ
            SourceDataLine sd = (SourceDataLine) AudioSystem.getLine(dataLineInfo); //Դ������

            sd.open();
            sd.start();

            byte buf[] = new byte[0xFF];    //һ�����д256���ֽ�
            int len;                        //һ��д�볤��
            while ((len = ais.read(buf, 0, buf.length)) != -1) {
                sd.write(buf, 0, len);
            }
            sd.drain();  //drain����ͨ������������I/O���Ŷ��ų����ݣ�ֱ�������ߵ��ڲ�����������ա�
            sd.close();  //�ر�������
            ais.close();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    class Recorder implements Runnable {        //¼����

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

    public void start(){        //��ʼ¼��
        Thread t = new Thread(new Recorder());
        t.start();
    }

    public void stop(){         //����¼��
        System.out.println("Record ended");
        flag = false;
        td.close();             //TargetDataLine���Ҫ�رգ��Ա���һ��¼��
        save();
    }

    public void save() {        //����¼���ļ�
        AudioFormat af = getAudioFormat();
        byte audioData[] = baos.toByteArray();      //תΪ�ֽ�����
        //���뵽�ļ���
        ByteArrayInputStream bais = new ByteArrayInputStream(audioData);
        AudioInputStream ais = new AudioInputStream(bais, af, audioData.length / af.getFrameSize());
        try {
            File filePath = new File(FileSystemView.getFileSystemView().getHomeDirectory().getAbsolutePath());   //����������
            path = filePath.getPath() + "\\" + System.currentTimeMillis() + ".mp3";
            File file = new File(path);
            AudioSystem.write(ais, AudioFileFormat.Type.WAVE, file);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
