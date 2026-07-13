/*
 * Entry: 004b4068
 * Name: TurretCraft::Cleanup
 * Namespace: TurretCraft
 * Signature: void Cleanup(TurretCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::Cleanup(TurretCraft *this)

{
  ClearHazard(this);
  Craft::Cleanup((Craft *)this);
  return;
}
