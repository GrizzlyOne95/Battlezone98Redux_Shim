/*
 * Entry: 004b2254
 * Name: undibs_textable
 * Namespace: Global
 * Signature: int undibs_textable(textab * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl undibs_textable(textab *param_1)

{
  int in_EAX;
  
  *(int *)(in_EAX + 0x10) = *(int *)(in_EAX + 0x10) + -1;
  return 1;
}
