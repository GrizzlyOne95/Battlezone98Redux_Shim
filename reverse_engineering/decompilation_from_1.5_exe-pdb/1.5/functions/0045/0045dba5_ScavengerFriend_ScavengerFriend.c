/*
 * Entry: 0045dba5
 * Name: ScavengerFriend::ScavengerFriend
 * Namespace: ScavengerFriend
 * Signature: ScavengerFriend * ScavengerFriend(ScavengerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerFriend * __thiscall ScavengerFriend::ScavengerFriend(ScavengerFriend *this)

{
  ScavengerProcess::ScavengerProcess((ScavengerProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
