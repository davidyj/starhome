package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharecter;

public class CCharacterCapXMLHandler extends DefaultHandler {
	private CCharecter 			character  	= null;		
	private CCharacterPart		parts		= null;
	private CCharacterFrame 	frames		= null;	
	
	private CCharacterPart		cap		= null;	
	private CCharacterPart		capac	= null;
	private CCharacterPart		backcap	= null;	
	
	private String file = null;
	private String[] tfile = null;
	private String ftag = null;
	private String stag = null;	
			
	public void setCharacter(CCharecter character){
		this.character = character;
	}
	
	public void setFile(String file){
		this.file = file;
		String[] temp = this.file.split("\\.");
		tfile = temp[0].split("/");
	}
	
	public CCharecter character(){
		return this.character;
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
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if ( "s".equals(localName)) {			
			stag = attributes.getValue("name");			
			if("info".equals(stag) == true || ("default".equals(stag) == true) || ("backDefault".equals(stag) == true))
				return;				
		}	
		else if("f".equals(localName)){
			ftag = attributes.getValue("name");
			if("default".equals(ftag)|| "defaultAc".equals(ftag))
				return;
			frames = character.getFrame(stag, ftag);								
		}
		else if("p".equals(localName)){
			String filepath = String.format("img/Character/Cap/%s/",tfile[3]);			
			if("default".equals(stag)){				
				if("default".equals(ftag)){
					cap = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						cap.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}
				else if("defaultAc".equals(ftag)){
					capac = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						capac.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}							
			}
			else if("backDefault".equals(stag)){				
				backcap = CCharacterPart.create(filepath);
				for(int i=0;i<attributes.getLength();i++){
					backcap.setValue(attributes.getLocalName(i), attributes.getValue(i));
				}							
			}
			else{				
				if("default/default".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(cap);
					parts.setName("cap");					
				}
				else if("default/defaultAc".equals(attributes.getValue("pointer"))){
					//parts = CCharacterPart.create(capac);
					//parts.setName("cap");
				}				
				else if("backDefault/default".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(backcap);
					parts.setName("cap");
				}				
			}
		}
		
	}
}
