/*
 * Entry: 004440f3
 * Name: Misns3Mission::Save
 * Namespace: Misns3Mission
 * Signature: bool Save(Misns3Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns3Mission::Save(Misns3Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x1a,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x5c).f_array,0x10,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x70).h_array,0x90,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x104).i_array,0x1c,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
