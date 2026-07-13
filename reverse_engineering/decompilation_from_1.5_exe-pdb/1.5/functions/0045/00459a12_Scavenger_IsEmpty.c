/*
 * Entry: 00459a12
 * Name: Scavenger::IsEmpty
 * Namespace: Scavenger
 * Signature: bool IsEmpty(Scavenger * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Scavenger::IsEmpty(Scavenger *this)

{
  return this->scrapHeld < 1;
}
