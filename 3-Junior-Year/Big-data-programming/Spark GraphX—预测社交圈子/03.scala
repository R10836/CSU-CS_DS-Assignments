import org.apache.log4j.{Level, Logger}
import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.graphx._

object predict2_s {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("predict2_s").setMaster("local[4]")
    val sc = new SparkContext(conf)
    
    // 屏蔽日志
    Logger.getLogger("org.apache.spark").setLevel(Level.WARN)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)

    // 从path/userId.egonet格式的文件路径中解析出用户ID
    def extract(s: String) = {
      val Pattern = """^.*?(\d+).egonet""".r
      val Pattern(num) = s
      num
    }

    // 处理egonet文件的每行数据，返回元组形式的边数据
    def get_edges_from_line(line: String): Array[(Long, Long)] = {
      val ary = line.split(":")
      val srcId = ary(0).toInt
      val dstIds = ary(1).split(" ")
      val edges = for {
        dstId <- dstIds
        if (dstId != "")
      } yield {
        (srcId.toLong, dstId.toLong)
      }
      if (edges.size > 0) edges else Array((srcId, srcId))
    }

    // 根据文件内容构造边元组
    def make_edges(contents: String) = {
      val lines = contents.split("\n")
      // 根据get_edges_from_line构造元组类型的数组，此时unflat为二维数组
      val unflat = for {
        line <- lines
      } yield {
        get_edges_from_line(line)
      }
      // 使用flatten函数降维，并返回值
      val flat = unflat.flatten
      flat
    }

    // 构建图对象，执行connectedComponents()操作，返回结果
    def get_circles(flat: Array[(Long, Long)]) = {
      val edges = sc.makeRDD(flat)
      val g = Graph.fromEdgeTuples(edges, 1)
      val cc = g.connectedComponents()
      cc.vertices.map(x => (x._2, Array(x._1))).
        reduceByKey((a, b) => a ++ b).
        values.map(_.mkString(" ")).collect.mkString(";")
    }

    // 读取目录内容
    val egonets = sc.wholeTextFiles("/root/data/egonets")

    // **************Begin*************************
    // 获取用户ID
    val egonet_numbers = egonets.map(x => extract(x._1)).collect
    // 构造边元组
    val egonet_edges = egonets.map(x => make_edges(x._2)).collect
    // 根据get_circles函数构造图，并计算连通分量
    val egonet_circles = egonet_edges.toList.map(x => get_circles(x))
    // **************End**************************

    // **************Begin*************************
    // 将用户ID与预测的社交圈子组合，需要使用zip函数
    val result = egonet_numbers.zip(egonet_circles).map(x => x._1 + "," + x._2)
    println("")
    println("UserId,Predicted social circles(Every social circle is used ';' separated.)")
    // 换行输出最终结果
    println(result.mkString("\n"))
    // **************End**************************
  }
}
