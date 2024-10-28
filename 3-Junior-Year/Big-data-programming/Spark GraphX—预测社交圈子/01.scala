import org.apache.log4j.{Level, Logger}
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.graphx._

object connectComponents {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("connectComponents").setMaster("local[4]")
    val sc = new SparkContext(conf)
    
    // 屏蔽日志
    Logger.getLogger("org.apache.spark").setLevel(Level.WARN)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)

    // **************Begin*************************
    // 构造VertexRDD
    val myVertices = sc.parallelize((1L to 8L).map((_, "")))
    
    // 构造EdgeRDD
    val myEdges = sc.parallelize(Array(
      Edge(1L, 2L, ""), 
      Edge(4L, 5L, ""), 
      Edge(4L, 6L, ""), 
      Edge(5L, 6L, ""), 
      Edge(5L, 7L, ""), 
      Edge(7L, 6L, "")
    ))

    // 构造图Graph[VD, ED]
    val myGraph = Graph(myVertices, myEdges)

    // 计算连通分量
    val connectedcomponents = myGraph.connectedComponents.vertices.map(_.swap).groupByKey.map(_._2).collect

    println("")

    // 输出结果
    connectedcomponents.foreach(println)
    // **************End**************************
  }
}
