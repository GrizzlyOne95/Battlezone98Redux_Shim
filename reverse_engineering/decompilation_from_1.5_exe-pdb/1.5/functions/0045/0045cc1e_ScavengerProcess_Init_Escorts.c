/*
 * Entry: 0045cc1e
 * Name: ScavengerProcess::Init_Escorts
 * Namespace: ScavengerProcess
 * Signature: void Init_Escorts(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::Init_Escorts(ScavengerProcess *this)

{
  tag_c_linked_list *ptVar1;
  Escort_Goal *pEVar2;
  
  ptVar1 = C_Linked_List_New();
  this->my_escorts = ptVar1;
  pEVar2 = ScheduleGlue_Create_Escort_Goal(this,this->team,(Craft *)this->craft);
  this->escort_goal = pEVar2;
  ScheduleGlue_Request_Escort_Goal(pEVar2,this->team);
  return;
}
