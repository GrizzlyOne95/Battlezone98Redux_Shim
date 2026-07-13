/*
 * Entry: 0042925c
 * Name: Misn06Mission::Save
 * Namespace: Misn06Mission
 * Signature: bool Save(Misn06Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn06Mission::Save(Misn06Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x62,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0xa4).f_array,0x88,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x130).h_array,0x1dc,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x310).i_array,0x3c,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
