/*
 * Entry: 0050b317
 * Name: AIBuild_CanThisUpgradeToThat
 * Namespace: Global
 * Signature: int AIBuild_CanThisUpgradeToThat(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_CanThisUpgradeToThat(int param_1,int param_2)

{
  uchar uVar1;
  tagBUILDINGTYPE *ptVar2;
  tagBUILDINGTYPE *ptVar3;
  
  uVar1 = PREREQ_IsBuilding((ushort)param_1);
  if (uVar1 != '\0') {
    uVar1 = PREREQ_IsBuilding((ushort)param_2);
    if (uVar1 != '\0') {
      ptVar2 = PREREQ_BuildingTypePtr((ushort)param_1);
      ptVar3 = PREREQ_BuildingTypePtr((ushort)param_2);
      if (ptVar2 == ptVar3->upgradeof) {
        return 1;
      }
    }
  }
  return 0;
}
