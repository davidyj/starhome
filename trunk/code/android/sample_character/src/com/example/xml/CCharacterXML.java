package com.example.xml;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.cocos2d.nodes.Director;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.example.core.CCore;

import com.example.core.*;
import com.example.nodes.CCharecter;

public class CCharacterXML {

	private static CCharacterXML instance=null;
	private SAXParser parser = null;
	
	public static synchronized CCharacterXML getInstance(){ 
		if(instance==null){ 
			instance=new CCharacterXML(); 
		} 
			return instance;			
	} 	
	
	public CCharecter Read(String filepath) throws SAXException, ParserConfigurationException, IOException
	{
	   // 构建SAXParser解析器
	   parser = SAXParserFactory.newInstance().newSAXParser();
	   // 实例化 DefaultHandler对象
	   CCharacterXMLHandler parseXml = new CCharacterXMLHandler();	   
	   
	   InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
	   // 调用parse()方法
	   if (inputStream != null) {
	    parser.parse(inputStream, parseXml);
		
		return parseXml.character();	
	   }
	   return null;	
	}
}
