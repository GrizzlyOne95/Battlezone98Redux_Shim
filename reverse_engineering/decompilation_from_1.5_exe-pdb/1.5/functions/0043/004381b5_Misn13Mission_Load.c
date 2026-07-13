/*
 * Entry: 004381b5
 * Name: Misn13Mission::Load
 * Namespace: Misn13Mission
 * Signature: bool Load(Misn13Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn13Mission::Load(Misn13Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn13Mission_u_124 *pMVar3;
  Misn13Mission_u_172 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x7c;
    for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).first_wave_time = 99999.0;
      pMVar3 = (Misn13Mission_u_124 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xac;
    for (iVar2 = 0x4c; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn13Mission_u_172 *)((int)pMVar4 + 4);
    }
    (this->field19_0x1e0)._s_0.check = 0;
    (this->field19_0x1e0)._s_0.scrap = 0;
    (this->field19_0x1e0)._s_0.shot_by = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x3b);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x7c).f_array,0x2c), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xac).h_array,0x130), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1e0).i_array,0xc), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
