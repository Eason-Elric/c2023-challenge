#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_
#include <fstream>
#include <string.h>
#define LevelStorageLength 300

std::vector<int> Score;

std::ifstream InArchiveFile, InScoreFile;
std::ofstream OutArchiveFile, OutScoreFile;

std::string ArchivePath = "C:/Users/56541/CLionProjects/c2023-challenge/level1/p08_push_boxes/Archive.dat";
std::string ScorePath = "C:/Users/56541/CLionProjects/c2023-challenge/level1/p08_push_boxes/Score.dat";

void ReadArchive(int GameLevel);
void SaveArchive(int SaveMap_[][MAXSIZE]);
void ReadScore();
void SaveScore();

void ReadArchive(int GameLevel){
    InArchiveFile.open(ArchivePath, std::ios::in);
    InArchiveFile.seekg((GameLevel - 1) * LevelStorageLength + GameLevel - 1, std::ios::beg);
    for(int i = 0; i <= MapSize + 1; i++)
        for(int j = 0; j <= MapSize + 1; j++){
            InArchiveFile >> Map[i][j];
            if(Map[i][j] == END)
                End.push_back(Point(i, j));
            else if(Map[i][j] == BOX)
                Start.push_back(Point(i, j));
        }
    InArchiveFile.close();
}

void SaveArchive(int SaveMap_[][MAXSIZE]){
    OutArchiveFile.open(ArchivePath, std::ios::app);
    OutArchiveFile << "\n";
    for(int i = 0; i <= MapSize + 1; i++){
        for(int j = 0; j <= MapSize + 1; j++)
            OutArchiveFile << SaveMap_[i][j] << " ";
        OutArchiveFile << "\n";
    }
    OutArchiveFile.close();
}

void ReadScore(){
    InScoreFile.open(ScorePath, std::ios::in);
    while(!InScoreFile.eof()){
        int ScoreNum = 0;
        InScoreFile >> ScoreNum;
        Score.push_back(ScoreNum);
    }
    InScoreFile.close();
}

void SaveScore(){
    OutScoreFile.open(ScorePath, std::ios::out);
    for(std::vector<int>::iterator iter = Score.begin(); iter != Score.end(); iter++)
        OutScoreFile << *iter << "\n";
    OutScoreFile.close();
}

#endif // _ARCHIVE_H_
