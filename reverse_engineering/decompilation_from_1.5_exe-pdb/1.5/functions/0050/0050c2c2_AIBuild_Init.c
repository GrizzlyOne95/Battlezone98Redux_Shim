/*
 * Entry: 0050c2c2
 * Name: AIBuild_Init
 * Namespace: Global
 * Signature: void AIBuild_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_Init(void)

{
  AIBuild_ResourceListNew();
  AIBuild_ResourceListDump(0);
  AIBuild_ResourceListDump(1);
  return;
}
