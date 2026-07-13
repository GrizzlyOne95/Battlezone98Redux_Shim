/*
 * Entry: 0050bbae
 * Name: AIBuild_ResourceClosestBuildable
 * Namespace: Global
 * Signature: int AIBuild_ResourceClosestBuildable(tag_team * param_1, int param_2, tagBUILDINGTYPE * param_3, int param_4, int param_5, int * param_6, int * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_ResourceClosestBuildable
          (tag_team *param_1,int param_2,tagBUILDINGTYPE *param_3,int param_4,int param_5,
          int *param_6,int *param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  local_10 = 0;
  do {
    iVar1 = AIBuild_ResourceListFind(param_2,local_10,&local_8,&local_c);
    if (iVar1 != 0) {
      iVar3 = param_4 - local_8;
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      iVar2 = param_5 - local_c;
      if (iVar2 < 0) {
        iVar2 = -iVar2;
      }
      if (iVar3 <= iVar2) {
        iVar3 = iVar2;
      }
      if ((local_14 == 0) || (iVar3 < local_18)) {
        local_c = local_c - (*(uint *)&param_3->field_0x24 >> 0x17 & 7);
        local_8 = local_8 - (*(uint *)&param_3->field_0x24 >> 0x13 & 7);
        iVar2 = AIBuild_CanMineFitHere(param_1->team_ID,param_3,local_8,local_c,&local_8,&local_c);
        if (iVar2 != 0) {
          *param_6 = local_8;
          local_14 = 1;
          *param_7 = local_c;
          local_18 = iVar3;
        }
      }
    }
    local_10 = local_10 + 1;
  } while (iVar1 != 0);
  return local_14;
}
