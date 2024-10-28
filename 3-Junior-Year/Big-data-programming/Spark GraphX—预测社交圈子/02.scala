import org.apache.log4j.{Level, Logger}
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.graphx._

object predict1_s {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("predict1_s").setMaster("local[4]")
    val sc = new SparkContext(conf)
    
    // 屏蔽日志
    Logger.getLogger("org.apache.spark").setLevel(Level.WARN)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)

    // 处理egonet文件的每行数据，返回元组形式的边数据
    def get_edges_from_line(line: String): Array[(Long, Long)] = {
      val ary = line.split(":")
      // 划分源顶点和目标顶点
      val srcId = ary(0).toInt
      // 根据分隔符把字符串切分为一个数组
      val dstIds = ary(1).split(" ")
      val edges = for {
        dstId <- dstIds
        if (dstId != "")
      } yield {
        // 将源顶点和目标顶点组合成元组
        (srcId.toLong, dstId.toLong)
      }
      if (edges.size > 0) edges else Array((srcId, srcId))
    }

    // 读取239.egonet文件内容
    val egonet_example = sc.textFile("/root/data/egonets/239.egonet")

    // **************Begin*************************
    // 根据定义的get_edges_from_line函数构造由边数据组成的Array
    val edges_array = egonet_example.map(x => get_edges_from_line(x)).collect
    // 现在是一个二维数组，需要用flatten函数转化为一维数组
    val edges = edges_array.flatten
    // 构造rawEdges:RDD[(VertexId, VertexId)]
    val g_edges = sc.makeRDD(edges)
    // 使用fromEdgeTuples构造图
    val g = Graph.fromEdgeTuples(g_edges, 1)
    // **************End**************************

    // **************Begin*************************
    // 找出图中的连通分量
    val connectedcomponents = g.connectedComponents.vertices.map(_.swap).groupByKey.map(_._2).collect
    println("")
    
    // 输出结果
    connectedcomponents.foreach(println)
    // **************End**************************
  }
}
