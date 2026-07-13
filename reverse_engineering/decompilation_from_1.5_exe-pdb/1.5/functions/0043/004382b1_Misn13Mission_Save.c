/*
 * Entry: 004382b1
 * Name: Misn13Mission::Save
 * Namespace: Misn13Mission
 * Signature: bool Save(Misn13Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn13Mission::Save(Misn13Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x3b,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x7c).f_array,0x2c,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xac).h_array,0x130,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1e0).i_array,0xc,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
