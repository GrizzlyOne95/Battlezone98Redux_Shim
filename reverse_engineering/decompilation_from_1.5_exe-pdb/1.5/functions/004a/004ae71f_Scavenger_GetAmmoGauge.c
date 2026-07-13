/*
 * Entry: 004ae71f
 * Name: Scavenger::GetAmmoGauge
 * Namespace: Scavenger
 * Signature: float GetAmmoGauge(Scavenger * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Scavenger::GetAmmoGauge(Scavenger *this)

{
  return (float)this->scrapHeld / (float)this->maxScrap;
}
