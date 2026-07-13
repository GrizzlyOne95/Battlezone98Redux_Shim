/*
 * Entry: 00429155
 * Name: Misn06Mission::Load
 * Namespace: Misn06Mission
 * Signature: bool Load(Misn06Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn06Mission::Load(Misn06Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn06Mission_u_164 *pMVar3;
  Misn06Mission_u_304 *pMVar4;
  Misn06Mission_u_784 *pMVar5;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0xa4;
    for (iVar2 = 0x22; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).transportgone = 99999.0;
      pMVar3 = (Misn06Mission_u_164 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x130;
    for (iVar2 = 0x77; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).haephestus = 0;
      pMVar4 = (Misn06Mission_u_304 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field19_0x310;
    for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).cam1hgt = 0;
      pMVar5 = (Misn06Mission_u_784 *)((int)pMVar5 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x62);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0xa4).f_array,0x88), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x130).h_array,0x1dc), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x310).i_array,0x3c), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
