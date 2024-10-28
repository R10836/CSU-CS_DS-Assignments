
object TestPhone{

  //定义父类Phone
  class Phone(var phoneBrand:String,var price:Int){
    def buy():Unit=println("buy() method in Phone") //buy方法，无参数
    //compare方法，参数为Phone类型
    def compare(p:Phone):Unit=println("compare() method in Phone")
  }

  //定义子类Apple
  class Apple( phoneBrand:String,price:Int) extends Phone(phoneBrand,price){
    private var AphoneNo:Int=0
    //重写父类compare方法
    override def compare(p:Phone):Unit={
      println("compare() method in Apple")
      println(this.phoneBrand+" is compared with "+p.phoneBrand)
    }
  }

  //定义子类HuaWei
  class HuaWei(phoneBrand:String,price:Int) extends Phone(phoneBrand,price){

    private var HphoneNo:Int=0
    //**************Begin*************************
//**************Begin*************************
override def buy(): Unit = println("buy() method in HuaWei")
override def compare(p: Phone): Unit = {
  println("compare() method in HuaWei")
  println(this.phoneBrand + " is compared with " + p.phoneBrand)
}
//**************End**************************

   
    //**************Begin*************************

  }

  //运行入口
  def main(args: Array[String]){

    val p1:Phone=new HuaWei("huawei",4500)
    val p2:Phone=new Apple("iphone",6400)

    p1.buy()

    p1.compare(p2)
    println("-----------------------------")

    /*p2引用的是Apple类型的对象，Apple类未对父类中的buy方法进行重写,因此它调用的是继承自父类的buy方法*/
    p2.buy()

    //p2.compare(p1)传入的实际类型是HuaWei，调用的是Apple类重写后的compare方法
    p2.compare(p1)
  }
}
