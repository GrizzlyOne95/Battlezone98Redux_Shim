/*
 * Entry: 00529cb2
 * Name: AnchorRocketClass::Build
 * Namespace: AnchorRocketClass
 * Signature: Ordnance * Build(AnchorRocketClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall AnchorRocketClass::Build(AnchorRocketClass *this,_OBJ76 *param_1)

{
  AnchorRocket *pAVar1;
  
  pAVar1 = operator_new(0x130);
  if (pAVar1 == (AnchorRocket *)0x0) {
    pAVar1 = (AnchorRocket *)0x0;
  }
  else {
    pAVar1 = AnchorRocket::AnchorRocket(pAVar1,param_1,this);
  }
  return (Ordnance *)pAVar1;
}
