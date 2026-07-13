/*
 * Entry: 0050c4e3
 * Name: AIBuild_PriorityLevelInit
 * Namespace: Global
 * Signature: void AIBuild_PriorityLevelInit(tagCP_PRIORITY_LEVEL * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_PriorityLevelInit(tagCP_PRIORITY_LEVEL *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1->build_type == NUMBER_TO_BUILD) {
    iVar2 = 0;
    iVar1 = 0;
    if (0 < param_1->nodes) {
      do {
        iVar1 = iVar1 + 1;
        *(undefined4 *)((int)&param_1->node->field2_0x8 + iVar2) =
             *(undefined4 *)((int)&param_1->node->field1_0x4 + iVar2);
        iVar2 = iVar2 + 0xc;
      } while (iVar1 < param_1->nodes);
    }
  }
  else if ((param_1->build_type == RATIO_TO_BUILD) && (0 < param_1->nodes)) {
    iVar2 = 0;
    iVar1 = 0;
    do {
      *(undefined4 *)((int)&param_1->node->field2_0x8 + iVar2) = 0;
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0xc;
    } while (iVar1 < param_1->nodes);
  }
  return;
}
