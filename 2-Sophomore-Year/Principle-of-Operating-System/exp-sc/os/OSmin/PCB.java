/****************************进程管理PCB进程块************************************/
package OSmin;
public class PCB {
    static final int 运行态 = 1;   //运行态=1
    static final int 就绪态 = 2;   //就绪态=2 
    static final int 就绪挂起 = 3; // 就绪挂起=3
    private String processName;    //进程名称
    private int runTime;           //进程运行时间
    private int prority;           //进程优先级
    private int processState;      //进程状态
    private int base;              //进程基址
    private int limit;             //限制长度
    public PCB(String name, int time,int pro,int base,int limit)
    {//-------------------------------------PCB包含进程参数
        this.processName = name;
        this.runTime = time;
        this.prority = pro;
        this.processState = 0;
        this.limit = limit;
        this.base = base;
    }
    public PCB(){}
    public void setProcessName(String name)//设置进程名
    {
        this.processName = name;
    }
    public String getProcessName()//---------获取进程名
    {
        return processName;
    }   
    public void setRunTime(int time)//-------设置运行时间
    {
        this.runTime = time;
    }
    public int getRunTime()//----------------获取运行时间
    {
        return this.runTime;
    }
    public void setPrority(int prority)//----设置优先级
    {
        this.prority = prority;
    }
    public int getPrority()//----------------获取优先级
    {
        return this.prority;
    }
    public void setProcessState(int state)//-设置运行状态
    {
        this.processState = state;
    }
    public String getProcessState()//--------获取运行状态
    {
        String s = new String();
        if(this.processState == 1)
        {
            s = "运行态";
        }
        else if(this.processState == 2)
        {
            s = "就绪态";
        }
        else if(this.processState == 3)
        {
            s = "就绪挂起";
        }
        return s;
    }
    public void setBase(int base)//----------设置进程基址
    {
        this.base = base;
    }
    public int getBase()//-------------------获取进程基址
    {
        return this.base;
    }
    public void setLimit(int limit)//--------设置进程长度
    {
        this.limit = limit;
    }
    public int getLimit()//------------------获取进程长度
    {
        return this.limit;
    }
}