/*
 * Entry: 0047e875
 * Name: Carrier::SetHardpoint
 * Namespace: Carrier
 * Signature: void SetHardpoint(Carrier * this, int param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::SetHardpoint(Carrier *this,int param_1,_OBJ76 *param_2)

{
  this->hardpoint[param_1] = param_2;
  if ((param_2 != (_OBJ76 *)0x0) && (param_2->class_id == CLASS_ID_SPECIAL_HARDPOINT)) {
    this->special = param_1;
  }
  return;
}
