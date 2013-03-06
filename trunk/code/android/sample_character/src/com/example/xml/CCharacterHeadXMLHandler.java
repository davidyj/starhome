package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.actions.interval.CCharacterAnimate;
import com.example.nodes.CCharacterAnimation;
import com.example.nodes.CCharacterFrame;
import com.example.nodes.CCharacterPart;
import com.example.nodes.CCharecter;

public class CCharacterHeadXMLHandler extends DefaultHandler {
	private CCharecter 			character  	= null;		
	private CCharacterPart		parts		= null;
	private CCharacterFrame 	frames		= null;
	private CCharacterAnimation animation 	= null;
	
	
	private CCharacterPart		backhead	= null;
	private CCharacterPart		fronthead	= null;
	
	private String anitag = null;
	private String stag = null;	
			
	public void setCharacter(CCharecter character){
		this.character = character;
	}
	
	public CCharecter character(){
		return this.character;
	}
			
	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
			
	}

	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		
		if("s".equals(localName)){
			if(animation != null)
				character.addAnimate(animation);			
			stag = null;
		}
		else if("f".equals(localName)){
			if(null != frames)
				animation.addFrame(frames);				
		}
		else if("p".equals(localName)){
			if(parts != null)
				frames.sprites.addSprite(parts.name(), parts);
		}			
	}

	@Override
	public void startDocument() throws SAXException {
		
	}

	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {
		
		if ( "s".equals(localName)) {			
			stag = attributes.getValue("name");
			anitag = stag;
			if("info".equals(stag) == true || ("front".equals(stag) == true) || ("back".equals(stag) == true))
				return;			
			animation = character.getAnimation(attributes.getValue("name"));			
		}	
		else if("f".equals(localName)){
			if("head".equals(attributes.getValue("name")))
				return;
			frames = character.getFrame(anitag, attributes.getValue("name"));								
		}
		else if("p".equals(localName)){
			if("front".equals(stag)){
				fronthead = CCharacterPart.create("img/Character/00012000/");
				for(int i=0;i<attributes.getLength();i++){
					fronthead.setValue(attributes.getLocalName(i), attributes.getValue(i));
				}
				stag = null;
			}
			else if("back".equals(stag)){
				backhead = CCharacterPart.create("img/Character/00012000/");
				for(int i=0;i<attributes.getLength();i++){
					backhead.setValue(attributes.getLocalName(i), attributes.getValue(i));
				}
				stag = null;
			}
			else{				
				if("front/head".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(fronthead);
					parts.setName("head");
					
				}
				else if("back/head".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(backhead);
					parts.setName("head");
				}
				else if("prone/0/head".equals(attributes.getValue("pointer"))){
					parts = CCharacterPart.create(backhead);
					parts.setName("head");
				}
			}
		}
		
	}
	
}
