/*
 * Entry: 0052a18f
 * Name: BeamClass::Build
 * Namespace: BeamClass
 * Signature: Ordnance * Build(BeamClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall BeamClass::Build(BeamClass *this,_OBJ76 *param_1)

{
  Beam *pBVar1;
  
  pBVar1 = operator_new(0x100);
  if (pBVar1 == (Beam *)0x0) {
    pBVar1 = (Beam *)0x0;
  }
  else {
    pBVar1 = Beam::Beam(pBVar1,param_1,this);
  }
  return (Ordnance *)pBVar1;
}
