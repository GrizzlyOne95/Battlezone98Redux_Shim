/*
 * Entry: 00464cbe
 * Name: Tran04Mission::Save
 * Namespace: Tran04Mission
 * Signature: bool Save(Tran04Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran04Mission::Save(Tran04Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Tran04Mission_u_136 *pTVar3;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
    return bVar1;
  }
  bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x16,"b_array");
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x58).f_array,8,"f_array"), bVar1)) &&
     (bVar1 = ::out(param_1,(this->field18_0x64).h_array,0x20,"h_array"), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pTVar3 = &this->field19_0x88;
  iVar2 = 8;
  do {
    if ((bVar1) && (bVar1 = out_ptr(param_1,pTVar3,4,"p_array"), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar3 = (Tran04Mission_u_136 *)((int)pTVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field20_0xac).i_array,8,"i_array"), bVar1)) &&
     (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
