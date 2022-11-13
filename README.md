# lulzlyn - franklyn bypass

Franklyn takes a screenshot of the whole monitor screen using the winapi.

Decompiled routine looks as follows:

<img src="https://i.imgur.com/RqDvADP.png">

Hooking it and returning an invalid or new bitmap basically does the job quite well. A nice 1920x1080 nyan cat is being sent to the caller in this poc.  
Discovering this probably took less time then for ida to analyze this huge binary lmao.