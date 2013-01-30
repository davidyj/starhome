/**
 ****************************************************************************
 * <P> McbXML.c - implementation file for basic XML parser written in ANSI C 
 * for portability.
 * It works by using recursion and a node tree for breaking down the elements
 * of an XML document.  </P>
 *
 * @version     V1.0
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	21st August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */

/*
 ****************************************************************************
 * Include all necessary include files
 ****************************************************************************
 */
#include "../stdafx.h"
#include "McbXML.h"
#include <memory.h>
#include "platform.h" // Plat_Alloc Plat_Free
//#include "mynew.h" // mynew mydelete
#include "dbg.h" // Assert

// memdbgon must be the last include file in a .cpp file!!!
//#include "memdbgon.h"

static int _issametag( LPCWSTR lpszTokenName, LPCWSTR lpszTokenStr )
{
	// provide default text comparison
	int namelen = wcslen( lpszTokenName );
	int result = _wcsnicmp( lpszTokenName, lpszTokenStr, namelen );
	if ( result == 0 )
	{
		// it seems to be same, so check length of tokenstr
		if ( lpszTokenStr[namelen] == L'>' ||
				lpszTokenStr[namelen] == L'\t' ||
				lpszTokenStr[namelen] == L'\n' ||
				lpszTokenStr[namelen] == L' ' )
			result = 0;
		else
			result = 1;
	}
	return result;
}

	template <typename T>
static T * _extmemset( T * dst, T value, uint count )
{
	T *start = dst;
	while (count--)
		*dst++ = value;
	return(start);
}
/*
 ****************************************************************************
 * Enumeration used to decipher what type a token is
 ****************************************************************************
 */
typedef enum McbTokenType
{
	eTokenText = 0,
	eTokenQuotedText,
	eTokenTagStart,			/* "<"			*/
	eTokenTagEnd,			/* "</"			*/
	eTokenCloseTag,			/* ">"			*/
	eTokenEquals,			/* "="			*/
	eTokenDeclaration,		/* "<?"			*/
	eTokenShortHandClose,	/* "/>"			*/
	eTokenClear,
	eTokenError
} McbTokenType;

typedef struct McbClearTag
{
	LPWSTR lpszOpen;
	LPWSTR lpszClose;

} McbClearTag;

typedef struct McbNextToken
{
	McbClearTag	*pClr;
	LPCWSTR		pStr;
} McbNextToken;

/*
 ****************************************************************************
 * Main structure used for parsing XML
 ****************************************************************************
 */
typedef struct McbXML
{
	LPCWSTR				lpXML;
	int					nIndex;
	enum McbXMLError	error;
	LPCWSTR				lpEndTag;
	int					cbEndTag;
	LPCWSTR				lpNewElement;
	int					cbNewElement;
	int					nFirst;
	McbClearTag			*pClrTags;

} McbXML;

/*
 ****************************************************************************
 * Enumeration used when parsing attributes
 ****************************************************************************
 */
typedef enum McbAttrib
{
	eAttribName = 0,
	eAttribEquals,
	eAttribValue
} McbAttrib;

/*
 ****************************************************************************
 * Enumeration used when parsing elements to dictate whether we are currently
 * inside a tag
 ****************************************************************************
 */
typedef enum McbStatus
{
	eInsideTag = 0,
	eOutsideTag
} McbStatus;

/**
 ****************************************************************************
 * <P> Initialise an element.  </P>
 *
 * @methodName  McbInitElement
 *
 * @param       *pEntry		
 * @param       lpszName		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	14th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbInitElement(McbXMLElement *pEntry, McbXMLElement *pParent, 
		LPWSTR lpszName, int nIsDeclaration)
{
	Assert(pEntry);

	pEntry->nMax = 0;
	pEntry->nSize = 0;
	pEntry->pEntries = NULL;
	pEntry->pParent = pParent;
	pEntry->nIsDeclaration = (nIsDeclaration != 0 ); //by  2009.8.10
	pEntry->lpszName = lpszName;

}/* McbInitElement */

/**
 ****************************************************************************
 * <P> Create the root element.  </P>
 *
 * @methodName  * McbCreateRoot
 *
 * @param       none
 *
 * @return      McbXMLElement
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	1st February  	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbCreateRoot()
{
	McbXMLElement * pElement;

	pElement = (McbXMLElement*)Plat_Alloc(sizeof(McbXMLElement));
	//pElement = (McbXMLElement*)mynew(sizeof(McbXMLElement));
	McbInitElement(pElement, NULL, 0, FALSE);

	return pElement;

}/* McbCreateRoot */

/**
 ****************************************************************************
 * <P> Delete the root element and set it to NULL.  </P>
 *
 * @methodName  McbDeleteRoot
 *
 * @param       ** ppElement		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	1st February  	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteRoot(McbXMLElement * pElement)
{
	McbDeleteElement(pElement);
	Plat_Free(pElement);
	//mydelete(pElement);

}/* McbDeleteRoot */

/**
 ****************************************************************************
 * <P> Delete an attribute.  </P>
 *
 * @methodName  McbDeleteAttribute
 *
 * @param       *pEntry		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	14th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteAttribute(McbXMLAttribute *pEntry)
{
	Assert(pEntry);

	if (pEntry->lpszName) 
	{
		Plat_Free(pEntry->lpszName);
		//mydelete(pEntry->lpszName);
		pEntry->lpszName = NULL;
	}

	if (pEntry->lpszValue) 
	{
		Plat_Free(pEntry->lpszValue);
		//mydelete(pEntry->lpszValue);
		pEntry->lpszValue=  NULL;
	}

}/* McbDeleteAttribute */

/**
 ****************************************************************************
 * <P> Attach attributes from one list to another.  </P>
 *
 * @methodName  McbAttributeAttach
 *
 * @param       *pDst		
 * @param       *pSrc		
 * @param       nNum		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	14th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbAttributeAttach(McbXMLAttribute *pDst, McbXMLAttribute *pSrc, int nNum)
{
	int n;

	for (n=0; n<nNum; n++)
	{
		pDst[n].lpszName = pSrc[n].lpszName;
		pDst[n].lpszValue = pSrc[n].lpszValue;

		pSrc[n].lpszName = NULL;
		pSrc[n].lpszValue = NULL;
	}

}/* McbAttributeAttach */

/**
 ****************************************************************************
 * <P> Obtain the next character from the string.  </P>
 *
 * @methodName  McbGetNextChar
 *
 * @param       *pXML		
 *
 * @return      WCHAR
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	17th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
WCHAR McbGetNextChar(McbXML *pXML)
{
	WCHAR ch;

	ch = pXML->lpXML[pXML->nIndex];

	if (ch != L'\0') pXML->nIndex++;

	return ch;

}/* McbGetNextChar */

/**
 ****************************************************************************
 * <P> Find next non-white space character.  </P>
 *
 * @methodName  McbFindNonWhiteSpace
 *
 * @param       *pXML		
 *
 * @return      WCHAR
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	18th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
WCHAR McbFindNonWhiteSpace(McbXML *pXML)
{
	WCHAR ch = 0;
	int nExit = FALSE;

	Assert(pXML);

	/*
	 *************************************************************************
	 * Iterate through characters in the string until we find a NULL or a
	 * non-white space character
	 *************************************************************************
	 */
	while((nExit == FALSE) && (ch = McbGetNextChar(pXML)))
	{
		switch(ch)
		{
			/*
			 *********************************************************************
			 * Ignore white space
			 *********************************************************************
			 */
			case L'\n':
			case L' ':
			case L'\t':
			case L'\r':
				continue;			

			default:
				nExit = TRUE;

		}
	}

	return ch;

}/* McbFindNonWhiteSpace */

/**
 ****************************************************************************
 * <P> Duplicate a given string.  </P>
 *
 * @methodName  McbStrdup
 *
 * @param       lpszData		
 * @param       cbData		
 *
 * @return      LPWSTR
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	18th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
LPWSTR McbStrdup(LPCWSTR lpszData, int cbData)
{
	LPWSTR lpszNew;

	Assert(lpszData);

	if (cbData == 0) cbData = wcslen(lpszData);

	lpszNew = (LPWSTR)Plat_Alloc((cbData+1) * sizeof(WCHAR));
	//lpszNew = (LPWSTR)mynew((cbData+1) * sizeof(WCHAR));

	if (lpszNew)
	{
		memcpy(lpszNew, lpszData, (cbData) * sizeof(WCHAR));
		lpszNew[cbData] = L'\0';
	}

	return lpszNew;

}/* McbStrdup */

/**
 ****************************************************************************
 * <P> Find the next token in a string.  </P>
 *
 * @methodName  McbGetNextToken
 *
 * @param       *pXML		
 * @param       *pcbToken		
 * @param       *pType		
 *
 * @return      LPCWSTR
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	17th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbNextToken McbGetNextToken(McbXML *pXML, int *pcbToken, McbTokenType *pType)
{
	McbNextToken	result;
	LPCWSTR			lpXML;
	WCHAR			ch;
	WCHAR			chTemp;
	int				nSize = 0;
	int				nFoundMatch;
	int				nExit;
	int				n;
	LPCWSTR			lpszOpen;
	int				cbOpen;
	int				nIsText = FALSE;

	/*
	 *************************************************************************
	 * Find next non-whte space character
	 *************************************************************************
	 */
	ch = McbFindNonWhiteSpace(pXML);
	
	if (ch)
	{
		/*
		 *********************************************************************
		 * Cache the current string pointer
		 *********************************************************************
		 */
		lpXML = pXML->lpXML;
		result.pStr = &lpXML[pXML->nIndex-1];

		/*
		 *********************************************************************
		 * First check whether the token is in the clear tag list (meaning it 
		 * does not need formatting).
		 *********************************************************************
		 */
		n = 0;

		while(TRUE)
		{
			/*
			 *****************************************************************
			 * Obtain the name of the open part of the clear tag
			 *****************************************************************
			 */
			lpszOpen = pXML->pClrTags[n].lpszOpen;

			if (lpszOpen)
			{
				/*
				 *************************************************************
				 * Compare the open tag with the current token
				 *************************************************************
				 */
				cbOpen = wcslen(lpszOpen);

				//if (_wcsnicmp(lpszOpen, result.pStr, cbOpen) == 0)
				int ret = _wcsnicmp(lpszOpen, result.pStr, cbOpen);
				if (!ret){
					result.pClr = &pXML->pClrTags[n];
					pXML->nIndex += cbOpen-1;
					*pType  = eTokenClear;
					return result;
				}

				n++;
			}
			else
			{
				break;
			}
		}

		/*
		 *********************************************************************
		 * If we didn't find a clear tag then check for standard tokens
		 *********************************************************************
		 */
		chTemp = L'\0';

		lpXML = pXML->lpXML;

		switch(ch)
		{
			/*
			 *********************************************************************
			 * Check for quotes
			 *********************************************************************
			 */
			case L'\'':
				case L'\"':

					/*
					 *****************************************************************
					 * Type of token
					 *****************************************************************
					 */
					*pType = eTokenQuotedText;

				chTemp = ch;

				/*
				 *****************************************************************
				 * Set the size
				 *****************************************************************
				 */			
				nSize = 1;

				nFoundMatch = FALSE;

				/*
				 *****************************************************************
				 * Search through the string to find a matching quote
				 *****************************************************************
				 */
				while(ch = McbGetNextChar(pXML))
				{
					nSize++;

					if (ch == chTemp)
					{
						nFoundMatch = TRUE;
						break;
					}
				}

				/*
				 *****************************************************************
				 * If we failed to find a matching quote
				 *****************************************************************
				 */
				if (nFoundMatch == FALSE)
				{
					/*
					 *************************************************************
					 * Indicate error
					 *************************************************************
					 */
					pXML->error = eXMLErrorNoMatchingQuote;				
					*pType = eTokenError;
				}

				/* MCB 4.02.2002 */
				if (McbFindNonWhiteSpace(pXML))
				{
					pXML->nIndex--;
				}

				break;

				/*
				 *********************************************************************
				 * Equals (used with attribute values)
				 *********************************************************************
				 */
			case L'=':
				nSize = 1;
				*pType = eTokenEquals;
				break;

				/*
				 *********************************************************************
				 * Close tag
				 *********************************************************************
				 */
			case L'>':
				nSize = 1;
				*pType = eTokenCloseTag;
				break;

				/*
				 *********************************************************************
				 * Check for tag start and tag end
				 *********************************************************************
				 */
			case L'<':

				/*
				 *****************************************************************
				 * Peek at the next character to see if we have an end tag '</',
				 * or an xml declaration '<?'
				 *****************************************************************
				 */
				chTemp = pXML->lpXML[pXML->nIndex];

				/*
				 *****************************************************************
				 * If we have a tag end...
				 *****************************************************************
				 */
				if (chTemp == L'/')
				{
					/*
					 *************************************************************
					 * Set the type and ensure we point at the next character 
					 *************************************************************
					 */
					McbGetNextChar(pXML);
					*pType = eTokenTagEnd;
					nSize = 2;
				}
				/*
				 *****************************************************************
				 * If we have an XML declaration tag
				 *****************************************************************
				 */
				else if (chTemp == L'?')
				{
					/*
					 *************************************************************
					 * Set the type and ensure we point at the next character 
					 *************************************************************
					 */
					McbGetNextChar(pXML);
					*pType = eTokenDeclaration;
					nSize = 2;
				}
				/*
				 *****************************************************************
				 * Otherwise we must have a start tag
				 *****************************************************************
				 */
				else 
				{
					*pType = eTokenTagStart;
					nSize = 1;
				}
				break;

				/*
				 *********************************************************************
				 * Check to see if we have a short hand type end tag ('/>').
				 *********************************************************************
				 */
			case L'/':
				/*
				 *****************************************************************
				 * Peek at the next character to see if we have an end tag '</'
				 * or an xml declaration '<?'
				 *****************************************************************
				 */
				chTemp = pXML->lpXML[pXML->nIndex];

				/*
				 *****************************************************************
				 * If we have a short hand end tag...
				 *****************************************************************
				 */
				if (chTemp == L'>')
				{
					/*
					 *************************************************************
					 * Set the type and ensure we point at the next character 
					 *************************************************************
					 */
					McbGetNextChar(pXML);
					*pType = eTokenShortHandClose;
					nSize = 2;
					break;
				}

				/*
				 *****************************************************************
				 * If we haven't found a short hand closing tag then drop into the
				 * text process
				 *****************************************************************
				 */

				/*
				 *********************************************************************
				 * Other characters
				 *********************************************************************
				 */
			default:
				nIsText = TRUE;
		}

		/*
		 *********************************************************************
		 * If this is a TEXT node
		 *********************************************************************
		 */
		if (nIsText)
		{
			/*
			 *****************************************************************
			 * Indicate we are dealing with text
			 *****************************************************************
			 */
			*pType = eTokenText;

			nSize = 1;
			nExit = FALSE;

			while((nExit == FALSE) && (ch = McbGetNextChar(pXML)))
			{
				switch(ch)
				{
					/*
					 *************************************************************
					 * Break when we find white space
					 *************************************************************
					 */
					case L'\n':
					case L' ':
					case L'\t':
					case L'\r':
						nExit = TRUE;
						break;

						/*
						 *************************************************************
						 * If we find a slash then this maybe text or a short hand end
						 * tag.
						 *************************************************************
						 */
					case L'/':
						/*
						 *********************************************************
						 * Peek at the next character to see it we have short hand
						 * end tag
						 *********************************************************
						 */
						chTemp = pXML->lpXML[pXML->nIndex];

						/*
						 *********************************************************
						 * If we found a short hand end tag then we need to exit 
						 * the loop
						 *********************************************************
						 */
						if (chTemp == L'>')
						{
							pXML->nIndex--; /* MCB 03.02.2002 */
							nExit = TRUE;
						}
						else
						{
							nSize++;
						}
						break;

						/*
						 *************************************************************
						 * Break when we find a terminator and decrement the index and
						 * column count so that we are pointing at the right character
						 * the next time we are called.
						 *************************************************************
						 */
					case L'<':
					case L'>':
					case L'=':
						pXML->nIndex--;					
						nExit = TRUE;
						break;

					case L'\0':
						nExit = TRUE;
						break;

					default:
						nSize++;
				}
			}
		}

		*pcbToken = nSize;
	}
	/*
	 *************************************************************************
	 * If we failed to obtain a valid character
	 *************************************************************************
	 */
	else 
	{
		*pcbToken = 0;
		*pType = eTokenError;
		result.pStr = 0;
	}

	return result;

}/* McbGetNextToken */

/*
 *************************************************************************
 * Structure for errors array
 *************************************************************************
 */
typedef struct McbErrorList
{
	enum McbXMLError err;
	LPCSTR lpszErr;
} McbErrorList;

/**
 ****************************************************************************
 * <P> Parse XML errors into a user friendly string.  </P>
 *
 * @methodName  McbGetError
 *
 * @param       error		
 *
 * @return      LPCWSTR
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	19th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
LPCSTR McbGetError(McbXMLError error)
{
	LPCSTR lpszErr = "Unknown";
	int n;


	/*
	 *************************************************************************
	 * Static array containing helpful error text.
	 *************************************************************************
	 */
	static struct McbErrorList errs[] = 
	{
		{ eXMLErrorNone,			"No error"			},
		{ eXMLErrorEmpty,			"No XML data"			},
		{ eXMLErrorFirstNotStartTag,		"First token not start tag"	},
		{ eXMLErrorMissingTagName,		"Missing start tag name"	},
		{ eXMLErrorMissingEndTagName,		"Missing end tag name"		},
		{ eXMLErrorNoMatchingQuote,		"Unmatched quote"		},
		{ eXMLErrorUnmatchedEndTag,		"Unmatched end tag"		},
		{ eXMLErrorUnexpectedToken,		"Unexpected token found"	},
		{ eXMLErrorInvalidTag,			"Invalid tag found"		},
		{ eXMLErrorNoElements,			"No elements found"		},
		{ eXMLErrorNone,			NULL				}
	};

	/*
	 *************************************************************************
	 * Iterate through the list of errors to find a matching error
	 *************************************************************************
	 */
	for(n = 0; errs[n].lpszErr; n++)
	{
		if (errs[n].err == error)
		{
			lpszErr = errs[n].lpszErr;
			break;
		}
	}

	return lpszErr;	

}/* McbGetError */

/**
 ****************************************************************************
 * <P> Delete memory associated with a text node.   </P>
 *
 * @methodName  McbDeleteText
 *
 * @param       *pText		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteText(McbXMLText *pText)
{
	Assert(pText);

	if (pText->lpszValue)
	{
		Plat_Free(pText->lpszValue);
		//mydelete(pText->lpszValue);
		pText->lpszValue = NULL;
	}

}/* McbDeleteText */

/**
 ****************************************************************************
 * <P> Delete memory associated with a clear (unformatted) node.   </P>
 *
 * @methodName  McbDeleteClear
 *
 * @param       *pClear		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteClear(McbXMLClear *pClear)
{
	Assert(pClear);

	if (pClear->lpszValue)
	{
		Plat_Free(pClear->lpszValue);
		//mydelete(pClear->lpszValue);
		pClear->lpszValue = NULL;
	}

}/* McbDeleteClear */

/**
 ****************************************************************************
 * <P> Delete a given node.  </P>
 *
 * @methodName  McbDeleteNode
 *
 * @param       *pEntry		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteNode(McbXMLNode *pEntry)
{
	if (pEntry)
	{
		if (pEntry->type == eNodeEmpty)
		{
			return;
		}

		/*
		 *********************************************************************
		 * Delete the appropriate node
		 *********************************************************************
		 */
		switch(pEntry->type)
		{
			case eNodeAttribute:
				McbDeleteAttribute(pEntry->node.pAttrib);
				break;

			case eNodeElement:
				McbDeleteElement(pEntry->node.pElement);
				break;

			case eNodeText:
				McbDeleteText(pEntry->node.pText);
				break;

			case eNodeClear:
				McbDeleteClear(pEntry->node.pClear);
				break;

			default:
				Assert(TRUE);
		}	

		Plat_Free(pEntry->node.pAttrib);
		//mydelete(pEntry->node.pAttrib);
		pEntry->type = eNodeEmpty;
	}

}/* McbDeleteNode */

/**
 ****************************************************************************
 * <P> Delete an element and all it's contained nodes.  </P>
 *
 * @methodName  McbDeleteElement
 *
 * @param       *pEntry		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbDeleteElement(McbXMLElement *pEntry)
{
	int n;

	Assert(pEntry);

	/*
	 *************************************************************************
	 * Delete each node (this may recurse)
	 *************************************************************************
	 */
	for(n = 0; n<pEntry->nSize; n++)
	{
		McbDeleteNode(&pEntry->pEntries[n]);
	}

	/*
	 *************************************************************************
	 * Cleanup the list of nodes
	 *************************************************************************
	 */
	pEntry->nMax = 0;
	pEntry->nSize = 0;

	if( pEntry->pEntries )
	{
		Plat_Free(pEntry->pEntries);
		//mydelete(pEntry->pEntries);
		pEntry->pEntries = NULL;
	}

	/*
	 *************************************************************************
	 * Delete the name of the element
	 *************************************************************************
	 */
	if (pEntry->lpszName)
	{
		Plat_Free(pEntry->lpszName);
		//mydelete(pEntry->lpszName);
		pEntry->lpszName = NULL;
	}

	/* Plat_Free(pEntry); */

}/* McbDeleteElement */

/**
 ****************************************************************************
 * <P> Attach nodes from one list to another.  </P>
 *
 * @methodName  McbAttachNodes
 *
 * @param       *pDst		
 * @param       *pSrc		
 * @param       nNum		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	14th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbAttachNodes(McbXMLNode *pDst, McbXMLNode *pSrc, int nNum)
{
	int n;

	for (n=0; n<nNum; n++)
	{
		pDst[n] = pSrc[n];
		pSrc[n].type = eNodeEmpty;
	}

}/* McbAttachNodes */

/**
 ****************************************************************************
 * <P> Reserve memory for additional nodes.  </P>
 *
 * @methodName  McbAllocNodes
 *
 * @param       *pEntry		
 * @param       nGrowBy		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	15th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbAllocNodes(McbXMLElement *pEntry, int nGrowBy)
{
	int nMax;
//	McbXMLNode * pNew;

	Assert(pEntry);
	Assert(nGrowBy > 0);

	nMax = pEntry->nMax += nGrowBy;
	pEntry->pEntries = (McbXMLNode *)Plat_Realloc( pEntry->pEntries, sizeof(McbXMLNode) * nMax );
	//pEntry->pEntries = (McbXMLNode *)myrenew( pEntry->pEntries, sizeof(McbXMLNode) * nMax );

	/*
	 *************************************************************************
	 * Allocate storage for new nodes
	 *************************************************************************
	 */
	//	nMax = pEntry->nMax += nGrowBy;
	//	pNew = (McbXMLNode *)Plat_Alloc(sizeof(McbXMLNode) * nMax);

	/*
	 *************************************************************************
	 * Attach old entries to the new storage
	 *************************************************************************
	 */
	//    McbAttachNodes(pNew, pEntry->pEntries, pEntry->nSize);

	//	if (pEntry->pEntries)
	//	{
	//		Plat_Free(pEntry->pEntries);
	//	}

	//  pEntry->pEntries = pNew;

}/* McbAllocNodes */

/**
 ****************************************************************************
 * <P> Add an element node to the element.  </P>
 *
 * @methodName  McbAddElement
 *
 * @param       *pEntry		
 * @param       lpszName		
 * @param       nIsDeclaration
 * @param       nGrowBy		
 *
 * @return      McbXMLElement *
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbAddElement(McbXMLElement *pEntry, LPWSTR lpszName, 
		int nIsDeclaration, int nGrowBy)
{
	McbXMLNode *pNode;
	McbXMLElement * pElement;

	Assert(pEntry);
	Assert(nGrowBy > 0);

	/*
	 *************************************************************************
	 * Check we have enough storage
	 *************************************************************************
	 */
	if (pEntry->nSize == pEntry->nMax)
	{
		McbAllocNodes(pEntry, nGrowBy);
	}

	/*
	 *************************************************************************
	 * Obtain the new node, set the type and initialise it.
	 *************************************************************************
	 */
	pNode = &pEntry->pEntries[pEntry->nSize];
	pNode->type = eNodeElement;

	pElement = (McbXMLElement *)Plat_Alloc(sizeof(McbXMLElement));
	//pElement = (McbXMLElement *)mynew(sizeof(McbXMLElement));
	pNode->node.pElement = pElement;

	McbInitElement(pElement, pEntry, lpszName, nIsDeclaration);

	/*
	 *************************************************************************
	 * Increment the number of contained nodes
	 *************************************************************************
	 */
	pEntry->nSize++;

	/*
	 *************************************************************************
	 * Return the new element.
	 *************************************************************************
	 */
	return pElement;

}/* McbAddElement */

/**
 ****************************************************************************
 * <P> Add an attribute to an element.  </P>
 *
 * @methodName  McbAddAttribute
 *
 * @param       *pEntry		
 * @param       lpszName		
 * @param       lpszValue		
 * @param       nGrowBy		
 *
 * @return      McbXMLAttribute * 
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	14th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLAttribute * McbAddAttribute(McbXMLElement *pEntry, LPWSTR lpszName, 
		LPWSTR lpszValue, int nGrowBy)
{
	McbXMLNode *pNode;
	McbXMLAttribute *pAttr;

	Assert(pEntry);
	Assert(nGrowBy > 0);

	/*
	 *************************************************************************
	 * Check we have enough storage
	 *************************************************************************
	 */
	if (pEntry->nSize == pEntry->nMax)
	{
		McbAllocNodes(pEntry, nGrowBy);
	}

	/*
	 *************************************************************************
	 * Obtain the new node, set the type and initialise it.
	 *************************************************************************
	 */
	pNode = &pEntry->pEntries[pEntry->nSize];
	pNode->type = eNodeAttribute;

	pAttr = (McbXMLAttribute*)Plat_Alloc(sizeof(McbXMLAttribute));
	//pAttr = (McbXMLAttribute*)mynew(sizeof(McbXMLAttribute));
	pNode->node.pAttrib = pAttr;

	pAttr->lpszName = lpszName;
	pAttr->lpszValue = lpszValue;

	/*
	 *************************************************************************
	 * Increment the number of contained nodes
	 *************************************************************************
	 */
	pEntry->nSize++;

	/*
	 *************************************************************************
	 * Return the new attribute.
	 *************************************************************************
	 */
	return pAttr;

}/* McbAddAttribute */

/**
 ****************************************************************************
 * <P> Add text to the element.  </P>
 *
 * @methodName  * McbAddText
 *
 * @param       *pEntry		
 * @param       lpszValue		
 * @param       nGrowBy		
 *
 * @return      McbXMLText
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLText * McbAddText(McbXMLElement *pEntry, LPWSTR lpszValue, int nGrowBy)
{
	McbXMLNode *pNode;
	McbXMLText *pText;

	Assert(pEntry);
	Assert(nGrowBy > 0);

	/*
	 *************************************************************************
	 * Check we have enough storage
	 *************************************************************************
	 */
	if (pEntry->nSize == pEntry->nMax)
	{
		McbAllocNodes(pEntry, nGrowBy);
	}

	/*
	 *************************************************************************
	 * Obtain the new node, set the type and initialise it.
	 *************************************************************************
	 */
	pNode = &pEntry->pEntries[pEntry->nSize];
	pNode->type = eNodeText;

	pText = (McbXMLText*)Plat_Alloc(sizeof(McbXMLText));
	//pText = (McbXMLText*)mynew(sizeof(McbXMLText));
	pNode->node.pText = pText;
	pText->lpszValue = lpszValue;

	/*
	 *************************************************************************
	 * Increment the number of contained nodes
	 *************************************************************************
	 */
	pEntry->nSize++;

	/*
	 *************************************************************************
	 * Return the new attribute.
	 *************************************************************************
	 */
	return pText;

}/* McbAddText */

/**
 ****************************************************************************
 * <P> Add clear (unformatted) to the element.  </P>
 *
 * @methodName  * McbAddClear
 *
 * @param       *pEntry		
 * @param       lpszValue		
 * @param       nGrowBy		
 *
 * @return      McbXMLClear
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLClear * McbAddClear(McbXMLElement *pEntry, LPWSTR lpszValue, 
		McbClearTag *pClear, int nGrowBy)
{
	McbXMLNode *pNode;
	McbXMLClear *pNewClear;

	Assert(pEntry);
	Assert(nGrowBy > 0);

	/*
	 *************************************************************************
	 * Check we have enough storage
	 *************************************************************************
	 */
	if (pEntry->nSize == pEntry->nMax)
	{
		McbAllocNodes(pEntry, nGrowBy);
	}

	/*
	 *************************************************************************
	 * Obtain the new node, set the type and initialise it.
	 *************************************************************************
	 */
	pNode = &pEntry->pEntries[pEntry->nSize];
	pNode->type = eNodeClear;

	pNewClear = (McbXMLClear*)Plat_Alloc(sizeof(McbXMLClear));
	//pNewClear = (McbXMLClear*)mynew(sizeof(McbXMLClear));
	pNode->node.pClear = pNewClear;
	pNewClear->lpszValue = lpszValue;
	pNewClear->lpszOpenTag = pClear->lpszOpen;
	pNewClear->lpszCloseTag = pClear->lpszClose;

	/*
	 *************************************************************************
	 * Increment the number of contained nodes
	 *************************************************************************
	 */
	pEntry->nSize++;

	/*
	 *************************************************************************
	 * Return the new attribute.
	 *************************************************************************
	 */
	return pNewClear;

}/* McbAddClear */

/**
 ****************************************************************************
 * <P> Enumerate nodes in the list.  </P>
 *
 * @methodName  McbEnumNodes
 *
 * @param       *pEntry		
 * @param       *pnIndex		
 *
 * @return      McbXMLNode
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLNode * McbEnumNodes(McbXMLElement *pEntry, int *pnIndex)
{	
	McbXMLNode * pResult = NULL;

	Assert(pnIndex);
	Assert(pEntry);

	if (*pnIndex < pEntry->nSize)
	{
		pResult = &pEntry->pEntries[*pnIndex];
		(*pnIndex)++;
	}

	return pResult;

}/* McbEnumNodes */

/**
 ****************************************************************************
 * <P> Enumerate elements on a base element.  </P>
 *
 * @methodName  McbEnumElements
 *
 * @param       *pEntry		
 * @param       *pnIndex		
 *
 * @return      McbXMLNode
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbEnumElements(McbXMLElement *pEntry, int *pnIndex)
{	
	McbXMLElement * pResult = NULL;
	int nIndex;

	Assert(pnIndex);
	Assert(pEntry);

	nIndex = *pnIndex;

	for (;nIndex < pEntry->nSize && !pResult; nIndex++)
	{
		if (pEntry->pEntries[nIndex].type == eNodeElement)
		{
			pResult = pEntry->pEntries[nIndex].node.pElement;
		}
	}

	*pnIndex = nIndex;

	return pResult;

}/* McbEnumElements */

/**
 ****************************************************************************
 * <P> Enumerate attributes on a base element.  </P>
 *
 * @methodName  McbEnumAttributes
 *
 * @param       *pEntry		
 * @param       *pnIndex		
 *
 * @return      McbXMLNode
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLAttribute * McbEnumAttributes(McbXMLElement *pEntry, int *pnIndex)
{	
	McbXMLAttribute * pResult = NULL;
	int nIndex;

	Assert(pnIndex);
	Assert(pEntry);

	nIndex = *pnIndex;

	for (;nIndex < pEntry->nSize && !pResult; nIndex++)
	{
		if (pEntry->pEntries[nIndex].type == eNodeAttribute)
		{
			pResult = pEntry->pEntries[nIndex].node.pAttrib;
		}
	}

	*pnIndex = nIndex;

	return pResult;

}/* McbEnumAttributes */

/**
 ****************************************************************************
 * <P> Trim the end of the text to remove white space characters.  </P>
 *
 * @methodName  McbFindEndOfText
 *
 * @param       lpszToken		
 * @param       *pcbText		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbFindEndOfText(LPCWSTR lpszToken, int *pcbText)
{
	WCHAR	ch;
	int		cbText;

	Assert(lpszToken);
	Assert(pcbText);

	cbText = (*pcbText)-1;	

	while(TRUE)
	{
		Assert(cbText >= 0);

		ch = lpszToken[cbText];

		switch(ch)
		{
			case L'\r':
			case L'\n':
			case L'\t':
			case L' ':
				cbText--;
				break;

			default:
				*pcbText = cbText+1;
				return;
		}
	}

}/* McbFindEndOfText */

/**
 ****************************************************************************
 * <P> Parse a clear (unformatted) type node.  </P>
 *
 * @methodName  McbParseClearTag
 *
 * @param       *pXML		
 * @param       *pElement		
 * @param       lpszClose		
 * @param       lpszToken		
 *
 * @return      int
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	26th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
int McbParseClearTag(McbXML *pXML, McbXMLElement *pElement, McbClearTag * pClear)
{
	int cbTemp = 0;

	LPWSTR lpszTemp;
	LPCWSTR lpszXML = &pXML->lpXML[pXML->nIndex];

	/*
	 *************************************************************************
	 * Find the closing tag
	 *************************************************************************
	 */
	lpszTemp = (wchar_t *)wcsstr(lpszXML, pClear->lpszClose);

	/*
	 *************************************************************************
	 * Iterate through the tokens until we find the closing tag.
	 *************************************************************************
	 */
	if (lpszTemp)
	{
		/*
		 *********************************************************************
		 * Cache the size and increment the index
		 *********************************************************************
		 */
		cbTemp = lpszTemp - lpszXML;

		pXML->nIndex += cbTemp;
		pXML->nIndex += wcslen(pClear->lpszClose);

		/*
		 *********************************************************************
		 * Add the clear node to the current element
		 *********************************************************************
		 */
		lpszTemp = McbStrdup(lpszXML, cbTemp);

		McbAddClear(pElement, lpszTemp, pClear, McbGROWBY);

#ifdef McbSTOREOFFSETS
		pElement->pEntries[pElement->nSize-1].nStringOffset = (lpszXML -
				wcslen(pClear->lpszOpen)) - pXML->lpXML;			
#endif /* McbSTOREOFFSETS */

		return TRUE;
	}
	/*
	 *************************************************************************
	 * If we failed to find the end tag
	 *************************************************************************
	 */
	else
	{
		pXML->error = eXMLErrorUnmatchedEndTag;
		return FALSE;
	}

}/* McbParseClearTag */

/**
 ****************************************************************************
 * <P> Recursively parse an XML element.  </P>
 *
 * @methodName  McbParseXMLElement
 *
 * @param       *pXML		
 * @param       * pElement		
 *
 * @return      int
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	19th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
int McbParseXMLElement(McbXML *pXML, McbXMLElement * pElement)
{
	LPCWSTR lpszToken;
	int cbToken;

	enum McbTokenType type;
	McbNextToken token;

	LPCWSTR lpszTemp = NULL;
	int cbTemp = 0;

	int nDeclaration;

	LPCWSTR lpszText = NULL;

	McbXMLElement *pNew;

	enum McbStatus status;
	enum McbAttrib attrib = eAttribName;

	Assert(pXML);
	Assert(pElement);

	/*
	 *************************************************************************
	 * If this is the first call to the function
	 *************************************************************************
	 */
	if (pXML->nFirst)
	{
		/*
		 *********************************************************************
		 * Assume we are outside of a tag definition
		 *********************************************************************
		 */
		pXML->nFirst = FALSE;
		status = eOutsideTag;
	}
	/*
	 *************************************************************************
	 * If this is not the first call then we should only be called when inside
	 * a tag.
	 *************************************************************************
	 */
	else 
	{
		status = eInsideTag;
	}

	/*
	 *************************************************************************
	 * Iterate through the tokens in the document
	 *************************************************************************
	 */
	while(TRUE)
	{
		/*
		 *********************************************************************
		 * Obtain the next token
		 *********************************************************************
		 */
		token = McbGetNextToken(pXML, &cbToken, &type);

		if (type != eTokenError)
		{
			//printf("type is not eTokenError line %d\n", __LINE__);
			/*
			 *****************************************************************
			 * Check the current status
			 *****************************************************************
			 */
			switch(status)
			{
				/*
				 *****************************************************************
				 * If we outside of a tag definition
				 *****************************************************************
				 */
				case eOutsideTag:
					//printf("eOutsideTag line %d\n", __LINE__);
					/*
					 *************************************************************
					 * Check what type of token we obtained
					 *************************************************************
					 */
					switch(type)
					{
						/*
						 *************************************************************
						 * If we have found text or quoted text
						 *************************************************************
						 */
						case eTokenText:
						case eTokenQuotedText:
						case eTokenEquals:
							if (!lpszText)
							{
								lpszText = token.pStr;
							}					

							break;				

							/*
							 *************************************************************
							 * If we found a start tag '<' and declarations '<?'
							 *************************************************************
							 */
						case eTokenTagStart:
						case eTokenDeclaration:
							//printf("we found a start tag \'<\' iline %d\n", __LINE__);
							/*
							 *********************************************************
							 * Cache whether this new element is a declaration or not
							 *********************************************************
							 */
							nDeclaration = type == eTokenDeclaration;

							/*
							 *********************************************************
							 * If we have node text then add this to the element
							 *********************************************************
							 */
							if (lpszText)
							{
								cbTemp = token.pStr - lpszText;

								McbFindEndOfText(lpszText, &cbTemp);

								McbAddText(pElement, McbStrdup(lpszText, cbTemp), 
										McbGROWBY);

#ifdef McbSTOREOFFSETS
								pElement->pEntries[pElement->nSize-1].nStringOffset
									= lpszText - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

								lpszText = NULL;
							}

							/*
							 *********************************************************
							 * Find the name of the tag
							 *********************************************************
							 */
							token = McbGetNextToken(pXML, &cbToken, &type);

							/*
							 *********************************************************
							 * Return an error if we couldn't obtain the next token or
							 * it wasnt text
							 *********************************************************
							 */
							if (type != eTokenText)
							{
								pXML->error = eXMLErrorMissingTagName;
								//printf("we couldn't obtain the next token or it wants text  line %d\n", __LINE__);
								return FALSE;
							}

							/*
							 *********************************************************
							 * If we found a new element which has the same as this 
							 * element then we need to pass this back to the caller..
							 *********************************************************
							 */
							// BUG_FIX 2004-03-10 nested tags
							if (pElement->lpszName && 
									_issametag( pElement->lpszName, token.pStr ) == 0 )
								//						_wcsnicmp(pElement->lpszName, token.pStr, 
								//						wcslen(pElement->lpszName)) == 0)
							{
								/*
								 *****************************************************
								 * Indicate to the caller that it needs to create a 
								 * new element.
								 *****************************************************
								 */
								pXML->lpNewElement = token.pStr;
								pXML->cbNewElement = cbToken;

								// BUG_FIX 2004-03-10 nested tags
								goto NewElement;

								return TRUE;
							}
							/*
							 *********************************************************
							 * If the name of the new element differs from the name of
							 * the current element we need to add the new element to 
							 * the current one and recurse
							 *********************************************************
							 */
							else
							{
								/*
								 *****************************************************
								 * Now we need to add the new element and recurse
								 *****************************************************
								 */
								pNew = McbAddElement(pElement, 
										McbStrdup(token.pStr, cbToken), nDeclaration, 
										McbGROWBY);

#ifdef McbSTOREOFFSETS
								pElement->pEntries[pElement->nSize-1].nStringOffset = 
									token.pStr - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

								while(pNew)
								{
									/*
									 *************************************************
									 * Callself to process the new node.  If we return 
									 * FALSE this means we dont have any more 
									 * processing to do...
									 *************************************************
									 */
									if (!McbParseXMLElement(pXML, pNew))
									{
										//printf("return error ,line %d\n",__LINE__);
										return FALSE;
									}
									else
									{
										/*
										 *********************************************
										 * If the call to recurse this function 
										 * evented in a end tag specified in XML then 
										 * we need to unwind the calls to this 
										 * function until we find the appropriate node 
										 * (the element name and end tag name must 
										 * match)
										 *********************************************
										 */
										if (pXML->cbEndTag)
										{
											/*
											 *****************************************
											 * If we are back at the root node then we 
											 * have an unmatched end tag
											 *****************************************
											 */
											if (!pElement->lpszName)
											{
												pXML->error = eXMLErrorUnmatchedEndTag;
												//printf("return error,line %d\n", __LINE__);
												return FALSE;
											}

											/*
											 *****************************************
											 * If the end tag matches the name of this 
											 * element then we only need to unwind 
											 * once more...
											 *****************************************
											 */
											if (_wcsnicmp(pXML->lpEndTag, 
														pElement->lpszName, 
														wcslen(pElement->lpszName)) == 0)
											{                                    
												pXML->cbEndTag = 0;
											}

											return TRUE;
										}
										/*
										 *********************************************
										 * If the call indicated a new element is to 
										 * be created on THIS element.
										 *********************************************
										 */
										else if (pXML->cbNewElement)
										{
											/*
											 *****************************************
											 * If the name of this element matches the
											 * name of the element we need to create 
											 * then we need to return to the caller 
											 * and let it process the element.
											 *****************************************
											 */
											if (_wcsnicmp(pXML->lpNewElement, 
														pElement->lpszName, 
														wcslen(pElement->lpszName)) == 0)
											{                                    
												return TRUE;
											}

											/*
											 *****************************************
											 * Add the new element and recurse
											 *****************************************
											 */
											// BUG_FIX 2004-03-10 nested tags
NewElement:;
	   pNew = McbAddElement(pElement, 
			   McbStrdup(pXML->lpNewElement, 
				   pXML->cbNewElement), FALSE, 
			   McbGROWBY);

#ifdef McbSTOREOFFSETS
	   pElement->pEntries[pElement->nSize-1].
		   nStringOffset = 
		   pXML->lpNewElement - pXML->lpXML;
#endif /* McbSTOREOFFSETS */


	   pXML->cbNewElement = 0;
										}
										/*
										 *********************************************
										 * If we didn't have a new element to create
										 *********************************************
										 */
										else 
										{
											pNew = NULL;
										}
									}
								}
							}
							break;

							/*
							 *************************************************************
							 * If we found an end tag
							 *************************************************************
							 */
						case eTokenTagEnd:
							//printf("eTokenTagEnd line %d\n", __LINE__);
							/*
							 *********************************************************
							 * If we have node text then add this to the element
							 *********************************************************
							 */
							if (lpszText)
							{
								cbTemp = token.pStr - lpszText;

								McbFindEndOfText(lpszText, &cbTemp);

								McbAddText(pElement, McbStrdup(lpszText, cbTemp), 
										McbGROWBY);

#ifdef McbSTOREOFFSETS
								pElement->pEntries[pElement->nSize-1].nStringOffset
									= lpszText - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

								lpszText = NULL;						
							}

							/*
							 *********************************************************
							 * Find the name of the end tag
							 *********************************************************
							 */
							token = McbGetNextToken(pXML, &cbTemp, &type);					

							/*
							 *********************************************************
							 * The end tag should be text
							 *********************************************************
							 */
							if (type != eTokenText)
							{
								pXML->error = eXMLErrorMissingEndTagName;
								//printf("return error,line %d\n", __LINE__);
								return FALSE;
							}

							lpszTemp = token.pStr;

							/*
							 *********************************************************
							 * After the end tag we should find a closing tag
							 *********************************************************
							 */
							token = McbGetNextToken(pXML, &cbToken, &type);

							if (type != eTokenCloseTag)
							{
								pXML->error = eXMLErrorMissingEndTagName;
								//printf("return error,line %d\n", __LINE__);
								return FALSE;
							}

							/*
							 *********************************************************
							 * We need to return to the previous caller.  If the name 
							 * of the tag cannot be found we need to keep returning to
							 * caller until we find a match
							 *********************************************************
							 */
							if (_wcsnicmp(lpszTemp, pElement->lpszName, 
										wcslen(pElement->lpszName)) != 0)
							{
								pXML->lpEndTag = lpszTemp;
								pXML->cbEndTag = cbTemp;
							}

							/*
							 *********************************************************
							 * Return to the caller
							 *********************************************************
							 */
							return TRUE;

							/*
							 *************************************************************
							 * If we found a clear (unformatted) token
							 *************************************************************
							 */
						case eTokenClear:
							//printf("eTokenClear line %d\n", __LINE__);
							/*
							 *********************************************************
							 * If we have node text then add this to the element
							 *********************************************************
							 */
							if (lpszText)
							{
								cbTemp = token.pStr - lpszText;

								McbFindEndOfText(lpszText, &cbTemp);

								McbAddText(pElement, McbStrdup(lpszText, cbTemp), 
										McbGROWBY);

#ifdef McbSTOREOFFSETS
								pElement->pEntries[pElement->nSize-1].nStringOffset
									= lpszText - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

								lpszText = NULL;
							} 

							if (!McbParseClearTag(pXML, pElement, token.pClr))
							{
							//	printf("return error,line %d\n", __LINE__);
								return FALSE;
							}
							break;

							/*
							 *************************************************************
							 * Errors...
							 *************************************************************
							 */				
						case eTokenCloseTag:		/* '>'		*/
						case eTokenShortHandClose:	/* '/>'		*/
							pXML->error = eXMLErrorUnexpectedToken;
							//printf("return error,line %d\n", __LINE__);
							return FALSE;
					}
					break;

					/*
					 *****************************************************************
					 * If we are inside a tag definition we need to search for 
					 * attributes
					 *****************************************************************
					 */
				case eInsideTag:
					//printf("inside a tag line %d\n");
					/*
					 *************************************************************
					 * Check what part of the attribute (name, equals, value) we 
					 * are looking for.
					 *************************************************************
					 */
					switch(attrib)
					{
						/*
						 ************************************************************
						 * If we are looking for a new attribute
						 ************************************************************
						 */
						case eAttribName:
							/*
							 *********************************************************
							 * Check what the current token type is
							 *********************************************************
							 */
							switch(type)
							{
								/*
								 *********************************************************
								 * If the current type is text...
								 * Eg.  'attribute'
								 *********************************************************
								 */
								case eTokenText:
									/*
									 *****************************************************
									 * Cache the token then indicate that we are next to 
									 * look for the equals
									 *****************************************************
									 */
									lpszTemp = token.pStr;
									cbTemp = cbToken;
									attrib = eAttribEquals;
									break;

									/*
									 *********************************************************
									 * If we found a closing tag...
									 * Eg.  '>'
									 *********************************************************
									 */
								case eTokenCloseTag:
									/*
									 *****************************************************
									 * We are now outside the tag
									 *****************************************************
									 */
									status = eOutsideTag;
									break;

									/*
									 *********************************************************
									 * If we found a short hand '/>' closing tag then we can 
									 * return to the caller
									 *********************************************************
									 */
								case eTokenShortHandClose:
									return TRUE;

									/*
									 *********************************************************
									 * Errors...
									 *********************************************************
									 */
								case eTokenQuotedText:	/* '"SomeText"'	*/
								case eTokenTagStart:	/* '<'			*/
								case eTokenTagEnd:		/* '</'			*/
								case eTokenEquals:		/* '='			*/
								case eTokenDeclaration:	/* '<?'			*/
								case eTokenClear:
									pXML->error = eXMLErrorUnexpectedToken;
									//printf("return error,line %d\n", __LINE__);
									return FALSE;
							}
							break;

							/*
							 ************************************************************
							 * If we are looking for an equals
							 ************************************************************
							 */
						case eAttribEquals:
							/*
							 *********************************************************
							 * Check what the current token type is
							 *********************************************************
							 */
							switch(type)
							{
								/*
								 *********************************************************
								 * If the current type is text...
								 * Eg.  'Attribute AnotherAttribute'
								 *********************************************************
								 */
								case eTokenText:
									/*
									 *****************************************************
									 * Add the unvalued attribute to the list
									 *****************************************************
									 */
									McbAddAttribute(pElement, McbStrdup(lpszTemp, 
												cbTemp), NULL, McbGROWBY);

#ifdef McbSTOREOFFSETS
									pElement->pEntries[pElement->nSize-1].nStringOffset =
										lpszTemp - pXML->lpXML;

#endif /* McbSTOREOFFSETS */

									/*
									 *****************************************************
									 * Cache the token then indicate.  We are next to 
									 * look for the equals attribute
									 *****************************************************
									 */
									lpszTemp = token.pStr;
									cbTemp = cbToken;
									break;

									/*
									 *********************************************************
									 * If we found a closing tag 'Attribute >' or a short hand 
									 * closing tag 'Attribute />'
									 *********************************************************
									 */
								case eTokenShortHandClose:
								case eTokenCloseTag:
									/*
									 *****************************************************
									 * If we are a declaration element '<?' then we need
									 * to remove extra closing '?' if it exists
									 *****************************************************
									 */
									if (pElement->nIsDeclaration && 
											(lpszTemp[cbTemp-1]) == L'?')
									{
										cbTemp--;
									}

									if (cbTemp)
									{
										/*
										 *************************************************
										 * Add the unvalued attribute to the list
										 *************************************************
										 */
										McbAddAttribute(pElement, McbStrdup(lpszTemp, 
													cbTemp), NULL, McbGROWBY);

#ifdef McbSTOREOFFSETS
										pElement->pEntries[pElement->nSize-1].
											nStringOffset = lpszTemp - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

									}

									/*
									 *****************************************************
									 * If this is the end of the tag then return to the 
									 * caller
									 *****************************************************
									 */
									if (type == eTokenShortHandClose)
									{
										return TRUE;
									}

									/*
									 *****************************************************
									 * We are now outside the tag
									 *****************************************************
									 */
									status = eOutsideTag;
									break;

									/*
									 *********************************************************
									 * If we found the equals token...
									 * Eg.  'Attribute ='
									 *********************************************************
									 */
								case eTokenEquals:
									/*
									 *****************************************************
									 * Indicate that we next need to search for the value
									 * for the attribute
									 *****************************************************
									 */
									attrib = eAttribValue;
									break;

									/*
									 *********************************************************
									 * Errors...
									 *********************************************************
									 */
								case eTokenQuotedText:	/* 'Attribute "InvalidAttr"'*/
								case eTokenTagStart:	/* 'Attribute <'			*/
								case eTokenTagEnd:		/* 'Attribute </'			*/
								case eTokenDeclaration:	/* 'Attribute <?'			*/
								case eTokenClear:
									pXML->error = eXMLErrorUnexpectedToken;
									//printf("return error,line %d\n", __LINE__);
									return FALSE;

							}
							break;

							/*
							 ************************************************************
							 * If we are looking for an attribute value
							 ************************************************************
							 */
						case eAttribValue:
							/*
							 *********************************************************
							 * Check what the current token type is
							 *********************************************************
							 */
							switch(type)
							{
								/*
								 *********************************************************
								 * If the current type is text or quoted text...
								 * Eg.  'Attribute = "Value"' or 'Attribute = Value' or
								 * 'Attribute = 'Value''.
								 *********************************************************
								 */
								case eTokenText:
								case eTokenQuotedText:
									/*
									 *****************************************************
									 * If we are a declaration element '<?' then we need
									 * to remove extra closing '?' if it exists
									 *****************************************************
									 */
									if (pElement->nIsDeclaration && 
											(token.pStr[cbToken-1]) == L'?')
									{
										cbToken--;
									}

									if (cbTemp)
									{
										lpszToken = McbStrdup(token.pStr, cbToken);
									}
									else
									{
										lpszToken = NULL;
									}

									/*
									 *****************************************************
									 * Add the valued attribute to the list
									 *****************************************************
									 */
									McbAddAttribute(pElement, McbStrdup(lpszTemp, 
												cbTemp), (LPWSTR)lpszToken, McbGROWBY);

#ifdef McbSTOREOFFSETS
									pElement->pEntries[pElement->nSize-1].nStringOffset
										= lpszTemp - pXML->lpXML;
#endif /* McbSTOREOFFSETS */

									/*
									 *****************************************************
									 * Indicate we are searching for a new attribute
									 *****************************************************
									 */
									attrib = eAttribName;
									break;

									/*
									 *********************************************************
									 * Errors...
									 *********************************************************
									 */
								case eTokenTagStart:		/* 'Attr = <'			*/
								case eTokenTagEnd:			/* 'Attr = </'			*/
								case eTokenCloseTag:		/* 'Attr = >'			*/
								case eTokenShortHandClose:	/* "Attr = />"			*/
								case eTokenEquals:			/* 'Attr = ='			*/
								case eTokenDeclaration:		/* 'Attr = <?'			*/
								case eTokenClear:
									pXML->error = eXMLErrorUnexpectedToken;
									//printf("return error,line %d\n", __LINE__);
									return FALSE;
									break;
							}
					}
			}
		}
		/*
		 *********************************************************************
		 * If we failed to obtain the next token
		 *********************************************************************
		 */
		else 
		{
			//printf("failed to obtain the next token line %d\n", __LINE__);
			return FALSE;	
		}
	}

}/* McbParseXMLElement */

/**
 ****************************************************************************
 * <P> Count the number of lines and columns in an XML string.  </P>
 *
 * @methodName  McbCountLinesAndColumns
 *
 * @param       lpXML		
 * @param       nUpto		
 * @param       *pResults		
 *
 * @return      void
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	21st August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
void McbCountLinesAndColumns(LPCWSTR lpXML, int nUpto, McbXMLResults *pResults)
{
	WCHAR ch;
	int n;

	Assert(lpXML);	
	Assert(pResults);

	pResults->nLine = 1;
	pResults->nColumn = 1;

	for(n=0; n<nUpto; n++)
	{
		ch = lpXML[n];

		Assert(ch);

		if (ch == L'\n')
		{
			pResults->nLine++;
			pResults->nColumn = 1;
		}
		else
		{
			pResults->nColumn++;
		}
	}
}/* McbCountLinesAndColumns */

/**
 ****************************************************************************
 * <P> Obtain tags used for unformatted text within elements.  </P>
 *
 * @methodName  * McbGetClearTags
 *
 * @param       none
 *
 * @return      McbClearTag
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	3rd February  	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbClearTag	* McbGetClearTags()
{
#ifdef WIN32	
	static struct McbClearTag tags[] =
	{
		{	L"<![CDATA[",	L"]]>"			},
		{	L"<PRE>",	L"</PRE>"		},
		{	L"<Script>",	L"</Script>"		},
		{	L"<!--",	L"-->"			},
		{	L"<!DOCTYPE",	L">"			},
		{	L'\0',		L'\0'			}
	};
#else	
	static struct McbClearTag tags[] =
	{
		{	(wchar_t *)L"<![CDATA[",	(wchar_t *)L"]]>"			},
		{	(wchar_t *)L"<PRE>",		(wchar_t *)L"</PRE>"			},
		{	(wchar_t *)L"<Script>",		(wchar_t *)L"</Script>"			},
		{	(wchar_t *)L"<!--",		(wchar_t *)L"-->"			},
		{	(wchar_t *)L"<!DOCTYPE",	(wchar_t *)L">"				},
		{	(wchar_t *)L'\0',		(wchar_t *)L'\0'			}
	};
#endif
	return tags;

}/* McbGetClearTags */

#define McbGETCDATA() &McbGetClearTags()[0]

/**
 ****************************************************************************
 * <P> Parse XML and return the root element.  </P>
 *
 * @methodName  * McbParseXML
 *
 * @param       lpszXML		
 * @param       *pResults		
 *
 * @return      McbXMLElement
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	20th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbParseXML(LPCWSTR lpszXML, McbXMLResults *pResults)
{
	enum McbXMLError error;

	struct McbXMLElement * pElement = NULL;

	struct McbXML xml = 
	{ NULL, 0, eXMLErrorNone, NULL, 0, NULL, 0, TRUE };

	xml.lpXML = lpszXML;
	xml.pClrTags = McbGetClearTags();

	/*
	 *************************************************************************
	 * Create header element
	 *************************************************************************
	 */
	pElement = McbCreateRoot();

	McbParseXMLElement(&xml, pElement);

	//printf("xml.nIndex = %d\n", xml.nIndex);
	error = xml.error;

	/*
	 *************************************************************************
	 * If an error occurred
	 *************************************************************************
	 */
	if (error != eXMLErrorNone)
	{
		/*
		 *********************************************************************
		 * Cleanup
		 *********************************************************************
		 */
		McbDeleteRoot(pElement);
		pElement = NULL;
	}

	/*
	 *************************************************************************
	 * If we hae been given somewhere to place results
	 *************************************************************************
	 */
	if (pResults)
	{
		pResults->error = error;

		/*
		 *********************************************************************
		 * If we have an error
		 *********************************************************************
		 */
		if (error != eXMLErrorNone)
		{
			/*
			 *****************************************************************
			 * Find which line and column it starts on.
			 *****************************************************************
			 */
			McbCountLinesAndColumns(xml.lpXML, xml.nIndex, pResults);
		}

	}

	return pElement;

}/* McbParseXML */

/**
 ****************************************************************************
 * <P> Search for an element in the list.  </P>
 *
 * @methodName  * McbFindElement
 *
 * @param       lpszName
 *
 * @return      McbXMLElement
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	25th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbFindElement(McbXMLElement *pEntry, LPCWSTR lpszPath)
{
	McbXMLElement * pChild;
	LPCWSTR lpszName;
	LPCWSTR lpszNext;
	int cbName;
	int nIndex;

	Assert(lpszPath);
	Assert(pEntry);

	/*
	 *************************************************************************
	 * Find the next name in the path in case we need to recurse
	 *************************************************************************
	 */
	lpszNext = wcschr(lpszPath, L'/');

	/*
	 *************************************************************************
	 * Calculate the length of the current name we are searching for
	 *************************************************************************
	 */
	if (!lpszNext)
	{
		cbName = wcslen(lpszPath);		
	}
	else
	{
		cbName = lpszNext - lpszPath;

		if (lpszNext[1])
		{
			lpszNext++;
		}
		else
		{
			lpszNext = NULL;
		}
	}

	if (cbName)
	{
		/*
		 *********************************************************************
		 * Enumerate child elements
		 *********************************************************************
		 */
		nIndex = 0;
		while(pChild = McbEnumElements(pEntry, &nIndex))
		{
			/*
			 *****************************************************************
			 * Obtain the name of the child element
			 *****************************************************************
			 */
			lpszName = pChild->lpszName;

			if (lpszName)
			{
				/*
				 *************************************************************
				 * If the name of the element is what we are looking for
				 *************************************************************
				 */
				//if (_wcsnicmp(lpszPath, lpszName, cbName) == 0)
				int ret = _wcsnicmp(lpszPath, lpszName, cbName);
				if (!ret) 
				{
					/*
					 *********************************************************
					 * Check if this is the last element to search for
					 *********************************************************
					 */
					if (!lpszNext)
					{
						return pChild;
					}
					/*
					 *********************************************************
					 * If we have further nodes to find then recurse.
					 *********************************************************
					 */
					else 
					{
						return McbFindElement(pChild, lpszNext);
					}
				}
			}
		}
	}

	return NULL;

}/* McbFindElement */

/**
 ****************************************************************************
 * <P> Find an attribute on an element.  </P>
 *
 * @methodName  * McbFindAttribute
 *
 * @param       *pEntry		
 * @param       lpszAttrib		
 *
 * @return      McbXMLAttribute
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	25th August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLAttribute * McbFindAttribute(McbXMLElement *pEntry, LPCWSTR lpszAttrib)
{
	McbXMLAttribute * pAttr;
	int cbAttrib;
	int nIndex;

	Assert(pEntry);
	Assert(lpszAttrib);

	cbAttrib = wcslen(lpszAttrib);
	nIndex = 0;

	while(pAttr = McbEnumAttributes(pEntry, &nIndex))
	{
		if (_wcsnicmp(pAttr->lpszName, lpszAttrib, cbAttrib) == 0)
		{
			return pAttr;
		}
	}

	return NULL;

}/* McbFindAttribute */

/**
 ****************************************************************************
 * <P> Add CData to the element.  </P>
 *
 * @methodName  * McbAddCData
 *
 * @param       *pEntry		
 * @param       lpszValue		
 * @param       nGrowBy		
 *
 * @return      McbXMLClear
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	3rd February  	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLClear * McbAddCData(McbXMLElement *pEntry, LPWSTR lpszValue, int nGrowBy)
{
	return McbAddClear(pEntry, lpszValue, McbGETCDATA(), nGrowBy);

}/* McbAddCData */

/**
 ****************************************************************************
 * <P> Add elements to the list if they do not exist, return the final node.
 * </P>
 *
 * @methodName  * McbCreateElements
 *
 * @param       *pEntry		
 * @param       lpszPath		
 *
 * @return      McbXMLElement
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	29th January   	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
McbXMLElement * McbCreateElements(McbXMLElement *pEntry, LPCWSTR lpszPath)
{
	McbXMLElement * pChild;
	McbXMLElement * pNew;
	LPCWSTR lpszName;
	LPCWSTR lpszNext;
	int cbName;
	int nIndex;

	Assert(lpszPath);
	Assert(pEntry);

	/*
	 *************************************************************************
	 * Find the next name in the path in case we need to recurse
	 *************************************************************************
	 */
	lpszNext = wcschr(lpszPath, L'/');

	/*
	 *************************************************************************
	 * Calculate the length of the current name we are searching for
	 *************************************************************************
	 */
	if (!lpszNext)
	{
		cbName = wcslen(lpszPath);		
	}
	else
	{
		cbName = lpszNext - lpszPath;

		if (lpszNext[1])
		{
			lpszNext++;
		}
		else
		{
			lpszNext = NULL;
		}
	}

	if (cbName)
	{
		/*
		 *********************************************************************
		 * Enumerate child elements
		 *********************************************************************
		 */
		nIndex = 0;
		while(pChild = McbEnumElements(pEntry, &nIndex))
		{
			/*
			 *****************************************************************
			 * Obtain the name of the child element
			 *****************************************************************
			 */
			lpszName = pChild->lpszName;

			if (lpszName)
			{
				/*
				 *************************************************************
				 * If the name of the element is what we are looking for
				 *************************************************************
				 */
				if (_wcsnicmp(lpszPath, lpszName, cbName) == 0)
				{
					/*
					 *********************************************************
					 * Check if this is the last element to search for
					 *********************************************************
					 */
					if (!lpszNext)
					{
						return pChild;
					}
					/*
					 *********************************************************
					 * If we have further nodes to find then recurse.
					 *********************************************************
					 */
					else 
					{
						return McbCreateElements(pChild, lpszNext);
					}
				}
			}
		}

		/*
		 *********************************************************************
		 * If we got this far then we couldn't find the required element so we
		 * need to add a new element to the current element
		 *********************************************************************
		 */
		pNew = McbAddElement(pEntry, McbStrdup(lpszPath, cbName), FALSE, 
				McbGROWBY);

		/*
		 *********************************************************************
		 * If there are no more entries then return the node we just created.
		 *********************************************************************
		 */
		if (!lpszNext)
		{
			return pNew;
		}
		/*
		 *********************************************************************
		 * If there are more elements to search
		 *********************************************************************
		 */
		else 
		{
			/*
			 *****************************************************************
			 * Recurse to add the remaining nodes
			 *****************************************************************
			 */
			return McbCreateElements(pNew, lpszNext);
		}
	}

	return NULL;

}/* McbCreateElements */

/**
 ****************************************************************************
 * <P> Creates an user friendly XML string from a given element with 
 * appropriate white space and carriage returns.
 *
 * This recurses through all subnodes then adds contents of the nodes to the
 * string.
 * </P>
 *
 * @methodName  McbCreateXMLStringR
 *
 * @param       McbXMLElement * pEntry - XML Element
 * @param       LPWSTR lpszMarker	  - String to create results into, this 
 *										can be zero if you want to calculate
 *										the size of the returned string.
 * @param       int nFormat			  -	Specify -1 for no formatting or the
 *										indent level (0 initially).
 * @return      int					  - Size of the returned string, not 
 *										including the NULL terminator.
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	31st January   	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
int McbCreateXMLStringR(McbXMLElement * pEntry, LPWSTR lpszMarker, int nFormat)
{
	int nResult = 0;
	int cb;
	int cbElement;
	int nIndex;
	int nChildFormat;
	int bHasChildren = FALSE;
	McbXMLNode * pChild;
	McbXMLAttribute * pAttr;

	Assert(pEntry);

#define McbLENSTR(lpsz) (lpsz ? wcslen(lpsz) : 0)

	/*
	 *************************************************************************
	 * If the element has no name then assume this is the head node.
	 *************************************************************************
	 */
	cbElement = McbLENSTR(pEntry->lpszName);

	if (cbElement)
	{
		/*
		 *********************************************************************
		 * "<elementname "
		 *********************************************************************
		 */
		cb = nFormat == -1 ? 0 : nFormat;

		if (lpszMarker)
		{
			if (cb)
			{
				/************************************
				  BUG_FIX zhangzhipeng 2004-03-16
				  修正memset只能按字节设置数据的问题
				 *************************************/
				_extmemset(lpszMarker, McbINDENTCHAR, cb);
				/*memset(lpszMarker, McbINDENTCHAR, sizeof(WCHAR)*cb);*/
			}

			nResult = cb;

			lpszMarker[nResult++] = L'<';        
			wcscpy(&lpszMarker[nResult], pEntry->lpszName);
			nResult += cbElement;
			lpszMarker[nResult++] = L' ';        
		}                
		else
		{
			nResult += cbElement + 2 + cb;
		}

		/*
		 *********************************************************************
		 * Enumerate attributes and add them to the string
		 *********************************************************************
		 */
		nIndex = 0;
		while (pChild = McbEnumNodes(pEntry, &nIndex))
		{
			switch(pChild->type)
			{
				/*
				 *****************************************************************
				 * Add attributes
				 *****************************************************************
				 */
				case eNodeAttribute:
					{
						pAttr = pChild->node.pAttrib;

						/*
						 *********************************************************
						 * "Attrib
						 *********************************************************
						 */
						cb = McbLENSTR(pAttr->lpszName);

						if (cb)
						{
							if (lpszMarker)
							{
								wcscpy(&lpszMarker[nResult], pAttr->lpszName);             
							}

							nResult += cb;

							/*
							 *****************************************************
							 * "Attrib=Value "
							 *****************************************************
							 */
							cb = McbLENSTR(pAttr->lpszValue);

							if (cb)
							{
								if (lpszMarker)
								{
									lpszMarker[nResult] = L'=';
									wcscpy(&lpszMarker[nResult+1], 
											pAttr->lpszValue);                  
								}
								nResult += cb + 1;
							}

							if (lpszMarker)
							{
								lpszMarker[nResult] = L' ';                              
							}

							nResult++;              
						}
					}
					break;

				case eNodeEmpty:
					continue;

				default:
					/*
					 *************************************************************
					 * If this node isn't an attribute then flag that this element 
					 * has children.
					 *************************************************************
					 */
					bHasChildren = TRUE;
			}
		}

		/*
		 *********************************************************************
		 * If there are child nodes we need to terminate the start tag
		 *********************************************************************
		 */
		if (bHasChildren)
		{   
			if (lpszMarker)
			{
				lpszMarker[nResult-1] = L'>';
			}

			if (nFormat != -1)
			{
				if (lpszMarker)
				{
					//					lpszMarker[nResult] = L'\n';
					wcscpy(&lpszMarker[nResult], L"\r\n");
				}

				//				nResult++;
				nResult+=2;
			}
		}
		else
		{
			nResult--;
		}
	}

	/*
	 *************************************************************************
	 * Calculate the child format for when we recurse.  This is used to 
	 * determine the number of spaces used for prefixes.
	 *************************************************************************
	 */
	if (nFormat == -1)
	{
		nChildFormat = -1;
	}
	else
	{
		if (cbElement) 
		{
			nChildFormat = nFormat + 1;
		}
		else
		{
			nChildFormat = nFormat;
		}	
	}

	/*
	 *************************************************************************
	 * Enumerate through remaining children
	 *************************************************************************
	 */
	nIndex = 0;	
	while (pChild = McbEnumNodes(pEntry, &nIndex))
	{
		switch(pChild->type)
		{
			/*
			 *********************************************************************
			 * Text nodes
			 *********************************************************************
			 */
			case eNodeText:
				{
					/*
					 *************************************************************
					 * "Text"
					 *************************************************************
					 */
					cb = McbLENSTR(pChild->node.pText->lpszValue);

					if (cb)
					{
						if (nFormat != -1)
						{
							if (lpszMarker)
							{
								// BUG_FIX zhangzhipeng 2004-03-16
								// 修正memset只能按字节设置数据的问题
								_extmemset(&lpszMarker[nResult], McbINDENTCHAR, nFormat + 1);
								//memset(&lpszMarker[nResult], McbINDENTCHAR, sizeof(WCHAR)*(nFormat + 1));

								wcscpy(&lpszMarker[nResult + nFormat + 1], 
										pChild->node.pText->lpszValue);

								//							lpszMarker[nResult + nFormat + 1 + cb] = L'\n';
								wcscpy(&lpszMarker[nResult + nFormat + 1 + cb], L"\r\n");
							}

							//						nResult += cb + nFormat + 2;
							nResult += cb + nFormat + 3;
						}
						else
						{
							if (lpszMarker)
							{
								wcscpy(&lpszMarker[nResult], 
										pChild->node.pText->lpszValue);
							}

							nResult += cb;
						}               
					}
				}
				break;

				/*
				 *********************************************************************
				 * Clear type nodes
				 *********************************************************************
				 */
			case eNodeClear:
				{
					/*
					 *************************************************************
					 * "OpenTag"
					 *************************************************************
					 */
					cb = McbLENSTR(pChild->node.pClear->lpszOpenTag);

					if (cb)
					{
						if (nFormat != -1)
						{
							if (lpszMarker)
							{
								/************************************
								  BUG_FIX zhangzhipeng 2004-03-16
								  修正memset只能按字节设置数据的问题
								 *************************************/
								_extmemset(&lpszMarker[nResult], McbINDENTCHAR, nFormat + 1);
								/*memset(&lpszMarker[nResult], McbINDENTCHAR, 
								  sizeof(WCHAR)*(nFormat + 1));*/

								wcscpy(&lpszMarker[nResult + nFormat + 1], 
										pChild->node.pClear->lpszOpenTag);

								/* lpszMarker[nResult + nFormat + 1 + cb] = 
								   L'\n'); */
							}

							/* nResult += cb + nFormat + 2; */
							nResult += cb + nFormat + 1;

						}
						else
						{
							if (lpszMarker)
							{
								wcscpy(&lpszMarker[nResult], 
										pChild->node.pClear->lpszOpenTag);
							}

							nResult += cb;
						}               
					}

					/*
					 *************************************************************
					 * "OpenTag Value"
					 *************************************************************
					 */
					cb = McbLENSTR(pChild->node.pClear->lpszValue);

					if (cb)
					{
						if (lpszMarker)
						{
							wcscpy(&lpszMarker[nResult], 
									pChild->node.pClear->lpszValue);
						}

						nResult += cb;
					}

					/*
					 *************************************************************
					 * "OpenTag Value CloseTag"
					 *************************************************************
					 */
					cb = McbLENSTR(pChild->node.pClear->lpszCloseTag);

					if (cb)
					{
						if (lpszMarker)
						{
							wcscpy(&lpszMarker[nResult], 
									pChild->node.pClear->lpszCloseTag);
						}

						nResult += cb;
					}

					if (nFormat != -1)
					{
						if (lpszMarker)
						{
							//						lpszMarker[nResult] = L'\n';
							wcscpy(&lpszMarker[nResult], L"\r\n" );
						}

						//					nResult++;
						nResult+=2;
					}
				}
				break;
				/*
				 *********************************************************************
				 * Element nodes
				 *********************************************************************
				 */
			case eNodeElement:
				{
					/*
					 *************************************************************
					 * Recursively add child nodes
					 *************************************************************
					 */
					nResult += McbCreateXMLStringR(pChild->node.pElement, 
							lpszMarker ? lpszMarker + nResult : 0, nChildFormat);
				}
		}
	}

	if (cbElement)
	{
		/*
		 *********************************************************************
		 * If we have child entries we need to use long XML notation for 
		 * closing the element - "<elementname>blah blah blah</elementname>"
		 *********************************************************************
		 */
		if (bHasChildren)
		{
			/*
			 *****************************************************************
			 * "</elementname>\0"
			 *****************************************************************
			 */
			if (lpszMarker)
			{
				if (nFormat != -1)
				{
					if (nFormat)
					{
						/************************************
						  BUG_FIX zhangzhipeng 2004-03-16
						  修正memset只能按字节设置数据的问题
						 *************************************/
						_extmemset(&lpszMarker[nResult], McbINDENTCHAR, nFormat);
						/*memset(&lpszMarker[nResult], McbINDENTCHAR, 
						  sizeof(WCHAR)*nFormat);*/

						nResult+=nFormat;
					}
				}       

				wcscpy(&lpszMarker[nResult], L"</");        
				nResult += 2;
				wcscpy(&lpszMarker[nResult], pEntry->lpszName);
				nResult += cbElement;

				if (nFormat == -1)
				{
					wcscpy(&lpszMarker[nResult], L">");
					nResult++;
				}
				else
				{
					//					wcscpy(&lpszMarker[nResult], L">\n");
					//					nResult += 2;
					wcscpy(&lpszMarker[nResult], L">\r\n");
					nResult += 3;
				}
			}
			else
			{
				if (nFormat != -1)
				{
					//					nResult += cbElement + 4 + nFormat;
					nResult += cbElement + 5 + nFormat;
				}
				else
				{
					nResult += cbElement + 3;
				}
			}       
		}
		/*
		 *********************************************************************
		 * If there are no children we can use shorthand XML notation - 
		 * "<elementname/>"
		 *********************************************************************
		 */
		else 
		{
			/*
			 *****************************************************************
			 * "/>\0"
			 *****************************************************************
			 */
			if (lpszMarker)
			{
				if (nFormat == -1)
				{
					wcscpy(&lpszMarker[nResult], L"/>"); 
					nResult += 2;
				}
				else
				{
					//					wcscpy(&lpszMarker[nResult], L"/>\n"); 
					//					nResult += 3;
					wcscpy(&lpszMarker[nResult], L"/>\r\n"); 
					nResult += 4;
				}
			}
			else
			{
				//				nResult += nFormat == -1 ? 2 : 3;
				nResult += nFormat == -1 ? 2 : 4;
			}
		}
	}

	return nResult;

}/* McbCreateXMLStringR */

/**
 ****************************************************************************
 * <P> Create an XML string from the head element.  </P>
 *
 * @methodName  McbCreateXMLString
 *
 * @param       McbXMLElement * pHead -	head element
 * @param       int nFormat			 -  0 if no formatting is required 
 *										otherwise nonzero for formatted text
 *										with carriage returns and indentation.
 * @param       int *pnSize			 -	[out] pointer to the size of the 
 *										returned string not including the 
 *										NULL terminator.
 *
 * @return      LPWSTR				 -	Allocated XML string, you must Plat_Free
 *										this with Plat_Free().
 *
 * @exception   none
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	31st January   	2002	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
LPWSTR McbCreateXMLString(McbXMLElement * pHead, int nFormat, int *pnSize)
{
	LPWSTR lpszResult = NULL;
	int cbStr;

	if (pHead)
	{
		/*
		 *********************************************************************
		 * Recursively Calculate the size of the XML string
		 *********************************************************************
		 */
		nFormat = nFormat ? 0 : -1;
		cbStr = McbCreateXMLStringR(pHead, 0, nFormat);
		Assert(cbStr);

		/*
		 *********************************************************************
		 * Alllocate memory for the XML string + the NULL terminator and
		 * create the recursively XML string.
		 *********************************************************************
		 */		
		lpszResult = (LPWSTR)Plat_Alloc( (cbStr+1) * sizeof(WCHAR) );

		if (lpszResult)
		{
			McbCreateXMLStringR(pHead, lpszResult, nFormat);

			if (pnSize) *pnSize = cbStr;
		}
	}

	return lpszResult;

}/* McbCreateXMLString */
