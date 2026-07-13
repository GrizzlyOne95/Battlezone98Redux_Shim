/*
 * Entry: 0053237c
 * Name: Mortar::Mortar
 * Namespace: Mortar
 * Signature: Mortar * Mortar(Mortar * this, _OBJ76 * param_1, MortarClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Mortar * __thiscall Mortar::Mortar(Mortar *this,_OBJ76 *param_1,MortarClass *param_2)

{
  Cannon::Cannon((Cannon *)this,param_1,(CannonClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
