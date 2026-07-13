/*
 * Entry: 00465445
 * Name: Tran05Mission::Load
 * Namespace: Tran05Mission
 * Signature: bool Load(Tran05Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran05Mission::Load(Tran05Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Tran05Mission_u_124 *pTVar3;
  Tran05Mission_u_196 *pTVar4;
  
  if (missionSave) {
    pTVar3 = &this->field18_0x7c;
    for (iVar2 = 0x11; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pTVar3->_s_0).player = 0;
      pTVar3 = (Tran05Mission_u_124 *)((int)pTVar3 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
    return bVar1;
  }
  bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x19);
  if (((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x5c).f_array,0x1c), bVar1)) &&
     (bVar1 = ::in(param_1,(this->field18_0x7c).h_array,0x44), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pTVar4 = &this->field19_0xc4;
  iVar2 = 4;
  do {
    if ((bVar1) && (bVar1 = in_ptr(param_1,pTVar4->p_array,4,"p_array",this), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar4 = (Tran05Mission_u_196 *)((int)pTVar4 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::in(param_1,(this->field20_0xd8).i_array,0xc), bVar1)) &&
     (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
