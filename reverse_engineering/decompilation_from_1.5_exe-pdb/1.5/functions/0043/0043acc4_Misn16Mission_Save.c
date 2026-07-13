/*
 * Entry: 0043acc4
 * Name: Misn16Mission::Save
 * Namespace: Misn16Mission
 * Signature: bool Save(Misn16Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn16Mission::Save(Misn16Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,6,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x48).f_array,0x24,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x70).h_array,0x54,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0xc8).i_array,8,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
