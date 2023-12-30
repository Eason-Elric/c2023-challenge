#include "GoDataProcessor.h"

inline GoDataProcessor::GoDataProcessor(const std::string& EncoderName, int BoardSize, const std::string& DataDirectory) {
    this -> encoder = GetEncoder(EncoderName, 19);
    this -> DataDir = DataDirectory;
}

inline torch::data::datasets::TensorDataset GoDataProcessor::LoadGoData(int Samples) {
    vector<torch::Tensor> FeatureSet;
    vector<torch::Tensor> LabelSet;
    torch::Tensor Features;
    torch::Tensor Labels;
    ifstream inKifuName;
    inKifuName.open(DataDir + "/KifuName.txt", ios::in);
    std::string KifuName;
    for(int Sample = 0; Sample < Samples; Sample++) {
        getline(inKifuName, KifuName);
        ifstream inKifu;
        inKifu.open(DataDir + "/" + KifuName, ios::in);
        std::string kifu;
        while(getline(inKifu, kifu)) {
            SGFGame sgfGame = SGFGame(kifu);
            BoardState boardState;
            for(int i = 1; i <= sgfGame.GoNum; i++) {
                torch::Tensor Label = torch::zeros(19 * 19);
                Label[encoder -> EncodePoint(sgfGame.kifu[i].second)] = 1;

                FeatureSet.emplace_back(encoder -> Encode(boardState));
                LabelSet.emplace_back(Label);

                if(sgfGame.kifu[i].first != boardState.Player)
                    boardState.PassGo();
                boardState.DropGo(sgfGame.kifu[i].second);
            }
        }
        inKifu.close();
    }
    Features = torch::stack(FeatureSet, 0);
    Labels = torch::stack(LabelSet, 0);
    auto FeaturesAndLabels = torch::data::datasets::TensorDataset({Features, Labels});
    inKifuName.close();
    return FeaturesAndLabels;
}

inline torch::data::datasets::TensorDataset GoDataProcessor::LoadValData(int Samples) const {
    vector<torch::Tensor> FeatureSet;
    vector<torch::Tensor> LabelSet;
    torch::Tensor Features;
    torch::Tensor Labels;
    ifstream inKifu;
    inKifu.open("val_kifu/kifu", ios::in);
    std::string kifu;
    while(getline(inKifu, kifu) && FeatureSet.size() < Samples) {
        SGFGame sgfGame = SGFGame(kifu);
        BoardState boardState;
        for(int i = 1; i <= sgfGame.GoNum; i++) {
            torch::Tensor Label = torch::zeros({19, 19});
            Label[encoder -> EncodePoint(sgfGame.kifu[i].second)] = 1;

            FeatureSet.emplace_back(encoder -> Encode(boardState));
            LabelSet.emplace_back(Label);

            if(sgfGame.kifu[i].first != boardState.Player)
                boardState.PassGo();
            boardState.DropGo(sgfGame.kifu[i].second);
        }
    }
    Features = torch::stack(FeatureSet, 0);
    Labels = torch::stack(LabelSet, 0);
    auto FeaturesAndLabels = torch::data::datasets::TensorDataset({Features, Labels});
    inKifu.close();
    return FeaturesAndLabels;
}

inline torch::data::datasets::TensorDataset GoDataProcessor::LoadSelfPlayingData(int Samples) const {
    vector<torch::Tensor> FeatureSet;
    vector<torch::Tensor> LabelSet;
    torch::Tensor Features;
    torch::Tensor Labels;
    ifstream inKifu;
    inKifu.open("SelfPlayingData/kifu", ios::in);
    std::string kifu;
    while(getline(inKifu, kifu) && FeatureSet.size() < Samples) {
        int Winner = kifu[0] - '0';
        SGFGame sgfGame = SGFGame(kifu);
        BoardState boardState;
        for(int i = 1; i <= sgfGame.GoNum; i++) {
            torch::Tensor Label = torch::zeros({19, 19});
            Label[encoder -> EncodePoint(sgfGame.kifu[i].second)] = sgfGame.kifu[i].first == Winner ? 1 : -1;

            FeatureSet.emplace_back(encoder -> Encode(boardState));
            LabelSet.emplace_back(Label);

            if(sgfGame.kifu[i].first != boardState.Player)
                boardState.PassGo();
            boardState.DropGo(sgfGame.kifu[i].second);
        }
    }
    Features = torch::stack(FeatureSet, 0);
    Labels = torch::stack(LabelSet, 0);
    auto FeaturesAndLabels = torch::data::datasets::TensorDataset({Features, Labels});
    inKifu.close();
    return FeaturesAndLabels;
}
