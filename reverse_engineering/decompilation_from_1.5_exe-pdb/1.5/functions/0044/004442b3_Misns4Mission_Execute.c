/*
 * Entry: 004442b3
 * Name: Misns4Mission::Execute
 * Namespace: Misns4Mission
 * Signature: void Execute(Misns4Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns4Mission::Execute(Misns4Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  Misns4Mission_u_124 *pMVar5;
  float fVar6;
  char *pcVar7;
  
  iVar3 = GetPlayerHandle();
  if ((this->field16_0x40)._s_0.start_done == false) {
    (this->field16_0x40)._s_0.start_done = true;
    fVar6 = Get_Time();
    (this->field17_0x60)._s_0.convoy_time = fVar6 + 420.0;
    fVar6 = Get_Time();
    (this->field17_0x60)._s_0.wakeup_time = fVar6 + 30.0;
    BuildObject("avartl",2,"spawn2",0);
    iVar4 = BuildObject("spcamr",1,"camerapt",0);
    (this->field18_0x7c)._s_0.cam1 = iVar4;
    fVar6 = Get_Time();
    (this->field17_0x60)._s_0.raider_time = fVar6 + 30.0;
    fVar6 = Get_Time();
    (this->field17_0x60)._s_0.army_time = fVar6 + 100.0;
    AddScrap(1,0x32);
    SetPilot(1,0x1e);
    SetPilot(2,0x1e);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misns4.otf",DisplayInterface::colorWhite,8.0);
    AudioMessage("misns401.wav");
    StartCockpitTimer(0x1a4,300,0);
    SetObjectiveName((this->field18_0x7c)._s_0.cam1,"Bridge");
    BuildObject("abtowe",2,"tower1",0);
    BuildObject("abtowe",2,"tower2",0);
    BuildObject("ablpow",2,"power1",0);
    BuildObject("ablpow",2,"power2",0);
    BuildObject("svcnst",1,"svcnst",0);
  }
  fVar6 = Get_Time();
  if ((this->field17_0x60)._s_0.wakeup_time < fVar6) {
    iVar4 = BuildObject("avfigh",2,"spawn4",0);
    Goto(iVar4,"wakeup",1);
    (this->field17_0x60)._s_0.wakeup_time = 99999.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x60)._s_0.convoy_time < fVar6) {
    if ((this->field16_0x40)._s_0.first == false) {
      AudioMessage("misns402.wav");
      cockpitTimer.active = false;
      CockpitTimer::HideTimer(&cockpitTimer);
      (this->field16_0x40)._s_0.first = true;
    }
    iVar4 = BuildObject("svhaul",1,"spawn1",0);
    SetObjectiveOn(iVar4);
    if ((this->field19_0xd4)._s_0.convoy_count < (this->field19_0xd4)._s_0.convoy_total) {
      fVar6 = Get_Time();
      fVar6 = fVar6 + 45.0;
    }
    else {
      fVar6 = 99999.0;
    }
    (this->field17_0x60)._s_0.convoy_time = fVar6;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x60)._s_0.raider_time < fVar6) {
    BuildObject("avfigh",2,"spawn4",0);
    BuildObject("avfigh",2,"spawn4",0);
    (this->field17_0x60)._s_0.raider_time = 99999.0;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x60)._s_0.army_time < fVar6) {
    iVar4 = BuildObject("avtank",2,"sbridge",0);
    (this->field18_0x7c)._s_0.t1 = iVar4;
    iVar4 = BuildObject("avtank",2,"sbridge",0);
    (this->field18_0x7c)._s_0.t2 = iVar4;
    iVar4 = BuildObject("avhraz",2,"sbridge",0);
    (this->field17_0x60)._s_0.army_time = 99999.0;
    (this->field18_0x7c)._s_0.b1 = iVar4;
  }
  if ((this->field16_0x40)._s_0.north_bridge == false) {
    fVar6 = GetDistance(iVar3,"sbridge",0);
    if (fVar6 < 200.0) {
      (this->field16_0x40)._s_0.north_bridge = true;
      BuildObject("avltnk",2,"spawn3",0);
      BuildObject("avturr",2,"spawn3",0);
      BuildObject("avscav",2,"spawn3",0);
      BuildObject("avrecy",2,"spawn3",0);
    }
  }
  if (((this->field16_0x40)._s_0.bridge_clear == false) &&
     ((this->field16_0x40)._s_0.north_bridge != false)) {
    bVar2 = IsAlive(&(this->field18_0x7c)._s_0.t1);
    if (!bVar2) {
      bVar2 = IsAlive(&(this->field18_0x7c)._s_0.t2);
      if (!bVar2) {
        bVar2 = IsAlive(&(this->field18_0x7c)._s_0.b1);
        if (!bVar2) {
          AudioMessage("misns405.wav");
          (this->field16_0x40)._s_0.bridge_clear = true;
          SetAIP("misns4.aip",2);
          fVar6 = Get_Time();
          (this->field17_0x60)._s_0.counter_time = fVar6 + 150.0;
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.warning == false) {
    fVar6 = GetDistance(iVar3,"warn1",0);
    if (fVar6 < 200.0) {
      AudioMessage("misns409.wav");
      (this->field16_0x40)._s_0.warning = true;
    }
  }
  piVar1 = (this->field18_0x7c)._s_0.convoy_handle + 2;
  bVar2 = IsAlive(piVar1);
  if ((bVar2) && ((this->field16_0x40)._s_0.counter == false)) {
    fVar6 = Get_Time();
    if (fVar6 <= (this->field17_0x60)._s_0.counter_time) {
      fVar6 = GetDistance(*piVar1,"warn1",0);
      if (200.0 <= fVar6) goto LAB_0044471f;
    }
    iVar3 = BuildObject("avrckt",2,"counter",0);
    (this->field18_0x7c)._s_0.counter1 = iVar3;
    iVar3 = BuildObject("avrckt",2,"counter",0);
    (this->field18_0x7c)._s_0.counter2 = iVar3;
    iVar3 = BuildObject("avrckt",2,"counter",0);
    (this->field18_0x7c)._s_0.counter3 = iVar3;
    iVar3 = BuildObject("avrckt",2,"counter",0);
    (this->field18_0x7c)._s_0.counter4 = iVar3;
    Goto((this->field18_0x7c)._s_0.counter1,"sbridge",1);
    Goto((this->field18_0x7c)._s_0.counter2,"sbridge",1);
    Goto((this->field18_0x7c)._s_0.counter3,"sbridge",1);
    Goto((this->field18_0x7c)._s_0.counter4,"sbridge",1);
    (this->field17_0x60)._s_0.counter_time = 99999.0;
    (this->field16_0x40)._s_0.counter = true;
  }
LAB_0044471f:
  iVar3 = 0;
  if (0 < (this->field19_0xd4)._s_0.convoy_total) {
    pMVar5 = &this->field18_0x7c;
    do {
      if ((pMVar5->_s_0).convoy_handle[0] != 0) {
        bVar2 = IsAlive(pMVar5->h_array);
        if ((!bVar2) && ((this->field16_0x40).b_array[iVar3 + 9] != false)) {
          AudioMessage("misns403.wav");
          piVar1 = &(this->field19_0xd4)._s_0.convoy_dead;
          (this->field16_0x40).b_array[iVar3 + 9] = false;
          *piVar1 = *piVar1 + 1;
          if ((this->field19_0xd4)._s_0.convoy_total / 3 < *piVar1) {
            pcVar7 = "misns4l1.des";
            fVar6 = Get_Time();
            FailMission(fVar6 + 15.0,pcVar7);
          }
        }
      }
      fVar6 = GetDistance((pMVar5->_s_0).convoy_handle[0],"goal",0);
      if ((fVar6 < 100.0) && ((this->field16_0x40).b_array[iVar3 + 0x13] == false)) {
        (this->field16_0x40).b_array[iVar3 + 0x13] = true;
        piVar1 = &(this->field19_0xd4)._s_0.win_count;
        *piVar1 = *piVar1 + 1;
      }
      iVar3 = iVar3 + 1;
      pMVar5 = (Misns4Mission_u_124 *)((int)pMVar5 + 4);
    } while (iVar3 < (this->field19_0xd4)._s_0.convoy_total);
  }
  if (((this->field19_0xd4)._s_0.win_count == (this->field19_0xd4)._s_0.convoy_total + -1) &&
     ((this->field16_0x40)._s_0.won == false)) {
    pcVar7 = "misns4w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6 + 10.0,pcVar7);
    (this->field16_0x40)._s_0.won = true;
  }
  return;
}
