/*
 * Entry: 00536c33
 * Name: ProximityMine::Cleanup
 * Namespace: ProximityMine
 * Signature: void Cleanup(ProximityMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ProximityMine::Cleanup(ProximityMine *this)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined1 uVar6;
  
  piVar1 = &this->_padding_;
  pfVar2 = (float *)(**(code **)(*piVar1 + 0xc))();
  uVar6 = 0;
  iVar3 = (**(code **)(*piVar1 + 4))();
  fVar5 = *(float *)(this->_padding_ + 0x168);
  iVar4 = (**(code **)(*piVar1 + 0xc))();
  HazardCells(*pfVar2,*(float *)(iVar4 + 8),fVar5,iVar3,(bool)uVar6);
  Building::Cleanup((Building *)this);
  return;
}
