#include "main.h"
#include "settings.h"

#include "scripts.h"

void script_extended_aeb() {
	int av_enc, av_dec, OldAvComp;
	int m;

	if (settings.eaeb_delay) {
		eventproc_RiseEvent("RequestBuzzer");
		SleepTask(2000);
	}

	if (cameraMode.AEMode == AE_MODE_M) {
		int m_end;
		m = settings.eaeb_m_min;
		do {
			SendToIntercom(0x08, 1, m);
			SleepTask(5);
			eventproc_Release();
			SleepTask(5);
			while(FLAG_CAMERA_BUSY)
				SleepTask(5);

			if(settings.eaeb_m_min == settings.eaeb_m_max) {
				m_end=m;
			} else if(settings.eaeb_m_min < settings.eaeb_m_max) {
				m += 8;
				m_end = settings.eaeb_m_max + 8;
			} else {
				m -= 8;
				m_end = settings.eaeb_m_max - 8;
			}
		} while(m != m_end);
	} else {
		if (cameraMode.CfSettingSteps)
			settings.eaeb_ev &= 0xFC;
		else if((settings.eaeb_ev & 7) != 0 && (settings.eaeb_ev & 3) == 0)
			settings.eaeb_ev -= 1;

		OldAvComp = cameraMode.AvComp;

		av_enc = cameraMode.AvComp;
		av_dec = cameraMode.AvComp;

		eventproc_Release();

		m = 0;
		while (m < (settings.eaeb_frames - 1) / 2) {
			av_dec -= settings.eaeb_ev;
			av_enc += settings.eaeb_ev;

			if (cameraMode.CfSettingSteps == 0) {
				if ((av_dec & 0x06) == 0x06)
					av_dec -= 1;
				else if((av_dec & 0x07) == 0x02)
					av_dec += 1;

				if ((av_enc & 0x06) == 0x06)
					av_enc -= 1;
				else if((av_enc & 0x07) == 0x02)
					av_enc += 1;
			}

			//if(av_dec<0xCB)av_dec=0xCB;
			//if(av_enc>0x30)av_enc=0x30;

			m++;

			while (FLAG_CAMERA_BUSY)
				SleepTask(5);

			SendToIntercom(0x0A, 1, av_dec);
			eventproc_Release();

			while (FLAG_CAMERA_BUSY)
				SleepTask(5);

			SendToIntercom(0x0A, 1, av_enc);
			eventproc_Release();
		}

		SleepTask(500);
		SendToIntercom(0x0A, 1, OldAvComp);
	}

	eventproc_RiseEvent("RequestBuzzer");
	SleepTask(500);
}

void script_interval() {
	int interval_original_ae_mode = cameraMode.AEMode;
	int i = 0;

	while (interval_original_ae_mode == cameraMode.AEMode) {
		while(FLAG_CAMERA_BUSY)
			SleepTask(5);

		eventproc_Release();

		for(i = 0; i < settings.interval_time; i++) {
			if(interval_original_ae_mode == cameraMode.AEMode)
				SleepTask(1000);
		}
	}

	eventproc_RiseEvent("RequestBuzzer");
}
