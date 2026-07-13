/*
 * Entry: 0052d7a6
 * Name: Dispenser::EnoughAmmo
 * Namespace: Dispenser
 * Signature: bool EnoughAmmo(Dispenser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Dispenser::EnoughAmmo(Dispenser *this)

{
  if ((this->_padding_ != 0) &&
     (*(int *)(this->_padding_ + 100) <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
    return true;
  }
  return false;
}
