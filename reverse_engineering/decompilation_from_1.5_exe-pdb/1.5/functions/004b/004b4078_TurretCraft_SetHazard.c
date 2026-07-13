/*
 * Entry: 004b4078
 * Name: TurretCraft::SetHazard
 * Namespace: TurretCraft
 * Signature: void SetHazard(TurretCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::SetHazard(TurretCraft *this)

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
    HazardCells((this->hazardPos).x,(this->hazardPos).z,200.0,iVar3,true);
  }
  return;
}
