/*
 * Entry: 0053a52e
 * Name: SprayBomb::SprayBomb
 * Namespace: SprayBomb
 * Signature: SprayBomb * SprayBomb(SprayBomb * this, _OBJ76 * param_1, SprayBombClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBomb * __thiscall SprayBomb::SprayBomb(SprayBomb *this,_OBJ76 *param_1,SprayBombClass *param_2)

{
  Grenade::Grenade((Grenade *)this,param_1,(GrenadeClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
