/*
 * Entry: 00406a12
 * Name: GetDamageRatio
 * Namespace: Global
 * Signature: float GetDamageRatio(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetDamageRatio(GameObject *param_1)

{
  GameObject *pGVar1;
  Carrier *this;
  _OBJ76 *p_Var2;
  int iVar3;
  Weapon *pWVar4;
  
  p_Var2 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
  if (((p_Var2->class_id == CLASS_ID_PERSON) || (iVar3 = IsCraft(p_Var2), iVar3 != 0)) &&
     (this = param_1->carrier, this != (Carrier *)0x0)) {
    param_1 = (GameObject *)0xf149f2ca;
    iVar3 = 0;
    do {
      pWVar4 = Carrier::GetWeapon(this,iVar3);
      if (((pWVar4 != (Weapon *)0x0) && (pWVar4->ordnanceClass != (OrdnanceClass *)0x0)) &&
         (pGVar1 = (GameObject *)pWVar4->ordnanceClass->damageValue, (float)param_1 < (float)pGVar1)
         ) {
        param_1 = pGVar1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
  }
  else {
    param_1 = (GameObject *)0x0;
  }
  return (float)param_1;
}
