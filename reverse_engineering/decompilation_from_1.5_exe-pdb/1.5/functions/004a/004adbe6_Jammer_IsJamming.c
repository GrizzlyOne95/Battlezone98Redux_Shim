/*
 * Entry: 004adbe6
 * Name: Jammer::IsJamming
 * Namespace: Jammer
 * Signature: bool IsJamming(Jammer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Jammer::IsJamming(Jammer *this)

{
  if (((this->owner->euler).v_mag < this->maxSpeed) && (this->owner->aiProcess != (AiProcess *)0x0))
  {
    return true;
  }
  return false;
}
