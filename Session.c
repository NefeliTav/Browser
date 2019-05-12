
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Session.h"

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;



struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
	//bonus
	TabNodePtr CalledBy;

};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};


InfoSessionPtr SessionNew(char * Add){    //allocate memory and initialize
	InfoSessionPtr list;

	list = (InfoSessionPtr)malloc(sizeof(struct InfoSession));
	list->CurrTab = (TabNodePtr)malloc(sizeof(struct TabNode));
	list->LastTab = list->CurrTab;                                //only one tab by now so currtab=firsttab=lasttab
	list->FirstTab = list->CurrTab;
	list->OpeningAddress = (char*)malloc(sizeof(char)*40);
	strcpy(list->OpeningAddress, Add);
	list->AuxTab = NULL;

	list->CurrTab->PrevTab = list->CurrTab;                          //because doubly circular linked list
	list->CurrTab->NextTab = list->CurrTab;
	list->CurrTab->CurrSite = (SiteNodePtr)malloc(sizeof(struct SiteNode));
	list->CurrTab->FirstSite = list->CurrTab->CurrSite;
	list->CurrTab->CalledBy = NULL;

	list->CurrTab->CurrSite->PrevSite = NULL;                        //only one site by now
	list->CurrTab->CurrSite->NextSite = NULL;
	list->CurrTab->CurrSite->UpTab = list->CurrTab;
	list->CurrTab->CurrSite->Address = (char*)malloc(sizeof(char)*40);
	strcpy(list->CurrTab->CurrSite->Address, Add);

	return list;

}

void SessionNewTab(InfoSessionPtr list){
	if(list!=NULL)
	{
		list->AuxTab = (TabNodePtr)malloc(sizeof(struct TabNode));
		list->AuxTab->PrevTab = list->LastTab;
		list->LastTab->NextTab = list->AuxTab;
		list->AuxTab->NextTab = list->FirstTab;
		list->LastTab = list->AuxTab;
		list->FirstTab->PrevTab = list->LastTab;
		list->CurrTab = list->AuxTab;
		list->AuxTab->CalledBy = NULL;

		list->AuxTab->CurrSite = (SiteNodePtr)malloc(sizeof(struct SiteNode));
		list->AuxTab->FirstSite = list->AuxTab->CurrSite;

		list->AuxTab->CurrSite->PrevSite = NULL;
		list->AuxTab->CurrSite->NextSite = NULL;
		list->AuxTab->CurrSite->UpTab = list->AuxTab;
		list->AuxTab->CurrSite->Address = (char*)malloc(sizeof(char)*40);
		strcpy(list->AuxTab->CurrSite->Address, "youtube");
		return;
	}
	return;
}



void SessionTabShow(InfoSessionPtr list){
	if (list->CurrTab->CurrSite->Address != NULL)
		printf("\nThe current site address is : %s\n",list->CurrTab->CurrSite->Address);
	else
		printf("There is no address\n");
}
void SessionTabNext(InfoSessionPtr list){
	list->CurrTab = list->CurrTab->NextTab;
}

void SessionTabPrev(InfoSessionPtr list){
	list->CurrTab = list->CurrTab->PrevTab;
}

void SessionTabMoveLeft(InfoSessionPtr list){
	list->AuxTab = list->CurrTab;
	if (list->CurrTab != list->FirstTab)
	{
		list->CurrTab = list->CurrTab->PrevTab;//antimetatheto currtab me prevtab
		list->AuxTab->PrevTab = list->AuxTab;
	}

}
void SessionTabMoveRight(InfoSessionPtr list){
	list->AuxTab = list->CurrTab;
	if (list->CurrTab != list->LastTab)
	{
		list->CurrTab = list->CurrTab->NextTab;//antimetatheto currtab me nexttab
		list->AuxTab->NextTab = list->AuxTab;
	}

}
void SessionNewOpeningAddress(char * Add,InfoSessionPtr list){
	strcpy(list->OpeningAddress,Add);
}

void SessionShowOpeningAddress(InfoSessionPtr list){
	printf("%s",list->OpeningAddress);
}

void SessionSiteNext(InfoSessionPtr list){
	if (list->CurrTab->CurrSite->NextSite!=NULL)
		list->CurrTab->CurrSite->NextSite = list->CurrTab->CurrSite;
}
void SessionSitePrev(InfoSessionPtr list){
	if (list->CurrTab->CurrSite->PrevSite!=NULL)
		list->CurrTab->CurrSite->PrevSite = list->CurrTab->CurrSite;
}

void SessionSiteShow(InfoSessionPtr list){
	if (list->CurrTab->CurrSite->Address != NULL)
		printf("\nThe current site address is : %s\n",list->CurrTab->CurrSite->Address);
}



void SessionTabClose(InfoSessionPtr list){
	SiteNodePtr temp = list->CurrTab->CurrSite;
	SiteNodePtr ptr;
	if (list->CurrTab != NULL){    						//if not deleted,delete it
		//delete address
		free(list->CurrTab->CurrSite->Address);
		list->CurrTab->CurrSite->Address = NULL;
		//delete all sites
		while(temp->PrevSite != NULL){
			ptr = temp->PrevSite;
			temp->PrevSite = ptr->PrevSite;
			free(ptr);
		}
		while(temp->NextSite != NULL){
			ptr = temp->NextSite;
			temp->NextSite = ptr->NextSite;
			free(ptr);
		}
		free(list->CurrTab->CurrSite);
		if (list->CurrTab->CalledBy == NULL){
			//fix list
			list->AuxTab = list->CurrTab;
			list->CurrTab->PrevTab->NextTab = list->CurrTab->NextTab;
			list->CurrTab->NextTab->PrevTab = list->CurrTab->PrevTab;
			list->CurrTab = list->CurrTab->NextTab;
		}
		else{
			//fix list
			list->AuxTab = list->CurrTab;
			list->CurrTab->PrevTab->NextTab = list->CurrTab->NextTab;
			list->CurrTab->NextTab->PrevTab = list->CurrTab->PrevTab;
			list->CurrTab = list->CurrTab->CalledBy;
		}
		//delete tab
		free(list->AuxTab);
		printf("Tab deleted\n");

	}
		if (list->LastTab == NULL){  				//last tab has been deleted
			SessionClose(list);						//delete the whole list
		}

}
void SessionClose(InfoSessionPtr list){
	SiteNodePtr ptr=NULL,temp=NULL;
	while (list->CurrTab != NULL){
		temp = list->CurrTab->CurrSite;
		//delete address
		free(list->CurrTab->CurrSite->Address);
		list->CurrTab->CurrSite->Address = NULL;
		//delete all sites
		while(temp->PrevSite != NULL){
			ptr = temp->PrevSite;
			temp->PrevSite = ptr->PrevSite;
			free(ptr);
		}
		while(temp->NextSite != NULL){
			ptr = temp->NextSite;
			temp->NextSite = ptr->NextSite;
			free(ptr);
		}
		//free(list->CurrTab->CurrSite);

		//fix list
		list->AuxTab = list->CurrTab;
		if (list->CurrTab != list->CurrTab->NextTab){
			list->CurrTab->PrevTab->NextTab = list->CurrTab->NextTab;
			list->CurrTab->NextTab->PrevTab = list->CurrTab->PrevTab;
			list->CurrTab = list->AuxTab->NextTab;
			//delete tab
			free(list->AuxTab);
			printf("Tab deleted\n");
		}
		else
		{
			//delete tab
			free(list->AuxTab);
			printf("Tab deleted\n");
			break;
		}
	}
	//delete list
	free(list->OpeningAddress);
	free(list);
	printf("Session deleted\n");

}

void SessionNewAddress(char *Add,InfoSessionPtr list){
	SiteNodePtr temp = (SiteNodePtr)malloc(sizeof(struct SiteNode));
	SiteNodePtr ptr;
	temp->PrevSite = list->CurrTab->CurrSite;
	temp->NextSite = list->CurrTab->CurrSite->NextSite;
	list->CurrTab->CurrSite = temp;
	while (temp->NextSite != NULL){  //delete sites
		ptr = temp->NextSite;
		temp->NextSite = ptr->NextSite;
		free(ptr);
	}
	temp->Address = (char *)malloc(sizeof(char)*40);
	strcpy(temp->Address,Add);

}
void SessionOpenNewTab(char * Add,InfoSessionPtr list){
	TabNodePtr temp = list->CurrTab;
	if(list!=NULL)
	{
		list->AuxTab = (TabNodePtr)malloc(sizeof(struct TabNode));
		list->AuxTab->PrevTab = list->LastTab;
		list->LastTab->NextTab = list->AuxTab;
		list->AuxTab->NextTab = list->FirstTab;
		list->LastTab = list->AuxTab;
		list->FirstTab->PrevTab = list->LastTab;
		list->CurrTab = list->AuxTab;
		list->AuxTab->CalledBy = temp;   //called by currtab

		list->AuxTab->CurrSite = (SiteNodePtr)malloc(sizeof(struct SiteNode));
		list->AuxTab->FirstSite = list->AuxTab->CurrSite;

		list->AuxTab->CurrSite->PrevSite = NULL;
		list->AuxTab->CurrSite->NextSite = NULL;
		list->AuxTab->CurrSite->UpTab = list->AuxTab;
		list->AuxTab->CurrSite->Address = (char*)malloc(sizeof(char)*40);
		strcpy(list->CurrTab->CurrSite->Address, Add);
		return;
	}
	return;
}
