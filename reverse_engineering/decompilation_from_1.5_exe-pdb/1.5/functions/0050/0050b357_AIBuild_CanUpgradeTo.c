/*
 * Entry: 0050b357
 * Name: AIBuild_CanUpgradeTo
 * Namespace: Global
 * Signature: int AIBuild_CanUpgradeTo(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_CanUpgradeTo(int param_1,int param_2)

{
  uchar uVar1;
  tagBUILDINGTYPE *ptVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = PREREQ_IsBuilding((ushort)param_1);
  if (uVar1 != '\0') {
    ptVar2 = PREREQ_BuildingTypePtr((ushort)param_1);
    if (ptVar2->upgradeof != (tagBUILDINGTYPE *)0x0) {
      iVar3 = PREREQ_HowMany(ptVar2->upgradeof->prereqtype,(char)param_2);
      iVar4 = PREREQ_HowMany(ptVar2->prereqtype,(char)param_2);
      if (iVar4 < iVar3) {
        return 1;
      }
    }
  }
  return 0;
}
