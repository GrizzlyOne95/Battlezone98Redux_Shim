/*
 * Entry: 0041a4e4
 * Name: GameObjectClass::Find
 * Namespace: GameObjectClass
 * Signature: GameObjectClass * Find(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __cdecl GameObjectClass::Find(char *param_1)

{
  GameObjectClass *pGVar1;
  long64 lVar2;
  
  lVar2 = StringToPrjID(param_1);
  pGVar1 = Find(lVar2);
  return pGVar1;
}
