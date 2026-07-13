/*
 * Entry: 004e9ee3
 * Name: Set_User_Entity
 * Namespace: Global
 * Signature: void Set_User_Entity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_User_Entity(tagENTITY *param_1)

{
  if (user_entity_ptr != (tagENTITY *)0x0) {
    obj_clear_flag(user_entity_ptr->obj76,0x10);
  }
  Switch_View_Camera_Owner(user_entity_ptr,param_1);
  user_entity_ptr = param_1;
  if (param_1 != (tagENTITY *)0x0) {
    obj_set_flag(param_1->obj76,0x10);
  }
  return;
}
