#include "RLPolicy.h"

inline RLPolicy::RLPolicy(int GPU_id) {
    if (GPU_id >= 0 && torch::cuda::is_available()) {
        device = torch::Device(torch::kCUDA, (c10::DeviceIndex)GPU_id);
    }
    else
        device = torch::Device(torch::kCPU);
}

inline void RLPolicy::Initialize(int InChannels, int OutChannels, const std::string& PretrainedPath) {
    Module = RLPolicyModule(InChannels, OutChannels);
    if (!PretrainedPath.empty()) {
        auto NetPretrained = RLPolicyModule(InChannels, OutChannels);
        torch::load(NetPretrained, PretrainedPath);
        torch::OrderedDict<std::string, torch::Tensor> PretrainedDict = NetPretrained -> named_parameters();
        torch::OrderedDict<std::string, torch::Tensor> ModuleDict = Module -> named_parameters();

        for (auto &Pair: PretrainedDict) {
            if (ModuleDict.contains(Pair.key())) {
                ModuleDict[Pair.key()].copy_(Pair.value());
            }
        }

        torch::autograd::GradMode::set_enabled(false); // make parameters copying possible
        auto NewParams = ModuleDict;
        auto Params = Module -> named_parameters(true);
        auto Buffers = Module -> named_buffers(true);
        for (auto &Pair: NewParams) {
            auto Name = Pair.key();
            auto *Param = Params.find(Name);
            if (Param != nullptr) {
                Param->copy_(Pair.value());
            } else {
                auto *Buffer = Buffers.find(Name);
                if (Buffer != nullptr) {
                    Buffer -> copy_(Pair.value());
                }
            }
        }
        torch::autograd::GradMode::set_enabled(true);

        try {
            torch::save(Module, PretrainedPath);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

inline void RLPolicy::LoadWeights(const std::string &Path) {
    torch::load(Module, Path);
    Module -> eval();
}

inline void RLPolicy::Train(int Samples, int Epochs, int BatchSize, float LearningRate) {
    torch::data::datasets::TensorDataset TrainDataset = goDataProcessor.LoadSelfPlayingData(Samples);

    auto TrainLoadData =
            torch::data::make_data_loader<torch::data::samplers::RandomSampler>(std::move(TrainDataset), BatchSize);

    float TrainLoss = 0.0;
    float TrainAcc = 0.0;
    float BestAcc = 0.0;

    for(int Epoch = 1; Epoch <= Epochs; Epoch++) {
        int TrainBatch = 0;
        if(Epoch == (Epochs / 2))
            LearningRate *= 0.1;
        torch::optim::Adam optimizer(Module -> parameters(), LearningRate);
        for(auto iter : Module -> named_parameters())
            iter.value().set_requires_grad(true);

        for(auto& batch : *TrainLoadData) {
            auto data = batch[0].data;
            auto target = batch[1].data;
            auto output = Module -> forward(data);
            auto loss = torch::nn::functional::cross_entropy(output, target);
            optimizer.zero_grad();
            loss.backward();
            optimizer.step();
            TrainLoss += loss.item<float>();
            auto prediction = output.argmax(1);
            auto label = target.argmax(1);
            TrainAcc += torch::sum(prediction.eq(label)).item<float>() / (float)BatchSize;
            TrainBatch++;
        }
        cout << "Epoch: " << Epoch << " |Train Loss: " << TrainLoss / (float)TrainBatch << " |Train Acc:" << TrainAcc / (float)TrainBatch << endl;
        cout << endl;

        if(TrainAcc > BestAcc) {
            BestAcc = TrainAcc;
            torch::save(Module, "../Module/SLPolicy.pt");
        }

        TrainLoss = 0.0;
        TrainAcc = 0.0;
    }
}

inline float RLPolicy::Predict(BoardState boardState) {
    torch::Tensor Input = goDataProcessor.encoder -> Encode(boardState);
    auto Output = Module -> forward(Input);
    auto Prediction = Output.argmax(1);
    return Output[Prediction.item<int>()].item<float>();
}