/*
 * Entry: 0050bc69
 * Name: AIBuild_CanUnitBuildHere
 * Namespace: Global
 * Signature: int AIBuild_CanUnitBuildHere(tag_team * param_1, tagUNIT * param_2, tagBUILDINGTYPE * param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_CanUnitBuildHere
          (tag_team *param_1,tagUNIT *param_2,tagBUILDINGTYPE *param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = AIBuild_ReservedAreaIsAreaReserved
                    (param_1->team_ID,param_4,param_5,*(uint *)&param_3->field_0x24 >> 0x12 & 0xf,
                     *(uint *)&param_3->field_0x24 >> 0x16 & 0xf);
  if ((((iVar1 == 0) && (iVar1 = AIBuild_ResourceIsClose(0,param_4,param_5), iVar1 == 0)) &&
      (iVar1 = AIBuild_ResourceIsClose(1,param_4,param_5), iVar1 == 0)) &&
     (iVar1 = AIBuild_IsSpaceAroundFacility(param_2,param_3,param_4,param_5), iVar1 != 0)) {
    iVar1 = AIBuild_CanBuildHere(param_3,param_4,param_5);
    return iVar1;
  }
  return 0;
}
