import org.apache.spark.graphx.{Edge, EdgeDirection, Graph, VertexId}
import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Twitter_test {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("Twittter Influencer").setMaster("local[*]")
    val sparkContext = new SparkContext(conf)
    sparkContext.setLogLevel("ERROR")

    // 读取文件
    val twitterData = sparkContext.textFile("/root/data/twitter-graph-data.txt")

    // 分别从文本文件中提取followee和follower的数据
    val followeeVertices: RDD[(VertexId, String)] = twitterData.map(_.split(",")).map { arr =>
      val user = arr(0).replace("((", "")
      val id = arr(1).replace(")", "")
      (id.toLong, user)
    }

    // 根据followee的提取方法，提取follower的数据
    val followerVertices: RDD[(VertexId, String)] = twitterData.map(_.split(",")).map { arr =>
      val user = arr(2).replace("(", "")
      val id = arr(3).replace("))", "")
      (id.toLong, user)
    }

    // 根据提取的数据创建图
    val vertices = followeeVertices.union(followerVertices)
    val edges: RDD[Edge[String]] = twitterData.map(_.split(",")).map { arr =>
      val followeeId = arr(1).replace(")", "").toLong
      val followerId = arr(3).replace("))", "").toLong
      Edge(followeeId, followerId, "follow")
    }
    val defaultUser = ("")
    val graph = Graph(vertices, edges, defaultUser)

    // 使用Pregel API和广度优先遍历算法，最大迭代次数为2
    val subGraph = graph.pregel("", 2, EdgeDirection.In)(
      (_, attr, msg) => attr + "," + msg,
      // sendMsg函数，发送follower的属性到源顶点，
      // 以便可以在Twitter上累积跟随个人用户的所有2级用户。
      triplet => Iterator((triplet.srcId, triplet.dstAttr)),
      // mergeMsg函数将属性用“,”连接
      (a, b) => (a + "," + b)
    )

    // **************Begin*************************
    // 找到拥有最多followers of followers的用户，对subGraph的顶点属性进行切分，除去重复属性，并计算长度
    val lengthRDD = subGraph.vertices.map(vertex =>
      (vertex._1, vertex._2.split(",").distinct.length - 2)
    ).max()(new Ordering[Tuple2[VertexId, Int]]() {
      override def compare(x: (VertexId, Int), y: (VertexId, Int)): Int =
        Ordering[Int].compare(x._2, y._2)
    })

    // 找出拥有一个最多跟随者的顶点
    val userId = graph.vertices.filter(_._1 == lengthRDD._1).map(_._2).collect().head
    println("")

    // 输出结果
    println(userId + " has maximum influence on network with " + lengthRDD._2 + " influencers.")
    // **************End**************************

    sparkContext.stop()
  }
}
