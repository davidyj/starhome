package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharecter;

public class CCharacterGloveXMLHandler extends DefaultHandler {
	private CCharecter 			character  	= null;		
	private CCharacterPart		parts		= null;
	private CCharacterFrame 	frames		= null;
	
		
	private String file = null;
	private String[] tfile = null;
	
	private String stag = null;	
	private String ftag = null;
			
	public void setCharacter(CCharecter character){
		this.character = character;
	}
	
	public CCharecter character(){
		return this.character;
	}
			
	public void setFile(String file){
		this.file = file;
		String[] temp = this.file.split("\\.");
		tfile = temp[0].split("/");
	}
	
	
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		
		if("s".equals(localName)){				
			stag = null;
		}
		else if("f".equals(localName)){
			ftag = null;				
		}
		else if("p".equals(localName)){
			if(parts != null){
				frames.sprites.addSprite(parts.name(), parts);
				parts = null;
			}
		}			
	}

	@Override
	public void startDocument() throws SAXException {
		
	}

	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {
		
		if ( "s".equals(localName)) {			
			stag = attributes.getValue("name");			
			if("info".equals(stag) == true)
				return;			
			
		}	
		else if("f".equals(localName)){
			ftag = attributes.getValue("name");
			if("info".equals(stag))
				return;
			frames = character.getFrame(stag, ftag);								
		}
		else if("p".equals(localName)){
			if("info".equals(attributes.getValue("name")) || "reqJob".equals(attributes.getValue("name")))
					return;
			String filepath = String.format("img/Character/%s/%s/",tfile[2],tfile[3]);			
			parts = CCharacterPart.create(filepath);
			for(int i=0;i<attributes.getLength();i++){
				parts.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}				
		}
		
	}
}
