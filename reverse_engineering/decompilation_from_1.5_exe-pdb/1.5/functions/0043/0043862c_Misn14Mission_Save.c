/*
 * Entry: 0043862c
 * Name: Misn14Mission::Save
 * Namespace: Misn14Mission
 * Signature: bool Save(Misn14Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn14Mission::Save(Misn14Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x18,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x5c).f_array,0x28,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x88).h_array,0x58,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0xe4).i_array,4,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
