/*
 * Entry: 0041d5b2
 * Name: LayMinesTask::DoArrived
 * Namespace: LayMinesTask
 * Signature: bool DoArrived(LayMinesTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::DoArrived(LayMinesTask *this)

{
  Carrier *this_00;
  char cVar1;
  Weapon *pWVar2;
  
  this_00 = *(Carrier **)(this->_padding_ + 0x198);
  if (this_00 != (Carrier *)0x0) {
    pWVar2 = Carrier::GetWeapon(this_00,0);
    if (pWVar2 != (Weapon *)0x0) {
      cVar1 = (**(code **)(pWVar2->_padding_ + 0x30))();
      if (cVar1 == '\0') {
        return false;
      }
    }
    Carrier::SetSelected(this_00,1);
    Carrier::TriggerSelected(this_00);
  }
  return true;
}
