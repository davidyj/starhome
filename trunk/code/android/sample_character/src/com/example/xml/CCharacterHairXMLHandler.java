package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharecter;

public class CCharacterHairXMLHandler extends DefaultHandler {
	private CCharecter 			character  	= null;		
	private CCharacterPart		parts		= null;
	private CCharacterFrame 	frames		= null;
	
	private CCharacterPart		hairoverhead = null;
	private CCharacterPart		hair		= null;
	private CCharacterPart		hairshade	= null;
	private CCharacterPart		backhair	= null;
	private CCharacterPart		backhairbelowcap = null;
	
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
			if("hairOverHead".equals(ftag)|| "hair".equals(ftag) || "hairShade".equals(ftag) || "backHair".equals(ftag) || "backHairBelowCap".equals(ftag))
				return;
			frames = character.getFrame(stag, ftag);								
		}
		else if("p".equals(localName)){
			String filepath = String.format("img/Character/Hair/%s/",tfile[3]);			
			if("default".equals(stag)){				
				if("hairOverHead".equals(ftag)){
					hairoverhead = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						hairoverhead.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}
				else if("hair".equals(ftag)){
					hair = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						hair.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}
				else if("hairShape".equals(ftag)){
					hairshade = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						hairshade.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}				
			}
			else if("backDefault".equals(stag)){				
				if("backHair".equals(ftag)){
					backhair = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						backhair.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}
				else if("backHairBelowCap".equals(ftag)){
					backhairbelowcap = CCharacterPart.create(filepath);
					for(int i=0;i<attributes.getLength();i++){
						backhairbelowcap.setValue(attributes.getLocalName(i), attributes.getValue(i));
					}
				}				
			}
			else{				
				if("default/hairOverHead".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(hairoverhead);
					parts.setName("hair");					
				}
				else if("default/hair".equals(attributes.getValue("pointer"))){
					//parts = CCharacterPart.create(hair);
					//parts.setName("hair");
				}
				//else if("default/hairShade".equals(attributes.getValue("pointer"))){
				//	parts = CCharacterPart.create(hairshade);
				//	parts.setName("hair");
				//}
				else if("backDefault/backHair".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(backhair);
					parts.setName("hair");
				}
				//else if("backDefault/backHairBelowCap".equals(attributes.getValue("pointer"))){
					//parts = CCharacterPart.create(backhairbelowcap);
					//parts.setName("hair");
				//}
			}
		}
		
	}
}
