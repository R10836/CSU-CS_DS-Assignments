import  scala.util.control.Breaks._
object BubbleSort {
      def main(args: Array[String]): Unit = {
 
          val sortArray = Array(49,38,65,97,76,13,27,49,78)
          var exchange = true
         
          //**************Begin************************* 
          breakable{
                while (exchange) {
                    exchange = false
                    for (i <- 0 until sortArray.length - 1) {
                        if (sortArray(i) > sortArray(i + 1)) {
                        val temp = sortArray(i)
                        sortArray(i) = sortArray(i + 1)
                        sortArray(i + 1) = temp
                        exchange = true
                        }
                    }
    if (!exchange) break
  } 
           

         
 
           }
          //**************End**************************
         
        sortArray.foreach(x=> print(x + " "))
    }   
}
