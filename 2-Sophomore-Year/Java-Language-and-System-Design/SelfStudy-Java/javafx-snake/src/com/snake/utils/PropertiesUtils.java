package com.snake.utils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class PropertiesUtils extends Properties{
	
	private static final long serialVersionUID = -4016165126226123907L;

	private PropertiesUtils(){
		
		InputStream is = null;
		
		try {
			is = PropertiesUtils.class.getResourceAsStream("/score.properties");
			this.load(is);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private static PropertiesUtils instance = null;
	
	public static PropertiesUtils getInstance(){
		
		if(instance == null){
			synchronized (PropertiesUtils.class) {
				if(instance == null){
					instance = new PropertiesUtils();
				}
			}
		}
		return instance;
	}
}
