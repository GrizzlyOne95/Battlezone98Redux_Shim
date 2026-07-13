/*
 * Entry: 004ea4dc
 * Name: Obj_Set_Texture_Quality
 * Namespace: Global
 * Signature: void Obj_Set_Texture_Quality(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Obj_Set_Texture_Quality(_OBJ76 *param_1,long param_2)

{
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    param_1->render_type_override = param_2;
    Obj_Set_Texture_Quality(param_1->child,param_2);
  }
  return;
}
