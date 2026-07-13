/*
 * Entry: 0042d6be
 * Name: Misn08Mission::Save
 * Namespace: Misn08Mission
 * Signature: bool Save(Misn08Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn08Mission::Save(Misn08Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x2c,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x70).f_array,0x84,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xf8).h_array,0xa4,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1a0).i_array,8,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
