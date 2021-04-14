#include <stdio.h>
#include <string.h>

/* this part need a external C library called libghttp.*/
/* Downloaded at http://www.linuxfromscratch.org/blfs/view/5.1/gnome/libghttp.html */

#include <ghttp.h>


int http(int temp, int humi)
{
    char *uri = "http://api.heclouds.com/devices/686117008/datapoints";
    char *APIKEY = "gnzeKvd5HGejpFUHOCW2FspUWtw=";
    ghttp_request *request = NULL;
    ghttp_status status;
    char *buf;
	/* HTTP format example: all[2048] = "{'datastreams':[{"id":"tempreture","datapoints":[{"value":temperature}]}]}"; */
	char part1[256];
	char TMP[8];
	char RH[8]
	char part2[256];
	char retbuf[128];
	char end[8];
	int len;
 
  /* HTTP message */
	strcpy(part1, "{'datastreams':[{\"id\":\"TMP\",\"datapoints\":[{\"value\":");
	sprintf(TMP, "%d", temp);
	strcpy(part2, "}]},{\"id\":\"RH\",\"datapoints\":[{\"value\":");
	sprintf(RH, "%d", humi);
	strcpy(end, "}]}]}");
	strcat(part1, TMP);
	strcat(part1, part2);
	strcat(part1, RH);
	strcat(part1, end);
 
	printf("%s\n", part1);		//test
 
	request = ghttp_request_new();
	if (ghttp_set_uri(request, uri) == -1)
		return -1;
	if (ghttp_set_type(request, ghttp_type_post) == -1)		//post mode
		return -1;
 
	ghttp_set_header(request,"api-key", APIKEY);
	len = strlen(part1);
	ghttp_set_body(request, part1, len);	//
	ghttp_prepare(request);
	status = ghttp_process(request);
	if (status == ghttp_error)
		return -1;
	buf = ghttp_get_body(request);	//test
	sprintf(retbuf, "%s", buf);
	ghttp_clean(request);	
	return 0;
}
