
abstract class Phone{
  val phoneBrand: String
  def info()
  def greeting() {
    println("Welcome to use phone!")
  }
}

class Apple extends Phone{
  override val phoneBrand = "Apple"

  def info() {
    printf("This is a/an %s phone. It is expensive.\n", phoneBrand)
  }

  override def greeting() {
    println("Welcome to use Apple Phone!")
  }
}

class HuaWei extends Phone {
  override val phoneBrand = "HuaWei"
  
   def info() {
    printf("This is a/an %s phone. It is useful.\n", phoneBrand)
  }

  //**************Begin*************************
override def greeting() {
    println("Welcome to use HuaWei Phone!")
}

  //**************End**************************

}

object MyPhone {

  def main(args: Array[String]){

    val myPhone1 = new Apple()
    val myPhone2 = new HuaWei ()
    myPhone1.greeting()
    myPhone1.info()
    myPhone2.greeting()
    myPhone2.info()
  }
}