import org.apache.log4j.{Level, Logger}
import org.apache.spark.graphx._
import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}
object GraphX_Test_stu{
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
    //*********************图的属性
    //找出图中成绩大于60的顶点
    println("Find the vertices with scores greater than 60 in the graph")
    graph.vertices.filter{case (id,(name,grade)) => grade > 60}.collect.foreach{
      case (id,(name,grade)) => println(s"$name $grade")
    }
    println
    //边操作，找出图中边属性大于5的边
    println("Find the edge of the graph whose edge attribute is greater than 5")
    graph.edges.filter(e => e.attr > 5).collect.foreach(e => println(s"${e.srcId} to ${e.dstId} att ${e.attr}"))
    println
    //triplets操作.((srcId,srcAttr),(dstID,dstAttr),attr)
    //列出边属性>5的tripltes
    println("Find the tripltes with edge attributes greater than 5")
    for (triplet <- graph.triplets.filter(t => t.attr > 5).collect){
      println(s"${triplet.srcAttr._1} ${triplet.dstAttr._1}")
    }
    println
    //Degrees操作
    //找出图中最大的出度、入度、度数
    println("Find the maximum outDegrees, inDegrees, and Degrees in the graph")
    def max(a:(VertexId,Int),b:(VertexId,Int)):(VertexId,Int) = {
      if(a._2 > b._2) a else b
    }
    println("max of outDegrees" + graph.outDegrees.reduce(max)  + " max of inDegrees" + graph.inDegrees.reduce(max) + " max of Degrees" + graph.degrees.reduce(max))
    //********************转换操作
    //顶点的转换操作，顶点成绩+10
    println("Vertex conversion operation   vertex scores added 10")
    graph.mapVertices{ case (id, (name, age)) => (id, (name,age+10))}.vertices.collect.foreach(v => println(s"${v._2._1} is ${v._2._1}"))
    println
    //边的转换操作，边的属性
    println("Edge conversion operation   multiplying the attribute of the edge by 2")
    graph.mapEdges(e => e.attr*2).edges.collect.foreach(e => println(s"${e.srcId} to ${e.dstId} att ${e.attr}"))
    println
    //********************结构操作
    //找出顶点成绩>60的子图
    println("Find subgraphs with vertex scores greater than 60")
    val subGraph = graph.subgraph(vpred = (id, vd) => vd._2 >= 60)
    //找出子图所有顶点
    println("Find all the vertices of the subgraph:")
    subGraph.vertices.collect.foreach(v => println(s"${v._2._1} is ${v._2._2}"))
    println
    //找出子图所有边
    println("Find all sides of the subgraph:")
    subGraph.edges.collect.foreach(e => println(s"${e.srcId} to ${e.dstId} att ${e.attr}"))
    println
    //********************结构操作
    //连接操作
    val inDegrees:VertexRDD[Int] = graph.inDegrees
    case class User(name:String,grade:Int,inDeg:Int,outDeg:Int)
    //创建一个新图，顶点VD的数据类型为User，并从graph做类型转换
    val initialUserGraph:Graph[User,Int] = graph.mapVertices{case (id,(name,grade)) => User(name,grade,0,0)}
    //initialUserGraph与inDegrees、outDegrees(RDD)进行连接
    //并修改initialUserGraph中inDeg值、outDeg值
    val userGraph = initialUserGraph.outerJoinVertices(initialUserGraph.inDegrees){
      case(id, u, inDegOpt) => User(u.name, u.grade, inDegOpt.getOrElse(0), u.outDeg)}.outerJoinVertices(initialUserGraph.outDegrees){
      case(id, u, outDegOpt) => User(u.name, u.grade, u.inDeg, outDegOpt.getOrElse(0))
    }
    //连接图的属性
    userGraph.vertices.collect.foreach(v => println(s"${v._2.name} inDeg: ${v._2.inDeg} outDeg:${v._2.outDeg}"))
    println
    //找出出度和入度相同的顶点
    println("Find the same vertex with the same degree of penetration")
    userGraph.vertices.filter{
      case (id,u) => u.inDeg == u.outDeg
    }.collect.foreach{
      case (id,property) => println(property.name)
    }
    println
    sc.stop()
  }
}