/*
 * Entry: 0047dbff
 * Name: APC::AddSoldiers
 * Namespace: APC
 * Signature: void AddSoldiers(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::AddSoldiers(APC *this)

{
  this->soldierCount = *(int *)(this->_padding_ + 0x3cc);
  return;
}
