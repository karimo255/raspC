#include "server.h"



void printliste(const struct client *e)

{

	for( ; e != NULL ; e = e->next )

	{
		process("from Listenendes");
		process(e->name );

	}

}



void append(struct client **lst, char *name,int uid,int gid)

{

	struct client *neuesclient;



	while( *lst != NULL ) 

	{

		lst = &(*lst)->next;

	}


    neuesclient = malloc(sizeof(*neuesclient)); /* erzeuge ein neues client */

	neuesclient->name = name;
	neuesclient->uid = uid;
	neuesclient->gid = gid;

    neuesclient->next = NULL; /* Wichtig für das Erkennen des Listenendes     */


	*lst = neuesclient;

}

int replace(struct client **lst, char *name,int uid, int gid)

{
	while( *lst != NULL ) 

	{
		
		if((*lst)->uid==uid){	
			(*lst)->name=name;	
			(*lst)->gid=gid;
			return 0;
		}
		lst = &(*lst)->next;
	
	}

	return -1;
}

int count(struct client **lst)

{
	return sizeof(lst)/sizeof(lst[1]);
}

int removeC(struct client **lst,int uid)

{
	while( *lst != NULL ) 

	{
		if((*lst)->uid==uid){	
			*lst=NULL;
		}			
		lst = &(*lst)->next;
			
	}

	return 1;
}

int find(struct client **lst, int uid)

{


	while( *lst != NULL ) 

	{
		
		if((*lst)->uid==uid){	
			return 0;
		}			
		lst = &(*lst)->next;
		
	}

	return -1;
}
