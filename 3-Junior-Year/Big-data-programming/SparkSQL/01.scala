import org.apache.spark.sql.{Row, SparkSession}
import org.apache.spark.sql.types._
import scala.collection.mutable
import java.text.SimpleDateFormat

object sparkSQL01 {

  def main(args: Array[String]): Unit = {

    val spark = SparkSession
      .builder()
      .master("local")
      .appName("test")
      .config("spark.sql.shuffle.partitions", "5")
      .getOrCreate()

    val studentRDD = spark.sparkContext.textFile("data/student.txt")

    val StudentSchema: StructType = StructType(mutable.ArraySeq(
      StructField("Sno", StringType, nullable = false),
      StructField("Sname", StringType, nullable = false),
      StructField("Ssex", StringType, nullable = false),
      StructField("Sbirthday", StringType, nullable = true),
      StructField("SClass", StringType, nullable = true)))
      
    val studentData = studentRDD.map(_.split(",")).map(attributes => Row(
      attributes(0),
      attributes(1),
      attributes(2),
      attributes(3),
      attributes(4)))
      
    val studentDF = spark.createDataFrame(studentData, StudentSchema)
    studentDF.createOrReplaceTempView("student")

    val teacherRDD = spark.sparkContext.textFile("data/teacher.txt")
    
    val TeacherSchema: StructType = StructType(mutable.ArraySeq(
      StructField("Tno", StringType, nullable = false),
      StructField("Tname", StringType, nullable = false),
      StructField("Tsex", StringType, nullable = false),
      StructField("Tyear", IntegerType, nullable = true),
      StructField("Prof", StringType, nullable = true),
      StructField("Depart", StringType, nullable = false)))
      
    val teacherData = teacherRDD.map(_.split(",")).map(attributes => Row(
      attributes(0),
      attributes(1),
      attributes(2),
      attributes(3).toInt,
      attributes(4),
      attributes(5)))
      
    val teacherDF = spark.createDataFrame(teacherData, TeacherSchema)
    teacherDF.createOrReplaceTempView("teacher")  

    val courseRDD = spark.sparkContext.textFile("data/course.txt")

    val CourseSchema: StructType = StructType(mutable.ArraySeq(
      StructField("Cno", StringType, nullable = false),
      StructField("Cname", StringType, nullable = false),
      StructField("Tno", StringType, nullable = false)))
      
    val courseData = courseRDD.map(_.split(",")).map(attributes => Row(
      attributes(0),
      attributes(1),
      attributes(2)))
      
    val courseDF = spark.createDataFrame(courseData,CourseSchema)
    courseDF.createOrReplaceTempView("course")

    val scoreRDD = spark.sparkContext.textFile("data/score.txt")

    val ScoreSchema: StructType = StructType(mutable.ArraySeq(
      StructField("Sno", StringType, nullable = false),
      StructField("Cno", StringType, nullable = false),
      StructField("Degree", IntegerType, nullable = true)))
      
    val scoreData = scoreRDD.map(_.split(",")).map(attributes => Row(
      attributes(0),
      attributes(1),
      attributes(2).toInt))
      
    val scoreDF = spark.createDataFrame(scoreData,ScoreSchema)
    scoreDF.createOrReplaceTempView("score")

    spark.sql("SELECT * FROM student ORDER BY Sno").show()

    spark.sql(
      """
        |SELECT tname AS tname, prof AS prof
        |FROM teacher
        |WHERE Prof NOT IN (
        |  SELECT a.Prof 
        |  FROM (
        |    SELECT Prof 
        |    FROM teacher 
        |    WHERE Depart = 'department of computer'
        |  ) a
        |  JOIN (
        |    SELECT Prof 
        |    FROM teacher 
        |    WHERE Depart = 'department of electronic engineering'
        |  ) b ON a.Prof = b.Prof
        |)
        |ORDER BY tname
      """.stripMargin).show(false)

    teacherDF.filter("Tsex = 'female'").show(false)

    teacherDF.select("Depart").distinct().show(false)

    val maxSc = scoreDF.agg("Degree" -> "max").show()

    val meanSc = scoreDF.groupBy("Cno").agg("Degree" -> "avg").orderBy("Cno").show()
  }
}