/*
 * Entry: 00486b0b
 * Name: Craft::Init
 * Namespace: Craft
 * Signature: Craft * Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft * __cdecl Craft::Init(_OBJ76 *param_1)

{
  GameObjectClass *pGVar1;
  Craft *pCVar2;
  
  pGVar1 = GameObjectClass::Find(param_1->id);
  pCVar2 = (Craft *)(**(code **)(pGVar1->_padding_ + 4))(param_1);
  pCVar2->vhcl->subclass = pCVar2;
  (**(code **)(pCVar2->_padding_ + 4))(*(ushort *)((int)&param_1->flags + 2) & 0xf);
  return pCVar2;
}
