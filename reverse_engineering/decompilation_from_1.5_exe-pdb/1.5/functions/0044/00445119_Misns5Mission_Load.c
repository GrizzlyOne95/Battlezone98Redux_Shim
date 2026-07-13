/*
 * Entry: 00445119
 * Name: Misns5Mission::Load
 * Namespace: Misns5Mission
 * Signature: bool Load(Misns5Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns5Mission::Load(Misns5Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns5Mission_u_104 *pMVar3;
  
  if (missionSave) {
    *(undefined4 *)&this->field16_0x40 = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 4) = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 8) = 0;
    (this->field16_0x40)._s_0.apc_here = false;
    (this->field17_0x50)._s_0.add_defender = 99999.0;
    (this->field17_0x50)._s_0.wave = 99999.0;
    (this->field17_0x50)._s_0.chaff = 99999.0;
    (this->field17_0x50)._s_0.camera_time = 99999.0;
    (this->field17_0x50)._s_0.apc_wave = 99999.0;
    pMVar3 = &this->field18_0x68;
    for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).a1 = 0;
      pMVar3 = (Misns5Mission_u_104 *)((int)pMVar3 + 4);
    }
    (this->field19_0xa8)._s_0.wave_count = 0;
    (this->field19_0xa8)._s_0.wave_type = 0;
    (this->field19_0xa8)._s_0.aud = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0xd);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x50).f_array,0x14), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x68).h_array,0x3c), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0xa8).i_array,0xc), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
