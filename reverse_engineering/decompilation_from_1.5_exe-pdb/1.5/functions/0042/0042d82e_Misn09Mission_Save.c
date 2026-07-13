/*
 * Entry: 0042d82e
 * Name: Misn09Mission::Save
 * Namespace: Misn09Mission
 * Signature: bool Save(Misn09Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn09Mission::Save(Misn09Mission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x36,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x78).f_array,0x70,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field18_0xec).h_array,0xd8,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field19_0x1c8).i_array,0x14,"i_array"), bVar1 &&
        (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
