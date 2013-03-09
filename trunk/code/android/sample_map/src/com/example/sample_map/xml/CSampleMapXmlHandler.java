package com.example.sample_map.xml;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.R.string;

import com.example.sample_map.map.CSampleMap;
import com.example.sample_map.map.CSampleMapObj;
import com.example.sample_map.map.CSampleMapTile;

public class CSampleMapXmlHandler extends DefaultHandler {
	
	private CSampleMap map = null;
	private String layertag = null;
	private CSampleMapObj obj = null;
	private CSampleMapTile tile = null;
	private String layerindex = null;
	
	public CSampleMap getMap(){
		return map; 
	}
	
	
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {		
		if("i".equals(localName)){				
		
		}
		else if("t".equals(localName)){
			map.addTile(Integer.valueOf(layerindex), tile);
		}
		else if("o".equals(localName)){			
			try {
				map.addObj(obj);
			} catch (NumberFormatException e) {
				e.printStackTrace();
			} catch (ParserConfigurationException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}			
	}

	@Override
	public void startDocument() throws SAXException {
		map = CSampleMap.create();
	}

	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if ( "info".equals(localName)) {			
			for(int i=0;i<attributes.getLength();i++){
				map.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}
			map.setValueEnd();
		}	
		else if("o".equals(localName)){
			// load obj
			obj = CSampleMapObj.create();
			for(int i=0;i<attributes.getLength();i++){
				obj.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}
		}
		else if("t".equals(localName)){
			// load obj
			tile = CSampleMapTile.create();
			for(int i=0;i<attributes.getLength();i++){
				tile.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}
		}
		else if("back".equals(localName)){
			
		}
		else if("life".equals(localName)){
				
		}
		else if("reactor".equals(localName)){
			
		}
		else if("layer".equals(localName)){
			layerindex = attributes.getValue("name");
		}
		else if("tile".equals(localName)){
			
		}
		else if("obj".equals(localName)){
			
		}
		else if("foothold".equals(localName)){
			
		}
		else if("ladderRope".equals(localName)){
			
		}
		else if("miniMap".equals(localName)){
			
		}
	}
}
