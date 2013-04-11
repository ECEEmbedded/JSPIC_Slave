#include "jspic.h"
#include "json.h"
#include "twitter.h"


void call() {
    static char name[100];
    strcpy(name, "shitface");
    static int value = 0;
    JsonNew(AsyncMessage);
    JsonSetString(AsyncMessage, "name", name);
    JsonSetValue(AsyncMessage,"sensor", value);
    ++value;

    JWireRespond(AsyncMessage);
}

void onSetup() {
    SerialBegin();

    //SetInterval(100, call);
    JWireBegin(0x4F);
    JWireOnRequest(call);;
}

void onLoop() {

}