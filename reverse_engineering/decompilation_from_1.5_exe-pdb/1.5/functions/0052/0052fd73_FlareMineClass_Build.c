/*
 * Entry: 0052fd73
 * Name: FlareMineClass::Build
 * Namespace: FlareMineClass
 * Signature: GameObject * Build(FlareMineClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall FlareMineClass::Build(FlareMineClass *this,_OBJ76 *param_1)

{
  FlareMine *pFVar1;
  
  pFVar1 = GameObject::operator_new(0x240);
  if (pFVar1 == (FlareMine *)0x0) {
    pFVar1 = (FlareMine *)0x0;
  }
  else {
    pFVar1 = FlareMine::FlareMine(pFVar1,param_1,this);
  }
  return (GameObject *)pFVar1;
}
