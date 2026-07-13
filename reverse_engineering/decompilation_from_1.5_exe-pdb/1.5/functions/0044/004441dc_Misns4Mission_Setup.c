/*
 * Entry: 004441dc
 * Name: Misns4Mission::Setup
 * Namespace: Misns4Mission
 * Signature: void Setup(Misns4Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns4Mission::Setup(Misns4Mission *this)

{
  bool *pbVar1;
  Misns4Mission_u_124 *pMVar2;
  
  (this->field17_0x60)._s_0.wakeup_time = 99999.0;
  (this->field17_0x60)._s_0.raider_time = 99999.0;
  (this->field17_0x60)._s_0.convoy_time = 99999.0;
  (this->field17_0x60)._s_0.attack_time = 99999.0;
  (this->field17_0x60)._s_0.counter_time = 99999.0;
  (this->field16_0x40)._s_0.counter = false;
  (this->field16_0x40)._s_0.warning = false;
  (this->field16_0x40)._s_0.first_bridge = false;
  (this->field16_0x40)._s_0.first = false;
  (this->field16_0x40)._s_0.start_done = false;
  (this->field16_0x40)._s_0.won = false;
  (this->field16_0x40)._s_0.lost = false;
  (this->field16_0x40)._s_0.north_bridge = false;
  (this->field16_0x40)._s_0.bridge_clear = false;
  (this->field19_0xd4)._s_0.convoy_count = 0;
  (this->field19_0xd4)._s_0.convoy_dead = 0;
  (this->field19_0xd4)._s_0.convoy_total = 5;
  (this->field18_0x7c)._s_0.counter1 = 0;
  (this->field18_0x7c)._s_0.counter2 = 0;
  (this->field18_0x7c)._s_0.counter3 = 0;
  (this->field18_0x7c)._s_0.counter4 = 0;
  (this->field19_0xd4)._s_0.win_count = 0;
  pbVar1 = (this->field16_0x40)._s_0.safe;
  pMVar2 = &this->field18_0x7c;
  do {
    pbVar1[-10] = true;
    *pbVar1 = false;
    (pMVar2->_s_0).convoy_handle[0] = 0;
    pMVar2 = (Misns4Mission_u_124 *)((int)pMVar2 + 4);
    pbVar1 = pbVar1 + 1;
  } while ((int)(pbVar1 + (-0x53 - (int)this)) < (this->field19_0xd4)._s_0.convoy_total);
  return;
}
