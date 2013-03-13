package com.example.sample_map.xml;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.cocos2d.nodes.Director;
import org.xml.sax.SAXException;

import com.example.sample_map.map.CSampleMap;
import com.example.sample_map.map.CSampleMapObj;
import com.example.sample_map.map.CSampleMapTile;

public class CSampleMapXml {
	private static CSampleMapXml instance=null;	 	
	
	public static synchronized CSampleMapXml getInstance(){ 
		if(instance==null){ 
			instance=new CSampleMapXml(); 
		} 
			return instance;			
	} 	
	
	public CSampleMap read(String filepath) throws SAXException, ParserConfigurationException, IOException
	{
	   // 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
	   // 实例化 DefaultHandler对象
		CSampleMapXmlHandler parseXml = new CSampleMapXmlHandler();	   
	   
	   InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
	   // 调用parse()方法
	   if (inputStream != null) {
	    parser.parse(inputStream, parseXml);	   
	    return parseXml.getMap();
	   }	   
	   return null;
	}	

	
	public void readObj(HashMap<String,CSampleMapObj> objs,String filepath) throws SAXException, ParserConfigurationException, IOException
	{
	   // 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
	   // 实例化 DefaultHandler对象
		CSampleMapObjHandler parseXml = new CSampleMapObjHandler();	   
		
		parseXml.setHashMap(objs);
		
		InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
		
	   // 调用parse()方法
		if (inputStream != null) {			
			parser.parse(inputStream, parseXml);		
		}   		
	}
	
	public void readTile(HashMap<String,CSampleMapTile> tiles,String filepath,String ts) throws SAXException, ParserConfigurationException, IOException
	{
	   // 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
	   // 实例化 DefaultHandler对象
		CSampleMapTileHandler parseXml = new CSampleMapTileHandler();	   
		
		parseXml.setHashMap(tiles,ts);
		
		InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
		
	   // 调用parse()方法
		if (inputStream != null) {			
			parser.parse(inputStream, parseXml);		
		}   		
	}
}
