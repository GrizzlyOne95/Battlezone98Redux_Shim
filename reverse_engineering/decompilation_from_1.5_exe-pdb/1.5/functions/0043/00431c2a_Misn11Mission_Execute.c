/*
 * Entry: 00431c2a
 * Name: Misn11Mission::Execute
 * Namespace: Misn11Mission
 * Signature: void Execute(Misn11Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn11Mission::Execute(Misn11Mission *this)

{
  int *piVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  int iVar4;
  GameObject **ppGVar5;
  float fVar6;
  char *pcVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  int local_8;
  
  iVar4 = GetPlayerHandle();
  bVar3 = (this->field16_0x40)._s_0.start_done;
  (this->field18_0x6c)._s_0.player = iVar4;
  if (bVar3 == false) {
    iVar4 = GetHandle("avhaul0_tug");
    (this->field18_0x6c)._s_0.tug1 = iVar4;
    iVar4 = GetHandle("avhaul1_tug");
    (this->field18_0x6c)._s_0.tug2 = iVar4;
    iVar4 = GetHandle("avhaul2_tug");
    (this->field18_0x6c)._s_0.openh = iVar4;
    iVar4 = GetHandle("svturr2_turrettank");
    (this->field18_0x6c)._s_0.turr1 = iVar4;
    iVar4 = GetHandle("second_blockade");
    (this->field18_0x6c)._s_0.turr2 = iVar4;
    iVar4 = GetHandle("svturr3_turrettank");
    (this->field18_0x6c)._s_0.turr3 = iVar4;
    iVar4 = GetHandle("apcamr3_camerapod");
    (this->field18_0x6c)._s_0.cam1 = iVar4;
    iVar4 = GetHandle("apcamr4_camerapod");
    (this->field18_0x6c)._s_0.cam2 = iVar4;
    iVar4 = GetHandle("apcamr5_camerapod");
    (this->field18_0x6c)._s_0.cam3 = iVar4;
    iVar4 = GetHandle("launch_pad");
    (this->field18_0x6c)._s_0.launch = iVar4;
    iVar4 = GetHandle("launch_pad2");
    (this->field18_0x6c)._s_0.launch2 = iVar4;
    SetObjectiveName((this->field18_0x6c)._s_0.cam1,"Waypoint 1");
    SetObjectiveName((this->field18_0x6c)._s_0.cam2,"Waypoint 2");
    SetObjectiveName((this->field18_0x6c)._s_0.cam3,"Launch Pad");
    SetObjectiveOn((this->field18_0x6c)._s_0.tug1);
    SetObjectiveName((this->field18_0x6c)._s_0.tug1,"Transport 1");
    SetObjectiveOn((this->field18_0x6c)._s_0.tug2);
    SetObjectiveName((this->field18_0x6c)._s_0.tug2,"Transport 2");
    SetObjectiveOn((this->field18_0x6c)._s_0.openh);
    SetObjectiveName((this->field18_0x6c)._s_0.openh,"Transport 3");
    SetUserTarget((this->field18_0x6c)._s_0.cam1);
    SetScrap(1,0x32);
    AudioMessage("misn1101.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1101.otf",DisplayInterface::colorWhite,8.0);
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.start_done = true;
    (this->field17_0x54)._s_0.start_delay = fVar6 + 15.0;
  }
  piVar1 = &(this->field18_0x6c)._s_0.openh;
  bVar3 = IsAlive(piVar1);
  if (bVar3) {
    AddHealth(*piVar1,300.0);
  }
  fVar6 = Get_Time();
  if ((this->field17_0x54)._s_0.start_delay < fVar6) {
    AudioMessage("misn1102.wav");
    (this->field17_0x54)._s_0.start_delay = 99999.0;
    Goto((this->field18_0x6c)._s_0.tug1,"base1",1);
    Goto((this->field18_0x6c)._s_0.tug2,"base1",1);
    Goto(*piVar1,"base1",0);
  }
  if (((this->field16_0x40)._s_0.betrayal == false) &&
     (fVar6 = GetDistance((this->field18_0x6c)._s_0.cam1,*piVar1), fVar6 < 50.0)) {
    fVar6 = Get_Time();
    iVar4 = *piVar1;
    (this->field17_0x54)._s_0.betrayal_time = fVar6 + 15.0;
    Goto(iVar4,"openheimer",1);
    (this->field16_0x40)._s_0.betrayal = true;
  }
  fVar6 = Get_Time();
  if ((this->field17_0x54)._s_0.betrayal_time < fVar6) {
    (this->field17_0x54)._s_0.betrayal_time = 99999.0;
    AudioMessage("misn1103.wav");
    AudioMessage("misn1104.wav");
    SetTeamNum((this->field18_0x6c)._s_0.openh,2);
    Defend((this->field18_0x6c)._s_0.turr1,0);
    Defend((this->field18_0x6c)._s_0.turr3,0);
    AudioMessage("misn1105.wav");
    BuildObject("svfigh",2,"strike1",0);
    pvVar2 = GameObject::objectList;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_10,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_18,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_18);
      if (bVar3) break;
      ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      if (*ppGVar5 == (GameObject *)0x0) {
        local_8 = 0;
      }
      else {
        local_8 = GameObject::GetHandle(*ppGVar5);
      }
      bVar3 = IsOdf(local_8,"svfigh");
      if (bVar3) {
        Goto(local_8,"strike_path1",0);
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
    }
    (this->field16_0x40)._s_0.betrayal_message = true;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1102.otf",DisplayInterface::colorWhite,8.0);
  }
  if (((this->field16_0x40)._s_0.betrayal_message != false) &&
     ((this->field16_0x40)._s_0.pursuit_warning == false)) {
    piVar1 = &(this->field18_0x6c)._s_0.turr1;
    bVar3 = IsAlive(piVar1);
    if ((bVar3) && (fVar6 = GetDistance(*piVar1,(this->field18_0x6c)._s_0.player), fVar6 != 0.0)) {
      AudioMessage("misn1106.wav");
      (this->field16_0x40)._s_0.pursuit_warning = true;
    }
  }
  piVar1 = &(this->field18_0x6c)._s_0.tug1;
  fVar6 = GetDistance((this->field18_0x6c)._s_0.cam1,*piVar1);
  if (((fVar6 < 50.0) ||
      (fVar6 = GetDistance((this->field18_0x6c)._s_0.cam1,(this->field18_0x6c)._s_0.player),
      fVar6 < 50.0)) && ((this->field16_0x40)._s_0.check1 == false)) {
    iVar4 = (this->field18_0x6c)._s_0.cam2;
    (this->field16_0x40)._s_0.check1 = true;
    SetUserTarget(iVar4);
  }
  fVar6 = GetDistance(*piVar1,"check2",1);
  if (50.0 <= fVar6) {
LAB_0043210a:
    if ((this->field16_0x40)._s_0.check2 != false) goto LAB_00432110;
LAB_00432159:
    if ((this->field16_0x40)._s_0.restart != false) goto LAB_00432163;
LAB_00432229:
    if ((this->field16_0x40)._s_0.launch_attack == false) goto LAB_004322b9;
  }
  else {
    if ((this->field16_0x40)._s_0.check2 == false) {
      SetObjectiveOff((this->field18_0x6c)._s_0.openh);
      iVar4 = (this->field18_0x6c)._s_0.cam3;
      (this->field16_0x40)._s_0.check2 = true;
      SetUserTarget(iVar4);
      AudioMessage("misn1107.wav");
      BuildObject("svfigh",2,"strike2",0);
      pvVar2 = GameObject::objectList;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_10,GameObject::objectList->_Myfirst,
                 (_Container_base_aux *)GameObject::objectList);
      while( true ) {
        std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
        _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                  (&local_18,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
        bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                          (&local_10,&local_18);
        if (bVar3) break;
        ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                            (&local_10);
        if (*ppGVar5 == (GameObject *)0x0) {
          local_8 = 0;
        }
        else {
          local_8 = GameObject::GetHandle(*ppGVar5);
        }
        bVar3 = IsOdf(local_8,"svfigh");
        if (bVar3) {
          Goto(local_8,"strike_path2",0);
        }
        std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
                  (&local_10);
      }
      goto LAB_0043210a;
    }
LAB_00432110:
    if ((this->field16_0x40)._s_0.restart == false) {
      bVar3 = IsAlive(&(this->field18_0x6c)._s_0.turr2);
      if (!bVar3) {
        AudioMessage("misn1102.wav");
        Goto((this->field18_0x6c)._s_0.tug1,"base2",1);
        Goto((this->field18_0x6c)._s_0.tug2,"base2",1);
        (this->field16_0x40)._s_0.restart = true;
      }
      goto LAB_00432159;
    }
LAB_00432163:
    if ((this->field16_0x40)._s_0.launch_attack == false) {
      fVar6 = GetDistance((this->field18_0x6c)._s_0.launch,(this->field18_0x6c)._s_0.player);
      if ((fVar6 < 450.0) ||
         (fVar6 = GetDistance((this->field18_0x6c)._s_0.launch,(this->field18_0x6c)._s_0.tug1),
         fVar6 < 450.0)) {
        iVar4 = BuildObject("svtank",2,"launch_attack",0);
        (this->field18_0x6c)._s_0.tank1 = iVar4;
        iVar4 = BuildObject("svtank",2,"launch_attack",0);
        (this->field18_0x6c)._s_0.tank2 = iVar4;
        AddHealth((this->field18_0x6c)._s_0.launch,-0.9);
        AudioMessage("misn1108.wav");
        Attack((this->field18_0x6c)._s_0.tank1,(this->field18_0x6c)._s_0.launch,1);
        Attack((this->field18_0x6c)._s_0.tank2,(this->field18_0x6c)._s_0.launch,1);
        (this->field16_0x40)._s_0.launch_attack = true;
      }
      goto LAB_00432229;
    }
  }
  bVar3 = IsAlive(&(this->field18_0x6c)._s_0.launch);
  if ((!bVar3) && ((this->field16_0x40)._s_0.launch_gone == false)) {
    AudioMessage("misn1109.wav");
    (this->field16_0x40)._s_0.launch_gone = true;
    fVar6 = Get_Time();
    (this->field17_0x54)._s_0.escape_time = fVar6 + 40.0;
  }
  if ((((this->field16_0x40)._s_0.launch_attack != false) &&
      (bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tank1), !bVar3)) &&
     (bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tank2), !bVar3)) {
    piVar1 = &(this->field18_0x6c)._s_0.launch;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      RemoveObject(*piVar1);
      (this->field16_0x40)._s_0.launch_gone = true;
      fVar6 = Get_Time();
      (this->field17_0x54)._s_0.escape_time = fVar6 + 10.0;
    }
  }
LAB_004322b9:
  if (((this->field16_0x40)._s_0.launch_gone != false) &&
     (fVar6 = Get_Time(), (this->field17_0x54)._s_0.escape_time < fVar6)) {
    Goto((this->field18_0x6c)._s_0.tug1,"escape",1);
    Goto((this->field18_0x6c)._s_0.tug2,"escape",1);
    AudioMessage("misn1110.wav");
    SetObjectiveOn((this->field18_0x6c)._s_0.launch2);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1103.otf",DisplayInterface::colorWhite,8.0);
    SetObjectiveName((this->field18_0x6c)._s_0.launch2,"Launch Pad 2");
    (this->field17_0x54)._s_0.escape_time = 99999.0;
    (this->field16_0x40)._s_0.escape_start = true;
    fVar6 = Get_Time();
    (this->field17_0x54)._s_0.last_wave_time = fVar6 + 15.0;
  }
  if (((this->field16_0x40)._s_0.last_wave == false) &&
     (fVar6 = Get_Time(), (this->field17_0x54)._s_0.last_wave_time < fVar6)) {
    BuildObject("svfigh",2,"strike2",0);
    BuildObject("svfigh",2,"strike2",0);
    pvVar2 = GameObject::objectList;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_10,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_18,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_18);
      if (bVar3) break;
      ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      if (*ppGVar5 == (GameObject *)0x0) {
        local_8 = 0;
      }
      else {
        local_8 = GameObject::GetHandle(*ppGVar5);
      }
      bVar3 = IsOdf(local_8,"svfigh");
      if (bVar3) {
        Attack(local_8,(this->field18_0x6c)._s_0.tug2,1);
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
    }
    iVar4 = BuildObject("svfigh",2,(this->field18_0x6c)._s_0.launch2);
    Attack(iVar4,(this->field18_0x6c)._s_0.player,1);
    BuildObject("apcamr",1,"last_camera",0);
    (this->field17_0x54)._s_0.last_wave_time = 99999.0;
    (this->field16_0x40)._s_0.last_wave = true;
  }
  if (((this->field16_0x40)._s_0.lost == false) &&
     (((bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tug1), !bVar3 ||
       (bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tug2), !bVar3)) ||
      (((this->field16_0x40)._s_0.betrayal == false &&
       (bVar3 = IsAlive(&(this->field18_0x6c)._s_0.openh), !bVar3)))))) {
    if ((this->field16_0x40)._s_0.betrayal != false) {
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn1102.otf",DisplayInterface::colorWhite,8.0);
    }
    AudioMessage("misn1111.wav");
    AudioMessage("misn1112.wav");
    (this->field16_0x40)._s_0.lost = true;
    pcVar7 = "misn11l1.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar7);
  }
  if ((this->field16_0x40)._s_0.last_wave != false) {
    if (((this->field16_0x40)._s_0.got_there1 == false) &&
       (fVar6 = GetDistance((this->field18_0x6c)._s_0.player,(this->field18_0x6c)._s_0.launch2),
       fVar6 < 200.0)) {
      (this->field16_0x40)._s_0.got_there1 = true;
    }
    if ((this->field16_0x40)._s_0.last_wave != false) {
      if (((this->field16_0x40)._s_0.got_there2 == false) &&
         (fVar6 = GetDistance((this->field18_0x6c)._s_0.tug1,(this->field18_0x6c)._s_0.launch2),
         fVar6 < 200.0)) {
        (this->field16_0x40)._s_0.got_there2 = true;
      }
      if ((((this->field16_0x40)._s_0.last_wave != false) &&
          ((this->field16_0x40)._s_0.got_there3 == false)) &&
         (fVar6 = GetDistance((this->field18_0x6c)._s_0.tug2,(this->field18_0x6c)._s_0.launch2),
         fVar6 < 200.0)) {
        (this->field16_0x40)._s_0.got_there3 = true;
      }
    }
  }
  if ((((((this->field16_0x40)._s_0.won == false) && ((this->field16_0x40)._s_0.last_wave != false))
       && ((bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tug1), bVar3 &&
           ((bVar3 = IsAlive(&(this->field18_0x6c)._s_0.tug2), bVar3 &&
            ((this->field16_0x40)._s_0.got_there1 != false)))))) &&
      ((this->field16_0x40)._s_0.got_there2 != false)) &&
     ((this->field16_0x40)._s_0.got_there3 != false)) {
    AudioMessage("misn1113.wav");
    (this->field16_0x40)._s_0.won = true;
    pcVar7 = "misn11w1.des";
    fVar6 = Get_Time();
    SucceedMission(fVar6 + 15.0,pcVar7);
  }
  return;
}
