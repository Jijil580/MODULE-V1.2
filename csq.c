#include "quecktel.h"


#define CSQ_ENTRY(rssi, ber) "\r\n+CSQ: " #rssi "," #ber "\r\n\r\nOK\r\n"
#define CSQ_ENTRIES(rssi) CSQ_ENTRY(rssi,0), CSQ_ENTRY(rssi,1), CSQ_ENTRY(rssi,2), CSQ_ENTRY(rssi,3), CSQ_ENTRY(rssi,4), CSQ_ENTRY(rssi,5), CSQ_ENTRY(rssi,6), CSQ_ENTRY(rssi,7),CSQ_ENTRY(rssi,99)
 

const char *SIGNAL_QUALITY[]=
{   

    CSQ_ENTRIES(0),//CSQ_ENTRY(rssi,0), CSQ_ENTRY(rssi,1), CSQ_ENTRY(rssi,2), CSQ_ENTRY(rssi,3), CSQ_ENTRY(rssi,4), CSQ_ENTRY(rssi,5), CSQ_ENTRY(rssi,6), CSQ_ENTRY(rssi,7),CSQ_ENTRY(rssi,99)
    CSQ_ENTRIES(1),
    CSQ_ENTRIES(2),
    CSQ_ENTRIES(3),
    CSQ_ENTRIES(4),
    CSQ_ENTRIES(5), 
    CSQ_ENTRIES(6),
    CSQ_ENTRIES(7),
    CSQ_ENTRIES(8), 
    CSQ_ENTRIES(9),
    CSQ_ENTRIES(10), 
    CSQ_ENTRIES(11), 
    CSQ_ENTRIES(12), 
    CSQ_ENTRIES(13), 
    CSQ_ENTRIES(14), 
    CSQ_ENTRIES(15),
    CSQ_ENTRIES(16),
    CSQ_ENTRIES(17),
    CSQ_ENTRIES(18), 
    CSQ_ENTRIES(19), 
    CSQ_ENTRIES(20),
    CSQ_ENTRIES(21), 
    CSQ_ENTRIES(22), 
    CSQ_ENTRIES(23), 
    CSQ_ENTRIES(24), 
    CSQ_ENTRIES(25),
    CSQ_ENTRIES(26), 
    CSQ_ENTRIES(27), 
    CSQ_ENTRIES(28), 
    CSQ_ENTRIES(29), 
    CSQ_ENTRIES(30),
    CSQ_ENTRIES(31)
    CSQ_ENTRIES(99)
};