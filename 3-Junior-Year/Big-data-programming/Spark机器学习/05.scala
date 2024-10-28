import org.apache.spark.ml.Pipeline
import org.apache.spark.ml.classification.MultilayerPerceptronClassifier
import org.apache.spark.ml.evaluation.BinaryClassificationEvaluator
import org.apache.spark.ml.feature.{IndexToString, StringIndexer, Word2Vec}
import org.apache.spark.sql.{DataFrame,SparkSession}

object SMSClassifier {
  final val VECTOR_SIZE = 100

  def evaluatingAUC(predictedResultDF:DataFrame, labelcol: String):Unit = {
    val evaluator = new BinaryClassificationEvaluator().setLabelCol(labelcol).setRawPredictionCol("prediction")
    val predictionAUC = evaluator.setMetricName("areaUnderROC").evaluate(predictedResultDF)
    if(predictionAUC > 0.8){
      print("\n" + "good")
    }else{
      print(s"areaUnderROC: $predictionAUC")
    }
  }

  def main(args: Array[String]) {

    val spark = SparkSession
      .builder
      .master("local")
      .appName("SMS Message Classification (HAM or SPAM)")
      .getOrCreate()

    val parsedRDD = spark.sparkContext.textFile("data/smsspamcollection/SMSSpamCollection").map(_.split("\t")).map(eachRow => {
      (eachRow(0),eachRow(1).split(" "))
    })

    val msgDF = spark.createDataFrame(parsedRDD).toDF("label","message")

    val labelIndexer = new StringIndexer()
      .setInputCol("label")
      .setOutputCol("indexedLabel")
      .fit(msgDF)

	/********** begin **********/
    val word2Vec =  new Word2Vec()  
      .setInputCol("message")  
      .setOutputCol("features")  
      .setVectorSize(VECTOR_SIZE)  
      .setMinCount(1)  
	
	/********** end **********/

    val layers = Array[Int](VECTOR_SIZE,6,5,2)
	
	/********** begin **********/
    val mlpc = new MultilayerPerceptronClassifier()  
      .setLayers(layers)  
      .setBlockSize(512)  
      .setSeed(1234L)  
      .setMaxIter(128)  
      .setFeaturesCol("features")  
      .setLabelCol("indexedLabel")  
      .setPredictionCol("prediction") 


	/********** end **********/

    val labelConverter = new IndexToString()
      .setInputCol("prediction")
      .setOutputCol("predictedLabel")
      .setLabels(labelIndexer.labels)

    val Array(trainingData, testData) = msgDF.randomSplit(Array(0.8, 0.2))

	/********** begin **********/
    val pipeline = new Pipeline().setStages(Array(labelIndexer,word2Vec,mlpc,labelConverter))  
    val model = pipeline.fit(trainingData)  

	
	/********** end **********/
  
    //取消以下两行注释
	val predictionResultDF = model.transform(testData)
    evaluatingAUC(predictionResultDF,"indexedLabel")
    spark.stop()
  }
}
