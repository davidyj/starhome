package com.example.sample_map.xml;

import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.cocos2d.nodes.Director;
import org.xml.sax.SAXException;

import com.example.sample_map.map.CSampleMap;


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
	   // ����SAXParser������
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
	   // ʵ���� DefaultHandler����
		CSampleMapXmlHandler parseXml = new CSampleMapXmlHandler();	   
	   
	   InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
	   // ����parse()����
	   if (inputStream != null) {
	    parser.parse(inputStream, parseXml);	   
	    return parseXml.getMap();
	   }	   
	   return null;	
	}
}
