/*
 * Entry: 005373a3
 * Name: RadarDamper::Activate
 * Namespace: RadarDamper
 * Signature: void Activate(RadarDamper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RadarDamper::Activate(RadarDamper *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 | 1;
  return;
}
