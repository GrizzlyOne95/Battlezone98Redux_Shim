/*
 * Entry: 005bcff4
 * Name: unlinkupval
 * Namespace: Global
 * Signature: void unlinkupval(UpVal * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl unlinkupval(UpVal *param_1)

{
  int in_EAX;
  
  *(undefined4 *)(*(int *)(in_EAX + 0x14) + 0x10) = *(undefined4 *)(in_EAX + 0x10);
  *(undefined4 *)(*(int *)(in_EAX + 0x10) + 0x14) = *(undefined4 *)(in_EAX + 0x14);
  return;
}
