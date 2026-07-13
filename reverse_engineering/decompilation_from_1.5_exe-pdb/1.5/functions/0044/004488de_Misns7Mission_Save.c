/*
 * Entry: 004488de
 * Name: Misns7Mission::Save
 * Namespace: Misns7Mission
 * Signature: bool Save(Misns7Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns7Mission::Save(Misns7Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x5f,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0xa0).f_array,0x8c,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x130).h_array,0x130,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x264).i_array,0x10,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
