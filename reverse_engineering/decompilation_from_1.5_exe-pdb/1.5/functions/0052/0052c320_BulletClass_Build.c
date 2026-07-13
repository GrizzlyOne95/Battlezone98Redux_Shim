/*
 * Entry: 0052c320
 * Name: BulletClass::Build
 * Namespace: BulletClass
 * Signature: Ordnance * Build(BulletClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall BulletClass::Build(BulletClass *this,_OBJ76 *param_1)

{
  Bullet *pBVar1;
  
  pBVar1 = operator_new(0xe0);
  if (pBVar1 == (Bullet *)0x0) {
    pBVar1 = (Bullet *)0x0;
  }
  else {
    pBVar1 = Bullet::Bullet(pBVar1,param_1,this);
  }
  return (Ordnance *)pBVar1;
}
