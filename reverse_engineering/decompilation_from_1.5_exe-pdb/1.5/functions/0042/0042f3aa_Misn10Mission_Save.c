/*
 * Entry: 0042f3aa
 * Name: Misn10Mission::Save
 * Namespace: Misn10Mission
 * Signature: bool Save(Misn10Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn10Mission::Save(Misn10Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x42,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x84).f_array,0x34,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xbc).h_array,0x7c,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x13c).i_array,4,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
