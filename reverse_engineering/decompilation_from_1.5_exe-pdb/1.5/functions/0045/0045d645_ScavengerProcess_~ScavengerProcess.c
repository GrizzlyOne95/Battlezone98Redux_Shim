/*
 * Entry: 0045d645
 * Name: ScavengerProcess::~ScavengerProcess
 * Namespace: ScavengerProcess
 * Signature: void ~ScavengerProcess(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::~ScavengerProcess(ScavengerProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  C_Linked_List_Delete(this->my_escorts);
  if (this->escort_goal != (Escort_Goal *)0x0) {
    this->escort_goal->_padding_ = 1;
    ScheduleGlue_Retract_Escort_Goal_Request(this->escort_goal,this->team);
  }
  CleanState(this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
