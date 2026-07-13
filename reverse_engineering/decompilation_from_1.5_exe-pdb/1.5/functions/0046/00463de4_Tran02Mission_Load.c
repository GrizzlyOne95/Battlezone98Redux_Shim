/*
 * Entry: 00463de4
 * Name: Tran02Mission::Load
 * Namespace: Tran02Mission
 * Signature: bool Load(Tran02Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran02Mission::Load(Tran02Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Tran02Mission_u_120 *pTVar3;
  
  if (missionSave) {
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
    return bVar1;
  }
  bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x16);
  if (((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x58).f_array,8), bVar1)) &&
     (bVar1 = ::in(param_1,(this->field18_0x64).h_array,0x10), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pTVar3 = &this->field19_0x78;
  iVar2 = 4;
  do {
    if ((bVar1) && (bVar1 = in_ptr(param_1,pTVar3->p_array,4,"p_array",this), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar3 = (Tran02Mission_u_120 *)((int)pTVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::in(param_1,(this->field20_0x8c).i_array,0xc), bVar1)) &&
     (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
