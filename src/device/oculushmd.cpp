#include "oculushmd.h"

#include <iostream>

OculusHMD::OculusHMD(int window_id):initSuccess(false),hmd(NULL){
    // initialize OVR
    if(ovr_Initialize(NULL)){
        initSuccess = true;
        // check if Oculus device and create it if possible
        int numDevices = ovrHmd_Detect();
        std::cout << numDevices << " Oculus devices detected" << std::endl;
        if(numDevices > 0){
            // create HMD object if we have one
            hmd = ovrHmd_Create(0);
            // get information about the HMD
            if(hmd){
                ovrSizei resolution = hmd->Resolution;
                std::cout << "Oculus device detected with:" << std::endl;
                std::cout << "Resolution: " << resolution.w << " " << resolution.h << std::endl;
                // configure the tracking
                ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, ovrTrackingCap_Orientation);
                // get the tracking state
                ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
                /*std::cout << "Tracking state: " << ts.StatusFlags << std::endl;
                if(ts.StatusFlags & ovrStatus_OrientationTracked){
                    std::cout << "Orientation tracking OK" << std::endl;
                }
                if(ts.StatusFlags & ovrTrackingCap_MagYawCorrection){
                    std::cout << "Corrected yaw drift correction OK" << std::endl;
                }
                if(ts.StatusFlags & ovrTrackingCap_Position){
                    std::cout << "Position tracking OK" << std::endl;
                }*/
            }
        }
        // if there is no HMD, create a virtual one
        if(!hmd){
            hmd = ovrHmd_CreateDebug(ovrHmd_DK2);
        }
        // compute the FOV and texture sizes
        // configure rendering to initialize distortion rendering, passing API specific device handles, configuration flags and FOV data
        // bind to the window, TODO: not sure this is working at the moment because OpenGL might be initialized first
        if(ovrHmd_AttachToWindow(hmd, (void*)window_id, NULL, NULL)){
            std::cout << "Attached to the window" << std::endl;
        }else{
            std::cout << "Failed to attach to the window" << std::endl;
        }
    }else{
        std::cout << "LibOVR initialization failed" << std::endl;
    }
}

OculusHMD::~OculusHMD(){
    if(hmd){
        ovrHmd_Destroy(hmd);
    }
    if(initSuccess){
        ovr_Shutdown();    
    }
}