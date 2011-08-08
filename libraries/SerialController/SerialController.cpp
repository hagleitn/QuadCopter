#include <SerialController.h>
#include <CommandParser.h>

void SerialController::executeCommand() {
    if (startSleep != 0) {
        if (millis()-startSleep < sleepTime) {
            return;
        } else {
            sleepTime = 0;
            startSleep = 0;
        }
    }
    
    const char *cmd = token.read();
    if (0 != cmd) {
        if (cmd[0] == 'z' || cmd[0] == 'Z') {
            int x = 0;
            int ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { parser.fail(); }
            sleepTime = x;
            startSleep = millis();
        } else {
            parser.doCmd(cmd);
        }
    }
}
