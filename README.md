# dfplayer


modify fbdev.ini like this

```
/ # cat /config/fbdev.ini
[FB_DEVICE]
FB_HWLAYER_ID = 1
FB_HWWIN_ID = 0
FB_HWLAYER_DST = 3
FB_HWWIN_FORMAT = 5
FB_HWLAYER_OUTPUTCOLOR = 1
FB_WIDTH = 1024
FB_HEIGHT = 600
FB_TIMMING_WIDTH = 1920
FB_TIMMING_HEIGHT = 1080
FB_MMAP_NAME = E_MMAP_ID_FB
FB_BUFFER_LEN = 1200
#unit:Kbyte,4096=4M, fbdev.ko alloc size = FB_BUFFER_LEN*1024
```
