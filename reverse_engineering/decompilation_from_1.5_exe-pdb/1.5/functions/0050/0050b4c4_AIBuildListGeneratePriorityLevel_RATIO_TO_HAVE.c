/*
 * Entry: 0050b4c4
 * Name: AIBuildListGeneratePriorityLevel_RATIO_TO_HAVE
 * Namespace: Global
 * Signature: int AIBuildListGeneratePriorityLevel_RATIO_TO_HAVE(tag_team * param_1, tagCP_PRIORITY_LEVEL * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuildListGeneratePriorityLevel_RATIO_TO_HAVE
          (tag_team *param_1,tagCP_PRIORITY_LEVEL *param_2,int param_3)

{
  ushort uVar1;
  float fVar2;
  uchar uVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  bool bVar7;
  float afStack_418 [128];
  int aiStack_218 [128];
  int local_18;
  int local_14;
  float local_10;
  int local_c;
  int local_8;
  
  Debug_Assert((int)param_2,0x61a,".\\Schedule\\Aibuild.cpp","priority_level");
  if ((param_2->nodes < 1) || (0x7f < param_2->nodes)) {
    iVar4 = 0;
  }
  else {
    iVar4 = 1;
  }
  Debug_Assert(iVar4,0x61b,".\\Schedule\\Aibuild.cpp",
               "(priority_level->nodes > 0) && (priority_level->nodes < MAX_NODES)");
  iVar4 = 0;
  local_8 = 0;
  local_c = 0;
  do {
    puVar6 = (ushort *)((int)&param_2->node->object_type + local_c);
    uVar3 = PREREQ_CanMake(*puVar6,(char)param_1->team_ID);
    if ((uVar3 == '\0') &&
       (iVar5 = AIBuild_CanUpgradeTo((uint)*puVar6,param_1->team_ID), iVar5 == 0)) {
      aiStack_218[iVar4] = 0;
    }
    else {
      iVar5 = param_1->team_ID;
      uVar1 = *puVar6;
      aiStack_218[iVar4] = 1;
      iVar5 = PREREQ_HowMany(uVar1,(char)iVar5);
      bVar7 = local_8 == 0;
      local_18 = iVar5 + number_under_construction[param_1->team_ID][*puVar6];
      fVar2 = (float)(iVar5 + number_under_construction[param_1->team_ID][*puVar6]) /
              (float)*(int *)(puVar6 + 2);
      afStack_418[iVar4] = fVar2;
      if ((bVar7) || (local_10 < fVar2)) {
        local_10 = fVar2;
        local_14 = iVar4;
      }
      local_8 = local_8 + 1;
    }
    local_c = local_c + 0xc;
    iVar4 = iVar4 + 1;
  } while (iVar4 < param_2->nodes);
  iVar4 = 0;
  if (0 < local_8) {
    iVar5 = 0;
    do {
      if ((aiStack_218[iVar5] != 0) && ((iVar5 != local_14 || (local_8 == 1)))) {
        AIBuild_BuildListNodeAdd
                  (param_1,(uint)*(ushort *)((int)&param_2->node->object_type + iVar4),param_3,1,3,
                   (int *)0x0);
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar5 < param_2->nodes);
  }
  return 1;
}
