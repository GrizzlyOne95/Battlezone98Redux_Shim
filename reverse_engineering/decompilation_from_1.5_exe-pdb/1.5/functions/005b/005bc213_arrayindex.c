/*
 * Entry: 005bc213
 * Name: arrayindex
 * Namespace: Global
 * Signature: int arrayindex(lua_TValue * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl arrayindex(lua_TValue *param_1)

{
  int iVar1;
  double *in_EAX;
  
  if (*(int *)(in_EAX + 1) == 3) {
    iVar1 = (int)ROUND(*in_EAX);
    if ((double)iVar1 == *in_EAX) {
      return iVar1;
    }
  }
  return -1;
}
