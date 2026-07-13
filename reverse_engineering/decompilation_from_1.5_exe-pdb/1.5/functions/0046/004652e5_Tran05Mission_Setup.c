/*
 * Entry: 004652e5
 * Name: Tran05Mission::Setup
 * Namespace: Tran05Mission
 * Signature: void Setup(Tran05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran05Mission::Setup(Tran05Mission *this)

{
  (this->field17_0x5c)._s_0.repeat_time = 0.0;
  (this->field16_0x40)._s_0.start_done = false;
  (this->field17_0x5c)._s_0.wave_timer = 0.0;
  (this->field16_0x40)._s_0.camera1 = false;
  (this->field16_0x40)._s_0.camera2 = false;
  (this->field17_0x5c)._s_0.last_wave_time = 99999.0;
  (this->field16_0x40)._s_0.camera3 = false;
  (this->field17_0x5c)._s_0.dramatic_pause = 99999.0;
  (this->field16_0x40)._s_0.message1 = false;
  (this->field17_0x5c)._s_0.NextSecond = 99999.0;
  (this->field16_0x40)._s_0.message2 = false;
  (this->field16_0x40)._s_0.message3 = false;
  (this->field16_0x40)._s_0.message4 = false;
  (this->field16_0x40)._s_0.message5 = false;
  (this->field16_0x40)._s_0.message6 = false;
  (this->field16_0x40)._s_0.message7 = false;
  (this->field16_0x40)._s_0.message8 = false;
  (this->field16_0x40)._s_0.message9 = false;
  (this->field16_0x40)._s_0.message10 = false;
  (this->field16_0x40)._s_0.message11 = false;
  (this->field16_0x40)._s_0.message12 = false;
  (this->field16_0x40)._s_0.message13 = false;
  (this->field16_0x40)._s_0.message14 = false;
  (this->field16_0x40)._s_0.message15 = false;
  (this->field16_0x40)._s_0.mission_won = false;
  (this->field16_0x40)._s_0.mission_lost = false;
  (this->field16_0x40)._s_0.found = false;
  (this->field16_0x40)._s_0.found2 = false;
  (this->field16_0x40)._s_0.patrol1 = false;
  (this->field20_0xd8)._s_0.num_reps = 0;
  (this->field20_0xd8)._s_0.audmsg = 0;
  (this->field18_0x7c)._s_0.bscav = 0;
  (this->field18_0x7c)._s_0.scav2 = 0;
  return;
}
