/*
 * Entry: 004293b3
 * Name: Misn07Mission::Save
 * Namespace: Misn07Mission
 * Signature: bool Save(Misn07Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn07Mission::Save(Misn07Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn07Mission_u_1288 *pMVar3;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
    return bVar1;
  }
  bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x12a,"b_array");
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x16c).f_array,0x74,"f_array"), bVar1)) &&
     (bVar1 = ::out(param_1,(this->field18_0x1e4).h_array,800,"h_array"), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pMVar3 = &this->field19_0x508;
  iVar2 = 0x70;
  do {
    if ((bVar1) && (bVar1 = out_ptr(param_1,pMVar3,4,"p_array"), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pMVar3 = (Misn07Mission_u_1288 *)((int)pMVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field20_0x6cc).i_array,0x14,"i_array"), bVar1)) &&
     (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
