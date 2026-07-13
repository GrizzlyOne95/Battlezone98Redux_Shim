/*
 * Entry: 0043b193
 * Name: Misn17Mission::Execute
 * Namespace: Misn17Mission
 * Signature: void Execute(Misn17Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn17Mission::Execute(Misn17Mission *this)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  AiCommand AVar4;
  float fVar5;
  char *pcVar6;
  
  if ((this->field16_0x40)._s_0.missionstart == false) {
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.minedistancecheck = fVar5 + 10.0;
    iVar3 = AudioMessage("misn1701.wav");
    (this->field18_0x110)._s_0.aud1 = iVar3;
    iVar3 = GetHandle("avrecy18_recycler");
    (this->field18_0x110)._s_0.avrec = iVar3;
    iVar3 = GetHandle("savfactory1");
    (this->field18_0x110)._s_0.savfactory1 = iVar3;
    iVar3 = GetHandle("savfactory2");
    (this->field18_0x110)._s_0.savfactory2 = iVar3;
    iVar3 = GetHandle("savfactory3");
    (this->field18_0x110)._s_0.savfactory3 = iVar3;
    iVar3 = GetHandle("savfactory4");
    (this->field18_0x110)._s_0.savfactory4 = iVar3;
    iVar3 = GetHandle("factorypart1");
    (this->field18_0x110)._s_0.factorypart1 = iVar3;
    iVar3 = GetHandle("factorypart2");
    (this->field18_0x110)._s_0.factorypart2 = iVar3;
    iVar3 = GetHandle("factorypart3");
    (this->field18_0x110)._s_0.factorypart3 = iVar3;
    iVar3 = GetHandle("factorynav");
    (this->field18_0x110)._s_0.factorynav = iVar3;
    iVar3 = GetHandle("basenav");
    (this->field18_0x110)._s_0.basenav = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer1",0);
    (this->field18_0x110)._s_0.tower1 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer2",0);
    (this->field18_0x110)._s_0.tower2 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer3",0);
    (this->field18_0x110)._s_0.tower3 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer4",0);
    (this->field18_0x110)._s_0.tower4 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer5",0);
    (this->field18_0x110)._s_0.tower5 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer6",0);
    (this->field18_0x110)._s_0.tower6 = iVar3;
    iVar3 = BuildObject("hbptow",2,"geizer7",0);
    (this->field18_0x110)._s_0.tower7 = iVar3;
    SetObjectiveOn((this->field18_0x110)._s_0.tower1);
    SetObjectiveOn((this->field18_0x110)._s_0.tower2);
    SetObjectiveOn((this->field18_0x110)._s_0.tower3);
    SetObjectiveOn((this->field18_0x110)._s_0.tower4);
    SetObjectiveOn((this->field18_0x110)._s_0.tower5);
    SetObjectiveOn((this->field18_0x110)._s_0.tower6);
    SetObjectiveOn((this->field18_0x110)._s_0.tower7);
    SetObjectiveName((this->field18_0x110)._s_0.tower1,"Tower 1");
    SetObjectiveName((this->field18_0x110)._s_0.tower2,"Tower 2");
    SetObjectiveName((this->field18_0x110)._s_0.tower3,"Tower 3");
    SetObjectiveName((this->field18_0x110)._s_0.tower4,"Tower 4");
    SetObjectiveName((this->field18_0x110)._s_0.tower5,"Tower 5");
    SetObjectiveName((this->field18_0x110)._s_0.tower6,"Tower 6");
    SetObjectiveName((this->field18_0x110)._s_0.tower7,"Tower 7 ");
    SetObjectiveName((this->field18_0x110)._s_0.factorynav,"Furies Factory");
    SetObjectiveName((this->field18_0x110)._s_0.basenav,"Home Base");
    (this->field16_0x40)._s_0.missionstart = true;
    (this->field16_0x40)._s_0.newobjective = true;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.camdone = fVar5 + 35.0;
    SetScrap(1,0x28);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime1 = fVar5 + 10.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime2 = fVar5 + 100.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime3 = fVar5 + 220.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime4 = fVar5 + 340.0;
    SetAIP("misn17.aip",2);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.discheck = fVar5 + 30.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower1check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower2check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower3check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower4check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower5check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower6check = fVar5 + 3.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower7check = fVar5 + 3.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.art1);
  if ((bVar2) && (bVar2 = IsAlive(&(this->field18_0x110)._s_0.desart1), !bVar2)) {
    iVar3 = BuildObject("hvsav",2,"counter",0);
    (this->field18_0x110)._s_0.desart1 = iVar3;
    Attack(iVar3,(this->field18_0x110)._s_0.art1,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.art2);
  if ((bVar2) && (bVar2 = IsAlive(&(this->field18_0x110)._s_0.desart2), !bVar2)) {
    iVar3 = BuildObject("hvsav",2,"counter",0);
    (this->field18_0x110)._s_0.desart2 = iVar3;
    Attack(iVar3,(this->field18_0x110)._s_0.art2,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.art3);
  if ((bVar2) && (bVar2 = IsAlive(&(this->field18_0x110)._s_0.desart3), !bVar2)) {
    iVar3 = BuildObject("hvsav",2,"counter",0);
    (this->field18_0x110)._s_0.desart3 = iVar3;
    Attack(iVar3,(this->field18_0x110)._s_0.art3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.art4);
  if ((bVar2) && (bVar2 = IsAlive(&(this->field18_0x110)._s_0.desart4), !bVar2)) {
    iVar3 = BuildObject("hvsav",2,"counter",0);
    (this->field18_0x110)._s_0.desart4 = iVar3;
    Attack(iVar3,(this->field18_0x110)._s_0.art4,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.art5);
  if ((bVar2) && (bVar2 = IsAlive(&(this->field18_0x110)._s_0.desart5), !bVar2)) {
    iVar3 = BuildObject("hvsav",2,"counter",0);
    (this->field18_0x110)._s_0.desart5 = iVar3;
    Attack(iVar3,(this->field18_0x110)._s_0.art5,1);
  }
  if ((this->field16_0x40)._s_0.openingcin == false) {
    CameraReady();
    (this->field16_0x40)._s_0.camera1 = true;
    (this->field16_0x40)._s_0.openingcin = true;
  }
  if (((this->field16_0x40)._s_0.camera2 == true) &&
     (bVar2 = CameraPath("cineractive2",500,2000,(this->field18_0x110)._s_0.tower1), bVar2)) {
    (this->field16_0x40)._s_0.camera2 = false;
    (this->field16_0x40)._s_0.camera3 = true;
  }
  if (((this->field16_0x40)._s_0.camera3 == true) &&
     (bVar2 = CameraPath("cineractive3",1000,2000,(this->field18_0x110)._s_0.tower6), bVar2)) {
    (this->field16_0x40)._s_0.camera3 = false;
    (this->field16_0x40)._s_0.camera4 = true;
  }
  if (((this->field16_0x40)._s_0.camera4 == true) &&
     (bVar2 = CameraPath("cineractive5",1000,2000,(this->field18_0x110)._s_0.tower3), bVar2)) {
    (this->field16_0x40)._s_0.camera4 = false;
    (this->field16_0x40)._s_0.camera5 = true;
  }
  if (((this->field16_0x40)._s_0.camera5 == true) &&
     (bVar2 = CameraPath("cineractive6",1000,2000,(this->field18_0x110)._s_0.tower4), bVar2)) {
    (this->field16_0x40)._s_0.camera5 = false;
    (this->field16_0x40)._s_0.camera6 = true;
  }
  if (((this->field16_0x40)._s_0.camera6 == true) &&
     (bVar2 = CameraPath("cineractive4",1000,2000,(this->field18_0x110)._s_0.tower5), bVar2)) {
    (this->field16_0x40)._s_0.camera6 = false;
    (this->field16_0x40)._s_0.camera7 = true;
  }
  if (((this->field16_0x40)._s_0.camera7 == true) &&
     (bVar2 = CameraPath("cineractive7",1000,0x6a4,(this->field18_0x110)._s_0.tower7), bVar2)) {
    (this->field16_0x40)._s_0.camera7 = false;
    CameraFinish();
  }
  if (((this->field16_0x40)._s_0.camera1 == true) &&
     (bVar2 = CameraPath("cineractive1",1000,2000,(this->field18_0x110)._s_0.savfactory1), bVar2)) {
    (this->field16_0x40)._s_0.camera1 = false;
    (this->field16_0x40)._s_0.camera2 = true;
  }
  if ((this->field16_0x40)._s_0.openingcindone == false) {
    piVar1 = &(this->field18_0x110)._s_0.aud1;
    bVar2 = IsAudioMessageDone(*piVar1);
    if ((bVar2) || (bVar2 = CameraCancelled(), bVar2)) {
      CameraFinish();
      StopAudioMessage(*piVar1);
      (this->field16_0x40)._s_0.openingcindone = true;
      (this->field16_0x40)._s_0.camera1 = false;
      (this->field16_0x40)._s_0.camera2 = false;
      (this->field16_0x40)._s_0.camera3 = false;
      (this->field16_0x40)._s_0.camera4 = false;
      (this->field16_0x40)._s_0.camera5 = false;
      (this->field16_0x40)._s_0.camera6 = false;
      (this->field16_0x40)._s_0.camera7 = false;
    }
  }
  if (((this->field16_0x40)._s_0.factorypart1dead == false) &&
     (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart1), !bVar2)) {
    BuildObject("eggeizr1",0,"part1geizer",0);
    (this->field16_0x40)._s_0.factorypart1dead = true;
  }
  if (((this->field16_0x40)._s_0.factorypart2dead == false) &&
     (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart2), !bVar2)) {
    BuildObject("eggeizr1",0,"part2geizer",0);
    (this->field16_0x40)._s_0.factorypart2dead = true;
  }
  if (((this->field16_0x40)._s_0.factorypart3dead == false) &&
     (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart3), !bVar2)) {
    BuildObject("eggeizr1",0,"part3geizer",0);
    (this->field16_0x40)._s_0.factorypart3dead = true;
  }
  if (((this->field16_0x40)._s_0.minesmade == false) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.minedistancecheck < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.savfactory2);
    (this->field18_0x110)._s_0.miner = iVar3;
    fVar5 = GetDistance(iVar3,"pt1",0);
    if ((fVar5 < 610.0) ||
       ((fVar5 = GetDistance((this->field18_0x110)._s_0.miner,"pt2",0), fVar5 < 610.0 ||
        (fVar5 = GetDistance((this->field18_0x110)._s_0.miner,"pt3",0), fVar5 < 610.0)))) {
      iVar3 = BuildObject("boltmine2",2,"mine54",0);
      (this->field18_0x110)._s_0.MINE[0] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine1",0);
      (this->field18_0x110)._s_0.MINE[1] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine2",0);
      (this->field18_0x110)._s_0.MINE[2] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine3",0);
      (this->field18_0x110)._s_0.MINE[3] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine4",0);
      (this->field18_0x110)._s_0.MINE[4] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine5",0);
      (this->field18_0x110)._s_0.MINE[5] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine6",0);
      (this->field18_0x110)._s_0.MINE[6] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine7",0);
      (this->field18_0x110)._s_0.MINE[7] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine8",0);
      (this->field18_0x110)._s_0.MINE[8] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine9",0);
      (this->field18_0x110)._s_0.MINE[9] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine10",0);
      (this->field18_0x110)._s_0.MINE[10] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine11",0);
      (this->field18_0x110)._s_0.MINE[0xb] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine12",0);
      (this->field18_0x110)._s_0.MINE[0xc] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine13",0);
      (this->field18_0x110)._s_0.MINE[0xd] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine14",0);
      (this->field18_0x110)._s_0.MINE[0xe] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine15",0);
      (this->field18_0x110)._s_0.MINE[0xf] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine16",0);
      (this->field18_0x110)._s_0.MINE[0x10] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine17",0);
      (this->field18_0x110)._s_0.MINE[0x11] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine18",0);
      (this->field18_0x110)._s_0.MINE[0x12] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine19",0);
      (this->field18_0x110)._s_0.MINE[0x13] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine20",0);
      (this->field18_0x110)._s_0.MINE[0x14] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine21",0);
      (this->field18_0x110)._s_0.MINE[0x15] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine22",0);
      (this->field18_0x110)._s_0.MINE[0x16] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine23",0);
      (this->field18_0x110)._s_0.MINE[0x17] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine24",0);
      (this->field18_0x110)._s_0.MINE[0x18] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine25",0);
      (this->field18_0x110)._s_0.MINE[0x19] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine26",0);
      (this->field18_0x110)._s_0.MINE[0x1a] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine27",0);
      (this->field18_0x110)._s_0.MINE[0x1b] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine28",0);
      (this->field18_0x110)._s_0.MINE[0x1c] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine29",0);
      (this->field18_0x110)._s_0.MINE[0x1d] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine30",0);
      (this->field18_0x110)._s_0.MINE[0x1e] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine31",0);
      (this->field18_0x110)._s_0.MINE[0x1f] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine32",0);
      (this->field18_0x110)._s_0.MINE[0x20] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine33",0);
      (this->field18_0x110)._s_0.MINE[0x21] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine34",0);
      (this->field18_0x110)._s_0.MINE[0x22] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine35",0);
      (this->field18_0x110)._s_0.MINE[0x23] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine36",0);
      (this->field18_0x110)._s_0.MINE[0x24] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine37",0);
      (this->field18_0x110)._s_0.MINE[0x25] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine38",0);
      (this->field18_0x110)._s_0.MINE[0x26] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine39",0);
      (this->field18_0x110)._s_0.MINE[0x27] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine40",0);
      (this->field18_0x110)._s_0.MINE[0x28] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine41",0);
      (this->field18_0x110)._s_0.MINE[0x29] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine42",0);
      (this->field18_0x110)._s_0.MINE[0x2a] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine43",0);
      (this->field18_0x110)._s_0.MINE[0x2b] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine44",0);
      (this->field18_0x110)._s_0.MINE[0x2c] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine45",0);
      (this->field18_0x110)._s_0.MINE[0x2d] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine46",0);
      (this->field18_0x110)._s_0.MINE[0x2e] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine47",0);
      (this->field18_0x110)._s_0.MINE[0x2f] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine48",0);
      (this->field18_0x110)._s_0.MINE[0x30] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine49",0);
      (this->field18_0x110)._s_0.MINE[0x31] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine55",0);
      (this->field18_0x110)._s_0.MINE[0x32] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine56",0);
      (this->field18_0x110)._s_0.MINE[0x33] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine52",0);
      (this->field18_0x110)._s_0.MINE[0x34] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine53",0);
      (this->field18_0x110)._s_0.MINE[0x35] = iVar3;
      (this->field16_0x40)._s_0.minesmade = true;
    }
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.minedistancecheck = fVar5 + 3.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower1);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower1spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower1check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower1);
    (this->field18_0x110)._s_0.trig1 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower1,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower1);
      (this->field18_0x110)._s_0.deftow1a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower1);
      (this->field18_0x110)._s_0.deftow1b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow1a,(this->field18_0x110)._s_0.tower1,1000);
      Defend2((this->field18_0x110)._s_0.deftow1b,(this->field18_0x110)._s_0.tower1,1000);
      (this->field16_0x40)._s_0.tower1spawn = true;
    }
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower1check = fVar5 + 2.0;
    (this->field18_0x110)._s_0.trig1 = 0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow1a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow1a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow1a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow1a);
    (this->field18_0x110)._s_0.badman1 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow1a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow1b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow1b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow1b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow1b);
    (this->field18_0x110)._s_0.badman2 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow1b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow2a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow2a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow2a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow2a);
    (this->field18_0x110)._s_0.badman3 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow2a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow2b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow2b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow2b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow2b);
    (this->field18_0x110)._s_0.badman4 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow2b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow3a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow3a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow3a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow3a);
    (this->field18_0x110)._s_0.badman5 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow3a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow3b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow3b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow3b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow3b);
    (this->field18_0x110)._s_0.badman6 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow3b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow4a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow4a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow4a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow4a);
    (this->field18_0x110)._s_0.badman7 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow4a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow4b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow4b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow4b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow4b);
    (this->field18_0x110)._s_0.badman8 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow4b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow5a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow5a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow5a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow5a);
    (this->field18_0x110)._s_0.badman9 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow5a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow5b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow5b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow5b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow5b);
    (this->field18_0x110)._s_0.badman10 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow5b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow6a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow6a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow6a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow6a);
    (this->field18_0x110)._s_0.badman11 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow6a,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow6b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow6b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow6b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow6b);
    (this->field18_0x110)._s_0.badman12 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow6b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow7a);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow7a), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow7a), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow7a);
    (this->field18_0x110)._s_0.badman13 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow7a,(this->field18_0x110)._s_0.badman14,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.deftow7b);
  if (((bVar2) &&
      (AVar4 = GetCurrentCommand((this->field18_0x110)._s_0.deftow7b), AVar4 == CMD_DEFEND)) &&
     (fVar5 = GetLastEnemyShot((this->field18_0x110)._s_0.deftow7b), 0.0 < fVar5)) {
    iVar3 = GetWhoShotMe((this->field18_0x110)._s_0.deftow7b);
    (this->field18_0x110)._s_0.badman14 = iVar3;
    Attack((this->field18_0x110)._s_0.deftow7b,iVar3,1);
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower2);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower2spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower2check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower2);
    (this->field18_0x110)._s_0.trig2 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower2,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower2);
      (this->field18_0x110)._s_0.deftow2a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower2);
      (this->field18_0x110)._s_0.deftow2b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow2a,(this->field18_0x110)._s_0.tower2,1000);
      Defend2((this->field18_0x110)._s_0.deftow2b,(this->field18_0x110)._s_0.tower2,1000);
      (this->field16_0x40)._s_0.tower2spawn = true;
    }
    (this->field18_0x110)._s_0.trig2 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower2check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower3);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower3spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower3check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower3);
    (this->field18_0x110)._s_0.trig3 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower3,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower3);
      (this->field18_0x110)._s_0.deftow3a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower3);
      (this->field18_0x110)._s_0.deftow3b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow3a,(this->field18_0x110)._s_0.tower3,1000);
      Defend2((this->field18_0x110)._s_0.deftow3b,(this->field18_0x110)._s_0.tower3,1000);
      (this->field16_0x40)._s_0.tower3spawn = true;
    }
    (this->field18_0x110)._s_0.trig3 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower3check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower4);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower4spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower4check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower4);
    (this->field18_0x110)._s_0.trig4 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower4,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower4);
      (this->field18_0x110)._s_0.deftow4a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower4);
      (this->field18_0x110)._s_0.deftow4b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow4a,(this->field18_0x110)._s_0.tower4,1000);
      Defend2((this->field18_0x110)._s_0.deftow4b,(this->field18_0x110)._s_0.tower4,1000);
      (this->field16_0x40)._s_0.tower4spawn = true;
    }
    (this->field18_0x110)._s_0.trig4 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower4check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower5);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower5spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower5check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower5);
    (this->field18_0x110)._s_0.trig5 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower5,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower5);
      (this->field18_0x110)._s_0.deftow5a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower5);
      (this->field18_0x110)._s_0.deftow5b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow5a,(this->field18_0x110)._s_0.tower5,1000);
      Defend2((this->field18_0x110)._s_0.deftow5b,(this->field18_0x110)._s_0.tower5,1000);
      (this->field16_0x40)._s_0.tower5spawn = true;
    }
    (this->field18_0x110)._s_0.trig5 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower5check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower6);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower6spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower6check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower6);
    (this->field18_0x110)._s_0.trig6 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower6,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower6);
      (this->field18_0x110)._s_0.deftow6a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower6);
      (this->field18_0x110)._s_0.deftow6b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow6a,(this->field18_0x110)._s_0.tower6,1000);
      Defend2((this->field18_0x110)._s_0.deftow6b,(this->field18_0x110)._s_0.tower6,1000);
      (this->field16_0x40)._s_0.tower6spawn = true;
    }
    (this->field18_0x110)._s_0.trig6 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower6check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower7);
  if (((bVar2) && ((this->field16_0x40)._s_0.tower7spawn == false)) &&
     (fVar5 = Get_Time(), (this->field17_0x84)._s_0.tower7check < fVar5)) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.tower7);
    (this->field18_0x110)._s_0.trig7 = iVar3;
    fVar5 = GetDistance((this->field18_0x110)._s_0.tower7,iVar3);
    if (fVar5 < 400.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower7);
      (this->field18_0x110)._s_0.deftow7a = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.tower7);
      (this->field18_0x110)._s_0.deftow7b = iVar3;
      Defend2((this->field18_0x110)._s_0.deftow7a,(this->field18_0x110)._s_0.tower7,1000);
      Defend2((this->field18_0x110)._s_0.deftow7b,(this->field18_0x110)._s_0.tower7,1000);
      (this->field16_0x40)._s_0.tower7spawn = true;
    }
    (this->field18_0x110)._s_0.trig7 = 0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.tower7check = fVar5 + 2.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower1);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower1dead == false)) {
    BuildObject("eggeizr1",0,"geizer1",0);
    (this->field16_0x40)._s_0.tower1dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower2);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower2dead == false)) {
    BuildObject("eggeizr1",0,"geizer2",0);
    (this->field16_0x40)._s_0.tower2dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower3);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower3dead == false)) {
    BuildObject("eggeizr1",0,"geizer3",0);
    (this->field16_0x40)._s_0.tower3dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower4);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower4dead == false)) {
    BuildObject("eggeizr1",0,"geizer4",0);
    (this->field16_0x40)._s_0.tower4dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower5);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower5dead == false)) {
    BuildObject("eggeizr1",0,"geizer5",0);
    (this->field16_0x40)._s_0.tower5dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower6);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower6dead == false)) {
    BuildObject("eggeizr1",0,"geizer6",0);
    (this->field16_0x40)._s_0.tower6dead = true;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.tower7);
  if ((!bVar2) && ((this->field16_0x40)._s_0.tower7dead == false)) {
    BuildObject("eggeizr1",0,"geizer7",0);
    (this->field16_0x40)._s_0.tower7dead = true;
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.towersdestroyed == false) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1701.otf",DisplayInterface::colorWhite,8.0);
    }
    if (((this->field16_0x40)._s_0.towersdestroyed == true) &&
       ((this->field16_0x40)._s_0.missionwon == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1701.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1702.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.missionwon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn1701.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn1702.otf",DisplayInterface::colorGreen,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.spawntime1 < fVar5) {
    BuildObject("hvsat",2,(this->field18_0x110)._s_0.savfactory1);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime1 = fVar5 + 400.0;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.spawntime2 < fVar5) {
    BuildObject("hvsav",2,(this->field18_0x110)._s_0.savfactory2);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime2 = fVar5 + 400.0;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.spawntime3 < fVar5) {
    BuildObject("hvsat",2,(this->field18_0x110)._s_0.savfactory3);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime3 = fVar5 + 400.0;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.spawntime4 < fVar5) {
    BuildObject("hvsat",2,(this->field18_0x110)._s_0.savfactory4);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.spawntime4 = fVar5 + 400.0;
  }
  fVar5 = Get_Time();
  if (((this->field17_0x84)._s_0.discheck < fVar5) && ((this->field16_0x40)._s_0.defenders == false)
     ) {
    iVar3 = GetNearestEnemy((this->field18_0x110)._s_0.savfactory1);
    (this->field18_0x110)._s_0.prey1 = iVar3;
    fVar5 = GetDistance(iVar3,"savspawn",1);
    if (fVar5 < 450.0) {
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.savfactory2);
      (this->field18_0x110)._s_0.ip1 = iVar3;
      iVar3 = BuildObject("hvsat",2,(this->field18_0x110)._s_0.savfactory3);
      (this->field18_0x110)._s_0.ip2 = iVar3;
      iVar3 = BuildObject("hvsav",2,(this->field18_0x110)._s_0.savfactory4);
      (this->field18_0x110)._s_0.ip3 = iVar3;
      iVar3 = BuildObject("hvsav",2,(this->field18_0x110)._s_0.savfactory1);
      (this->field18_0x110)._s_0.ip4 = iVar3;
      (this->field16_0x40)._s_0.defenders = true;
      Defend2((this->field18_0x110)._s_0.ip1,(this->field18_0x110)._s_0.savfactory2,1);
      Defend2((this->field18_0x110)._s_0.ip2,(this->field18_0x110)._s_0.savfactory3,1);
      Defend2((this->field18_0x110)._s_0.ip3,(this->field18_0x110)._s_0.savfactory4,1);
      Defend2((this->field18_0x110)._s_0.ip4,(this->field18_0x110)._s_0.savfactory1,1);
    }
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.discheck = fVar5 + 5.0;
  }
  bVar2 = IsAlive(&(this->field18_0x110)._s_0.avrec);
  if ((!bVar2) && ((this->field16_0x40)._s_0.missionfail == false)) {
    pcVar6 = "misn17l1.des";
    fVar5 = Get_Time();
    FailMission(fVar5 + 20.0,pcVar6);
    AudioMessage("misn1704.wav");
    (this->field16_0x40)._s_0.missionfail = true;
  }
  if ((((((this->field16_0x40)._s_0.tower1dead == true) &&
        ((this->field16_0x40)._s_0.tower2dead == true)) &&
       ((this->field16_0x40)._s_0.tower3dead == true)) &&
      (((this->field16_0x40)._s_0.tower4dead == true &&
       ((this->field16_0x40)._s_0.tower5dead == true)))) &&
     (((this->field16_0x40)._s_0.tower6dead == true &&
      (((this->field16_0x40)._s_0.tower7dead == true &&
       ((this->field16_0x40)._s_0.towersdestroyed == false)))))) {
    if ((this->field16_0x40)._s_0.minesmade == false) {
      GetRidOfSomeScrap(300);
      iVar3 = BuildObject("boltmine2",2,"mine54",0);
      (this->field18_0x110)._s_0.MINE[0] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine1",0);
      (this->field18_0x110)._s_0.MINE[1] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine2",0);
      (this->field18_0x110)._s_0.MINE[2] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine3",0);
      (this->field18_0x110)._s_0.MINE[3] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine4",0);
      (this->field18_0x110)._s_0.MINE[4] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine5",0);
      (this->field18_0x110)._s_0.MINE[5] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine6",0);
      (this->field18_0x110)._s_0.MINE[6] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine7",0);
      (this->field18_0x110)._s_0.MINE[7] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine8",0);
      (this->field18_0x110)._s_0.MINE[8] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine9",0);
      (this->field18_0x110)._s_0.MINE[9] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine10",0);
      (this->field18_0x110)._s_0.MINE[10] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine11",0);
      (this->field18_0x110)._s_0.MINE[0xb] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine12",0);
      (this->field18_0x110)._s_0.MINE[0xc] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine13",0);
      (this->field18_0x110)._s_0.MINE[0xd] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine14",0);
      (this->field18_0x110)._s_0.MINE[0xe] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine15",0);
      (this->field18_0x110)._s_0.MINE[0xf] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine16",0);
      (this->field18_0x110)._s_0.MINE[0x10] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine17",0);
      (this->field18_0x110)._s_0.MINE[0x11] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine18",0);
      (this->field18_0x110)._s_0.MINE[0x12] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine19",0);
      (this->field18_0x110)._s_0.MINE[0x13] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine20",0);
      (this->field18_0x110)._s_0.MINE[0x14] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine21",0);
      (this->field18_0x110)._s_0.MINE[0x15] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine22",0);
      (this->field18_0x110)._s_0.MINE[0x16] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine23",0);
      (this->field18_0x110)._s_0.MINE[0x17] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine24",0);
      (this->field18_0x110)._s_0.MINE[0x18] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine25",0);
      (this->field18_0x110)._s_0.MINE[0x19] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine26",0);
      (this->field18_0x110)._s_0.MINE[0x1a] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine27",0);
      (this->field18_0x110)._s_0.MINE[0x1b] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine28",0);
      (this->field18_0x110)._s_0.MINE[0x1c] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine29",0);
      (this->field18_0x110)._s_0.MINE[0x1d] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine30",0);
      (this->field18_0x110)._s_0.MINE[0x1e] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine31",0);
      (this->field18_0x110)._s_0.MINE[0x1f] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine32",0);
      (this->field18_0x110)._s_0.MINE[0x20] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine33",0);
      (this->field18_0x110)._s_0.MINE[0x21] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine34",0);
      (this->field18_0x110)._s_0.MINE[0x22] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine35",0);
      (this->field18_0x110)._s_0.MINE[0x23] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine36",0);
      (this->field18_0x110)._s_0.MINE[0x24] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine37",0);
      (this->field18_0x110)._s_0.MINE[0x25] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine38",0);
      (this->field18_0x110)._s_0.MINE[0x26] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine39",0);
      (this->field18_0x110)._s_0.MINE[0x27] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine40",0);
      (this->field18_0x110)._s_0.MINE[0x28] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine41",0);
      (this->field18_0x110)._s_0.MINE[0x29] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine42",0);
      (this->field18_0x110)._s_0.MINE[0x2a] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine43",0);
      (this->field18_0x110)._s_0.MINE[0x2b] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine44",0);
      (this->field18_0x110)._s_0.MINE[0x2c] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine45",0);
      (this->field18_0x110)._s_0.MINE[0x2d] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine46",0);
      (this->field18_0x110)._s_0.MINE[0x2e] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine47",0);
      (this->field18_0x110)._s_0.MINE[0x2f] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine48",0);
      (this->field18_0x110)._s_0.MINE[0x30] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine49",0);
      (this->field18_0x110)._s_0.MINE[0x31] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine55",0);
      (this->field18_0x110)._s_0.MINE[0x32] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine56",0);
      (this->field18_0x110)._s_0.MINE[0x33] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine52",0);
      (this->field18_0x110)._s_0.MINE[0x34] = iVar3;
      iVar3 = BuildObject("boltmine2",2,"mine53",0);
      (this->field18_0x110)._s_0.MINE[0x35] = iVar3;
      (this->field16_0x40)._s_0.minesmade = true;
    }
    CameraReady();
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field16_0x40)._s_0.towersdestroyed = true;
    (this->field16_0x40)._s_0.minesdestroyed = true;
    (this->field16_0x40)._s_0.minecinstart = true;
    (this->field19_0x34c)._s_0.minecount = 0;
    iVar3 = AudioMessage("misn1730.wav");
    (this->field18_0x110)._s_0.mineaudio = iVar3;
  }
  if ((this->field16_0x40)._s_0.minesdestroyed == true) {
    if ((this->field16_0x40)._s_0.minesmade == true) {
      piVar1 = &(this->field19_0x34c)._s_0.minecount;
      Damage(*(int *)((int)&this->field18_0x110 + *piVar1 * 4 + 0x114),10000);
      *piVar1 = *piVar1 + 1;
      if (0x35 < *piVar1) {
        (this->field16_0x40)._s_0.minesdestroyed = false;
      }
    }
    if (((this->field16_0x40)._s_0.minesdestroyed == true) &&
       ((this->field16_0x40)._s_0.minecin == false)) {
      CameraPath("minecin",1000,500,(this->field18_0x110)._s_0.savfactory2);
    }
  }
  if (((this->field16_0x40)._s_0.minecinstart == true) &&
     ((bVar2 = IsAudioMessageDone((this->field18_0x110)._s_0.mineaudio), bVar2 ||
      (bVar2 = CameraCancelled(), bVar2)))) {
    CameraFinish();
    (this->field16_0x40)._s_0.minecin = true;
    StopAudioMessage((this->field18_0x110)._s_0.mineaudio);
    (this->field16_0x40)._s_0.minecinstart = false;
  }
  if (((((this->field16_0x40)._s_0.missionwon == false) &&
       (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart1), !bVar2)) &&
      (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart2), !bVar2)) &&
     (bVar2 = IsAlive(&(this->field18_0x110)._s_0.factorypart3), !bVar2)) {
    AudioMessage("misn1703.wav");
    (this->field16_0x40)._s_0.missionwon = true;
    pcVar6 = "misn17w1.des";
    fVar5 = Get_Time();
    SucceedMission(fVar5 + 4.0,pcVar6);
    CameraReady();
    iVar3 = BuildObject("eggeizr1",3,"cinscrap",0);
    (this->field18_0x110)._s_0.cinscrap = iVar3;
    CameraObject(iVar3,1000,8000,1000,(this->field18_0x110)._s_0.savfactory1);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.sf2blow = fVar5 + 1.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.sf4blow = fVar5 + 2.5;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.sf3blow = fVar5 + 3.2;
  }
  if ((this->field16_0x40)._s_0.missionwon == true) {
    if (((this->field16_0x40)._s_0.sf2gone == false) &&
       (fVar5 = Get_Time(), (this->field17_0x84)._s_0.sf2blow < fVar5)) {
      Damage((this->field18_0x110)._s_0.savfactory2,200000);
      (this->field16_0x40)._s_0.sf2gone = true;
    }
    if (((this->field16_0x40)._s_0.sf3gone == false) &&
       (fVar5 = Get_Time(), (this->field17_0x84)._s_0.sf3blow < fVar5)) {
      Damage((this->field18_0x110)._s_0.savfactory3,200000);
      (this->field16_0x40)._s_0.sf3gone = true;
    }
    if (((this->field16_0x40)._s_0.sf4gone == false) &&
       (fVar5 = Get_Time(), (this->field17_0x84)._s_0.sf4blow < fVar5)) {
      Damage((this->field18_0x110)._s_0.savfactory4,200000);
      (this->field16_0x40)._s_0.sf4gone = true;
    }
  }
  return;
}
