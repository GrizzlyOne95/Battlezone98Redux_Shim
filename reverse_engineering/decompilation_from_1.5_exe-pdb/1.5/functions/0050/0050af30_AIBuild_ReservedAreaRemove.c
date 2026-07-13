/*
 * Entry: 0050af30
 * Name: AIBuild_ReservedAreaRemove
 * Namespace: Global
 * Signature: void AIBuild_ReservedAreaRemove(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ReservedAreaRemove(int param_1,int param_2)

{
  if ((uint)param_2 < 0x20) {
    reserved_used[param_1][param_2] = '\0';
  }
  return;
}
