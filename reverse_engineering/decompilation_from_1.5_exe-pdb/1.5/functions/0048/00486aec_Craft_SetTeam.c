/*
 * Entry: 00486aec
 * Name: Craft_SetTeam
 * Namespace: Global
 * Signature: void Craft_SetTeam(_OBJ76 * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Craft_SetTeam(_OBJ76 *param_1,int param_2)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  (**(code **)(*(int *)((int)pvVar1 + 0x20) + 8))(param_2);
  return;
}
