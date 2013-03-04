package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.actions.interval.CCharacterAnimate;
import com.example.core.CCore;
import com.example.nodes.CCharacterDefine;
import com.example.nodes.CCharacterAnimation;
import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharacterSprite;
import com.example.nodes.CCharecter;

//该类负责解析 xml 数据
public class CCharacterBodyXMLHandler extends DefaultHandler{
	
		private CCharecter 			character  	= null;		
		private CCharacterPart		parts		= null;
		private CCharacterFrame 	frames		= null;
		private CCharacterAnimation animation 	= null;
		private CCharacterAnimate 	animate 	= null;
		
		private String stag = null;	
				
		
		public CCharecter character(){
			return this.character;
		}
				
		@Override
		public void characters(char[] ch, int start, int length) throws SAXException {
				
		}

		@Override
		public void endElement(String uri, String localName, String qName) throws SAXException {
			Log.i("endElement",localName);
			if("s".equals(localName)){
				if("info".equals(stag) == false){
					character.addAnimate(animation);
				}
				stag = null;
			}
			else if("f".equals(localName)){
				animation.addFrame(frames);				
			}
			else if("p".equals(localName)){
				frames.sprites.addSprite(parts.name(), parts);
			}			
		}

		@Override
		public void startDocument() throws SAXException {
			character = CCharecter.create();
		}

		@Override
		public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {
			Log.i("startElement",localName);
			if ( "s".equals(localName)) {				
				if("info".equals(attributes.getValue("name")) != true){
					animation = CCharacterAnimation.create(attributes.getValue("name"));
				}				
				stag = attributes.getValue("name");
			}	
			else if("f".equals(localName)){
				frames = CCharacterFrame.create(attributes.getValue("name"));								
			}
			else if("p".equals(localName)){			
				parts = CCharacterPart.create("img/Character/00002000/");
				for(int i=0;i<attributes.getLength();i++){
					parts.setValue(attributes.getLocalName(i), attributes.getValue(i));
				}
			}
			
		}
		
	}