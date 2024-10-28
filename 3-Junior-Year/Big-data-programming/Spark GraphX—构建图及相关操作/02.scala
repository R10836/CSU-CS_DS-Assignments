import org.apache.log4j.{Level,Logger}
import org.apache.spark.{SparkContext,SparkConf}
import org.apache.spark.graphx._
import org.apache.spark.rdd.RDD
object GraphX_Test_2_stu{
  def main(args:Array[String]): Unit ={
    //屏蔽日志
    Logger.getLogger("org.apache.spark").setLevel(Level.WARN)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)
    //设置运行环境
    val conf = new SparkConf().setAppName("SimpleGraph").setMaster("local")
    val sc = new SparkContext(conf)
    //设置顶点和边，注意顶点和边都是用元组定义的Array
    //顶点的数据类型是VD:(String,Int)
    val vertexArray = Array(
      (1L,("Bob",89)),
      (2L,("Sunny",70)),
      (3L,("Tony",99)),
      (4L,("Helen",58)),
      (5L,("John",55)),
      (6L,("Tom",83)),
      (7L,("Marry",94)),
      (8L,("Cook",76)),
      (9L,("Linda",84))
    )
    //边的数据类型ED:Int
    val edgeArray = Array(
      Edge(1L,2L,5),
      Edge(1L,3L,9),
      Edge(2L,4L,4),
      Edge(3L,4L,6),
      Edge(3L,6L,8),
      Edge(3L,7L,4),
      Edge(4L,5L,7),
      Edge(4L,8L,6),
      Edge(8L,3L,7),
      Edge(8L,7L,2),
      Edge(8L,9L,1)
    )
    //构造vertexRDD和edgeRDD
    val vertexRDD:RDD[(Long,(String,Int))] = sc.parallelize(vertexArray)
    val edgeRDD:RDD[Edge[Int]] = sc.parallelize(edgeArray)
    //构造Graph[VD,ED]
    val graph:Graph[(String,Int),Int] = Graph(vertexRDD, edgeRDD)
    //********************实用操作
    //找出顶点1到各顶点的最短距离
    println("Find the shortest distance from vertex 1 to each vertex")
    val sourceId:VertexId = 1L  //定义远点
    val initialGraph = graph.mapVertices((id,_) => if (id == sourceId) 0.0 else Double.PositiveInfinity)
    val sssp = initialGraph.pregel(Double.PositiveInfinity)(
      (id,dist,newDist) => math.min(dist,newDist),
      triplet => {//计算权重
        if(triplet.srcAttr + triplet.attr < triplet.dstAttr){
          Iterator((triplet.dstId,triplet.srcAttr + triplet.attr))
        }else{
          Iterator.empty
        }
      },
      (a,b) => math.min(a,b)
    )
    println(sssp.vertices.collect.mkString("\n"))
    println
    def sendMsgFunc(edge:EdgeTriplet[Int, Int]) = {
      if(edge.srcAttr <= 0){
        if(edge.dstAttr <= 0){
          // 如果双方都小于0，则不发送信息
          Iterator.empty
        }else{
          // srcAttr小于0，dstAttr大于零，则将dstAttr-1后发送
          Iterator((edge.srcId, edge.dstAttr - 1))
        }
      }else{
        if(edge.dstAttr <= 0){
          // srcAttr大于0，dstAttr<0,则将srcAttr-1后发送
          Iterator((edge.dstId, edge.srcAttr - 1))
        }else{
          // 双方都大于零，则将属性-1后发送
          val toSrc = Iterator((edge.srcId, edge.dstAttr - 1))
          val toDst = Iterator((edge.dstId, edge.srcAttr - 1))
          toDst ++ toSrc
        }
      }
    }
    val friends = Pregel(
      graph.mapVertices((vid, value)=> if(vid == 1) 2 else -1),
      // 发送初始值
      -1,
      // 指定阶数
      2,
      // 双方向发送
      EdgeDirection.Either
    )(
      // 将值设为大的一方
      vprog = (vid, attr, msg) => math.max(attr, msg),
      //
      sendMsgFunc,
      //
      (a, b) => math.max(a, b)
    ).subgraph(vpred = (vid, v) => v >= 0)
    println("Confirm Vertices of friends ")
    friends.vertices.collect.foreach(println(_))
    sc.stop()
  }
}