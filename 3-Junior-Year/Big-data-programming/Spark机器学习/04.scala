import org.apache.spark.rdd.RDD
import org.apache.spark.sql.{DataFrame,SparkSession}
import org.apache.spark.ml.classification.RandomForestClassifier
import org.apache.spark.ml.evaluation.BinaryClassificationEvaluator
import org.apache.spark.ml.feature.StringIndexer
import org.apache.spark.ml.feature.VectorAssembler
import org.apache.spark.ml.tuning.{CrossValidator, ParamGridBuilder}
import org.apache.spark.ml.{Pipeline, PipelineStage}
import org.apache.spark.mllib.evaluation.RegressionMetrics
object Credit {
  case class Credit(
                     creditability: Double,
                     balance: Double, duration: Double, history: Double, purpose: Double, amount: Double,
                     savings: Double, employment: Double, instPercent: Double, sexMarried: Double, guarantors: Double,
                     residenceDuration: Double, assets: Double, age: Double, concCredit: Double, apartment: Double,
                     credits: Double, occupation: Double, dependents: Double, hasPhone: Double, foreign: Double
                   )

  def parseCredit(line: Array[Double]): Credit = {
    Credit(
      line(0),
      line(1) - 1, line(2), line(3), line(4), line(5),
      line(6) - 1, line(7) - 1, line(8), line(9) - 1, line(10) - 1,
      line(11) - 1, line(12) - 1, line(13), line(14) - 1, line(15) - 1,
      line(16) - 1, line(17) - 1, line(18) - 1, line(19) - 1, line(20) - 1
    )
  }

  def parseRDD(rdd: RDD[String]): RDD[Array[Double]] = {
    rdd.map(_.split(",")).map(_.map(_.toDouble))
  }

  def evaluatingAUC(predictedResultDF:DataFrame, labelstring:String):Unit = {
	val evaluator = new BinaryClassificationEvaluator().setLabelCol(labelstring).setRawPredictionCol("prediction")
    val predictionAUC = evaluator.setMetricName("areaUnderROC").evaluate(predictedResultDF)
    if(predictionAUC > 0.6){
		print("\n" + "good")
	}else{
		print(s"areaUnderROC: $predictionAUC")
	}
  }

  def main(args: Array[String]) {

    val spark = SparkSession
      .builder
      .appName("Credit")
      .master("local")
      .getOrCreate()

    import spark.implicits._
    val creditDF = parseRDD(spark.sparkContext.textFile("/root/data/germancredit.csv")).map(parseCredit).toDF()
    creditDF.createTempView("credit")
	
    val featureCols = Array("balance", "duration", "history", "purpose", "amount",
      "savings", "employment", "instPercent", "sexMarried", "guarantors",
      "residenceDuration", "assets", "age", "concCredit", "apartment",
      "credits", "occupation", "dependents", "hasPhone", "foreign")

	/********** begin **********/
    
	// 合并特征列。
	val assembler = new VectorAssembler().setInputCols(featureCols).setOutputCol("features")  
	val df2 = assembler.transform(creditDF)
	
	/********** end **********/

	//取消以下4行注释
    val labelIndexer = new StringIndexer().setInputCol("creditability").setOutputCol("label")
    val df3 = labelIndexer.fit(df2).transform(df2)
    val splitSeed = 5043
    val Array(trainingData, testData) = df3.randomSplit(Array(0.7, 0.3), splitSeed)

	/********** begin **********/
	
	//调用随机森林API，使用trainingData训练生成模型model
    val classifier =  new RandomForestClassifier().setImpurity("gini").setMaxDepth(5).setNumTrees(20).setFeatureSubsetStrategy("auto").setSeed(5043)  
    val model = classifier.fit(trainingData)  
	
	/********** end **********/

	//取消以下2行注释
    val predictions = model.transform(testData)
	evaluatingAUC(predictions,"label")
    spark.stop()
  }
}
