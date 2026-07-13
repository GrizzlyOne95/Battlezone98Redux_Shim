/*
 * Entry: 00485d97
 * Name: Craft_GetClass
 * Namespace: Global
 * Signature: int Craft_GetClass(long64 * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Craft_GetClass(long64 *param_1,int param_2)

{
  GameObjectClass *pGVar1;
  
  pGVar1 = GameObjectClass::Find(*param_1);
  return pGVar1->class_id;
}
