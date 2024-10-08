export module ivoicetweak;


// These provide access to the voice controls.
export enum VoiceTweakControl
{
	MicrophoneVolume = 0,			// values 0-1.
	OtherSpeakerScale			// values 0-1. Scales how loud other players are.
};


export struct IVoiceTweak_s
{
	// These turn voice tweak mode on and off. While in voice tweak mode, the user's voice is echoed back
	// without sending to the server. 
	int				(*StartVoiceTweakMode)();	// Returns 0 on error.
	void			(*EndVoiceTweakMode)();

	// Get/set control values.
	void			(*SetControlFloat)(VoiceTweakControl iControl, float value);
	float			(*GetControlFloat)(VoiceTweakControl iControl);
};

export using IVoiceTweak = IVoiceTweak_s;
