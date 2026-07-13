/*
 * Entry: 005326c0
 * Name: ObjectLobber::Control
 * Namespace: ObjectLobber
 * Signature: void Control(ObjectLobber * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ObjectLobber::Control(ObjectLobber *this,float param_1)

{
  VECTOR_3D *pVVar1;
  
  Weapon::Control((Weapon *)this,param_1);
  if (this->carrier == GameObject::userObject) {
    pVVar1 = reticle.groundPos;
    if (reticle.selectObj != (GameObject *)0x0) {
      pVVar1 = (VECTOR_3D *)(**(code **)((reticle.selectObj)->_padding_ + 0xc))();
    }
    this->target = pVVar1;
  }
  return;
}
