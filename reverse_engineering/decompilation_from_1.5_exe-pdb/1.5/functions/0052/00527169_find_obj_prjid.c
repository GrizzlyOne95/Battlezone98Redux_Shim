/*
 * Entry: 00527169
 * Name: find_obj_prjid
 * Namespace: Global
 * Signature: _OBJ76 * find_obj_prjid(_OBJ76 * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl find_obj_prjid(_OBJ76 *param_1,long64 param_2)

{
  _OBJ76 *p_Var1;
  undefined4 unaff_ESI;
  int in_stack_00000008;
  
  while( true ) {
    if (param_1 == (_OBJ76 *)0x0) {
      return (_OBJ76 *)0x0;
    }
    if (((int)param_1->id == in_stack_00000008) && (*(int *)((int)&param_1->id + 4) == (int)param_2)
       ) break;
    p_Var1 = find_obj_prjid(param_1->child,CONCAT44(unaff_ESI,(int)param_2));
    if (p_Var1 != (_OBJ76 *)0x0) {
      return p_Var1;
    }
    param_1 = param_1->sibling;
  }
  return param_1;
}
