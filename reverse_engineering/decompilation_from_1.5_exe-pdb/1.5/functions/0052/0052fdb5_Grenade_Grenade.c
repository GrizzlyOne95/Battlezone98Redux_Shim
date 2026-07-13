/*
 * Entry: 0052fdb5
 * Name: Grenade::Grenade
 * Namespace: Grenade
 * Signature: Grenade * Grenade(Grenade * this, _OBJ76 * param_1, GrenadeClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Grenade * __thiscall Grenade::Grenade(Grenade *this,_OBJ76 *param_1,GrenadeClass *param_2)

{
  Rocket::Rocket((Rocket *)this,param_1,(RocketClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
