#include <iostream>
#include <fstream>
#include <cstdint>

struct WAVHeader {
    char riff[4];
    uint32_t chunkSize;
    char wave[4];
    char fmt[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4];
    uint32_t dataSize;
};

int main(){
    std::ifstream file("pianos-by-jtwayne-7-174717.wav", std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    WAVHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    if(std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE"){
        std::cerr << "Not a valid WAV file.\n";
        return 1;
    }

    std::cout << "Sample Rate: " << header.sampleRate << " Hz\n";
    std::cout << "Channels: " << header.numChannels << "\n";
    std::cout << "Bit Depth: " << header.bitsPerSample << "-bit\n";

    float duration = static_cast<float>(header.dataSize) / header.byteRate;
    std::cout << "Duration: " << duration << " seconds\n";

    file.close();
    return 0;
}