/*
 * Entry: 004162be
 * Name: Inst4XMission::Start
 * Namespace: Inst4XMission
 * Signature: void Start(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Inst4XMission::Start(Inst4XMission *this)

{
  float fVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  float *pfVar5;
  Team *this_00;
  long lVar6;
  Team *this_01;
  long extraout_EAX;
  undefined4 *puVar7;
  long lVar8;
  char *local_30;
  long local_2c;
  long local_28;
  long local_24;
  long local_20;
  undefined1 local_1c [4];
  char local_18 [8];
  undefined4 uStack_10;
  undefined2 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  LuaMission::Start((LuaMission *)this);
  if (loaded != false) {
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    uStack_10 = 0;
    uStack_c = 0;
    pcVar3 = strchr(&msn_filename,0x2e);
    pcVar3 = pcVar3 + -0xd42330;
    if (8 < (int)pcVar3) {
      pcVar3 = (char *)0x8;
    }
    strncpy(local_18,&msn_filename,(size_t)pcVar3);
    puVar2 = (undefined4 *)(local_1c + 3);
    do {
      puVar7 = puVar2;
      loaded = *(bool *)((int)puVar7 + 1);
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (loaded != false);
    *(undefined4 *)((int)puVar7 + 1) = 0x66646f2e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    iVar4 = ItemExists(local_18);
    if (iVar4 != 0) {
      ParameterDB::ParameterDB((ParameterDB *)local_1c,local_18);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x3986dd43,&startVoice,startVoice);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x2de2fe6c,&missionObjective,missionObjective);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x198af464,&shellSuccess,shellSuccess);
      ParameterDB::Get((ParameterDB *)local_1c,0,0xc79eb669,&shellFail,shellFail);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x152e9876,&failCondition,failCondition);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x84d79505,&successCondition,successCondition);
      ParameterDB::Get((ParameterDB *)local_1c,0,0xb4ef8667,&shellOutOfTime,shellOutOfTime);
      ParameterDB::~ParameterDB((ParameterDB *)local_1c);
    }
  }
  if ((this->field19_0x4c)._s_0.firstFrame != false) {
    (this->field19_0x4c)._s_0.firstFrame = false;
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    uStack_10 = 0;
    uStack_c = 0;
    local_30 = strchr(&msn_filename,0x2e);
    local_30 = local_30 + -0xd42330;
    if (8 < (int)local_30) {
      local_30 = (char *)0x8;
    }
    strncpy(local_18,&msn_filename,(size_t)local_30);
    puVar2 = (undefined4 *)(local_1c + 3);
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x66646f2e;
    local_28 = 0x1e;
    local_20 = 0x1e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    local_2c = 0;
    local_24 = 0x2d;
    iVar4 = ItemExists(local_18);
    if (iVar4 != 0) {
      ParameterDB::ParameterDB((ParameterDB *)local_1c,local_18);
      ParameterDB::Get((ParameterDB *)local_1c,0,0x8af01d94,&local_2c,local_2c);
      ParameterDB::Get((ParameterDB *)local_1c,0,0xb2ce525c,&local_28,local_28);
      ParameterDB::Get((ParameterDB *)local_1c,0,0xa5739020,&local_20,local_20);
      ParameterDB::Get((ParameterDB *)local_1c,0,0xc4283588,&local_24,local_24);
      pfVar5 = &(this->field20_0x50)._s_0.timeLeft;
      ParameterDB::Get((ParameterDB *)local_1c,0,0x1752b305,pfVar5,*pfVar5);
      ParameterDB::~ParameterDB((ParameterDB *)local_1c);
    }
    this_00 = Team::GetTeam(1);
    lVar6 = Team::GetMaxPilot(this_00);
    lVar6 = local_2c - lVar6;
    if (lVar6 < 0) {
      lVar6 = 0;
    }
    Team::AddMaxPilot(this_00,lVar6);
    Team::AddPilot(this_00,local_2c);
    this_01 = Team::GetTeam(2);
    lVar6 = Team::GetMaxPilot(this_01);
    lVar6 = local_28 - lVar6;
    if (lVar6 < 0) {
      lVar6 = 0;
    }
    Team::AddMaxPilot(this_01,lVar6);
    Team::AddPilot(this_01,local_28);
    lVar6 = Team::GetMaxScrap(this_00);
    lVar6 = local_20 - lVar6;
    if (lVar6 < 0) {
      lVar6 = 0;
    }
    Team::AddMaxScrap(this_00,lVar6);
    Team::AddScrap(this_00,local_20);
    lVar6 = Team::GetMaxScrap(this_01);
    lVar6 = local_24 - lVar6;
    if (lVar6 < 0) {
      lVar6 = 0;
    }
    Team::AddMaxScrap(this_01,lVar6);
    Team::AddScrap(this_01,local_24);
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    uStack_10 = 0;
    uStack_c = 0;
    strncpy(local_18,&msn_filename,(size_t)local_30);
    puVar2 = (undefined4 *)(local_1c + 3);
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x7069612e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    iVar4 = ItemExists(local_18);
    if (iVar4 == 0) {
      builtin_strncpy(local_18,"misn14.a",8);
      uStack_10 = CONCAT13(uStack_10._3_1_,0x7069);
    }
    SetAIP(local_18,2);
    if (*startVoice != '\0') {
      AudioMessage(startVoice);
    }
    InfoDisplay::ClearObjectives(&infoDisplay);
    AddObjective(missionObjective,DisplayInterface::colorWhite,8.0);
    fVar1 = (this->field20_0x50)._s_0.timeLeft;
    if (!NAN(fVar1) && 0.1 < fVar1 != (fVar1 == 0.1)) {
      lVar8 = 0xf;
      lVar6 = 0x2d;
      _ftol2_sse();
      StartCockpitTimer(extraout_EAX,lVar6,lVar8);
      (this->field19_0x4c)._s_0.timerRunning = true;
    }
  }
  return;
}
