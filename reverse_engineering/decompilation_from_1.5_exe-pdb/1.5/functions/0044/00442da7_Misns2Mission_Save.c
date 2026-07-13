/*
 * Entry: 00442da7
 * Name: Misns2Mission::Save
 * Namespace: Misns2Mission
 * Signature: bool Save(Misns2Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns2Mission::Save(Misns2Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x25,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x68).f_array,0x24,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x90).h_array,0x1a0,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x234).i_array,0x24,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
