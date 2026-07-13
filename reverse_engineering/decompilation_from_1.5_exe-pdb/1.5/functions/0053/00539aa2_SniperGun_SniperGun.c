/*
 * Entry: 00539aa2
 * Name: SniperGun::SniperGun
 * Namespace: SniperGun
 * Signature: SniperGun * SniperGun(SniperGun * this, _OBJ76 * param_1, SniperGunClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperGun * __thiscall SniperGun::SniperGun(SniperGun *this,_OBJ76 *param_1,SniperGunClass *param_2)

{
  Cannon::Cannon((Cannon *)this,param_1,(CannonClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
