/*
 * Entry: 00532334
 * Name: MissileClass::Build
 * Namespace: MissileClass
 * Signature: Ordnance * Build(MissileClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall MissileClass::Build(MissileClass *this,_OBJ76 *param_1)

{
  Missile *pMVar1;
  
  pMVar1 = operator_new(0xf0);
  if (pMVar1 == (Missile *)0x0) {
    pMVar1 = (Missile *)0x0;
  }
  else {
    pMVar1 = Missile::Missile(pMVar1,param_1,this);
  }
  return (Ordnance *)pMVar1;
}
