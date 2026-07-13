/*
 * Entry: 0050b990
 * Name: AIBuild_CanMineFitExactlyHere
 * Namespace: Global
 * Signature: int AIBuild_CanMineFitExactlyHere(int param_1, tagBUILDINGTYPE * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_CanMineFitExactlyHere(int param_1,tagBUILDINGTYPE *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = AIBuild_ReservedAreaIsAreaReserved
                    (param_1,param_3,param_4,*(uint *)&param_2->field_0x24 >> 0x12 & 0xf,
                     *(uint *)&param_2->field_0x24 >> 0x16 & 0xf);
  if (iVar1 == 0) {
    iVar1 = AIBuild_CanBuildHere(param_2,param_3,param_4);
    if (iVar1 != 0) {
      iVar2 = 1;
    }
  }
  return iVar2;
}
