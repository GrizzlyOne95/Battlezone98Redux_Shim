/*
 * Entry: 0041114d
 * Name: DemoMission::Setup
 * Namespace: DemoMission
 * Signature: void Setup(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DemoMission::Setup(DemoMission *this)

{
  (this->field17_0x54)._s_0.camera_time = -99999.0;
  (this->field16_0x40)._s_0.camera1 = false;
  (this->field16_0x40)._s_0.camera2 = false;
  (this->field20_0xcc)._s_0.angle = 3;
  (this->field16_0x40)._s_0.lost = false;
  (this->field16_0x40)._s_0.first_start = false;
  (this->field20_0xcc)._s_0.cycle_count = 0;
  (this->field16_0x40)._s_0.start_done = false;
  (this->field20_0xcc)._s_0.frame_count = 0;
  return;
}
