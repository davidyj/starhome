/*---------------------------------------------------------------------------
	  OBJbase.CPP
	  Author  : PersyZhang
	  Date    : 7/6/95;
---------------------------------------------------------------------------*/
#include  "../stdafx.h"
#include  "Chain.h"
#include  "dbg.h"

///////////////////
// self out chain
void	CHAINITEM::DisConnect()
{
   if (pHeader)
   {
   	   pHeader->SetNum(pHeader->GetNum() - 1);
	   if (pHeader->GetNum() == 0)
	   {
		   pHeader->pHead = NULL;
		   pHeader->pEnd = NULL;
		   pHeader->pCurrent = NULL;
	   }
	   else
	   {
		   //if first item
   		   if  ( pHeader->pHead == this )
		   {
			   pHeader->pHead = pNext;
			   pHeader->pCurrent = pNext;
		   }

		   //if last item
		   if  ( pHeader->pEnd == this )
		   {
			   pHeader->pEnd = pPrevious;
			   pHeader->pCurrent = pPrevious;
		   }

		   //else
		   if  ( pHeader->pCurrent == this )
		   {
			   /*******************************************
			   !!! IMPORTANT !!!  RULE
			   current pointer is always moving to Next if possible
			   *******************************************/
			   //pHeader->pCurrent = pPrevious;
			   pHeader->pCurrent = pNext;
		   }
	   }
   }

   //connect previous item and next item
   if (pNext)
	   pNext->SetPrevious(pPrevious);
   if (pPrevious)
	   pPrevious->SetNext(pNext);

   pNext = NULL;
   pPrevious = NULL;
   pHeader = NULL;

}

//move current pointer to specified position
CHAINITEM *  CHAINHEADER::MoveTo(int i)
{
	// modified by Jerry 2002.9.24.
	if ( (pCurrent = pHead) )
	{
		for(int j=0;j<i;j++)
		{
			if (pCurrent->Next())
				pCurrent = pCurrent->Next();
			else
				return NULL;
		}
	}
	return  pCurrent;
}

// add a chain item to the end of the chain
BOOL CHAINHEADER::Add (CHAINITEM * pCi) {
					Assert(pCi);

					//DisConnect if item already in a chain
					 pCi->DisConnect();

					 // first note
					 if  (!num){
							 pEnd = pCi;
							 pHead = pCi;
							 pCurrent = pCi;
							 SetNext(pCi);
							 pCi->SetPrevious((CHAINITEM *)this);
							 pCi->SetNext(NULL);
							 num++;
							 }
					 else {
							 pEnd->SetNext(pCi);
							 pCi->SetPrevious(pEnd);
							 pCi->SetNext(NULL);
							 pEnd = pCi;
							 num++;
							 }
					 pCi->SetHeader(this);
					return TRUE;
 }


// Insert a chain item to the head of the chain
BOOL CHAINHEADER::Insert (CHAINITEM * pCi) {
					Assert(pCi);
					 // first note
					 if  (!num){
							 pEnd = pCi;
							 pHead = pCi;
							 pCurrent = pCi;
							 SetNext(pCi);
							 pCi->SetPrevious((CHAINITEM *)this);
							 pCi->SetNext(NULL);
							 num++;
							 }
					 else {
							 SetNext(pCi);
							 pCi->SetPrevious((CHAINITEM *)this);
							 pCi->SetNext(pHead);
							 pHead->SetPrevious(pCi);
							 pHead = pCi;
							 num++;
							}
					 pCi->SetHeader(this);
					return TRUE;
 }


// Insert a chain item to the previous of current chainitem
BOOL CHAINHEADER::InsertBeforeCurrent (CHAINITEM * pCi) {
					 // first note
					 if  (!num){
							 pEnd = pCi;
							 pHead = pCi;
							 pCurrent = pCi;
							 SetNext(pCi);
							 pCi->SetPrevious((CHAINITEM *)this);
							 pCi->SetNext(NULL);
							 num++;
							 }
					 else {
						     if (pCurrent == pHead)
								 pHead = pCi;

							 pCi->SetNext(pCurrent);
							 pCi->SetPrevious(pCurrent->Previous());
							 pCurrent->Previous()->SetNext(pCi);
							 pCurrent->SetPrevious(pCi);

							 num++;
							}
					 pCi->SetHeader(this);
					return TRUE;
 }


//write by ly
// Insert a chain item to the after of current chainitem
BOOL   CHAINHEADER::InsertAfterCurrent(CHAINITEM * pCi)
{
	CHAINITEM * pNext = Next();
	if( pNext )
		InsertBeforeCurrent( pCi );
	else Add( pCi );
	return TRUE;
}



 // remove  chain item
 CHAINITEM * CHAINHEADER::Remove()
 {
	  CHAINITEM *    pPreviousCurrent = pCurrent;


	  if (pCurrent)
	  {
		  CHAINITEM *    pReturn = pCurrent->Next();
		  /*
		  if (pCurrent == pHead){
				pHead = pCurrent->Next();
				pNextCurrent = pHead;
		  }
		  if (pCurrent == pEnd)
		  {
				pEnd = pCurrent->Previous();
				pNextCurrent = pEnd;
		  }
		  if (pCurrent->Previous())
				(pCurrent->Previous())->SetNext(pCurrent->Next());
		  else
				return FALSE;
		  if (pCurrent->Next())
				 (pCurrent->Next())->SetPrevious(pCurrent->Previous());

		  if (!pNextCurrent)
			   pNextCurrent = pCurrent->Previous();

		  delete  pCurrent;

		  pCurrent = pNextCurrent;
		  num--;
    	  if (!num)
		  {
	          pEnd = NULL;
	          pHead = NULL;
	          pCurrent = NULL;
	      }
		  */
  		/***********************************
		IMPORTANT!!!
		After call DisConnect() pCurrent will be chged
		************************************/
		  pCurrent->DisConnect();
		  delete pPreviousCurrent;
		  return  pReturn;
	  }
	  else
		   return   NULL;

 }


 // out chain
CHAINITEM* CHAINHEADER::OutChain(){
	/*
		CHAINITEM*    pNextCurrent = NULL;
		CHAINITEM*    pReturn = pCurrent;
		   if (pCurrent)
		   {
			  if (pCurrent == pHead)
			  {
					pHead = pCurrent->Next();
					pNextCurrent = pHead;
			  }
			  if (pCurrent == pEnd)
			  {
					pEnd = pCurrent->Previous();
					pNextCurrent = pEnd;
			  }
			  if (pCurrent->Previous())
					(pCurrent->Previous())->SetNext(pCurrent->Next());
			  else
					 Assert(FALSE);

  			  if (pCurrent->Next())
					(pCurrent->Next())->SetPrevious(pCurrent->Previous());

			  num--;
			  if (!num)
			  {
				  pEnd = NULL;
				  pHead = NULL;
				  pCurrent = NULL;
			  }
			  else
			  {
				  if (!pNextCurrent)
    				pNextCurrent = pCurrent->Previous();
     			  //if (pCurrent->Next())
	    		  //	(pCurrent->Next())->SetPrevious(pCurrent->Previous());
    			  pCurrent = pNextCurrent;
			  }
			  pReturn->SetHeader(NULL);
		  }

		  return pReturn;
	  */
		/***********************************
		IMPORTANT!!!
		After call DisConnect() pCurrent will be chged
		************************************/
		CHAINITEM*    pReturn = pCurrent;
		if (pCurrent)
			pCurrent->DisConnect();
		return pReturn;


 }

// write by liuyan
 int  CHAINHEADER::Get(CHAINITEM *p)
 {
	 int i = 0;
	 CHAINITEM * temp = First();
	 while(temp)
	 {
		if(p == temp)
			return i;
		temp = Next();
		i++;
	 }

	 return -1;
 }


 BOOL CHAINHEADER::OutAll(){
	Last();
	while(num > 0){
		OutChain();
	  ;
	}
	num = 0;
	return TRUE;
 }

 BOOL CHAINHEADER::RemoveAll(){
	First();
	while(Remove()){
	  ;
	}
	num = 0;
	return TRUE;
 }

BOOL CPointerChainHeader::AddPointer(void *pPointerVal)
{
	CPointerChainItem *pPointer = new CPointerChainItem;
	pPointer->SetPointer(pPointerVal);

	return Add(pPointer);
}

BOOL CPointerChainHeader::RemovePointer(void *pPointerVal)
{
	CPointerChainItem *pPointer = (CPointerChainItem *)First();
	while(pPointer)
	{
		if (pPointer->GetPointer() == pPointerVal)
		{
			CHAINHEADER::Remove();
			return true;
		}
		pPointer = (CPointerChainItem *)Next();
	};
	return false;
}
