/*
 * Entry: 00484865
 * Name: MCUseItem
 * Namespace: Global
 * Signature: void * MCUseItem(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl MCUseItem(MULTICACHE *param_1,char *param_2)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) &&
     (iVar1 = _strnicmp(param_2,"null",4), iVar1 != 0)) {
    pvVar2 = MCuse_nonpack_item(param_1,param_2);
    return pvVar2;
  }
  return (void *)0x0;
}
