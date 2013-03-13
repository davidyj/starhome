package com.example.sample_map.xml;

import java.util.HashMap;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import com.example.sample_map.map.CSampleMapTile;

public class CSampleMapTileHandler extends DefaultHandler {
	private HashMap<String,CSampleMapTile> tiles = null;
	private CSampleMapTile tile = null;
	private String ts = null;
	
	public void setHashMap(HashMap<String,CSampleMapTile> tiles,String ts)
	{
		this.tiles = tiles;  
		this.ts = ts;
	}
	
	@Override
	public void startDocument() throws SAXException {		
	}
	
	@Override
	public void startElement(String uri, String localName, String qName,Attributes attributes) throws SAXException {		
		if ( "t".equals(localName)) {			
			tile = CSampleMapTile.create();
			for(int i=0;i<attributes.getLength();i++){
				tile.setValue(attributes.getLocalName(i), attributes.getValue(i));
			}
			tile.path = String.format("img/Map/Tile/%s.img/%s", ts,tile.img);
		}	
	}
	
	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {		
		if("t".equals(localName)){			
			tiles.put(tile.path, tile);			
		}				
	}
}
