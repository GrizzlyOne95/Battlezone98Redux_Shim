/*
 * Entry: 0045dbb7
 * Name: ScavengerFriend::~ScavengerFriend
 * Namespace: ScavengerFriend
 * Signature: void ~ScavengerFriend(ScavengerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerFriend::~ScavengerFriend(ScavengerFriend *this)

{
  *(undefined ***)this = &ScavengerProcess::_vftable_;
  C_Linked_List_Delete(*(tag_c_linked_list **)&this->field_0x50);
  if (*(int *)&this->field_0x4c != 0) {
    *(undefined4 *)(*(int *)&this->field_0x4c + 0x30) = 1;
    ScheduleGlue_Retract_Escort_Goal_Request
              (*(Escort_Goal **)&this->field_0x4c,*(int *)&this->field_0x48);
  }
  ScavengerProcess::CleanState((ScavengerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
