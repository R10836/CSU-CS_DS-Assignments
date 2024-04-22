/************************首次适应算法的动态可变分区分配*****************************/
package OSmin;
public class MMA {//Memory Management and Allocation内存管理与动态分区分配
    private int Base;    //分区基址
    private int length;  //分区长度
    private int divFlag; //分区标志
    public MMA(int Base,int length,int divFlag)
    {
        this.Base = Base;
        this.divFlag = divFlag;
        this.length = length;
    }
    public MMA(){}
    public void setDivBase(int base)//-设置分区基址
    {
        this.Base = base;
    }
    public int getDivBase()//----------获取分区基址
    {
        return this.Base;
    }
    public void setLength(int length)//设置分区长度
    {
        this.length = length;
    }
    public int getLength()//-----------获取分区长度
    {
        return this.length;
    }
    public void setDivFlag(int flag)//-设置分区标志
    {
        this.divFlag = flag;
    }
    public int getDivFalg()//----------获取分区标志
    {
        return this.divFlag;
    }
}