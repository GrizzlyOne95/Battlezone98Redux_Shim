/*
 * Entry: 005372c3
 * Name: QuakeBlastClass::Build
 * Namespace: QuakeBlastClass
 * Signature: Explosion * Build(QuakeBlastClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall QuakeBlastClass::Build(QuakeBlastClass *this,_OBJ76 *param_1)

{
  QuakeBlast *pQVar1;
  
  pQVar1 = operator_new(0x40);
  if (pQVar1 == (QuakeBlast *)0x0) {
    pQVar1 = (QuakeBlast *)0x0;
  }
  else {
    pQVar1 = QuakeBlast::QuakeBlast(pQVar1,param_1,this);
  }
  return (Explosion *)pQVar1;
}
