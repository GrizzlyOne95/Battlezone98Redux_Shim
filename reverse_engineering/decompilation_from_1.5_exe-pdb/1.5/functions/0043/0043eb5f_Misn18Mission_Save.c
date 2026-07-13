/*
 * Entry: 0043eb5f
 * Name: Misn18Mission::Save
 * Namespace: Misn18Mission
 * Signature: bool Save(Misn18Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn18Mission::Save(Misn18Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x2a,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x6c).f_array,0x34,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xa4).h_array,0x100,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1a8).i_array,0x14,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
