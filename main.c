#include "jspic.h"
#include "json.h"
#include "twitter.h"

#define SLAVE 1

#ifdef SLAVE

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
#endif
#ifdef MASTER

#include "jspic.h"
#include "json.h"
#include "twitter.h"

void call2() {
    static char message[50];
    int value = JsonGetValue(AsyncMessage, "sensor");
    JsonGetString(AsyncMessage, "name", message);
    sprintf(AsyncMessage, "%s\n", message);
    SerialWrite(AsyncMessage);
}

void call() {
    WireGetString(0x4F, call2);
}

void hello() {

}

void onSetup() {
    //Setup I2C master
    WireBegin();
    SerialBegin();
    SetInterval(40, call);

    TwitterSignUp("@sotownesnd");
    TwitterAddWireSlave(0x4F);
    TwitterRegisterHashtag("#hello", hello);
}

void onLoop() {
}

#endif

