/*
 * Entry: 004572bb
 * Name: PersonEnemy::PersonEnemy
 * Namespace: PersonEnemy
 * Signature: PersonEnemy * PersonEnemy(PersonEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonEnemy * __thiscall PersonEnemy::PersonEnemy(PersonEnemy *this)

{
  PersonProcess::PersonProcess((PersonProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
