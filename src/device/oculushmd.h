#pragma once

#include <OVR_CAPI_0_5_0.h>

class OculusHMD {

public:
    OculusHMD(int window_id);
    ~OculusHMD();

private:
    bool initSuccess;
    ovrHmd hmd; 
};