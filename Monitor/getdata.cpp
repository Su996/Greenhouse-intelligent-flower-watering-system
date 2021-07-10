  
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <ghttp.h>

using namespace std;

/* this part need a external C/C++ library called libghttp.*/
/* Downloaded at http://www.linuxfromscratch.org/blfs/view/5.1/gnome/libghttp.html */

int http_get_data()
{
    char *uri = "http://api.heclouds.com/devices/686117008/datapoints";
    char *APIKEY = "gnzeKvd5HGejpFUHOCW2FspUWtw=";
    ghttp_request *request = NULL;
    ghttp_status status;
    int bytes_read;
    int size;
    char *buf;
	/* HTTP format example: all[2048] = "{'datastreams':[{"id":"tempreture","datapoints":[{"value":temperature}]}]}"; */
	char TMP[8];
	char RH[8]
	int len;
    
    request = ghttp_request_new();
    if(ghttp_set_uri(request, uri) == -1)
       return -1;
    if(ghttp_set_type(request, ghttp_type_get) == -1)//get
    	 return -1;
    ghttp_prepare(request);
    status = ghttp_process(request);
    if(status == ghttp_error)
    	 return -1;
    cout << "Status code ->" << ghttp_status_code(request) << endl; 
    printf("Status code -> %d\n", ghttp_status_code(request));
    buf = ghttp_get_body(request);
 
    bytes_read = ghttp_get_body_len(request);
    size = strlen(buf);//size == bytes_read
    return 0;
}

get = str(http_get_data())
RH=get.split('datapoints":')[1].split('"value":')[1].split('}')[0] ;
TMP=get.split('datapoints":')[2].split('"value":')[1].split('}')[0] ;

cout << RH << endl; 
cout << TMP << endl; 
