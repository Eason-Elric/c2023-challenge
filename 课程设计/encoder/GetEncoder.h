#ifndef GO_GETENCODER_H
#define GO_GETENCODER_H

#include <string>
#include "encoder/encoder.h"
#include "encoder/OnePlaneEncoder.cpp"
#include "encoder/ThreePlaneEncoder.cpp"
#include "encoder/EightPlaneEncoder.cpp"

inline Encoder * GetEncoder(const std::string& EncoderName = "OnePlane", int BoardSize = 19) {
    Encoder * encoder;
    if(EncoderName == "OnePlane")
        encoder = new OnePlaneEncoder(BoardSize);
    else if(EncoderName == "ThreePlane")
        encoder = new ThreePlaneEncoder(BoardSize);
    else if(EncoderName == "EightPlane")
        encoder = new EightPlaneEncoder(BoardSize);
    return encoder;
}

#endif //GO_GETENCODER_H
