/*
 * Entry: 0043d458
 * Name: Misn17Mission::Save
 * Namespace: Misn17Mission
 * Signature: bool Save(Misn17Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn17Mission::Save(Misn17Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x40,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x84).f_array,0x88,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x110).h_array,0x238,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x34c).i_array,0xc,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
