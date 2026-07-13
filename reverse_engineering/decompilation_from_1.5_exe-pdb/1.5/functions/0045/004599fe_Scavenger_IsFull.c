/*
 * Entry: 004599fe
 * Name: Scavenger::IsFull
 * Namespace: Scavenger
 * Signature: bool IsFull(Scavenger * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Scavenger::IsFull(Scavenger *this)

{
  return this->maxScrap <= this->scrapHeld;
}
