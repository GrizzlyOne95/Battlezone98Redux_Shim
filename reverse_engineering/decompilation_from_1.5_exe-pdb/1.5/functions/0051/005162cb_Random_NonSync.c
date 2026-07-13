/*
 * Entry: 005162cb
 * Name: Random_NonSync
 * Namespace: Global
 * Signature: ulong Random_NonSync(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl Random_NonSync(int param_1)

{
  ulong uVar1;
  int in_stack_00000008;
  
  uVar1 = Random_Rand((int *)param_1,in_stack_00000008);
  return uVar1;
}
