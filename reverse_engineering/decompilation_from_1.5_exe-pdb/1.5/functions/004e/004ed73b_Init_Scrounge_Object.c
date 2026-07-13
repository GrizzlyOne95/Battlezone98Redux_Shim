/*
 * Entry: 004ed73b
 * Name: Init_Scrounge_Object
 * Namespace: Global
 * Signature: void Init_Scrounge_Object(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Scrounge_Object(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  
  if (param_1 != (_OBJ76 *)0x0) {
    param_1->class_ptr = param_1;
    p_Var1 = param_1->child;
    Scrounge_Object = p_Var1;
    for (; p_Var1 != (_OBJ76 *)0x0; p_Var1 = p_Var1->sibling) {
      p_Var1->flags = p_Var1->flags | 0x40;
      p_Var1->class_id = CLASS_ID_SCROUNGE;
    }
  }
  return;
}
