/*
 * Entry: 0050b8dd
 * Name: AIBuild_IsSpaceAroundFacility
 * Namespace: Global
 * Signature: int AIBuild_IsSpaceAroundFacility(tagUNIT * param_1, tagBUILDINGTYPE * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_IsSpaceAroundFacility(tagUNIT *param_1,tagBUILDINGTYPE *param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = AIBuild_IsAreaLevel(param_3,((*(uint *)&param_2->field_0x24 >> 0x16 & 0xf) - 1) + param_4,
                              *(uint *)&param_2->field_0x24 >> 0x12 & 0xf,2);
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = AIBuild_IsAreaFreeOfBuildings
                      (param_3 + -1,param_4 + -1,(*(uint *)&param_2->field_0x24 >> 0x12 & 0xf) + 2,
                       (*(uint *)&param_2->field_0x24 >> 0x16 & 0xf) + 2);
    uVar2 = (uint)(iVar1 != 0);
  }
  return uVar2;
}
