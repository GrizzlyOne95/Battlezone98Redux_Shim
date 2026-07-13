/*
 * Entry: 00445205
 * Name: Misns5Mission::Save
 * Namespace: Misns5Mission
 * Signature: bool Save(Misns5Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns5Mission::Save(Misns5Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0xd,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x50).f_array,0x14,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x68).h_array,0x3c,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0xa8).i_array,0xc,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
