/*
 * Entry: 00431a6f
 * Name: Misn11Mission::Load
 * Namespace: Misn11Mission
 * Signature: bool Load(Misn11Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn11Mission::Load(Misn11Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn11Mission_u_108 *pMVar3;
  
  if (missionSave) {
    *(undefined4 *)&this->field16_0x40 = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 4) = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 8) = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 0xc) = 0;
    (this->field16_0x40)._s_0.launch_attack = false;
    (this->field17_0x54)._s_0.escape_time = 99999.0;
    (this->field17_0x54)._s_0.last_wave_time = 99999.0;
    (this->field17_0x54)._s_0.camera_time = 99999.0;
    (this->field17_0x54)._s_0.betrayal_time = 99999.0;
    (this->field17_0x54)._s_0.start_delay = 99999.0;
    pMVar3 = &this->field18_0x6c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).player = 0;
      pMVar3 = (Misn11Mission_u_108 *)((int)pMVar3 + 4);
    }
    (this->field19_0xb0)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x11);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x54).f_array,0x14), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x6c).h_array,0x40), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0xb0).i_array,4), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
