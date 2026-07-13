/*
 * Entry: 004b3c1d
 * Name: TurretCraft::ClearHazard
 * Namespace: TurretCraft
 * Signature: void ClearHazard(TurretCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::ClearHazard(TurretCraft *this)

{
  if (this->hazardTeam != 0) {
    HazardCells((this->hazardPos).x,(this->hazardPos).z,200.0,this->hazardTeam,false);
    this->hazardTeam = 0;
  }
  return;
}
