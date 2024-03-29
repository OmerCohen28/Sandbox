import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
from bs4 import BeautifulSoup
import time

#url = "https://docs.microsoft.com/en-us/windows/win32/fileio/file-management-functions"
#url = "https://learn.microsoft.com/en-us/windows/win32/winsock/winsock-functions"
urls = ["https://learn.microsoft.com/en-us/windows/win32/sysinfo/registry-functions","https://learn.microsoft.com/en-us/windows/win32/winsock/winsock-functions","https://docs.microsoft.com/en-us/windows/win32/fileio/file-management-functions"]
count =0 
for url in urls:
    page = requests.get(url)
    soup = BeautifulSoup(page.content, "html.parser")

    links = []

    functions = soup.find_all("tr")
    count+=len(functions)
print(count)
exit(1)
for function in functions:
    name = function.find("td")
    if name:
        print(name.text)
        link = name.find("a")
        if "href" in link.attrs:
            print(link["href"])
            links.append(link["href"])
        
#import requests
#from bs4 import BeautifulSoup
session = requests.Session()
retry = Retry(connect=3, backoff_factor=0.5)
adapter = HTTPAdapter(max_retries=retry)
session.mount('http://', adapter)
session.mount('https://', adapter)
recevied = []
#link = "https://docs.microsoft.com/en-us/windows/desktop/api/FileAPI/nf-fileapi-writefilegather"
for link in links:
    try:
        page = session.get(f"https://docs.microsoft.com{link}")
    except requests.exceptions.ConnectionError:
        continue
    soup = BeautifulSoup(page.content, "html.parser")
    time.sleep(2)
    params = soup.find("code", class_="lang-cpp")
    try:
        params.text
    except AttributeError:
        params = soup.find("code",class_ = "lang-c++")
    recevied.append(params.text)
'''proto = soup.find("div", class_="syntax")
print(proto.text)'''

print(len(recevied))

with open("reg_functions.txt",'w') as file:
    file.writelines(recevied)