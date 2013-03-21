package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.example.nodes.CCharacterFace;
import com.example.nodes.CCharacterPart;

public class CCharacterFaceXMLHandler extends DefaultHandler {
			
	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
			
	}

	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {		
	}

	@Override
	public void startDocument() throws SAXException {
		
	}

	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if("p".equals(localName)){
			if("default".equals(attributes.getValue("name")))
				return;				
			CCharacterPart	parts = CCharacterPart.create("img/Character/Face/00020000/");
			for(int i=0;i<attributes.getLength();i++){
				parts.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}		
			CCharacterFace.getInstance().addFace(parts.name(), parts);
		}		
	}
}
