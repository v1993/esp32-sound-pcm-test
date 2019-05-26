#include <sound.h>
#include <soundProviderPcm.h>
#include <memory>
#include <iostream>

USING_NS_SOUND;

std::unique_ptr<SoundMixer> player; // Global to prevent destroying

const extern long unsigned int voice_length;
const extern uint8_t voice_data[];


extern "C" void app_main() {
	player = std::make_unique<SoundMixer>(1, 0, DAC_GPIO25_CHANNEL); // Create SoundMixer
	auto provider = std::make_shared<SoundProviderPcm>(voice_data, voice_length, 8000); // Create our provider
	provider->repeat = false; // Change to true for looping
	player->play(0, provider); // Play on channel 0 (only aviable)
}
