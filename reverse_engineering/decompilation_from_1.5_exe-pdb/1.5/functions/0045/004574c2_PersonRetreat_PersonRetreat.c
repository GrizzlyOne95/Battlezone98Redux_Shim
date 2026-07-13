/*
 * Entry: 004574c2
 * Name: PersonRetreat::PersonRetreat
 * Namespace: PersonRetreat
 * Signature: PersonRetreat * PersonRetreat(PersonRetreat * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonRetreat * __thiscall
PersonRetreat::PersonRetreat(PersonRetreat *this,Craft *param_1,GameObject *param_2)

{
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  this->field_0x142 = 1;
  return this;
}
