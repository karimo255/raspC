#include "server.h"

extern char *new_user;

void lst_print(const struct client *e)

{

	for( ; e != NULL ; e = e->next )

	{
		printf("************ \n");
		process(e->name );
		process(e->session_id );

	}

}

char *lst_json(struct client **lst){

	cJSON *root,*root_object,*root_object_array;	

	root = cJSON_CreateArray();
	root_object=cJSON_CreateObject();
	cJSON_AddItemToArray(root,root_object);
	root_object_array = cJSON_CreateArray();

	cJSON_AddStringToObject(root_object, "request", "count_client");			            
	cJSON_AddNumberToObject(root_object, "data", get_client_count());
	cJSON_AddItemToObject(root_object, "users", root_object_array);
	if(new_user)
	cJSON_AddStringToObject(root_object, "user_changed", new_user);			            



	cJSON *prev=NULL;

	while( *lst != NULL ) 
	{
		cJSON *root_object_array_object = cJSON_CreateObject();
		cJSON_AddStringToObject(root_object_array_object, "user", (*lst)->name);
		cJSON_AddStringToObject(root_object_array_object, "id", (*lst)->session_id);
		cJSON_AddNumberToObject(root_object_array_object, "gid", (*lst)->gid);		
		if (!prev) root_object_array->child = root_object_array_object;
		else prev->next = root_object_array_object, root_object_array_object->prev = prev;
		prev = root_object_array_object;
		lst = &(*lst)->next;
	}

    char *json=NULL;
    json = (char *) malloc (sizeof(cJSON_Print(root)));      
    json=cJSON_Print(root);
    
    
    free(root);free(root_object);free(root_object_array);   
    return json;


}

int lst_append(struct client **lst, char *name,int uid,int gid,char *session_id)

{

	struct client *neuesclient;
	int i=0;

	while( *lst != NULL ) 

	{
		i++;
		lst = &(*lst)->next;

	}


	neuesclient = malloc(sizeof(struct client)); 

	strcpy(neuesclient->name,name);
	strcpy(neuesclient->session_id,session_id);	
	neuesclient->uid = uid;
	neuesclient->gid = gid;

	neuesclient->next = NULL;


	*lst = neuesclient;
	i++;

	return i;

}

int lst_replace(struct client **lst, char *name,int uid, int gid,char *session_id)

{
	int i=0;
	while( *lst != NULL ) 

	{
		
		if((*lst)->uid==uid){	
			strcpy((*lst)->name,name);	
			strcpy((*lst)->session_id,session_id);				
			(*lst)->gid=gid;
			return i;
		}
		lst = &(*lst)->next;

	}

	return -1;
}

int lst_count(struct client **lst)

{
	return sizeof(lst)/sizeof(lst[0]);
}



int lst_remove(struct client **lst,int uid)

{
	struct client *prev=NULL;
	int i=0;

	if(*lst != NULL && (*lst)->uid==uid){
		
		struct client *tmp_lst;

		tmp_lst= (*lst)->next;
		free(*lst);

		*(lst)=tmp_lst;

	}else{
		
		while( *lst != NULL ) 

		{
			i++;
			if((*lst)->uid==uid){
				if(prev->next->next!=NULL){
					free(prev->next);

					prev->next=(*lst)->next;
				}else{
					free(prev->next);					
					prev->next=NULL;
					break;
				}

			}
			prev=(*lst);
			
			/*iteration*/
			lst = &(*lst)->next;

		}
		
	}

	return i;
}

int lst_find(struct client **lst, int uid)

{

	int i=0;

	while( *lst != NULL ) 

	{
		i++;
		if((*lst)->uid==uid){	
			return i;
		}			
		lst = &(*lst)->next;

	}

	return -1;
}