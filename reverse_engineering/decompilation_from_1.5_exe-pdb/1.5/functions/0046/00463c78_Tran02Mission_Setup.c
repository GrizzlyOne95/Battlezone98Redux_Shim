/*
 * Entry: 00463c78
 * Name: Tran02Mission::Setup
 * Namespace: Tran02Mission
 * Signature: void Setup(Tran02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran02Mission::Setup(Tran02Mission *this)

{
  int iVar1;
  
  (this->field16_0x40)._s_0.lost = false;
  (this->field16_0x40)._s_0.start_done = false;
  (this->field16_0x40)._s_0.first_selection = false;
  (this->field16_0x40)._s_0.second_selection = false;
  (this->field16_0x40)._s_0.third_selection = false;
  (this->field16_0x40)._s_0.fourth_selection = false;
  (this->field16_0x40)._s_0.fifth_selection = false;
  (this->field16_0x40)._s_0.first_objective = false;
  (this->field16_0x40)._s_0.second_objective = false;
  (this->field16_0x40)._s_0.third_objecitve = false;
  (this->field16_0x40)._s_0.thirda_selection = false;
  (this->field16_0x40)._s_0.start_path1 = false;
  (this->field16_0x40)._s_0.start_path2 = false;
  (this->field16_0x40)._s_0.start_path3 = false;
  (this->field16_0x40)._s_0.start_path4 = false;
  (this->field16_0x40)._s_0.jump_start = false;
  (this->field16_0x40)._s_0.combat_start = false;
  (this->field16_0x40)._s_0.combat_start2 = false;
  (this->field16_0x40)._s_0.end_message = false;
  (this->field16_0x40)._s_0.go_reminder = false;
  (this->field16_0x40)._s_0.hint1 = false;
  (this->field16_0x40)._s_0.hint2 = false;
  iVar1 = GetHandle("avturr-1_turrettank");
  (this->field18_0x64)._s_0.turret = iVar1;
  iVar1 = GetHandle("nparr-1_i76building");
  (this->field18_0x64)._s_0.pointer = iVar1;
  iVar1 = GetHandle("avhaul-1_tug");
  (this->field18_0x64)._s_0.haul1 = iVar1;
  iVar1 = GetHandle("avhaul19_tug");
  (this->field17_0x58)._s_0.hint_delay = 99999.0;
  (this->field20_0x8c)._s_0.num_reps = 0;
  (this->field17_0x58)._s_0.repeat_time = 99999.0;
  (this->field20_0x8c)._s_0.message = 0;
  (this->field18_0x64)._s_0.haul2 = iVar1;
  return;
}
