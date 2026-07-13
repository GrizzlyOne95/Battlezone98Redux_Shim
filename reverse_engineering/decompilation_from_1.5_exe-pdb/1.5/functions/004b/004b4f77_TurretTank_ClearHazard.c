/*
 * Entry: 004b4f77
 * Name: TurretTank::ClearHazard
 * Namespace: TurretTank
 * Signature: void ClearHazard(TurretTank * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::ClearHazard(TurretTank *this)

{
  float fVar1;
  
  if (this->hazardTeam != 0) {
    fVar1 = (float)this->_padding_;
    PerimeterCells((this->hazardPos).x - fVar1,(this->hazardPos).z - fVar1,
                   (this->hazardPos).x + fVar1,(this->hazardPos).z + fVar1,false);
    HazardCells((this->hazardPos).x,(this->hazardPos).z,150.0,this->hazardTeam,false);
    this->hazardTeam = 0;
  }
  return;
}
