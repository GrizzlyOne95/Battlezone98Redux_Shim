/*
 * Entry: 0043ea63
 * Name: Misn18Mission::Load
 * Namespace: Misn18Mission
 * Signature: bool Load(Misn18Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn18Mission::Load(Misn18Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn18Mission_u_108 *pMVar3;
  Misn18Mission_u_164 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x6c;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).explosions = 99999.0;
      pMVar3 = (Misn18Mission_u_108 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xa4;
    for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).transport = 0;
      pMVar4 = (Misn18Mission_u_164 *)((int)pMVar4 + 4);
    }
    (this->field19_0x1a8)._s_0.x = 0;
    (this->field19_0x1a8)._s_0.y = 0;
    (this->field19_0x1a8)._s_0.z = 0;
    (this->field19_0x1a8)._s_0.quake_level = 0;
    (this->field19_0x1a8)._s_0.quake_count = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x2a);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x6c).f_array,0x34), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xa4).h_array,0x100), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1a8).i_array,0x14), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
