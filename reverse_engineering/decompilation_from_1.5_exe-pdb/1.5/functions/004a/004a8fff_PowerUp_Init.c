/*
 * Entry: 004a8fff
 * Name: PowerUp::Init
 * Namespace: PowerUp
 * Signature: PowerUp * Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerUp * __cdecl PowerUp::Init(_OBJ76 *param_1)

{
  PowerUpClass *pPVar1;
  PowerUp *pPVar2;
  
  pPVar1 = (PowerUpClass *)GameObjectClass::Find(param_1->id);
  if (pPVar1 == (PowerUpClass *)0x0) {
    pPVar1 = &powerUpClass;
  }
  pPVar2 = (PowerUp *)(**(code **)(pPVar1->_padding_ + 4))(param_1);
  pPVar2->vhcl->subclass = pPVar2;
  (**(code **)(pPVar2->_padding_ + 4))(*(ushort *)((int)&param_1->flags + 2) & 0xf);
  return pPVar2;
}
