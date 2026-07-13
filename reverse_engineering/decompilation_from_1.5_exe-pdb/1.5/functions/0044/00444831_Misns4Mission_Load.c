/*
 * Entry: 00444831
 * Name: Misns4Mission::Load
 * Namespace: Misns4Mission
 * Signature: bool Load(Misns4Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns4Mission::Load(Misns4Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns4Mission_u_64 *pMVar3;
  Misns4Mission_u_96 *pMVar4;
  Misns4Mission_u_124 *pMVar5;
  
  if (missionSave) {
    pMVar3 = &this->field16_0x40;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pMVar3 = 0;
      pMVar3 = (Misns4Mission_u_64 *)((int)pMVar3 + 4);
    }
    (pMVar3->_s_0).counter = false;
    pMVar4 = &this->field17_0x60;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).wakeup_time = 99999.0;
      pMVar4 = (Misns4Mission_u_96 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field18_0x7c;
    for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).convoy_handle[0] = 0;
      pMVar5 = (Misns4Mission_u_124 *)((int)pMVar5 + 4);
    }
    (this->field19_0xd4)._s_0.convoy_total = 0;
    (this->field19_0xd4)._s_0.convoy_count = 0;
    (this->field19_0xd4)._s_0.convoy_dead = 0;
    (this->field19_0xd4)._s_0.win_count = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x1d);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x60).f_array,0x18), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x7c).h_array,0x54), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0xd4).i_array,0x10), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
