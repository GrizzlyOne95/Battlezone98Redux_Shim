/*
 * Entry: 004848fc
 * Name: GetItem
 * Namespace: Global
 * Signature: uchar * GetItem(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl GetItem(char *param_1)

{
  uchar *puVar1;
  
  puVar1 = MCUseItem(&GlobalCache,param_1);
  return puVar1;
}
