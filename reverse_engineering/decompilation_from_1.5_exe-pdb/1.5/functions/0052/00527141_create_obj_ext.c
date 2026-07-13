/*
 * Entry: 00527141
 * Name: create_obj_ext
 * Namespace: Global
 * Signature: _OBJ76 * create_obj_ext(_OBJ76 * param_1, long64 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl create_obj_ext(_OBJ76 *param_1,long64 *param_2)

{
  _OBJ76 *p_Var1;
  
  p_Var1 = create_obj(param_1,"world2");
  if ((p_Var1 != (_OBJ76 *)0x0) && (param_2 != (long64 *)0x0)) {
    *(int *)&p_Var1->id = (int)*param_2;
    *(undefined4 *)((int)&p_Var1->id + 4) = *(undefined4 *)((int)param_2 + 4);
  }
  return p_Var1;
}
