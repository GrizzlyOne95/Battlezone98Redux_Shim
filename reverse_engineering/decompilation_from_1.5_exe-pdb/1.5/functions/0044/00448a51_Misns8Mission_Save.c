/*
 * Entry: 00448a51
 * Name: Misns8Mission::Save
 * Namespace: Misns8Mission
 * Signature: bool Save(Misns8Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns8Mission::Save(Misns8Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x71,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0xb4).f_array,0x78,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x130).h_array,0x140,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x274).i_array,0x34,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
