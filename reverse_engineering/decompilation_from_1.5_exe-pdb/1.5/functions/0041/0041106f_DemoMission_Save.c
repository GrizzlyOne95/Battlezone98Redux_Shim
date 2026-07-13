/*
 * Entry: 0041106f
 * Name: DemoMission::Save
 * Namespace: DemoMission
 * Signature: bool Save(DemoMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DemoMission::Save(DemoMission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  DemoMission_u_184 *pDVar3;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
    return bVar1;
  }
  bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x13,"b_array");
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x54).f_array,0x14,"f_array"), bVar1)) &&
     (bVar1 = ::out(param_1,(this->field18_0x70).h_array,0x30,"h_array"), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pDVar3 = &this->field19_0xb8;
  iVar2 = 4;
  do {
    if ((bVar1) && (bVar1 = out_ptr(param_1,pDVar3,4,"p_array"), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pDVar3 = (DemoMission_u_184 *)((int)pDVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((bVar1) && (bVar1 = ::out(param_1,(this->field20_0xcc).i_array,0x14,"i_array"), bVar1)) &&
     (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
