/*
 * Entry: 0050c6d9
 * Name: AIBuild_PriorityLevelIs
 * Namespace: Global
 * Signature: void AIBuild_PriorityLevelIs(tagCP_ACCOUNT * param_1, int param_2, int param_3, int param_4, tagCP_BUILD_TYPE param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AIBuild_PriorityLevelIs
          (tagCP_ACCOUNT *param_1,int param_2,int param_3,int param_4,tagCP_BUILD_TYPE param_5)

{
  int iVar1;
  tagCP_NODE *ptVar2;
  
  Debug_Assert((int)param_1,0xe93,".\\Schedule\\Aibuild.cpp","account");
  if ((param_2 < 0) || (param_1->priority_levels <= param_2)) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  Debug_Assert(iVar1,0xe94,".\\Schedule\\Aibuild.cpp",
               "(priority_level >= 0) && (priority_level < account->priority_levels)");
  Debug_Assert((uint)(0 < param_4),0xe95,".\\Schedule\\Aibuild.cpp","number_of_nodes > 0");
  Debug_Assert((uint)((uint)param_3 < 0x100),0xe96,".\\Schedule\\Aibuild.cpp",
               "(priority >= 0) && (priority <= AIBUILD_MAX_PRIORITY)");
  Debug_Assert((uint)(param_5 < 4),0xe97,".\\Schedule\\Aibuild.cpp",
               "(build_type >= 0) && (build_type <= 3)");
  param_1->priority_level[param_2].nodes = param_4;
  param_1->priority_level[param_2].build_type = param_5;
  param_1->priority_level[param_2].priority = param_3;
  ptVar2 = calloc(1,param_4 * 0xc);
  param_1->priority_level[param_2].node = ptVar2;
  Debug_Assert((int)param_1->priority_level[param_2].node,0xea1,".\\Schedule\\Aibuild.cpp",
               "account->priority_level[priority_level].node");
  if (0 < param_4) {
    iVar1 = 0;
    do {
      *(undefined2 *)((int)&(param_1->priority_level[param_2].node)->object_type + iVar1) = 0;
      *(undefined4 *)((int)&(param_1->priority_level[param_2].node)->field1_0x4 + iVar1) = 0;
      iVar1 = iVar1 + 0xc;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}
