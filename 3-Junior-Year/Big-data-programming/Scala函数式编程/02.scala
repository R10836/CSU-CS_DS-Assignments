object TestSort{
    def main(args:Array[String]){  
       val pairs = Array(
            ("Cathy",  100,  110,  108,  78,  95,  89),
            ("Daniel",  110,  98,  110,  80, 94, 88),
            ("Andy",   105,  120,  115, 85,	 90, 95) )
 
        //**************Begin**************************
        //构造新数组（姓名，三科总分，六科总分）
        val newData = pairs.map { case (name, chinese, math, english, physics, chemistry, biology) =>
          val totalScore = chinese + math + english
          val totalScoreAll = chinese + math + english + physics + chemistry + biology
          (name, totalScore, totalScoreAll)
        }
				
		//排序
        val sortedData = newData.sortWith { case ((name1, totalScore1, totalScoreAll1), (name2, totalScore2, totalScoreAll2)) =>
          if (totalScore1 != totalScore2) {
            totalScore1 > totalScore2 // 按总分降序排序
          } else if (totalScoreAll1 != totalScoreAll2) {
            totalScoreAll1 > totalScoreAll2 // 若总分相同，则按语数英三门总分降序排序
          } else {
            name1 < name2 // 若三门总分仍然相同，则按姓名升序排序
          }
        }
	   
       //打印结果
       sortedData.foreach { case (name, totalScore, totalScoreAll) =>
          println(s"($name,$totalScore,$totalScoreAll)")
       }
	  //**************End**************************
    }
}
