/*
 * Entry: 004ecd45
 * Name: obj_find_class
 * Namespace: Global
 * Signature: _OBJ76 * obj_find_class(_OBJ76 * param_1, OBJECT_CLASS_T param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl obj_find_class(_OBJ76 *param_1,OBJECT_CLASS_T param_2)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  
  if ((param_1 != (_OBJ76 *)0x0) && (param_1->class_id != param_2)) {
    for (p_Var2 = param_1->child; p_Var2 != (_OBJ76 *)0x0; p_Var2 = p_Var2->sibling) {
      p_Var1 = obj_find_class(p_Var2,param_2);
      if (p_Var1 != (_OBJ76 *)0x0) {
        return p_Var1;
      }
    }
    param_1 = (_OBJ76 *)0x0;
  }
  return param_1;
}
