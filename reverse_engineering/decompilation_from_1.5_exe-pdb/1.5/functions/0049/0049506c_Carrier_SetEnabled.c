/*
 * Entry: 0049506c
 * Name: Carrier::SetEnabled
 * Namespace: Carrier
 * Signature: void SetEnabled(Carrier * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::SetEnabled(Carrier *this,ulong param_1)

{
  this->enabled = this->existant & param_1;
  return;
}
