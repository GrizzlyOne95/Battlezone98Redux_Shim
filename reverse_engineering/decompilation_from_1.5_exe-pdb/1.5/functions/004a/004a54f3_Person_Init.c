/*
 * Entry: 004a54f3
 * Name: Person::Init
 * Namespace: Person
 * Signature: Person * Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Person * __cdecl Person::Init(_OBJ76 *param_1)

{
  GameObjectClass *pGVar1;
  Person *pPVar2;
  
  pGVar1 = GameObjectClass::Find(param_1->id);
  pPVar2 = (Person *)(**(code **)(pGVar1->_padding_ + 4))(param_1);
  (**(code **)(pPVar2->_padding_ + 4))(*(ushort *)((int)&param_1->flags + 2) & 0xf);
  return pPVar2;
}
