/*
 * Entry: 00415157
 * Name: HovDelay
 * Namespace: Global
 * Signature: int HovDelay(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HovDelay(_OBJ76 *param_1,_OBJ76 *param_2)

{
  int iVar1;
  
  iVar1 = rand();
  return (uint)(iVar1 % 100 == 1);
}
