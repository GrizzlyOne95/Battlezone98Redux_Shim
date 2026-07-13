/*
 * Entry: 004487d8
 * Name: Misns7Mission::Load
 * Namespace: Misns7Mission
 * Signature: bool Load(Misns7Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns7Mission::Load(Misns7Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misns7Mission_u_160 *pMVar3;
  Misns7Mission_u_304 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0xa0;
    for (iVar2 = 0x23; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).unit_spawn_time1 = 99999.0;
      pMVar3 = (Misns7Mission_u_160 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x130;
    for (iVar2 = 0x4c; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misns7Mission_u_304 *)((int)pMVar4 + 4);
    }
    (this->field19_0x264)._s_0.stuff = 0;
    (this->field19_0x264)._s_0.stuff2 = 0;
    (this->field19_0x264)._s_0.stuff4 = 0;
    (this->field19_0x264)._s_0.scrap = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x5f);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0xa0).f_array,0x8c), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x130).h_array,0x130), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x264).i_array,0x10), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
