package com.example.sample_map.xml;

import java.util.HashMap;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;


import com.example.sample_map.map.CSampleMapObj;

public class CSampleMapObjHandler extends DefaultHandler {
	
	private HashMap<String,CSampleMapObj> objs = null;
	private CSampleMapObj obj = null;
	
	public void setHashMap(HashMap<String,CSampleMapObj> objs)
	{
		this.objs = objs;  
	}
	
	@Override
	public void startDocument() throws SAXException {		
	}
	
	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if ( "i".equals(localName)) {			
			obj = CSampleMapObj.create();
			for(int i=0;i<attributes.getLength();i++){
				obj.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}
		}	
	}
	
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {		
		if("i".equals(localName)){
			objs.put(obj.img, obj);
			obj = null;
		}				
	}
}
