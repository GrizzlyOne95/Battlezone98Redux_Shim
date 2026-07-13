/*
 * Entry: 004b3a05
 * Name: Tug::Explode
 * Namespace: Tug
 * Signature: void Explode(Tug * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::Explode(Tug *this)

{
  SetCargo((Tug *)&this[-1].cargo,(GameObject *)0x0);
  Craft::Explode((Craft *)this);
  return;
}
