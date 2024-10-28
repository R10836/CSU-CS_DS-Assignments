import org.apache.spark.ml.evaluation.RegressionEvaluator
import org.apache.spark.ml.recommendation.ALS
import org.apache.spark.sql.{DataFrame, SparkSession}

object ALS {
  case class Rating(userId: Int, movieId: Int, rating: Float)
  def parseRating(str: String): Rating = {
    val fields = str.split(",")
    assert(fields.size == 3)
    Rating(fields(0).toInt, fields(1).toInt, fields(2).toFloat)
  }

  def main(args: Array[String]) {
    val spark = SparkSession
      .builder
      .master("local")
      .appName("ALS")
      .getOrCreate()
    import spark.implicits._

    val ratings = spark.read.textFile("data/als/ratingdata.txt")
      .map(parseRating)
      .toDF()
    val Array(training, test) = ratings.randomSplit(Array(0.8, 0.2))
	/********** begin **********/
    // Build the recommendation model using ALS on the training data
	
    val als = new ALS()  
      .setMaxIter(5)  
      .setRegParam(0.01)  
      .setUserCol("userId")  
      .setItemCol("movieId")  
      .setRatingCol("rating")  
    val model = als.fit(training) 
    

	/********** end **********/
    // "Evaluate the model by computing the RMSE on the test data"
    // "Note we set cold start strategy to 'drop' to ensure we don't get NaN evaluation metrics"
    //取消以下3行注释
	  model.setColdStartStrategy("drop")
    val predictions = model.transform(test)
    evaluatingRMSE(predictions)
    spark.stop()
  }
  def evaluatingRMSE(predictions:DataFrame):Unit = {
    val evaluator = new RegressionEvaluator()
      .setMetricName("rmse")
      .setLabelCol("rating")
      .setPredictionCol("prediction")
    val rmse = evaluator.evaluate(predictions)
    if (rmse <= 2){
      print("\n" + "good")
    }else{
	  println()
      predictions.show(false)
    }
  }
}