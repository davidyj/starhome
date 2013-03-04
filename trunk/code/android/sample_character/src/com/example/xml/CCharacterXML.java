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
	
	
	public static synchronized CCharacterXML getInstance(){ 
		if(instance==null){ 
			instance=new CCharacterXML(); 
		} 
			return instance;			
	} 	
	
	public CCharecter readBody(String filepath) throws SAXException, ParserConfigurationException, IOException
	{
	   // 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
	   // 实例化 DefaultHandler对象
	   CCharacterBodyXMLHandler parseXml = new CCharacterBodyXMLHandler();	   
	   
	   InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
	   // 调用parse()方法
	   if (inputStream != null) {
	    parser.parse(inputStream, parseXml);
		
	    return parseXml.character();	    
	   }	   
	   return null;	
	}
	
	public void readHead(CCharecter character,String filepath) throws ParserConfigurationException, SAXException, IOException{
		// 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
		// 实例化 DefaultHandler对象
		CCharacterHeadXMLHandler parseXml = new CCharacterHeadXMLHandler();	   
	   
		InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
		// 调用parse()方法
		if (inputStream != null) {
			parseXml.setCharacter(character);
			parser.parse(inputStream, parseXml);
		}   	
	}
	
	public void readFace(String filepath) throws ParserConfigurationException, SAXException, IOException{
		// 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
		// 实例化 DefaultHandler对象
		CCharacterFaceXMLHandler parseXml = new CCharacterFaceXMLHandler();	   
	   
		InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
		// 调用parse()方法
		if (inputStream != null) {			
			parser.parse(inputStream, parseXml);
		}   	
	}
	
	public void readHair(CCharecter character,String filepath) throws ParserConfigurationException, SAXException, IOException{
		// 构建SAXParser解析器
		SAXParser parser = SAXParserFactory.newInstance().newSAXParser();
		// 实例化 DefaultHandler对象
		CCharacterHairXMLHandler parseXml = new CCharacterHairXMLHandler();	   
	   
		InputStream inputStream = Director.sharedDirector().getActivity().getAssets().open(filepath);
		// 调用parse()方法
		if (inputStream != null) {	
			parseXml.setFile(filepath);
			parseXml.setCharacter(character);
			parser.parse(inputStream, parseXml);
		}   	
	}
}
