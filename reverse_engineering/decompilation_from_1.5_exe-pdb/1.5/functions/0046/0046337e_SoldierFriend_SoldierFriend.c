/*
 * Entry: 0046337e
 * Name: SoldierFriend::SoldierFriend
 * Namespace: SoldierFriend
 * Signature: SoldierFriend * SoldierFriend(SoldierFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierFriend * __thiscall SoldierFriend::SoldierFriend(SoldierFriend *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
