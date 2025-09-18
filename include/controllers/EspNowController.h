#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class EspNowController
{
public:
private:
    typedef struct data_message
    {
        int16_t values[12];
        uint8_t id;
    } data_message;
    data_message myData;
    esp_now_peer_info_t peerInfo;
    
};

extern EspNowController espNowController;