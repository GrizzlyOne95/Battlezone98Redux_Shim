/*
 * Entry: 00444a24
 * Name: Misns5Mission::Setup
 * Namespace: Misns5Mission
 * Signature: void Setup(Misns5Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns5Mission::Setup(Misns5Mission *this)

{
  (this->field17_0x50)._s_0.camera_time = 99999.0;
  (this->field18_0x68)._s_0.h1 = 0;
  (this->field17_0x50)._s_0.add_defender = 99999.0;
  (this->field18_0x68)._s_0.h2 = 0;
  (this->field17_0x50)._s_0.apc_wave = 99999.0;
  (this->field16_0x40)._s_0.third_attack = false;
  (this->field17_0x50)._s_0.wave = 99999.0;
  (this->field16_0x40)._s_0.fourth_attack = false;
  (this->field17_0x50)._s_0.chaff = 99999.0;
  (this->field16_0x40)._s_0.art_dead = false;
  (this->field16_0x40)._s_0.apc_here = false;
  (this->field18_0x68)._s_0.killme = 0;
  (this->field16_0x40)._s_0.camera1 = false;
  (this->field19_0xa8)._s_0.wave_count = 0;
  (this->field16_0x40)._s_0.start_done = false;
  (this->field16_0x40)._s_0.second_message = false;
  (this->field16_0x40)._s_0.third_message = false;
  (this->field16_0x40)._s_0.defender = false;
  (this->field16_0x40)._s_0.com_dead = false;
  (this->field16_0x40)._s_0.last_phase = false;
  (this->field16_0x40)._s_0.won = false;
  (this->field16_0x40)._s_0.lost = false;
  return;
}
