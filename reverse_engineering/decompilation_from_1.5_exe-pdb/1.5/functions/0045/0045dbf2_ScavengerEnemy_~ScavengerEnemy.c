/*
 * Entry: 0045dbf2
 * Name: ScavengerEnemy::~ScavengerEnemy
 * Namespace: ScavengerEnemy
 * Signature: void ~ScavengerEnemy(ScavengerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerEnemy::~ScavengerEnemy(ScavengerEnemy *this)

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
