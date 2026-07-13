/*
 * Entry: 004aa4b1
 * Name: FindHardpoint
 * Namespace: Global
 * Signature: _OBJ76 * FindHardpoint(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl FindHardpoint(_OBJ76 *param_1,char *param_2)

{
  int iVar1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  
  if (param_1 != (_OBJ76 *)0x0) {
    iVar1 = _strnicmp((char *)((int)&param_1->id + 5),param_2,3);
    if (iVar1 == 0) {
      return param_1;
    }
    for (p_Var3 = param_1->child; p_Var3 != (_OBJ76 *)0x0; p_Var3 = p_Var3->sibling) {
      p_Var2 = FindHardpoint(p_Var3,param_2);
      if (p_Var2 != (_OBJ76 *)0x0) {
        return p_Var2;
      }
    }
  }
  return (_OBJ76 *)0x0;
}
