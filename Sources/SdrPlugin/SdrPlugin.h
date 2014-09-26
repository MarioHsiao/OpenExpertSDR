/*
 * This file is part of ExpertSDR
 *
 * ExpertSDR is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * ExpertSDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 *
 * Copyright (C) 2012 Valery Mikhaylovsky
 * The authors can be reached by email at maksimus1210@gmail.com
 */

#ifndef SDRPLUGIN_H
#define SDRPLUGIN_H

#include <QtGui/QWidget>
#include <qt_windows.h>
#include "../tmp/ui_Options.h"
#include "../Options.h"
#include "../Defines.h"
#include "PortAudio/pa19.h"
#include "SunSDR/sunCtrl.h"

typedef enum
{
	SUNSDR = 0
}SDR_DEVICE;

class SdrPlugin : public QWidget
{
		Q_OBJECT

		double CalibrateFreq;
        double Sun2CalibrateFreq;
		double FreqDDS;

	public:
        SdrPlugin(Options *pOpt, StreamCallback *pCallBack, StreamCallback *pCallBack4, void *UsrData = 0, QWidget *parent = 0);
		~SdrPlugin();

		PLUGIN_OPTIONS OptPlug;
		void SetSdrType(SDR_DEVICE Type);
		SDR_DEVICE GetSdrType();

		void SetPreamp(int Preamp);
		void SetExtCtrl(DWORD ExtData);
		void SetDdsFreq(float Freq);
		float GetDdsFreq();
		void SetTrxMode(bool Mode);
		void Close();
		int  Start();
		void Stop();
		bool IsStart();
		void SetDdsCalibrate(double val);

        void setCalGen(bool Mode);
        void setVhfOsc(quint32 freq);
        void setUhfOsc(quint32 freq);
        void setMute(bool status);
        void setXvAnt(int Mode);


	private:
		Ui::OptionsClass *pUi;
		bool isStarted;
		SDR_DEVICE SdrType;
		StreamCallback *AudioCallBack;
		StreamCallback *AudioCallBack4;

    public:
		pa19 *pAudio;
		sunCtrl   *pSunSDR;

	private slots:
		void onPaDriverChanged(int Index);
		void onSdrTypeChanged(int Index);
		void onS2ChangeBuffers(int NumBuffers);

	signals:
		void PttChanged(bool);
		void DashChanged(bool);
		void DotChanged(bool);
		void sunsdrConnectInfo(QString);
        void AdcChanged(int, int);
        void forceStop();
};

#endif // SDRPLUGIN_H
