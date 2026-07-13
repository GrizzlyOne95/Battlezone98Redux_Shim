/*
 * Entry: 0047dc12
 * Name: APC::FullSoldiers
 * Namespace: APC
 * Signature: bool FullSoldiers(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall APC::FullSoldiers(APC *this)

{
  return *(int *)(this->_padding_ + 0x3cc) <= this->soldierCount;
}
