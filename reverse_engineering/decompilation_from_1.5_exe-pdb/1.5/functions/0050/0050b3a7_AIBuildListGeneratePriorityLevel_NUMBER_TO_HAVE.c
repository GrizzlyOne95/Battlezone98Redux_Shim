/*
 * Entry: 0050b3a7
 * Name: AIBuildListGeneratePriorityLevel_NUMBER_TO_HAVE
 * Namespace: Global
 * Signature: int AIBuildListGeneratePriorityLevel_NUMBER_TO_HAVE(tag_team * param_1, tagCP_PRIORITY_LEVEL * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuildListGeneratePriorityLevel_NUMBER_TO_HAVE
          (tag_team *param_1,tagCP_PRIORITY_LEVEL *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uchar uVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_10 = 0;
  local_8 = 0;
  do {
    puVar5 = (ushort *)((int)&param_2->node->object_type + local_8);
    uVar1 = *puVar5;
    uVar8 = (uint)uVar1;
    iVar2 = *(int *)(puVar5 + 2);
    iVar6 = PREREQ_HowMany(uVar1,(char)param_1->team_ID);
    iVar3 = number_under_construction[param_1->team_ID][uVar8];
    if (iVar6 + iVar3 < iVar2) {
      local_10 = 1;
      uVar4 = PREREQ_CanMake(uVar1,(char)param_1->team_ID);
      if (uVar4 == '\0') {
        iVar7 = AIBuild_CanUpgradeTo(uVar8,param_1->team_ID);
        if (iVar7 == 0) goto LAB_0050b428;
      }
      AIBuild_BuildListNodeAdd(param_1,uVar8,param_3,iVar2 - (iVar6 + iVar3),0,(int *)0x0);
    }
LAB_0050b428:
    local_c = local_c + 1;
    local_8 = local_8 + 0xc;
    if (param_2->nodes <= local_c) {
      return local_10;
    }
  } while( true );
}
