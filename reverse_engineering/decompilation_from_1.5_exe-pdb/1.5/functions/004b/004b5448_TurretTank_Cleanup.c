/*
 * Entry: 004b5448
 * Name: TurretTank::Cleanup
 * Namespace: TurretTank
 * Signature: void Cleanup(TurretTank * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::Cleanup(TurretTank *this)

{
  ClearHazard(this);
  Craft::Cleanup((Craft *)this);
  return;
}
