//
// Created by zy on 8/1/2018.
//

#include "IPlayerBuilder.h"
#include "IVideoView.h"
#include "IResample.h"
#include "IDecode.h"
#include "IDemux.h"
#include "IAudioPlay.h"
IPlayer* IPlayerBuilder::BuilderPlayer(unsigned char index){

    IPlayer* play = CreatePlayer(index);
    IDemux* de = CreateDemux();

    IDecode* vdecode = CreateDecode();

    IDecode* adecode = CreateDecode();
    de->AddObs(vdecode);
    de->AddObs(adecode);

    IVideoView* view = CreateVideoView();
    vdecode->AddObs(view);

    IResample* resample = CreateResample();
    adecode->AddObs(resample);

    IAudioPlay* audioPlay = CreateAudioPlay();
    resample->AddObs(audioPlay);

    play->demux = de;
    play->vdecode = vdecode;
    play->adecode = adecode;
    play->resample = resample;
    play->audioPlay = audioPlay;
    play->videoView = view;
    return play;
}