/*
 * Entry: 004236f0
 * Name: Misn05Mission::Save
 * Namespace: Misn05Mission
 * Signature: bool Save(Misn05Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn05Mission::Save(Misn05Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x46,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x88).f_array,0xa0,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0x12c).h_array,0x104,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x234).i_array,4,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
