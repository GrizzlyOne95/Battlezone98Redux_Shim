/*
 * Entry: 0050c5e9
 * Name: AIBuild_AccountNew
 * Namespace: Global
 * Signature: tagCP_ACCOUNT * AIBuild_AccountNew(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagCP_ACCOUNT * __cdecl AIBuild_AccountNew(int param_1)

{
  tagCP_ACCOUNT *ptVar1;
  tagCP_PRIORITY_LEVEL *ptVar2;
  int iVar3;
  
  Debug_Assert((uint)(0 < param_1),0xe49,".\\Schedule\\Aibuild.cpp","priority_levels > 0");
  ptVar1 = calloc(1,8);
  Debug_Assert((int)ptVar1,0xe4d,".\\Schedule\\Aibuild.cpp","account");
  ptVar1->priority_levels = param_1;
  ptVar2 = calloc(1,param_1 << 4);
  ptVar1->priority_level = ptVar2;
  Debug_Assert((int)ptVar2,0xe54,".\\Schedule\\Aibuild.cpp","account->priority_level");
  if (0 < param_1) {
    iVar3 = 0;
    do {
      *(undefined4 *)((int)&ptVar1->priority_level->nodes + iVar3) = 0;
      *(undefined4 *)((int)&ptVar1->priority_level->node + iVar3) = 0;
      *(undefined4 *)((int)&ptVar1->priority_level->priority + iVar3) = 0;
      *(undefined4 *)((int)&ptVar1->priority_level->build_type + iVar3) = 0;
      iVar3 = iVar3 + 0x10;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  return ptVar1;
}
