/*
 * Entry: 00411018
 * Name: DemoMission::DemoMission
 * Namespace: DemoMission
 * Signature: DemoMission * DemoMission(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DemoMission * __thiscall DemoMission::DemoMission(DemoMission *this)

{
  AiMission::AiMission((AiMission *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
