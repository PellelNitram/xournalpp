/*
 * Xournal++
 *
 * Audio Recording / Playing controller
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <XournalType.h>
#include "settings/Settings.h"
#include "Control.h"
#include <Path.h>
#include <util/audio/AudioRecorder.h>
#include <util/audio/AudioPlayer.h>

class AudioController
{
public:
	AudioController(Settings* settings, Control* control);
	virtual ~AudioController();

public:
	bool recStart();
	bool recStop();
	string getAudioFilename();
	Path getAudioFolder();
	size_t getStartTime();
	AudioRecorder* getAudioRecorder();
	AudioPlayer* getAudioPlayer();

protected:
	string audioFilename;
	size_t timestamp = 0;
	Settings* settings;
	Control* control;
	AudioRecorder* audioRecorder;
	AudioPlayer* audioPlayer;

private:
	XOJ_TYPE_ATTRIB;

};
