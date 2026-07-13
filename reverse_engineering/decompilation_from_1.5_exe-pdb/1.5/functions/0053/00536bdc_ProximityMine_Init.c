/*
 * Entry: 00536bdc
 * Name: ProximityMine::Init
 * Namespace: ProximityMine
 * Signature: void Init(ProximityMine * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ProximityMine::Init(ProximityMine *this,int param_1)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined1 uVar6;
  
  Building::Init((Building *)this,param_1);
  piVar1 = &this->_padding_;
  pfVar2 = (float *)(**(code **)(*piVar1 + 0xc))();
  uVar6 = 1;
  iVar3 = (**(code **)(*piVar1 + 4))();
  fVar5 = *(float *)(this->_padding_ + 0x168);
  iVar4 = (**(code **)(*piVar1 + 0xc))();
  HazardCells(*pfVar2,*(float *)(iVar4 + 8),fVar5,iVar3,(bool)uVar6);
  return;
}
