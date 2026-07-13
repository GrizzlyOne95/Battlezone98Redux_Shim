/*
 * Entry: 0053a18d
 * Name: SpecialItem::EnoughAmmo
 * Namespace: SpecialItem
 * Signature: bool EnoughAmmo(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SpecialItem::EnoughAmmo(SpecialItem *this)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)(int)(this->carrier->curAmmo ^ 0x33333333);
  fVar2 = TimeStep();
  fVar2 = fVar2 * (float)*(int *)(this->_padding_ + 0x78);
  if (fVar2 < fVar1 != (fVar2 == fVar1)) {
    return true;
  }
  return false;
}
