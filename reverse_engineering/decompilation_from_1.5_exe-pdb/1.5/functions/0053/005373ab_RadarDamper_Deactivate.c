/*
 * Entry: 005373ab
 * Name: RadarDamper::Deactivate
 * Namespace: RadarDamper
 * Signature: void Deactivate(RadarDamper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RadarDamper::Deactivate(RadarDamper *this)

{
  uint *puVar1;
  
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffffe;
  return;
}
