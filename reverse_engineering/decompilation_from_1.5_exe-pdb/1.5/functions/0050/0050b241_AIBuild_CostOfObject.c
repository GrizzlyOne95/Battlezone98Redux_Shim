/*
 * Entry: 0050b241
 * Name: AIBuild_CostOfObject
 * Namespace: Global
 * Signature: int AIBuild_CostOfObject(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_CostOfObject(int param_1)

{
  uchar uVar1;
  tagUNITTYPE *ptVar2;
  tagBUILDINGTYPE *ptVar3;
  uint uVar4;
  ushort uVar5;
  
  uVar5 = (ushort)param_1;
  uVar1 = PREREQ_IsUnit(uVar5);
  if (uVar1 == '\0') {
    uVar1 = PREREQ_IsBuilding(uVar5);
    if (uVar1 == '\0') {
      uVar4 = 1000000000;
      tlog(1,"AIBuild_CostOfObject (%d) - input is not a building or unit\n");
    }
    else {
      ptVar3 = PREREQ_BuildingTypePtr(uVar5);
      uVar4 = ptVar3->cost;
    }
  }
  else {
    ptVar2 = PREREQ_UnitTypePtr(uVar5);
    uVar4 = (uint)ptVar2->buildcost;
  }
  return uVar4;
}
