/*
 * Entry: 00432670
 * Name: Misn12Mission::Save
 * Namespace: Misn12Mission
 * Signature: bool Save(Misn12Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn12Mission::Save(Misn12Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x5c,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0xa0).f_array,0x6c,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x110).h_array,0xe4,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1f8).i_array,4,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
