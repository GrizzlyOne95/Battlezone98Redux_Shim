/*
 * Entry: 0049c5fc
 * Name: HoverCraft::InitSound
 * Namespace: HoverCraft
 * Signature: void InitSound(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::InitSound(HoverCraft *this)

{
  this->lastThrot = 0.0;
  this->soundTurbo = (_gas_object *)0x0;
  this->lastFly = 0.0;
  this->soundThrust = (_gas_object *)0x0;
  this->soundFly = (_gas_object *)0x0;
  return;
}
