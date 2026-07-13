/*
 * Entry: 0047fc3d
 * Name: AudioMessageMgr::Init
 * Namespace: AudioMessageMgr
 * Signature: void Init(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AudioMessageMgr::Init(AudioMessageMgr *this)

{
  int iVar1;
  ParameterDB local_8;
  
  this->playing = false;
  *(byte *)&this->_padding_ = (byte)this->_padding_ & 0xf1 | 1;
  this->seqNo = 1;
  this->lastMsg[0] = '\0';
  local_8.DB_file = (FileData *)this;
  iVar1 = ItemExists("audio.odf");
  if (iVar1 != 0) {
    ParameterDB::ParameterDB(&local_8,"audio.odf");
    ParameterDB::Get(&local_8,0x49172362,0x37e230bd,&insideDistanceFactor,insideDistanceFactor);
    ParameterDB::Get(&local_8,0x49172362,0x6b9de01c,&insideRolloffFactor,insideRolloffFactor);
    ParameterDB::Get(&local_8,0x49172362,0xaf94b358,&insideDopplerFactor,insideDopplerFactor);
    ParameterDB::Get(&local_8,0x49172362,0xd5868120,&outsideDistanceFactor,outsideDistanceFactor);
    ParameterDB::Get(&local_8,0x49172362,0x5e165aef,&outsideRolloffFactor,outsideRolloffFactor);
    ParameterDB::Get(&local_8,0x49172362,0x79cffcbb,&outsideDopplerFactor,outsideDopplerFactor);
    ParameterDB::Get(&local_8,0x49172362,0xca24532,&minSoundDist,minSoundDist);
    ParameterDB::Get(&local_8,0x49172362,0x7a9fd210,&maxSoundDist,maxSoundDist);
    ParameterDB::Get(&local_8,0x49172362,0x925b352e,&minDiscardSoundDist,minDiscardSoundDist);
    ParameterDB::Get(&local_8,0x49172362,0x92f5be2c,&maxDiscardSoundDist,maxDiscardSoundDist);
    ParameterDB::Get(&local_8,0x49172362,0x2e50edc,&explosionMinDist,minSoundDist);
    ParameterDB::Get(&local_8,0x49172362,0xc7834d4a,&turboPitchBase,turboPitchBase);
    ParameterDB::Get(&local_8,0x49172362,0xdcb07fdc,&turboPitchRange,turboPitchRange);
    ParameterDB::Get(&local_8,0x49172362,0xd58454fb,&turboVolumeBaseUser,turboVolumeBaseUser);
    ParameterDB::Get(&local_8,0x49172362,0x55188f35,&turboVolumeRangeUser,turboVolumeRangeUser);
    ParameterDB::Get(&local_8,0x49172362,0x88f86c72,&thrustPitchBase,thrustPitchBase);
    ParameterDB::Get(&local_8,0x49172362,0xe358bda4,&thrustPitchRange,thrustPitchRange);
    ParameterDB::Get(&local_8,0x49172362,0x14548923,&thrustVolumeBaseUser,thrustVolumeBaseUser);
    ParameterDB::Get(&local_8,0x49172362,0x9074837d,&thrustVolumeRangeUser,thrustVolumeRangeUser);
    ParameterDB::Get(&local_8,0x49172362,0xfbe7633a,&aiEngineFactor,aiEngineFactor);
    ParameterDB::Get(&local_8,0x49172362,0x863e8495,&explosionVolumeFactor,explosionVolumeFactor);
    ParameterDB::Get(&local_8,0x49172362,0xd2fb08d7,&audioMixRate,audioMixRate);
    ParameterDB::Get(&local_8,0x49172362,0x550dcc8e,&waveMaxSetting,waveMaxSetting);
    if (0xffff < waveMaxSetting) {
      waveMaxSetting = 0xffff;
    }
    if (waveMaxSetting < 0) {
      waveMaxSetting = 0;
    }
    ParameterDB::~ParameterDB(&local_8);
  }
  return;
}
