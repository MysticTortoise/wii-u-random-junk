#include "GameInput.hpp"

#include "HelperStandard.hpp"

#include "vpad/input.h"


void Input::WiiUGamepad::processInput(){
    VPADStatus padStatuses[16];
    VPADStatus* padStatusPointer = padStatuses;
    VPADReadError readError;
    int success = VPADRead(VPAD_CHAN_0,padStatusPointer,16,&readError);
    if(success || readError == VPAD_READ_SUCCESS){
        for(auto &[key, val] : buttons){
            val.wasPressedLastFrame = val.isPressed;

            val.isPressed = (padStatuses[0].hold & ButtonTypeToVPAD.at(val.buttonType)); // Check if button held.
        }


    } else {
        switch (readError)
        {
        case VPAD_READ_SUCCESS:
            //print("VPAD Read Error: task failed successfuly.");
            break;
        case VPAD_READ_NO_SAMPLES:
            print("VPAD Read Error: No new sample data to write.");
            break;
        case VPAD_READ_INVALID_CONTROLLER:
            print("VPAD Read Error: Invalid Channel/Controller.");
            break;
        case VPAD_READ_BUSY:
            print("VPAD Read Error: Channel busy - Likely accessed by another thread.");
            break;
        case VPAD_READ_UNINITIALIZED:
            print("VPAD Read Error: Vpad is uninitialized. Please call VPADInit();");
            break;
        
        default:
            print("VPAD Read Error: Unknown Error Reason");
            break;
        }
    }
}
