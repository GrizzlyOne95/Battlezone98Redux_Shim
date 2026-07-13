/*
 * Entry: 0054ec9e
 * Name: PreloadItem
 * Namespace: Global
 * Signature: int PreloadItem(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PreloadItem(char *param_1)

{
  void *pvVar1;
  
  pvVar1 = UseItem(param_1);
  if (pvVar1 != (void *)0x0) {
    UnlockItem(param_1);
  }
  return (uint)(pvVar1 != (void *)0x0);
}
