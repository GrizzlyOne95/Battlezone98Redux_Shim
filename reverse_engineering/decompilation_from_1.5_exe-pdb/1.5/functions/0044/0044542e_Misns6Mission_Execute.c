/*
 * Entry: 0044542e
 * Name: Misns6Mission::Execute
 * Namespace: Misns6Mission
 * Signature: void Execute(Misns6Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns6Mission::Execute(Misns6Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  AiCommand AVar5;
  float fVar6;
  char *pcVar7;
  int *local_14;
  int local_c;
  
  iVar2 = GetPlayerHandle();
  if ((this->field16_0x40)._s_0.start_done == false) {
    (this->field19_0xb0)._s_0.next_target = 0;
    fVar6 = Get_Time();
    (this->field17_0x50)._s_0.aip_time = fVar6 + 120.0;
    BuildObject("avmine",2,"m1",0);
    BuildObject("avmine",2,"m2",0);
    BuildObject("avmine",2,"m3",0);
    iVar3 = GetHandle("abcafe8_i76building");
    (this->field18_0x6c)._s_0.goal = iVar3;
    iVar3 = GetHandle("avartl3_howitzer");
    (this->field18_0x6c)._s_0.art1 = iVar3;
    iVar3 = GetHandle("avartl4_howitzer");
    (this->field18_0x6c)._s_0.art2 = iVar3;
    iVar3 = GetHandle("avturr0_turrettank");
    (this->field18_0x6c)._s_0.tur1 = iVar3;
    iVar3 = GetHandle("avturr1_turrettank");
    (this->field18_0x6c)._s_0.tur2 = iVar3;
    iVar3 = GetHandle("defender1");
    (this->field18_0x6c)._s_0.tur3 = iVar3;
    iVar3 = GetHandle("defender2");
    (this->field18_0x6c)._s_0.tur4 = iVar3;
    iVar3 = GetHandle("svrecy0_recycler");
    (this->field18_0x6c)._s_0.recy = iVar3;
    iVar3 = GetHandle("absilo0_scrapsilo");
    (this->field18_0x6c)._s_0.far_silo = iVar3;
    Defend((this->field18_0x6c)._s_0.art1,1);
    Defend((this->field18_0x6c)._s_0.art2,1);
    Defend((this->field18_0x6c)._s_0.tur3,1);
    Defend((this->field18_0x6c)._s_0.tur4,1);
    Defend((this->field18_0x6c)._s_0.tur1,1);
    Defend((this->field18_0x6c)._s_0.tur2,1);
    SetScrap(1,0x14);
    fVar6 = Get_Time();
    (this->field17_0x50)._s_0.check_time = fVar6 + 10.0;
    AudioMessage("misns601.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns601.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns602.otf",DisplayInterface::colorWhite,8.0);
    (this->field16_0x40)._s_0.start_done = true;
  }
  if (((this->field16_0x40)._s_0.warning == false) &&
     (((fVar6 = GetDistance(iVar2,"m1",1), fVar6 < 250.0 ||
       (fVar6 = GetDistance(iVar2,"m2",1), fVar6 < 250.0)) ||
      (fVar6 = GetDistance(iVar2,"m3",1), fVar6 < 250.0)))) {
    AudioMessage("misns602.wav");
    (this->field16_0x40)._s_0.warning = true;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x50)._s_0.aip_time < fVar6) {
    SetAIP("misns6.aip",2);
    (this->field17_0x50)._s_0.aip_time = 99999.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x50)._s_0.check_time < fVar6) {
    local_14 = (this->field18_0x6c)._s_0.miners;
    local_c = 3;
    do {
      bVar1 = IsAlive(local_14);
      if (bVar1) {
        fVar6 = GetLastEnemyShot(*local_14);
        if ((0.0 < fVar6) && ((this->field16_0x40)._s_0.counter1 == false)) {
          (this->field16_0x40)._s_0.counter1 = true;
          iVar3 = BuildObject("bvraz",2,"counter1",0);
          iVar4 = BuildObject("bvraz",2,"counter2",0);
          Attack(iVar3,iVar2,1);
          Attack(iVar4,iVar2,1);
        }
        AVar5 = GetCurrentCommand(*local_14);
        if (AVar5 == CMD_NONE) {
          iVar3 = (this->field19_0xb0)._s_0.next_target;
          if (iVar3 == 0) {
            pcVar7 = "s1";
LAB_00445761:
            Mine(*local_14,pcVar7,1);
          }
          else {
            if (iVar3 == 1) {
              pcVar7 = "s2";
              goto LAB_00445761;
            }
            if (iVar3 == 2) {
              pcVar7 = "s3";
              goto LAB_00445761;
            }
            if (iVar3 == 3) {
              pcVar7 = "m1";
              goto LAB_00445761;
            }
            if (iVar3 == 4) {
              pcVar7 = "m2";
              goto LAB_00445761;
            }
            if (iVar3 == 5) {
              pcVar7 = "m3";
              goto LAB_00445761;
            }
          }
          (this->field19_0xb0)._s_0.next_target = (this->field19_0xb0)._s_0.next_target + 1;
          if (5 < (this->field19_0xb0)._s_0.next_target) {
            (this->field19_0xb0)._s_0.next_target = 0;
          }
        }
      }
      fVar6 = Get_Time();
      local_14 = local_14 + 1;
      local_c = local_c + -1;
      (this->field17_0x50)._s_0.check_time = fVar6 + 3.0;
    } while (local_c != 0);
  }
  if (((this->field16_0x40)._s_0.counter2 == false) &&
     (fVar6 = Get_Time(), (this->field17_0x50)._s_0.check1 < fVar6)) {
    fVar6 = GetDistance(iVar2,"counter2",0);
    if (400.0 <= fVar6) {
      fVar6 = Get_Time();
      fVar6 = fVar6 + 3.0;
    }
    else {
      BuildObject("bvtank",2,"counter2",0);
      BuildObject("bvtank",2,"counter2",0);
      BuildObject("bvturr",2,"counter2",0);
      fVar6 = (this->field17_0x50)._s_0.check1 + 300.0;
    }
    (this->field17_0x50)._s_0.check1 = fVar6;
  }
  if (((this->field16_0x40)._s_0.counter3 == false) &&
     (fVar6 = Get_Time(), (this->field17_0x50)._s_0.check2 < fVar6)) {
    fVar6 = GetDistance(iVar2,"counter3",0);
    if (400.0 <= fVar6) {
      fVar6 = Get_Time();
      fVar6 = fVar6 + 3.0;
    }
    else {
      BuildObject("bvtank",2,"counter3",0);
      BuildObject("bvtank",2,"counter3",0);
      BuildObject("bvturr",2,"counter3",0);
      fVar6 = (this->field17_0x50)._s_0.check2 + 300.0;
    }
    (this->field17_0x50)._s_0.check2 = fVar6;
  }
  if (((this->field16_0x40)._s_0.counter4 == false) &&
     (fVar6 = Get_Time(), (this->field17_0x50)._s_0.check3 < fVar6)) {
    fVar6 = GetDistance(iVar2,"counter4",0);
    if (200.0 <= fVar6) {
      fVar6 = Get_Time();
      fVar6 = fVar6 + 3.0;
    }
    else {
      BuildObject("bvtank",2,"counter4",0);
      BuildObject("bvtank",2,"counter4",0);
      BuildObject("bvturr",2,"counter4",0);
      fVar6 = Get_Time();
      fVar6 = fVar6 + 300.0;
    }
    (this->field17_0x50)._s_0.check3 = fVar6;
  }
  if (((this->field16_0x40)._s_0.counter5 == false) &&
     (fVar6 = Get_Time(), (this->field17_0x50)._s_0.check4 < fVar6)) {
    fVar6 = GetDistance(iVar2,"counter5",0);
    if (200.0 <= fVar6) {
      fVar6 = Get_Time();
      fVar6 = fVar6 + 3.0;
    }
    else {
      BuildObject("bvtank",2,"counter5",0);
      BuildObject("bvtank",2,"counter5",0);
      BuildObject("bvturr",2,"counter5",0);
      fVar6 = Get_Time();
      fVar6 = fVar6 + 300.0;
    }
    (this->field17_0x50)._s_0.check4 = fVar6;
  }
  if (((this->field16_0x40)._s_0.art_found == false) &&
     ((fVar6 = GetDistance(iVar2,(this->field18_0x6c)._s_0.art1), fVar6 < 200.0 ||
      (fVar6 = GetDistance(iVar2,(this->field18_0x6c)._s_0.art2), fVar6 < 200.0)))) {
    (this->field16_0x40)._s_0.art_found = true;
    AudioMessage("misns605.wav");
  }
  if (((this->field16_0x40)._s_0.counter_attack == false) &&
     (fVar6 = GetDistance((this->field18_0x6c)._s_0.far_silo,iVar2), fVar6 < 400.0)) {
    iVar3 = BuildObject("bvltnk",2,"counter_attack",0);
    Goto(iVar3,"counter_attack_path",1);
    iVar3 = BuildObject("bvltnk",2,"counter_attack",0);
    Goto(iVar3,"counter_attack_path",1);
    iVar3 = BuildObject("bvtank",2,"counter_attack",0);
    Goto(iVar3,"counter_attack_path",1);
    iVar3 = BuildObject("bvtank",2,"counter_attack",0);
    Goto(iVar3,"counter_attack_path",1);
    iVar3 = BuildObject("bvrckt",2,"counter_attack",0);
    Goto(iVar3,"counter_attack_path",1);
    AudioMessage("misns603.wav");
    (this->field16_0x40)._s_0.counter_attack = true;
  }
  if (((this->field16_0x40)._s_0.last_objective == false) &&
     (fVar6 = GetDistance(iVar2,(this->field18_0x6c)._s_0.goal), fVar6 < 300.0)) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns601.otf",DisplayInterface::colorGreen,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misns602.otf",DisplayInterface::colorWhite,8.0);
    iVar2 = (this->field18_0x6c)._s_0.goal;
    (this->field16_0x40)._s_0.last_objective = true;
    SetObjectiveOn(iVar2);
  }
  if ((this->field16_0x40)._s_0.won == false) {
    bVar1 = IsAlive(&(this->field18_0x6c)._s_0.goal);
    if (!bVar1) {
      iVar2 = AudioMessage("misns609.wav");
      (this->field19_0xb0)._s_0.audmsg = iVar2;
      (this->field16_0x40)._s_0.won_message = true;
      (this->field16_0x40)._s_0.won = true;
    }
    if ((this->field16_0x40)._s_0.won == false) goto LAB_00445b4a;
  }
  bVar1 = IsAudioMessageDone((this->field19_0xb0)._s_0.audmsg);
  if (bVar1) {
    pcVar7 = "misns6w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6,pcVar7);
    (this->field16_0x40)._s_0.won = false;
  }
  if ((this->field16_0x40)._s_0.won != false) {
    return;
  }
LAB_00445b4a:
  if (((this->field16_0x40)._s_0.lost == false) &&
     (bVar1 = IsAlive(&(this->field18_0x6c)._s_0.recy), !bVar1)) {
    pcVar7 = "misns6l1.des";
    (this->field16_0x40)._s_0.lost = true;
    fVar6 = Get_Time();
    FailMission(fVar6 + 2.0,pcVar7);
  }
  return;
}
