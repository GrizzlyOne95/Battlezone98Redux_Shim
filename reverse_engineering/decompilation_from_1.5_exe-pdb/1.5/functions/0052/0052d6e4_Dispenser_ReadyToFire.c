/*
 * Entry: 0052d6e4
 * Name: Dispenser::ReadyToFire
 * Namespace: Dispenser
 * Signature: bool ReadyToFire(Dispenser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Dispenser::ReadyToFire(Dispenser *this)

{
  float fVar1;
  
  fVar1 = this->shotTimer;
  if (!NAN(fVar1) && 0.0 < fVar1 != (fVar1 == 0.0)) {
    return true;
  }
  return false;
}
