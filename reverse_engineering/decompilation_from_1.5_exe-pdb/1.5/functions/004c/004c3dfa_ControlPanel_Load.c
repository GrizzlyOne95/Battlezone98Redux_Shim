/*
 * Entry: 004c3dfa
 * Name: ControlPanel::Load
 * Namespace: ControlPanel
 * Signature: bool Load(ControlPanel * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ControlPanel::Load(ControlPanel *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,this->groupNum,0x28);
  if ((bVar1) && (bVar1 = ::in(param_1,this->groupList,0xe10), bVar1)) {
    return true;
  }
  return false;
}
