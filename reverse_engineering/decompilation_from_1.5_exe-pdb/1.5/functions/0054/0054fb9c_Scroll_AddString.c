/*
 * Entry: 0054fb9c
 * Name: Scroll_AddString
 * Namespace: Global
 * Signature: void Scroll_AddString(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_AddString(void *param_1,char *param_2)

{
  Scroll_AddStringColored(param_1,param_2,*(ulong *)(*(int *)((int)param_1 + 8) + 0x2c));
  return;
}
