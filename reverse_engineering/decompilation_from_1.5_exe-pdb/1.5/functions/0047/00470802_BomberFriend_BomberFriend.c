/*
 * Entry: 00470802
 * Name: BomberFriend::BomberFriend
 * Namespace: BomberFriend
 * Signature: BomberFriend * BomberFriend(BomberFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BomberFriend * __thiscall BomberFriend::BomberFriend(BomberFriend *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
