/*
 * Entry: 00440356
 * Name: Misns1Mission::Save
 * Namespace: Misns1Mission
 * Signature: bool Save(Misns1Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns1Mission::Save(Misns1Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x40,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x84).f_array,0x6c,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xf4).h_array,0xb4,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1ac).i_array,0x1c,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
