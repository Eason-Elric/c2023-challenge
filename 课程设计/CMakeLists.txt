cmake_minimum_required(VERSION 3.27)
project(Go)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)
find_package(Eigen3 REQUIRED)
set(CMAKE_PREFIX_PATH D:/libtorch-win-shared-with-deps-debug-2.1.2+cu121/libtorch)
find_package(Torch REQUIRED)

add_executable(Go main.cpp
        rdrawing/rdrawing.h
        rdrawing/rdrawing.c
        rdrawing/utils.c
        board/board.h
        board/board.cpp
        board/gostring.h
        board/boardstate.cpp
        board/boardstate.h
        agent.h
        MCTS/MCTS.cpp
        MCTS/MCTS.h
        encoder/SGFGame.cpp
        encoder/SGFGame.h
        encoder/encoder/encoder.h
        encoder/encoder/GoDataProcessor.cpp
        encoder/encoder/GoDataProcessor.h
        encoder/encoder/OnePlaneEncoder.h
        encoder/encoder/OnePlaneEncoder.cpp
        encoder/encoder/EightPlaneEncoder.cpp
        encoder/encoder/EightPlaneEncoder.h
        encoder/encoder/ThreePlaneEncoder.cpp
        encoder/encoder/ThreePlaneEncoder.h
        Network/utils/LinearBnReluImpl.cpp
        Network/utils/LinearBnReluImpl.h
        Network/utils/ConvReluBnImpl.cpp
        Network/utils/ConvReluBnImpl.h
        Network/RolloutPolicy/RolloutPolicyModule.cpp
        Network/RolloutPolicy/RolloutPolicyModule.h
        Network/RolloutPolicy/RolloutPolicy.cpp
        Network/RolloutPolicy/RolloutPolicy.h
        Network/SLPolicy/SLPolicyModule.cpp
        Network/SLPolicy/SLPolicyModule.h
        Network/SLPolicy/SLPolicy.cpp
        Network/SLPolicy/SLPolicy.h
        Network/RLPolicy/RLPolicyModule.cpp
        Network/RLPolicy/RLPolicyModule.h
        Network/RLPolicy/GetRLPolicyData.h
        Network/RLPolicy/RLPolicy.cpp
        Network/RLPolicy/RLPolicy.h
        MCTS/AlphaGoMCTS.cpp
        MCTS/AlphaGoMCTS.h
)

target_link_libraries(Go raylib Eigen3::Eigen)
target_link_libraries(Go ${TORCH_LIBRARIES})
