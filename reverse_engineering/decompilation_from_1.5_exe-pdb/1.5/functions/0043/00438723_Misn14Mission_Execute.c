/*
 * Entry: 00438723
 * Name: Misn14Mission::Execute
 * Namespace: Misn14Mission
 * Signature: void Execute(Misn14Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn14Mission::Execute(Misn14Mission *this)

{
  Misn14Mission_u_136 *pMVar1;
  int *piVar2;
  GameObject *this_00;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar3;
  bool bVar4;
  int iVar5;
  GameObject **ppGVar6;
  _OBJ76 *p_Var7;
  int iVar8;
  int *piVar9;
  float fVar10;
  char *pcVar11;
  int local_14;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_8;
  
  iVar5 = GetPlayerHandle();
  (this->field18_0x88)._s_0.player = iVar5;
  if ((this->field16_0x40)._s_0.start_done == false) {
    iVar5 = GetHandle("avrecy-1_recycler");
    (this->field18_0x88)._s_0.recy = iVar5;
    iVar5 = GetHandle("svrecy-1_recycler");
    (this->field18_0x88)._s_0.erecy = iVar5;
    piVar9 = &(this->field18_0x88)._s_0.base;
    iVar5 = GetHandle("sbbarr0_i76building");
    *piVar9 = iVar5;
    SetAIP("misn14.aip",2);
    AddPilot(2,0x1e);
    SetScrap(1,0x1e);
    SetScrap(2,0x2d);
    iVar5 = GetHandle("apcamr0_camerapod");
    (this->field18_0x88)._s_0.cam1 = iVar5;
    iVar5 = GetHandle("apcamr1_camerapod");
    (this->field18_0x88)._s_0.cam2 = iVar5;
    iVar5 = GetHandle("apcamr2_camerapod");
    (this->field18_0x88)._s_0.cam3 = iVar5;
    iVar5 = GetHandle("apcamr3_camerapod");
    (this->field18_0x88)._s_0.cam4 = iVar5;
    iVar5 = GetHandle("sbtowe0_turret");
    (this->field18_0x88)._s_0.tow1 = iVar5;
    iVar5 = GetHandle("sbtowe1_turret");
    (this->field18_0x88)._s_0.tow2 = iVar5;
    iVar5 = GetHandle("sbtowe55_turret");
    (this->field18_0x88)._s_0.tow3 = iVar5;
    iVar5 = GetHandle("sbtowe56_turret");
    (this->field18_0x88)._s_0.tow4 = iVar5;
    iVar5 = GetHandle("sblpow1_powerplant");
    (this->field18_0x88)._s_0.pow1 = iVar5;
    iVar5 = GetHandle("sblpow55_powerplant");
    (this->field18_0x88)._s_0.pow2 = iVar5;
    SetObjectiveName((this->field18_0x88)._s_0.cam1,"Foothill Geysers");
    SetObjectiveName((this->field18_0x88)._s_0.cam2,"Canyon Geysers");
    SetObjectiveName((this->field18_0x88)._s_0.cam3,"CCA Base");
    SetObjectiveName((this->field18_0x88)._s_0.cam4,"Plateau Geysers");
    (this->field16_0x40)._s_0.start_done = true;
    fVar10 = Get_Time();
    (this->field16_0x40)._s_0.camera1 = true;
    (this->field17_0x5c)._s_0.next_second = fVar10 + 1.0;
    CameraReady();
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.camera_time = fVar10 + 12.0;
    iVar5 = AudioMessage("misn1401.wav");
    (this->field18_0x88)._s_0.audmsg = iVar5;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetMaxHealth(*piVar9,100000.0);
      fVar10 = Get_Time();
      (this->field17_0x5c)._s_0.next_second = fVar10 + 1.0;
    }
  }
  if ((((this->field16_0x40)._s_0.camera1 != false) &&
      (CameraPath("cam_path1",2000,1000,(this->field18_0x88)._s_0.recy),
      (this->field16_0x40)._s_0.camera1 != false)) &&
     ((fVar10 = Get_Time(), (this->field17_0x5c)._s_0.camera_time < fVar10 ||
      (bVar4 = CameraCancelled(), bVar4)))) {
    (this->field16_0x40)._s_0.camera1 = false;
    (this->field16_0x40)._s_0.camera2 = true;
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.camera_time = fVar10 + 15.0;
  }
  if ((((this->field16_0x40)._s_0.camera2 != false) &&
      (CameraPath("cam_path2",2000,500,(this->field18_0x88)._s_0.recy),
      (this->field16_0x40)._s_0.camera2 != false)) &&
     ((fVar10 = Get_Time(), (this->field17_0x5c)._s_0.camera_time < fVar10 ||
      (bVar4 = CameraCancelled(), bVar4)))) {
    StopAudioMessage((this->field18_0x88)._s_0.audmsg);
    (this->field16_0x40)._s_0.camera2 = false;
    CameraFinish();
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1401.otf",DisplayInterface::colorWhite,8.0);
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.alien_time = fVar10 + 720.0;
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.beacon_time1 = fVar10 + 15.0;
  }
  fVar10 = Get_Time();
  if ((this->field17_0x5c)._s_0.beacon_time1 < fVar10) {
    AudioMessage("misn1416.wav");
    (this->field17_0x5c)._s_0.beacon_time1 = 99999.0;
    iVar5 = BuildObject("apcamr",1,"rescue1",0);
    (this->field18_0x88)._s_0.beacon1 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help1",0);
    (this->field18_0x88)._s_0.guy1 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help2",0);
    (this->field18_0x88)._s_0.guy2 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help3",0);
    (this->field18_0x88)._s_0.guy3 = iVar5;
    SetIndependence((this->field18_0x88)._s_0.guy1,0);
    SetIndependence((this->field18_0x88)._s_0.guy2,0);
    SetIndependence((this->field18_0x88)._s_0.guy3,0);
    Defend((this->field18_0x88)._s_0.guy1,1);
    Defend((this->field18_0x88)._s_0.guy2,1);
    Defend((this->field18_0x88)._s_0.guy3,1);
    SetObjectiveName((this->field18_0x88)._s_0.beacon1,"Rescue 1");
    SetObjectiveOn((this->field18_0x88)._s_0.beacon1);
  }
  pMVar1 = &this->field18_0x88;
  if (((((pMVar1->_s_0).beacon1 != 0) &&
       (fVar10 = GetDistance((this->field18_0x88)._s_0.player,(pMVar1->_s_0).beacon1),
       fVar10 < 200.0)) && ((this->field16_0x40)._s_0.rescue_reminder == false)) &&
     (fVar10 = GetDistance((this->field18_0x88)._s_0.apc,(pMVar1->_s_0).beacon1), 300.0 < fVar10)) {
    AudioMessage("misn1415.wav");
    (this->field16_0x40)._s_0.rescue_reminder = true;
  }
  if (((((this->field16_0x40)._s_0.lost == false) && ((pMVar1->_s_0).beacon1 != 0)) &&
      ((this->field16_0x40)._s_0.rescue1 == false)) &&
     (((bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy1), !bVar4 ||
       (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy2), !bVar4)) ||
      (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy3), !bVar4)))) {
    AudioMessage("misn1421.wav");
    pcVar11 = "misn14l2.des";
    fVar10 = Get_Time();
    FailMission(fVar10 + 15.0,pcVar11);
    (this->field16_0x40)._s_0.lost = true;
  }
  if (((((pMVar1->_s_0).beacon1 != 0) && (iVar5 = (this->field18_0x88)._s_0.apc, iVar5 != 0)) &&
      ((this->field16_0x40)._s_0.rescue1 == false)) &&
     (fVar10 = GetDistance(iVar5,(pMVar1->_s_0).beacon1), fVar10 < 100.0)) {
    iVar5 = (pMVar1->_s_0).beacon1;
    (this->field16_0x40)._s_0.rescue1 = true;
    Goto((this->field18_0x88)._s_0.guy1,iVar5,1);
    Goto((this->field18_0x88)._s_0.guy2,(pMVar1->_s_0).beacon1,1);
    Goto((this->field18_0x88)._s_0.guy3,(pMVar1->_s_0).beacon1,1);
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.rescue_finish1 = fVar10 + 25.0;
    AudioMessage("misn1409.wav");
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.camera_time = fVar10 + 3.0;
    CameraReady();
    (this->field16_0x40)._s_0.rescuecam1 = true;
  }
  if ((this->field16_0x40)._s_0.rescuecam1 != false) {
    iVar5 = (this->field18_0x88)._s_0.apc;
    CameraObject(iVar5,1000,1000,1000,iVar5);
    bVar4 = CameraCancelled();
    if ((bVar4) || (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.camera_time < fVar10)) {
      CameraFinish();
      (this->field16_0x40)._s_0.rescuecam1 = false;
    }
  }
  if ((((pMVar1->_s_0).beacon1 != 0) && ((this->field16_0x40)._s_0.rescue1 != false)) &&
     (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.rescue_finish1 < fVar10)) {
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy1);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy1);
    }
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy2);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy2);
    }
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy3);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy3);
    }
    bVar4 = IsAlive(pMVar1->h_array);
    if (bVar4) {
      RemoveObject((pMVar1->_s_0).beacon1);
    }
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.beacon_time2 = fVar10 + 10.0;
    CameraReady();
    AudioMessage("misn1417.wav");
    (this->field17_0x5c)._s_0.rescue_finish1 = 99999.0;
    (this->field16_0x40)._s_0.finishcam1 = true;
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.camera_time = fVar10 + 3.0;
  }
  if ((this->field16_0x40)._s_0.finishcam1 != false) {
    iVar5 = (this->field18_0x88)._s_0.apc;
    CameraObject(iVar5,1000,1000,1000,iVar5);
    bVar4 = CameraCancelled();
    if ((bVar4) || (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.camera_time < fVar10)) {
      CameraFinish();
      (this->field16_0x40)._s_0.finishcam1 = false;
    }
  }
  fVar10 = Get_Time();
  if ((this->field17_0x5c)._s_0.beacon_time2 < fVar10) {
    (this->field17_0x5c)._s_0.beacon_time2 = 99999.0;
    iVar5 = BuildObject("apcamr",1,"rescue2",0);
    (this->field18_0x88)._s_0.beacon2 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help4",0);
    (this->field18_0x88)._s_0.guy1 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help5",0);
    (this->field18_0x88)._s_0.guy2 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help6",0);
    (this->field18_0x88)._s_0.guy3 = iVar5;
    SetIndependence((this->field18_0x88)._s_0.guy1,0);
    SetIndependence((this->field18_0x88)._s_0.guy2,0);
    SetIndependence((this->field18_0x88)._s_0.guy3,0);
    Defend((this->field18_0x88)._s_0.guy1,1);
    Defend((this->field18_0x88)._s_0.guy2,1);
    Defend((this->field18_0x88)._s_0.guy3,1);
    SetObjectiveName((this->field18_0x88)._s_0.beacon2,"Rescue 2");
    SetObjectiveOn((this->field18_0x88)._s_0.beacon2);
  }
  if (((((this->field16_0x40)._s_0.lost == false) && ((this->field18_0x88)._s_0.beacon2 != 0)) &&
      ((this->field16_0x40)._s_0.rescue2 == false)) &&
     (((bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy1), !bVar4 ||
       (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy2), !bVar4)) ||
      (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy3), !bVar4)))) {
    (this->field16_0x40)._s_0.lost = true;
    AudioMessage("misn1421.wav");
    pcVar11 = "misn14l2.des";
    fVar10 = Get_Time();
    FailMission(fVar10 + 15.0,pcVar11);
  }
  piVar9 = &(this->field18_0x88)._s_0.beacon2;
  if (((*piVar9 != 0) && (iVar5 = (this->field18_0x88)._s_0.apc, iVar5 != 0)) &&
     (((this->field16_0x40)._s_0.rescue2 == false &&
      (fVar10 = GetDistance(iVar5,*piVar9), fVar10 < 100.0)))) {
    iVar5 = *piVar9;
    (this->field16_0x40)._s_0.rescue2 = true;
    Goto((this->field18_0x88)._s_0.guy1,iVar5,1);
    Goto((this->field18_0x88)._s_0.guy2,*piVar9,1);
    Goto((this->field18_0x88)._s_0.guy3,*piVar9,1);
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.rescue_finish2 = fVar10 + 25.0;
    AudioMessage("misn1409.wav");
  }
  if (((*piVar9 != 0) && ((this->field16_0x40)._s_0.rescue2 != false)) &&
     (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.rescue_finish2 < fVar10)) {
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy1);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy1);
    }
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy2);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy2);
    }
    bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy3);
    if (bVar4) {
      RemoveObject((this->field18_0x88)._s_0.guy3);
    }
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      RemoveObject(*piVar9);
    }
    AudioMessage("misn1418.wav");
    (this->field17_0x5c)._s_0.rescue_finish2 = 99999.0;
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.beacon_time3 = fVar10 + 10.0;
  }
  fVar10 = Get_Time();
  if ((this->field17_0x5c)._s_0.beacon_time3 < fVar10) {
    (this->field17_0x5c)._s_0.beacon_time3 = 99999.0;
    iVar5 = BuildObject("apcamr",1,"rescue3",0);
    (this->field18_0x88)._s_0.beacon3 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help7",0);
    (this->field18_0x88)._s_0.guy1 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help8",0);
    (this->field18_0x88)._s_0.guy2 = iVar5;
    iVar5 = BuildObject("aspilo",1,"help9",0);
    (this->field18_0x88)._s_0.guy3 = iVar5;
    SetIndependence((this->field18_0x88)._s_0.guy1,0);
    SetIndependence((this->field18_0x88)._s_0.guy2,0);
    SetIndependence((this->field18_0x88)._s_0.guy3,0);
    Defend((this->field18_0x88)._s_0.guy1,1);
    Defend((this->field18_0x88)._s_0.guy2,1);
    Defend((this->field18_0x88)._s_0.guy3,1);
    SetObjectiveName((this->field18_0x88)._s_0.beacon3,"Rescue 3");
    SetObjectiveOn((this->field18_0x88)._s_0.beacon3);
  }
  if ((((this->field16_0x40)._s_0.lost == false) && ((this->field18_0x88)._s_0.beacon3 != 0)) &&
     (((this->field16_0x40)._s_0.rescue3 == false &&
      (((bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy1), !bVar4 ||
        (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy2), !bVar4)) ||
       (bVar4 = IsAlive(&(this->field18_0x88)._s_0.guy3), !bVar4)))))) {
    (this->field16_0x40)._s_0.lost = true;
    AudioMessage("misn1421.wav");
    pcVar11 = "misn14l2.des";
    fVar10 = Get_Time();
    FailMission(fVar10 + 15.0,pcVar11);
  }
  piVar9 = &(this->field18_0x88)._s_0.beacon3;
  if ((((*piVar9 != 0) && (iVar5 = (this->field18_0x88)._s_0.apc, iVar5 != 0)) &&
      ((this->field16_0x40)._s_0.rescue3 == false)) &&
     (fVar10 = GetDistance(iVar5,*piVar9), fVar10 < 100.0)) {
    iVar5 = *piVar9;
    (this->field16_0x40)._s_0.rescue3 = true;
    Goto((this->field18_0x88)._s_0.guy1,iVar5,1);
    Goto((this->field18_0x88)._s_0.guy2,*piVar9,1);
    Goto((this->field18_0x88)._s_0.guy3,*piVar9,1);
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.rescue_finish3 = fVar10 + 25.0;
    AudioMessage("misn1409.wav");
  }
  if (((*piVar9 != 0) && ((this->field16_0x40)._s_0.rescue3 != false)) &&
     (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.rescue_finish3 < fVar10)) {
    piVar2 = &(this->field18_0x88)._s_0.guy1;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      RemoveObject(*piVar2);
    }
    piVar2 = &(this->field18_0x88)._s_0.guy2;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      RemoveObject(*piVar2);
    }
    piVar2 = &(this->field18_0x88)._s_0.guy3;
    bVar4 = IsAlive(piVar2);
    if (bVar4) {
      RemoveObject(*piVar2);
    }
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      RemoveObject(*piVar9);
    }
    AudioMessage("misn1419.wav");
    (this->field17_0x5c)._s_0.rescue_finish3 = 99999.0;
  }
  piVar9 = &(this->field18_0x88)._s_0.base;
  bVar4 = IsAlive(piVar9);
  if ((bVar4) && (fVar10 = Get_Time(), (this->field17_0x5c)._s_0.next_second < fVar10)) {
    AddHealth(*piVar9,5000.0);
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.next_second = fVar10 + 1.0;
  }
  fVar10 = Get_Time();
  if ((this->field17_0x5c)._s_0.alien_time < fVar10) {
    (this->field19_0xe4)._s_0.wave_count = (this->field19_0xe4)._s_0.wave_count + 1;
    (this->field16_0x40)._s_0.alien_attack = true;
    iVar5 = rand();
    iVar5 = iVar5 % 3;
    if (iVar5 == 0) {
      BuildObject("hvsav",3,"alien1",0);
      BuildObject("hvsav",3,"alien2",0);
      pcVar11 = "alien5";
LAB_0043931e:
      BuildObject("hvsav",3,pcVar11,0);
    }
    else {
      if (iVar5 == 1) {
        BuildObject("hvsav",3,"alien3",0);
        BuildObject("hvsav",3,"alien4",0);
        pcVar11 = "alien1";
        goto LAB_0043931e;
      }
      if (iVar5 == 2) {
        BuildObject("hvsav",3,"alien5",0);
        BuildObject("hvsav",3,"alien6",0);
        pcVar11 = "alien3";
        goto LAB_0043931e;
      }
    }
    fVar10 = Get_Time();
    (this->field17_0x5c)._s_0.alien_time = fVar10 + 180.0;
  }
  if (((this->field16_0x40)._s_0.alien_attack != false) &&
     ((this->field16_0x40)._s_0.alien_warning == false)) {
    AudioMessage("misn1403.wav");
    (this->field16_0x40)._s_0.alien_warning = true;
  }
  if ((2 < (this->field19_0xe4)._s_0.wave_count) &&
     ((this->field16_0x40)._s_0.cca_surrender == false)) {
    AudioMessage("misn1404.wav");
    AudioMessage("misn1405.wav");
    (this->field16_0x40)._s_0.cca_surrender = true;
    pvVar3 = GameObject::objectList;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_10,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    while( true ) {
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_8,pvVar3->_Mylast,(_Container_base_aux *)pvVar3);
      bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_8);
      if (bVar4) break;
      ppGVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      this_00 = *ppGVar6;
      if (this_00 == (GameObject *)0x0) {
        local_14 = 0;
      }
      else {
        local_14 = GameObject::GetHandle(this_00);
      }
      piVar9 = &this_00->_padding_;
      p_Var7 = (_OBJ76 *)(**(code **)(*piVar9 + 0x30))();
      iVar5 = IsCraft(p_Var7);
      if ((iVar5 != 0) && (iVar5 = (**(code **)(*piVar9 + 4))(), iVar5 == 2)) {
        (**(code **)(*piVar9 + 8))(0);
        bVar4 = IsOdf(local_14,"svtank");
        if ((bVar4) ||
           ((bVar4 = IsOdf(local_14,"svturr"), bVar4 || (bVar4 = IsOdf(local_14,"svfigh"), bVar4))))
        {
          Retreat(local_14,"escape",1);
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
    }
    piVar9 = &(this->field18_0x88)._s_0.base;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.pow1;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.pow2;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.tow1;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.tow2;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.tow3;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
    piVar9 = &(this->field18_0x88)._s_0.tow4;
    bVar4 = IsAlive(piVar9);
    if (bVar4) {
      SetTeamNum(*piVar9,1);
    }
  }
  if (((3 < (this->field19_0xe4)._s_0.wave_count) &&
      ((this->field16_0x40)._s_0.gen_message == false)) &&
     ((this->field16_0x40)._s_0.rescue3 != false)) {
    SetScrap(2,0);
    iVar8 = AudioMessage("misn1406.wav");
    iVar5 = (this->field18_0x88)._s_0.player;
    (this->field18_0x88)._s_0.audmsg = iVar8;
    (this->field16_0x40)._s_0.gen_message = true;
    iVar5 = GetNearestEnemy(iVar5);
    fVar10 = GetDistance((this->field18_0x88)._s_0.player,iVar5);
    if (fVar10 <= 150.0) {
      (this->field16_0x40)._s_0.camera3 = false;
    }
    else {
      (this->field16_0x40)._s_0.camera3 = true;
      fVar10 = Get_Time();
      (this->field17_0x5c)._s_0.camera_time = fVar10 + 20.0;
      CameraReady();
    }
  }
  if ((((this->field16_0x40)._s_0.camera3 != false) &&
      (CameraPath("camera_path",0x9c4,300,(this->field18_0x88)._s_0.base),
      (this->field16_0x40)._s_0.camera3 != false)) &&
     ((fVar10 = Get_Time(), (this->field17_0x5c)._s_0.camera_time < fVar10 ||
      (bVar4 = CameraCancelled(), bVar4)))) {
    StopAudioMessage((this->field18_0x88)._s_0.audmsg);
    (this->field16_0x40)._s_0.camera3 = false;
    CameraFinish();
  }
  if (4 < (this->field19_0xe4)._s_0.wave_count) {
    if (((this->field16_0x40)._s_0.rescue_message == false) &&
       ((this->field16_0x40)._s_0.rescue3 != false)) {
      SetScrap(2,0);
      AudioMessage("misn1407.wav");
      piVar9 = &(this->field18_0x88)._s_0.base;
      (this->field16_0x40)._s_0.rescue_message = true;
      bVar4 = IsAlive(piVar9);
      if (bVar4) {
        SetObjectiveOn(*piVar9);
        SetObjectiveName(*piVar9,"Rescue CCA");
      }
      else {
        FailMission(5.0,"misn14l.des");
      }
    }
    if ((((4 < (this->field19_0xe4)._s_0.wave_count) && ((this->field16_0x40)._s_0.found != false))
        && ((this->field16_0x40)._s_0.rescue_start == false)) &&
       ((this->field16_0x40)._s_0.rescue3 != false)) {
      AudioMessage("misn1408.wav");
      (this->field16_0x40)._s_0.rescue_start = true;
    }
  }
  if ((this->field16_0x40)._s_0.pick_up == false) {
    if (((this->field16_0x40)._s_0.rescue_start != false) &&
       (fVar10 = GetDistance((this->field18_0x88)._s_0.apc,(this->field18_0x88)._s_0.base),
       fVar10 < 200.0)) {
      (this->field16_0x40)._s_0.pick_up = true;
      fVar10 = Get_Time();
      (this->field17_0x5c)._s_0.pick_up_time = fVar10 + 15.0;
      AudioMessage("misn1409.wav");
    }
    if ((this->field16_0x40)._s_0.pick_up == false) goto LAB_004396e5;
  }
  fVar10 = Get_Time();
  if ((this->field17_0x5c)._s_0.pick_up_time < fVar10) {
    (this->field17_0x5c)._s_0.pick_up_time = 99999.0;
    AudioMessage("misn1410.wav");
  }
LAB_004396e5:
  if ((((this->field16_0x40)._s_0.lost == false) && ((this->field16_0x40)._s_0.pick_up != false)) &&
     (bVar4 = IsAlive(&(this->field18_0x88)._s_0.apc), !bVar4)) {
    AudioMessage("misn1412.wav");
    AudioMessage("misn1413.wav");
    pcVar11 = "misn14l3.des";
    fVar10 = Get_Time();
    FailMission(fVar10 + 10.0,pcVar11);
    (this->field16_0x40)._s_0.lost = true;
  }
  if ((((this->field16_0x40)._s_0.won == false) && ((this->field16_0x40)._s_0.pick_up != false)) &&
     (fVar10 = GetDistance((this->field18_0x88)._s_0.recy,(this->field18_0x88)._s_0.apc),
     fVar10 < 300.0)) {
    pcVar11 = "misn14w1.des";
    (this->field16_0x40)._s_0.won = true;
    fVar10 = Get_Time();
    SucceedMission(fVar10 + 10.0,pcVar11);
    AudioMessage("misn1411.wav");
  }
  if (((this->field16_0x40)._s_0.lost == false) &&
     (bVar4 = IsAlive(&(this->field18_0x88)._s_0.recy), !bVar4)) {
    AudioMessage("misn1414.wav");
    pcVar11 = "misn14l1.des";
    fVar10 = Get_Time();
    FailMission(fVar10 + 10.0,pcVar11);
    (this->field16_0x40)._s_0.lost = true;
  }
  return;
}
