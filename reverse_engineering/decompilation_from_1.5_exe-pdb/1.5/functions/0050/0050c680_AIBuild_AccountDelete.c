/*
 * Entry: 0050c680
 * Name: AIBuild_AccountDelete
 * Namespace: Global
 * Signature: void AIBuild_AccountDelete(tagCP_ACCOUNT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_AccountDelete(tagCP_ACCOUNT *param_1)

{
  void *_Memory;
  int iVar1;
  int iVar2;
  
  Debug_Assert((int)param_1,0xe6c,".\\Schedule\\Aibuild.cpp","account");
  iVar2 = 0;
  if (param_1->priority_level != (tagCP_PRIORITY_LEVEL *)0x0) {
    iVar1 = 0;
    if (0 < param_1->priority_levels) {
      do {
        _Memory = *(void **)((int)&param_1->priority_level->node + iVar2);
        if (_Memory != (void *)0x0) {
          free(_Memory);
        }
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x10;
      } while (iVar1 < param_1->priority_levels);
    }
    free(param_1->priority_level);
  }
  free(param_1);
  return;
}
