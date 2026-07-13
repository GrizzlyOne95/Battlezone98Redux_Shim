/*
 * Entry: 004132c3
 * Name: GotoGeyser::GotoGeyser
 * Namespace: GotoGeyser
 * Signature: GotoGeyser * GotoGeyser(GotoGeyser * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoGeyser * __thiscall GotoGeyser::GotoGeyser(GotoGeyser *this,Craft *param_1,GameObject *param_2)

{
  int iVar1;
  
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  this->_padding_ = (int)&_vftable_;
  Say(param_1,REPAIR_MSG,0);
  *(undefined1 *)((int)&this->_padding_ + 2) = 1;
  this->blocked = false;
  iVar1 = GameObject::GetHandle(param_2);
  this->oneGeyser = iVar1;
  return this;
}
