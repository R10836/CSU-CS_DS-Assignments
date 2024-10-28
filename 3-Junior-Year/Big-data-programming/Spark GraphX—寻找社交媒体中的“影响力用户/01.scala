import org.apache.log4j.{Level, Logger}
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.graphx._

object farthest_distance{
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("farthest distance").setMaster("local[4]")
    val sc = new SparkContext(conf) //屏蔽日志
    Logger.getLogger("org.apache.spark").setLevel(Level.WARN)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)
    //构造图
    val myVertices = sc.parallelize(Array((1L,"Ann"),(2L,"Bill"),(3L,"Diane"),(4L,"Cody"),(5L,"Adam"),(6L,"Bob")))
    val myEdges = sc.parallelize(Array(Edge(1L,2L,""),Edge(2L,3L,""),Edge(2L,4L,""),Edge(3L,4L,""),Edge(4L,5L,"C"),Edge(4L,6L,""),Edge(5L,6L,""))) //构造EdgeRDD
    val myGraph = Graph(myVertices,myEdges)
    //**************Begin*************************
    //使用pregel函数找到距离Ann（1号）最远的顶点
    val g=Pregel(myGraph.mapVertices((vid,vd) => 0),0,
activeDirection=EdgeDirection.Out)(
(id:VertexId, vd:Int, a:Int) => math.max(vd,a),
(et:EdgeTriplet[Int,String]) => Iterator((et.dstId,et.srcAttr+1)),
(a:Int,b:Int) => math.max(a,b))




    //得到返回的新图的顶点集合
    val result = g.vertices.collect

    println("")
    //输出结果
    result.foreach(println)
    
    //**************End**************************
  }
}
