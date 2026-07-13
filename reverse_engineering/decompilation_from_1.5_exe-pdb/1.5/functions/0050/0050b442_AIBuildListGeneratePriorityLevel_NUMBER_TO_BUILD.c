/*
 * Entry: 0050b442
 * Name: AIBuildListGeneratePriorityLevel_NUMBER_TO_BUILD
 * Namespace: Global
 * Signature: int AIBuildListGeneratePriorityLevel_NUMBER_TO_BUILD(tag_team * param_1, tagCP_PRIORITY_LEVEL * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuildListGeneratePriorityLevel_NUMBER_TO_BUILD
          (tag_team *param_1,tagCP_PRIORITY_LEVEL *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  uchar uVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  iVar6 = 0;
  local_8 = 0;
  local_c = 0;
  do {
    puVar4 = (ushort *)((int)&param_2->node->object_type + iVar6);
    uVar1 = *puVar4;
    iVar2 = *(int *)(puVar4 + 4);
    if (0 < iVar2) {
      local_c = 1;
      uVar3 = PREREQ_CanMake(uVar1,(char)param_1->team_ID);
      if (uVar3 == '\0') {
        iVar5 = AIBuild_CanUpgradeTo((uint)uVar1,param_1->team_ID);
        if (iVar5 == 0) goto LAB_0050b4ae;
      }
      AIBuild_BuildListNodeAdd
                (param_1,(uint)uVar1,param_3,iVar2,1,
                 (int *)((int)&param_2->node->field2_0x8 + iVar6));
    }
LAB_0050b4ae:
    local_8 = local_8 + 1;
    iVar6 = iVar6 + 0xc;
    if (param_2->nodes <= local_8) {
      return local_c;
    }
  } while( true );
}
