/*
 * Entry: 004c3e3c
 * Name: ControlPanel::Save
 * Namespace: ControlPanel
 * Signature: bool Save(ControlPanel * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ControlPanel::Save(ControlPanel *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,this->groupNum,0x28,"groupNum");
  if ((bVar1) && (bVar1 = ::out(param_1,this->groupList,0xe10,"groupList"), bVar1)) {
    return true;
  }
  return false;
}
