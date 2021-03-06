#include "AudioController.h"
#include "Util.h"

#include <i18n.h>
#include <XojMsgBox.h>

AudioController::AudioController(Settings* settings, Control* control)
{
	XOJ_INIT_TYPE(AudioController);
	this->settings = settings;
	this->control = control;
	this->audioRecorder = new AudioRecorder(settings);
	this->audioPlayer = new AudioPlayer(settings);
}

AudioController::~AudioController()
{
	XOJ_CHECK_TYPE(AudioController);

	delete this->audioRecorder;
	this->audioRecorder = nullptr;

	delete this->audioPlayer;
	this->audioPlayer = nullptr;

	XOJ_RELEASE_TYPE(AudioController);
}

bool AudioController::recStart()
{
	XOJ_CHECK_TYPE(AudioController);

	if (!this->getAudioRecorder()->isRecording())
	{
		if (getAudioFolder().isEmpty())
		{
			return false;
		}

		this->timestamp = static_cast<size_t>(g_get_monotonic_time() / 1000);

		char buffer[50];
		time_t secs = time(nullptr);
		tm* t = localtime(&secs);
		// This prints the date and time in ISO format.
		sprintf(buffer, "%04d-%02d-%02d_%02d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour,
				t->tm_min, t->tm_sec);
		string data(buffer);
		data += ".ogg";

		audioFilename = data;

		g_message("Start recording");

		bool isRecording = this->getAudioRecorder()->start(getAudioFolder().str() + "/" + data);

		if (!isRecording)
		{
			audioFilename = "";
			this->timestamp = 0;
		}

		return isRecording;
	}
	return false;
}

bool AudioController::recStop()
{
	if (this->audioRecorder->isRecording())
	{
		audioFilename = "";
		this->timestamp = 0;

		g_message("Stop recording");

		this->audioRecorder->stop();
	}
	return true;
}

string AudioController::getAudioFilename()
{
	XOJ_CHECK_TYPE(AudioController);

	return this->audioFilename;
}

Path AudioController::getAudioFolder()
{
	XOJ_CHECK_TYPE(AudioController);

	string af = this->settings->getAudioFolder();

	if (af.length() < 8)
	{
		string msg = _("Audio folder not set! Recording won't work!\nPlease set the "
					   "recording folder under \"Preferences > Audio recording\"");
		g_warning("%s", msg.c_str());
		XojMsgBox::showErrorToUser(this->control->getGtkWindow(), msg);
		return Path("");
	}

	return Path::fromUri(af);
}

size_t AudioController::getStartTime()
{
	XOJ_CHECK_TYPE(AudioController);

	return this->timestamp;
}

AudioRecorder* AudioController::getAudioRecorder()
{
	return this->audioRecorder;
}

AudioPlayer* AudioController::getAudioPlayer()
{
	return this->audioPlayer;
}
