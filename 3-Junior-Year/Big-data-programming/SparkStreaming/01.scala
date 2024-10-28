import org.apache.spark.SparkConf
import org.apache.spark.streaming.StreamingContext
import org.apache.spark.streaming.Seconds

object TransformBlackList {
  def main(args: Array[String]): Unit = {
    /********** Begin **********/
    // 初始化
    val sparkConf = new SparkConf().setMaster("local[2]").setAppName("TransformBlackList")
    // 创建StreamingContext，设置每五秒秒刷新一次
    val ssc = new StreamingContext(sparkConf, Seconds(5))
    ssc.sparkContext.setLogLevel("error")
    // 设置需要过滤的黑名单（Abby、Paige、Carla、Mary、Ken）
    val blackList = Array("Abby", "Paige", "Carla", "Mary", "Ken")
    // 把黑名单数组转换成rdd
    val blackListRdd = ssc.sparkContext.parallelize(blackList, 3)
    // 设置主机名localhost，端口号5566
    val nameList = ssc.socketTextStream("localhost", 5566)
    // 过滤黑名单算法
    val validName = nameList.filter(x => !blackList.contains(x))
    validName.print()
    ssc.start()
    Thread.sleep(5000)
    ssc.stop(false, false)
    sys.exit(0)
    /********** End **********/
  }
}
