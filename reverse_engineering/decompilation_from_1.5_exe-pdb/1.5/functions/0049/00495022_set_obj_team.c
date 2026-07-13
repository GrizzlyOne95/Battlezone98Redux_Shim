/*
 * Entry: 00495022
 * Name: set_obj_team
 * Namespace: Global
 * Signature: void set_obj_team(_OBJ76 * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_team(_OBJ76 *param_1,int param_2)

{
  param_1->flags = param_2 << 0x10 | param_1->flags & 0xfff0ffff;
  return;
}
