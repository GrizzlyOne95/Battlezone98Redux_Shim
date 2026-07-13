/*
 * Entry: 0041102a
 * Name: DemoMission::~DemoMission
 * Namespace: DemoMission
 * Signature: void ~DemoMission(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DemoMission::~DemoMission(DemoMission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
