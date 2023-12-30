#ifndef GO_GODATAPROCESSOR_H
#define GO_GODATAPROCESSOR_H

#include <string>
#include <torch/utils.h>
#include <torch/data.h>
#include <torch/data/datasets.h>
#include "../SGFGame.cpp"
#include "encoder.h"
#include "../GetEncoder.h"

class GoDataProcessor {
    public:
        Encoder * encoder{};

    private:
        std::string DataDir;

    public:
        explicit GoDataProcessor(const std::string& EncoderName = "OnePlane",
                                 int BoardSize = 19,
                                 const std::string& DataDirectory = R"(kifu)");
        torch::data::datasets::TensorDataset LoadGoData(int Samples);
        torch::data::datasets::TensorDataset LoadValData(int Samples) const;
        torch::data::datasets::TensorDataset LoadSelfPlayingData(int Samples) const;
};

#endif //GO_GODATAPROCESSOR_H
