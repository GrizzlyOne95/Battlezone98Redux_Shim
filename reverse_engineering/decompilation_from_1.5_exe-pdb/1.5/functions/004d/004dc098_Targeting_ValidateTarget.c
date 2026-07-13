/*
 * Entry: 004dc098
 * Name: Targeting::ValidateTarget
 * Namespace: Targeting
 * Signature: GameObject * ValidateTarget(Targeting * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Targeting::ValidateTarget(Targeting *this,GameObject *param_1)

{
  float fVar1;
  GameObject *pGVar2;
  bool bVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D *pVVar5;
  float fVar6;
  
  pGVar2 = GameObject::userObject;
  if ((param_1 != (GameObject *)0x0) && ((param_1->obj->flags & 0x201) == 0)) {
    bVar3 = GameObject::FriendP(GameObject::userObject,param_1);
    if (bVar3) {
      return param_1;
    }
    fVar1 = pGVar2->scanner->range;
    pVVar4 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
    pVVar5 = (VECTOR_3D *)(**(code **)(pGVar2->_padding_ + 0xc))();
    fVar6 = Dist3D_Squared(*pVVar5,*pVVar4);
    if (fVar6 <= fVar1 * fVar1) {
      return param_1;
    }
  }
  return (GameObject *)0x0;
}
