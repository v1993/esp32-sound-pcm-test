#include <sound.h>
#include <soundProviderPcm.h>
#include <memory>
#include <iostream>

USING_NS_SOUND;

std::shared_ptr<SoundMixer> player;

const extern long unsigned int voice_length; // Nice!
const extern uint8_t voice_data[];


void play_voice() {
	{
		auto provider = std::make_shared<SoundProviderPcm>(voice_data, voice_length, 8000);
		player = std::make_unique<SoundMixer>(1, 0, DAC_GPIO25_CHANNEL);
		provider->repeat = false;
		player->play(0, provider);
		vTaskDelay(100);
		std::cout << provider.use_count() << std::endl;
	}
	while (true) {vTaskDelay(100);};
}


/*
void play_voice() {
	auto provider = std::make_shared<SoundProviderPcm>(voice_data, voice_length, 8000);
	player = std::make_unique<SoundMixer>(1, 0, DAC_GPIO25_CHANNEL);
	provider->repeat = true;
	player->play(0, provider.get());
	vTaskDelay(100);
	std::cout << provider.use_count() << std::endl;
	while (true) {vTaskDelay(100);};
}
*/

extern "C" void app_main() {
	play_voice();
}
