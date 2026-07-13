/*
 * Entry: 004572a4
 * Name: PersonFriend::PersonFriend
 * Namespace: PersonFriend
 * Signature: PersonFriend * PersonFriend(PersonFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonFriend * __thiscall PersonFriend::PersonFriend(PersonFriend *this)

{
  PersonProcess::PersonProcess((PersonProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
