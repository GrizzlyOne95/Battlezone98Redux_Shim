/*
 * Entry: 0041580d
 * Name: Inst01Event::Inst01Event
 * Namespace: Inst01Event
 * Signature: Inst01Event * Inst01Event(Inst01Event * this, AiMission * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Inst01Event * __thiscall Inst01Event::Inst01Event(Inst01Event *this,AiMission *param_1)

{
  AiProcess::AiProcess((AiProcess *)this,param_1,(GameObject *)0x0);
  this->_padding_ = (int)&_vftable_;
  *(undefined1 *)&this->_padding_ = 1;
  this->game_start = false;
  this->camera_start1 = false;
  this->camera_start2 = false;
  return this;
}
