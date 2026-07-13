/*
 * Entry: 0043a1b5
 * Name: Misn15Mission::Save
 * Namespace: Misn15Mission
 * Signature: bool Save(Misn15Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn15Mission::Save(Misn15Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0xf,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x50).f_array,0x2c,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x80).h_array,0x204,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x288).i_array,8,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
