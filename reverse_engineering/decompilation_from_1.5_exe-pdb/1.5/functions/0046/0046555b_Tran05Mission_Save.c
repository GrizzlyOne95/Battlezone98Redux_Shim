/*
 * Entry: 0046555b
 * Name: Tran05Mission::Save
 * Namespace: Tran05Mission
 * Signature: bool Save(Tran05Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran05Mission::Save(Tran05Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Tran05Mission_u_196 *pTVar3;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
    return bVar1;
  }
  bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x19,"b_array");
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x5c).f_array,0x1c,"f_array"), bVar1)) &&
     (bVar1 = ::out(param_1,(this->field18_0x7c).h_array,0x44,"h_array"), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pTVar3 = &this->field19_0xc4;
  iVar2 = 4;
  do {
    if ((bVar1) && (bVar1 = out_ptr(param_1,pTVar3,4,"p_array"), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar3 = (Tran05Mission_u_196 *)((int)pTVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field20_0xd8).i_array,0xc,"i_array"), bVar1)) &&
     (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
