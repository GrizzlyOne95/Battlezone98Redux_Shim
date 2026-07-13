/*
 * Entry: 004161c3
 * Name: Inst4XMission::Save
 * Namespace: Inst4XMission
 * Signature: bool Save(Inst4XMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst4XMission::Save(Inst4XMission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    bVar1 = LuaMission::Save((LuaMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field19_0x4c).b_array,3,"b_array");
    if ((((bVar1) && (bVar1 = ::out(param_1,(this->field20_0x50).f_array,8,"f_array"), bVar1)) &&
        (bVar1 = ::out(param_1,(this->field21_0x5c).h_array,4,"h_array"), bVar1)) &&
       ((bVar1 = ::out(param_1,(this->field22_0x64).i_array,4,"i_array"), bVar1 &&
        (bVar1 = LuaMission::Save((LuaMission *)this,param_1), bVar1)))) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
