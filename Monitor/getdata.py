# This Python file uses the following encoding: utf-8

# if__name__ == "__main__":
#     pass

import urllib.request #python3
API_KEY='gnzeKvd5HGejpFUHOCW2FspUWtw='
def http_get_data():
    url='http://api.heclouds.com/devices/686117008/datapoints'
    request = urllib.request.Request(url)
    request.add_header('api-key',API_KEY)
    request.get_method = lambda:'GET'           # 设置HTTP的访问方式
    request = urllib.request.urlopen(request)
    return request.read()
post = str(http_get_data())
RH=post.split('datapoints":')[1].split('"value":')[1].split('}')[0]
TMP=post.split('datapoints":')[2].split('"value":')[1].split('}')[0]
RH = int(RH)
TMP = int(TMP)


def getRH():
    return RH
def getTMP():
    return TMP


