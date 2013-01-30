/*------------------------------------------------------------------------
	Chain.h
	author : PersyZhang
	date   : 6/7/95.
-------------------------------------------------------------------------*/
#ifndef   __CHAIN_H
#define   __CHAIN_H
#include  "CommDef.h"


class  CHAINHEADER;
class  CHAINITEM{
  private  :
	  CHAINHEADER * pHeader;
	  CHAINITEM  *  pNext;
	  CHAINITEM  *  pPrevious;
	  int           cntr;
  public   :
	  CHAINITEM(){
				  pNext = NULL;
				  pPrevious = NULL;
				  pHeader = NULL;
				  cntr = 0;
				 }
	  virtual ~CHAINITEM(){;}
	  void  SetPrevious(CHAINITEM * pCi){
		  pPrevious = pCi;
	  }
	  void  SetNext(CHAINITEM * pCi){
		  pNext = pCi;
	  }
	  void  SetHeader(CHAINHEADER * p){
		  pHeader = p;
	  }
	  CHAINHEADER * GetHeader(){
		  return pHeader;
	  }
	  CHAINITEM * Next(){return pNext;}
	  CHAINITEM * Previous(){return pPrevious;}
	  int   IncCounter(){return ++cntr;}
	  int   DecCounter(){return --cntr;}
	  void  SetCounter(int i){ cntr = i;} 
	  
	  int	Counter()const{
		  return cntr;
	  }  

	  void	DisConnect();
};

//chain header
class CHAINHEADER : public CHAINITEM{
 friend  class CHAINITEM;
 private  :
	 int          num;
	 CHAINITEM  * pEnd;
	 CHAINITEM  * pHead;
	 CHAINITEM  * pCurrent;
  public  :
	 CHAINHEADER() {
				  pEnd = NULL;
				  pHead = NULL;
				  pCurrent = NULL;
				  num = 0;}
	 ~CHAINHEADER(){;}

	 /*
	  * Move To number i chainitem
 	  */
	 CHAINITEM *   MoveTo(int i);
	 
	 
	 /* add ChainItem to the end of chain  */
	 BOOL   Add(CHAINITEM * pCi);  
	 /* Insert ChainItem to the head of chain */
	 BOOL   Insert(CHAINITEM * pCi);  
	 /* Insert ChainItem to the previous of current */
	 BOOL   InsertBeforeCurrent(CHAINITEM * pCi);  
	 

	 //ly write 
	 // Insert a chain item to the after of current chainitem
	 BOOL   InsertAfterCurrent(CHAINITEM * pCi);
	
	 CHAINITEM *   Remove(); 
	
	  //outchain and delete current chainitem  always return next item
	 CHAINITEM *  OutChain();
     
	 /*
	  * Outchain delete all chainitems
	  */
	 BOOL   RemoveAll();
	 
	 /*
	  * Outchain all chainitem
	  */
	 BOOL   OutAll();
	 
	 BOOL   Insert(){return TRUE;}
	 int    GetNum()const{
		 return num;
	 }
	 void    SetNum(int i){
		 num = i;
	 }


	 /*
	  * Top - Bottom 
	  */
	 CHAINITEM * First(){pCurrent = pHead;  return pCurrent;}
     inline CHAINITEM * Next();
	 inline CHAINITEM * NextCycle();
	 inline CHAINITEM * ViewFirst();
	 inline CHAINITEM * ViewNext();

	 /*
	  * Bottom - Top
	  */
	 CHAINITEM * Last(){pCurrent = pEnd; return pCurrent;}
	 inline CHAINITEM * Previous();
	 inline CHAINITEM * PreviousCycle();
	 inline CHAINITEM * ViewPrevious();

	 /*
	  * current chainitem
	  */
	 CHAINITEM * Current(){return pCurrent;}

	 //ly write
	 void SetCurrent(CHAINITEM *p)
	 {pCurrent = p;}

	 int  Get(CHAINITEM *p);
};

inline CHAINITEM * CHAINHEADER::Previous()
{
	if (pCurrent == pHead)
		return NULL;
	pCurrent = pCurrent->Previous();
	return pCurrent;
}

inline CHAINITEM * CHAINHEADER::PreviousCycle()
{
	if (!pCurrent)
		pCurrent = pEnd;
	else if (pCurrent == pHead)
		pCurrent = pEnd;
	else
    	pCurrent = pCurrent->Previous();
	
	return pCurrent;
}

inline CHAINITEM * CHAINHEADER::ViewFirst()
{
	return pHead;
}

inline CHAINITEM * CHAINHEADER::ViewPrevious()
{
	if (pCurrent == pHead)
		return NULL;
	return pCurrent->Previous();
}

inline CHAINITEM * CHAINHEADER::Next()
{
	if (!pCurrent)
		return NULL;
	pCurrent = pCurrent->Next(); 
	return pCurrent;
}

inline CHAINITEM * CHAINHEADER::NextCycle()
{
	if (!pCurrent)
		pCurrent = pHead;
	else if (pCurrent == pEnd)
		pCurrent = pHead;
	else
     	pCurrent = pCurrent->Next(); 
	
	return pCurrent;
}

inline CHAINITEM * CHAINHEADER::ViewNext()
{
	if (!pCurrent)
		return NULL;
	return pCurrent->Next(); 
	
}


class	CPointerChainItem : public CHAINITEM
{
private:
	void	*	m_ptr;
public:
	void	* GetPointer(){
		return m_ptr;
	}
	void	SetPointer(void * ptr){
		m_ptr = ptr;
	}
	CPointerChainItem(){
		m_ptr = NULL;
	}

};

class CPointerChainHeader : public CHAINHEADER
{
public:
	//include new
	BOOL   AddPointer(void *pPointerVal);
	BOOL   RemovePointer(void *pPointerVal);
};

#endif


