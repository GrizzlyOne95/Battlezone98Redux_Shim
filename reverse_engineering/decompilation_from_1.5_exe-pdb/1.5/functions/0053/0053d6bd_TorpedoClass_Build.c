/*
 * Entry: 0053d6bd
 * Name: TorpedoClass::Build
 * Namespace: TorpedoClass
 * Signature: GameObject * Build(TorpedoClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall TorpedoClass::Build(TorpedoClass *this,_OBJ76 *param_1)

{
  Torpedo *pTVar1;
  
  pTVar1 = GameObject::operator_new(0x230);
  if (pTVar1 == (Torpedo *)0x0) {
    pTVar1 = (Torpedo *)0x0;
  }
  else {
    pTVar1 = Torpedo::Torpedo(pTVar1,param_1,this);
  }
  return (GameObject *)pTVar1;
}
