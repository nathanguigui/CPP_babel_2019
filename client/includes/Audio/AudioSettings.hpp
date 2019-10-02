//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_AUDIOSETTINGS_HPP
#define CPP_BABEL_2019_AUDIOSETTINGS_HPP
#include <QMetaType>
#include <vector>
#include <opus/opus.h>

namespace AudioSettings {
    const int	SAMPLE_RATE = 48000;
	const int	NB_CHANNELS = 2;
	const int	FRAMES_PER_BUFFER = 480;

	struct Encoded {
		std::vector<unsigned char> buffer;
		int	size;
	};

	struct Decoded {
		std::vector<float> buffer;
		int	size;
	};
}

Q_DECLARE_METATYPE(AudioSettings::Encoded);

#endif //CPP_BABEL_2019_AUDIOSETTINGS_HPP
