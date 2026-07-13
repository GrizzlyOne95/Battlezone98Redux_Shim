/*
 * Entry: 00537399
 * Name: RadarDamper::IsActive
 * Namespace: RadarDamper
 * Signature: bool IsActive(RadarDamper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RadarDamper::IsActive(RadarDamper *this)

{
  return (bool)((byte)*(undefined4 *)(*(int *)&this->field_0x18 + 0x14) & 1);
}
