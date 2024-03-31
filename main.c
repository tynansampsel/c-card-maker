#include <stdio.h>
#include <cJSON.h>

int printJson(){

    FILE *fp = fopen("../info.json", "r"); 
	if (!fp)perror("fopen");
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
  
    // read the file contents into a string 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 


	const cJSON *card = NULL;
	const cJSON *cards = NULL;
	int status = 0;
	cJSON *info_json = cJSON_Parse(buffer);

	if (info_json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		status = 0;
		cJSON_Delete(info_json);
    	return status;
	}

	printf("_\n");
	cards = cJSON_GetObjectItemCaseSensitive(info_json, "cards");
	
	cJSON_ArrayForEach(card, cards)
	{
		cJSON *name = cJSON_GetObjectItemCaseSensitive(card, "name");
		cJSON *text = cJSON_GetObjectItemCaseSensitive(card, "text");
		cJSON *id = cJSON_GetObjectItemCaseSensitive(card, "id");

		printf("id: %d name: %s text: %s \n", id->valuedouble, name->valuestring, text->valuestring);
	}


	// char *stringd = cJSON_Print(info_json);
	// if (stringd == NULL)
    // {
    //     fprintf(stderr, "Failed to print monitor.\n");
    // } else {
	// 	printf("%s \r\n",stringd);
	// }
	printf("x\n");
	

	cJSON_Delete(info_json);
    return status;

}

int main()
{
	int status = printJson();
	printf("%d\n", status);

}