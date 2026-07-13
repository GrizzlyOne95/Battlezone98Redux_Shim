/*
 * Entry: 0050b60f
 * Name: AIBuildListGeneratePriorityLevel_RATIO_TO_BUILD
 * Namespace: Global
 * Signature: int AIBuildListGeneratePriorityLevel_RATIO_TO_BUILD(tag_team * param_1, tagCP_PRIORITY_LEVEL * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuildListGeneratePriorityLevel_RATIO_TO_BUILD
          (tag_team *param_1,tagCP_PRIORITY_LEVEL *param_2,int param_3)

{
  float fVar1;
  tagCP_PRIORITY_LEVEL *ptVar2;
  uchar uVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  float afStack_410 [128];
  int aiStack_210 [128];
  float local_10;
  int local_c;
  int local_8;
  
  ptVar2 = param_2;
  Debug_Assert((int)param_2,0x66a,".\\Schedule\\Aibuild.cpp","priority_level");
  if ((param_2->nodes < 1) || (0x7f < param_2->nodes)) {
    iVar4 = 0;
  }
  else {
    iVar4 = 1;
  }
  Debug_Assert(iVar4,0x66b,".\\Schedule\\Aibuild.cpp",
               "(priority_level->nodes > 0) && (priority_level->nodes < MAX_NODES)");
  iVar4 = 0;
  param_2 = (tagCP_PRIORITY_LEVEL *)0x0;
  local_8 = 0;
  do {
    puVar6 = (ushort *)((int)&ptVar2->node->object_type + local_8);
    uVar3 = PREREQ_CanMake(*puVar6,(char)param_1->team_ID);
    if ((uVar3 == '\0') &&
       (iVar5 = AIBuild_CanUpgradeTo((uint)*puVar6,param_1->team_ID), iVar5 == 0)) {
      aiStack_210[iVar4] = 0;
    }
    else {
      iVar5 = *(int *)(puVar6 + 4);
      aiStack_210[iVar4] = 1;
      fVar1 = (float)iVar5 / (float)*(int *)(puVar6 + 2);
      afStack_410[iVar4] = fVar1;
      if ((param_2 == (tagCP_PRIORITY_LEVEL *)0x0) || (local_10 < fVar1)) {
        local_10 = fVar1;
        local_c = iVar4;
      }
      param_2 = (tagCP_PRIORITY_LEVEL *)((int)&param_2->priority + 1);
    }
    local_8 = local_8 + 0xc;
    iVar4 = iVar4 + 1;
  } while (iVar4 < ptVar2->nodes);
  iVar4 = 0;
  if (0 < (int)param_2) {
    iVar5 = 0;
    do {
      puVar6 = (ushort *)((int)&ptVar2->node->object_type + iVar4);
      if ((aiStack_210[iVar5] != 0) &&
         ((iVar5 != local_c || (param_2 == (tagCP_PRIORITY_LEVEL *)0x1)))) {
        AIBuild_BuildListNodeAdd(param_1,(uint)*puVar6,param_3,1,2,(int *)(puVar6 + 4));
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar5 < ptVar2->nodes);
  }
  return 1;
}
