import org.apache.log4j.{Level, Logger}
import org.apache.spark.mllib.linalg.distributed.{CoordinateMatrix, MatrixEntry, RowMatrix}
import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object UserBasedCF {
  def main(args: Array[String]): Unit = {
    Logger.getLogger("org.apache.spark").setLevel(Level.ERROR)
    Logger.getLogger("org.eclipse.jetty.server").setLevel(Level.OFF)
    // 创建一个SparkContext
    val conf = new SparkConf().setAppName("UserBasedCF").setMaster("local")
    val sc = new SparkContext(conf)
    // 读入数据
    val data = sc.textFile("/root/data/als/ratingdata.txt")
    // 解析出评分矩阵的每一行
    val parseData: RDD[MatrixEntry] = data.map(_.split(",")
    match { case Array(user, item, rate) =>
        MatrixEntry(user.toLong, item.toLong, rate.toDouble)
    })
    // 构建关联矩阵
    val ratings = new CoordinateMatrix(parseData)

    // 转置矩阵以计算列(用户)的相似性
    val matrix: RowMatrix = ratings.transpose().toRowMatrix()

    // 计算得到用户的相似度矩阵
    val similarities = matrix.columnSimilarities()

    // 得到某个用户对所有物品的评分
    val ratingOfUser1 = ratings.entries.filter(_.i == 1).
      map(x => (x.j, x.value)).
      sortBy(_._1).
      map(_._1).
      collect().
      toList.
      toArray

    // 得到用户1相对于其他用户的相似性
    val similarityOfUser1 = similarities.entries.filter(_.i == 1).
      sortBy(_.value, false).
      map(_.value).
      collect

    // 需求：为用户1推荐2个商品
    // 思路：找到与用户1相似性最高的两个用户，将这两个用户评过分的物品，用户1没有评过分的物品推荐给用户1
    /********** begin **********/

    //找到与用户1相似性最高的两个用户
    val similarityTopUser = similarities.entries.filter(_.i == 1).
      sortBy(_.value, false).
      map(x=>(x.j, x.value)).
      collect.
      take(2)
    //println("与用户1最相似的两个用户如下：")
    //取消以下2行注释
	for (s <- similarityTopUser) print(s._1 + " ")
    
	for (s <- similarityTopUser) {
      // 找到这两个用户评过分的商品，与用户1没有评过分的物品
      val userId = s._1
      val ratingOfTemp = ratings.entries.filter(_.i == userId).
        map(x => (x.j, x.value)).
        sortBy(_._1).
        map(_._1).
        collect().
        toList.
        toArray
      // 用户1与当前用户求差集
      val dis = ratingOfTemp diff ratingOfUser1
      //println("用户" + userId + "要推荐给用户1的商品id为")
      for (id <- dis) print(id + " ")
    }
    
	/********** end **********/

    sc.stop()
  }
}
