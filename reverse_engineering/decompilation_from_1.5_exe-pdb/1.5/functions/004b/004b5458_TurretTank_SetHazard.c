/*
 * Entry: 004b5458
 * Name: TurretTank::SetHazard
 * Namespace: TurretTank
 * Signature: void SetHazard(TurretTank * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::SetHazard(TurretTank *this)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  
  piVar1 = &this->_padding_;
  iVar3 = (**(code **)(*piVar1 + 4))();
  if (this->hazardTeam != iVar3) {
    ClearHazard(this);
    iVar3 = (**(code **)(*piVar1 + 4))();
    this->hazardTeam = iVar3;
    pfVar4 = (float *)(**(code **)(*piVar1 + 0xc))();
    fVar2 = pfVar4[2];
    iVar3 = this->hazardTeam;
    (this->hazardPos).x = *pfVar4;
    (this->hazardPos).z = fVar2;
    HazardCells((this->hazardPos).x,(this->hazardPos).z,150.0,iVar3,true);
    fVar2 = (float)this->_padding_;
    PerimeterCells((this->hazardPos).x - fVar2,(this->hazardPos).z - fVar2,
                   (this->hazardPos).x + fVar2,fVar2 + (this->hazardPos).z,true);
  }
  return;
}
