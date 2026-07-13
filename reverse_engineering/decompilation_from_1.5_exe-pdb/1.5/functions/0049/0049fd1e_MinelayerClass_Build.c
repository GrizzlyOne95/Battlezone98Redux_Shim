/*
 * Entry: 0049fd1e
 * Name: MinelayerClass::Build
 * Namespace: MinelayerClass
 * Signature: GameObject * Build(MinelayerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall MinelayerClass::Build(MinelayerClass *this,_OBJ76 *param_1)

{
  Minelayer *pMVar1;
  
  pMVar1 = GameObject::operator_new(0x2d0);
  if (pMVar1 == (Minelayer *)0x0) {
    pMVar1 = (Minelayer *)0x0;
  }
  else {
    pMVar1 = Minelayer::Minelayer(pMVar1,param_1,this);
  }
  return (GameObject *)pMVar1;
}
