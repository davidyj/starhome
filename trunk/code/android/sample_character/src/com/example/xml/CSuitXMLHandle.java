package com.example.xml;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.example.core.CSuitMgr;

public class CSuitXMLHandle extends DefaultHandler {
	
	private String name = null;	
	private String type = null;
	private String img = null;
	
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {	
		
	}

	@Override
	public void startDocument() throws SAXException {
		
	}

	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if ( "item".equals(localName)) {			
			name = attributes.getValue("name");			
		}	
		else if("e".equals(localName)){
			type = attributes.getValue("type");
			img = attributes.getValue("url");	
			CSuitMgr.getInstance().add(name, type, img);
		}	
	}
}
