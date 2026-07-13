/*
 * Entry: 0042de61
 * Name: Misn09Mission::Execute
 * Namespace: Misn09Mission
 * Signature: void Execute(Misn09Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn09Mission::Execute(Misn09Mission *this)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  bool bVar4;
  int iVar5;
  float fVar6;
  long lVar7;
  char *pcVar8;
  
  if ((this->field16_0x40)._s_0.relic_free != false) {
    piVar1 = &(this->field18_0xec)._s_0.relic;
    bVar4 = IsAlive(piVar1);
    if (bVar4) {
      piVar2 = &(this->field18_0xec)._s_0.tugger;
      iVar5 = GetTug(*piVar1);
      *piVar2 = iVar5;
      bVar4 = IsAlive(piVar2);
      if (bVar4) {
        iVar5 = GetTeamNum(*piVar2);
        (this->field16_0x40)._s_0.relic_free = false;
        if (iVar5 == 1) {
          (this->field16_0x40)._s_0.relic_secure = true;
        }
        else {
          iVar5 = (this->field18_0xec)._s_0.ccatug;
          (this->field16_0x40)._s_0.relic_seized = true;
          *piVar2 = iVar5;
        }
      }
    }
  }
  if (((this->field16_0x40)._s_0.relic_secure != false) &&
     (bVar4 = IsAlive(&(this->field18_0xec)._s_0.tugger), !bVar4)) {
    (this->field16_0x40)._s_0.relic_free = true;
    (this->field16_0x40)._s_0.relic_secure = false;
  }
  if (((this->field16_0x40)._s_0.relic_seized != false) &&
     (bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccatug), !bVar4)) {
    (this->field16_0x40)._s_0.relic_free = true;
    (this->field16_0x40)._s_0.relic_seized = false;
  }
  piVar1 = &(this->field18_0xec)._s_0.relic;
  bVar4 = IsAlive(piVar1);
  if (bVar4) {
    piVar2 = &(this->field18_0xec)._s_0.ccatug;
    bVar4 = IsAlive(piVar2);
    if (((bVar4) && ((this->field16_0x40)._s_0.relic_free != false)) &&
       ((this->field16_0x40)._s_0.tug_underway == false)) {
      Pickup(*piVar2,*piVar1,1);
      (this->field16_0x40)._s_0.tug_underway = true;
    }
    if (((this->field16_0x40)._s_0.relic_seized != false) &&
       ((this->field16_0x40)._s_0.head_4_pad == false)) {
      Dropoff(*piVar2,"soviet_path",1);
      (this->field16_0x40)._s_0.head_4_pad = true;
    }
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccatug);
  if (!bVar4) {
    (this->field16_0x40)._s_0.tug_underway = false;
    (this->field16_0x40)._s_0.head_4_pad = false;
  }
  iVar5 = GetPlayerHandle();
  (this->field18_0xec)._s_0.user = iVar5;
  if ((this->field16_0x40)._s_0.start_done == false) {
    CameraReady();
    Defend((this->field18_0xec)._s_0.nsdfmuf,1);
    SetScrap(2,0x28);
    SetPilot(2,0x28);
    Follow((this->field18_0xec)._s_0.nsdfrig,(this->field18_0xec)._s_0.nsdfmuf,1);
    Follow((this->field18_0xec)._s_0.avscav1,(this->field18_0xec)._s_0.nsdfmuf,1);
    Follow((this->field18_0xec)._s_0.avscav2,(this->field18_0xec)._s_0.nsdfmuf,1);
    Follow((this->field18_0xec)._s_0.avscav3,(this->field18_0xec)._s_0.nsdfmuf,1);
    Follow((this->field18_0xec)._s_0.nsdfslf,(this->field18_0xec)._s_0.nsdfrig,0);
    Defend((this->field18_0xec)._s_0.ccaturret1,1);
    Defend((this->field18_0xec)._s_0.ccaturret2,1);
    Defend((this->field18_0xec)._s_0.ccaturret3,1);
    Defend((this->field18_0xec)._s_0.ccaturret4,1);
    Defend((this->field18_0xec)._s_0.ccaturret5,1);
    Defend((this->field18_0xec)._s_0.ccaturret6,1);
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.camera_ready_time = fVar6 + 6.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.muf_check = fVar6 + 3.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.first_warning_time = fVar6 + 700.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.second_warning_time = fVar6 + 1000.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.third_warning_time = fVar6 + 1300.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.unit_check = fVar6 + 1360.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.atril_check = fVar6 + 15.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.player_camera_time = fVar6 + 11.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.deploy_check = fVar6 + 6.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.charon_check = fVar6 + 30.0;
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.next_shot_time = fVar6 + 22.0;
    SetObjectiveName((this->field18_0xec)._s_0.nav1,"Choke Point");
    (this->field16_0x40)._s_0.start_camera1 = true;
    (this->field16_0x40)._s_0.start_done = true;
  }
  if ((this->field16_0x40)._s_0.start_camera1 != false) {
    CameraPath("camera_circle",0x177,0x2ee,(this->field18_0xec)._s_0.key_scrap);
  }
  if (((this->field16_0x40)._s_0.player_camera_off == false) &&
     ((fVar6 = Get_Time(), (this->field17_0x78)._s_0.next_shot_time < fVar6 ||
      (bVar4 = CameraCancelled(), bVar4)))) {
    CameraFinish();
    (this->field16_0x40)._s_0.start_camera1 = false;
    (this->field16_0x40)._s_0.player_camera_off = true;
  }
  bVar4 = CameraCancelled();
  if (bVar4) {
    StopAudioMessage((this->field19_0x1c8)._s_0.audmsg);
  }
  fVar6 = Get_Time();
  if (((this->field17_0x78)._s_0.camera_ready_time < fVar6) &&
     ((this->field16_0x40)._s_0.opening_vo == false)) {
    iVar5 = AudioMessage("misn0900.wav");
    (this->field19_0x1c8)._s_0.audmsg = iVar5;
    (this->field16_0x40)._s_0.opening_vo = true;
  }
  if ((this->field16_0x40)._s_0.opening_vo == false) {
LAB_0042e208:
    if ((this->field16_0x40)._s_0.muf_gobaby != false) goto LAB_0042e211;
  }
  else {
    if ((this->field16_0x40)._s_0.muf_gobaby == false) {
      bVar4 = IsAudioMessageDone((this->field19_0x1c8)._s_0.audmsg);
      if (bVar4) {
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn0900.otf",DisplayInterface::colorWhite,8.0);
        Goto((this->field18_0xec)._s_0.nsdfmuf,"return_path",1);
        (this->field16_0x40)._s_0.muf_gobaby = true;
      }
      goto LAB_0042e208;
    }
LAB_0042e211:
    fVar6 = Get_Time();
    if (((this->field17_0x78)._s_0.muf_check < fVar6) &&
       ((this->field16_0x40)._s_0.muf_contact == false)) {
      fVar6 = Get_Time();
      iVar5 = (this->field18_0xec)._s_0.nsdfmuf;
      iVar3 = (this->field18_0xec)._s_0.user;
      (this->field17_0x78)._s_0.muf_check = fVar6 + 1.0;
      fVar6 = GetDistance(iVar3,iVar5);
      if (fVar6 < 70.0) {
        Stop((this->field18_0xec)._s_0.nsdfmuf,0);
        Stop((this->field18_0xec)._s_0.nsdfslf,0);
        Defend((this->field18_0xec)._s_0.nsdfrig,0);
        SetScrap(1,0x14);
        SetPilot(1,7);
        AudioMessage("misn0905.wav");
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.muf_contact = true;
        (this->field17_0x78)._s_0.movie_time = fVar6 + 7.0;
      }
    }
  }
  if (((this->field16_0x40)._s_0.objective1 == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.atril_check < fVar6)) {
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.atril_check = fVar6 + 15.0;
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret1);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret1,1);
    }
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret2);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret2,1);
    }
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret3);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret3,1);
    }
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret4);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret4,1);
    }
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret5);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret5,1);
    }
    bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret6);
    if (bVar4) {
      Defend((this->field18_0xec)._s_0.ccaturret6,1);
    }
  }
  fVar6 = Get_Time();
  if (fVar6 <= (this->field17_0x78)._s_0.deploy_check) {
LAB_0042e3ea:
    if (((this->field16_0x40)._s_0.muf_deployed != false) ||
       (bVar4 = IsAlive(&(this->field18_0xec)._s_0.avsilo), bVar4)) goto LAB_0042e400;
  }
  else {
    if ((this->field16_0x40)._s_0.muf_deployed == false) {
      fVar6 = Get_Time();
      piVar1 = &(this->field18_0xec)._s_0.nsdfmuf;
      (this->field17_0x78)._s_0.deploy_check = fVar6 + 2.0;
      bVar4 = IsAlive(piVar1);
      if ((bVar4) && (bVar4 = IsDeployed(*piVar1), bVar4)) {
        (this->field16_0x40)._s_0.muf_deployed = true;
      }
      goto LAB_0042e3ea;
    }
LAB_0042e400:
    if ((this->field16_0x40)._s_0.scavs_alive == false) {
      Stop((this->field18_0xec)._s_0.avscav1,0);
      Stop((this->field18_0xec)._s_0.avscav2,0);
      Stop((this->field18_0xec)._s_0.avscav3,0);
      (this->field16_0x40)._s_0.scavs_alive = true;
    }
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret6);
  if ((((bVar4) && ((this->field16_0x40)._s_0.muf_contact != false)) &&
      (fVar6 = Get_Time(), (this->field17_0x78)._s_0.movie_time < fVar6)) &&
     ((this->field16_0x40)._s_0.camera_ready == false)) {
    CameraReady();
    fVar6 = Get_Time();
    (this->field16_0x40)._s_0.camera_ready = true;
    (this->field17_0x78)._s_0.cam5_time = fVar6 + 7.0;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x78)._s_0.recon_message_time < fVar6) &&
     ((this->field16_0x40)._s_0.recon_artil == false)) {
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.recon_message_time = fVar6 + 1.0;
    AudioMessage("misn0913.wav");
    (this->field16_0x40)._s_0.recon_artil = true;
  }
  fVar6 = Get_Time();
  if (((this->field17_0x78)._s_0.recon_message_time < fVar6) &&
     ((this->field16_0x40)._s_0.base_warning == false)) {
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0xec)._s_0.nav1;
    (this->field17_0x78)._s_0.recon_message_time = fVar6 + 2.0;
    bVar4 = IsAlive(piVar1);
    if ((!bVar4) || (fVar6 = GetDistance((this->field18_0xec)._s_0.user,*piVar1), 100.0 <= fVar6)) {
      piVar1 = &(this->field18_0xec)._s_0.cca5;
      bVar4 = IsAlive(piVar1);
      if ((!bVar4) || (fVar6 = GetDistance((this->field18_0xec)._s_0.user,*piVar1), 400.0 <= fVar6))
      {
        piVar1 = &(this->field18_0xec)._s_0.cca6;
        bVar4 = IsAlive(piVar1);
        if ((!bVar4) ||
           (fVar6 = GetDistance((this->field18_0xec)._s_0.user,*piVar1), 400.0 <= fVar6))
        goto LAB_0042e574;
      }
    }
    AudioMessage("misn0914.wav");
    (this->field16_0x40)._s_0.base_warning = true;
  }
LAB_0042e574:
  if (((this->field16_0x40)._s_0.camera_ready == false) ||
     ((this->field16_0x40)._s_0.cam2_on != false)) {
LAB_0042e5b0:
    if ((this->field16_0x40)._s_0.cam1_on != false) goto LAB_0042e5b5;
LAB_0042e5f9:
    if ((this->field16_0x40)._s_0.cam2_on != false) goto LAB_0042e5fe;
LAB_0042e642:
    if ((this->field16_0x40)._s_0.cam3_on != false) goto LAB_0042e647;
LAB_0042e68b:
    if ((this->field16_0x40)._s_0.cam4_on != false) goto LAB_0042e690;
LAB_0042e6d4:
    if ((this->field16_0x40)._s_0.cam5_on != false) goto LAB_0042e6d9;
  }
  else {
    iVar5 = (this->field18_0xec)._s_0.ccaturret6;
    CameraObject(iVar5,3000,3000,3000,iVar5);
    if ((this->field16_0x40)._s_0.cam1_on == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.cam1_on = true;
      (this->field17_0x78)._s_0.cam1_time = fVar6 + 2.0;
      goto LAB_0042e5b0;
    }
LAB_0042e5b5:
    fVar6 = Get_Time();
    if ((fVar6 <= (this->field17_0x78)._s_0.cam1_time) ||
       ((this->field16_0x40)._s_0.cam3_on != false)) goto LAB_0042e5f9;
    iVar5 = (this->field18_0xec)._s_0.ccaturret5;
    CameraObject(iVar5,3000,3000,3000,iVar5);
    if ((this->field16_0x40)._s_0.cam2_on == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.cam2_on = true;
      (this->field17_0x78)._s_0.cam2_time = fVar6 + 2.0;
      goto LAB_0042e5f9;
    }
LAB_0042e5fe:
    fVar6 = Get_Time();
    if ((fVar6 <= (this->field17_0x78)._s_0.cam2_time) ||
       ((this->field16_0x40)._s_0.cam4_on != false)) goto LAB_0042e642;
    iVar5 = (this->field18_0xec)._s_0.ccaturret4;
    CameraObject(iVar5,3000,3000,3000,iVar5);
    if ((this->field16_0x40)._s_0.cam3_on == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.cam3_on = true;
      (this->field17_0x78)._s_0.cam3_time = fVar6 + 2.0;
      goto LAB_0042e642;
    }
LAB_0042e647:
    fVar6 = Get_Time();
    if ((fVar6 <= (this->field17_0x78)._s_0.cam3_time) ||
       ((this->field16_0x40)._s_0.cam5_on != false)) goto LAB_0042e68b;
    iVar5 = (this->field18_0xec)._s_0.ccaturret3;
    CameraObject(iVar5,3000,3000,3000,iVar5);
    if ((this->field16_0x40)._s_0.cam4_on == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.cam4_on = true;
      (this->field17_0x78)._s_0.cam4_time = fVar6 + 2.0;
      goto LAB_0042e68b;
    }
LAB_0042e690:
    fVar6 = Get_Time();
    if ((fVar6 <= (this->field17_0x78)._s_0.cam4_time) ||
       ((this->field16_0x40)._s_0.cam_off != false)) goto LAB_0042e6d4;
    iVar5 = (this->field18_0xec)._s_0.ccaturret2;
    CameraObject(iVar5,3000,3000,3000,iVar5);
    if ((this->field16_0x40)._s_0.cam5_on == false) {
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.cam5_on = true;
      (this->field17_0x78)._s_0.cam5_time = fVar6 + 2.0;
      goto LAB_0042e6d4;
    }
LAB_0042e6d9:
    fVar6 = Get_Time();
    if (((this->field17_0x78)._s_0.cam5_time < fVar6) &&
       ((this->field16_0x40)._s_0.cam_off == false)) {
      CameraFinish();
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0900.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0901.otf",DisplayInterface::colorWhite,8.0);
      Stop((this->field18_0xec)._s_0.nsdfrig,0);
      SetAIP("misn09.aip",2);
      (this->field16_0x40)._s_0.cam_off = true;
    }
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccarecycle);
  if ((bVar4) && ((this->field16_0x40)._s_0.turret1_set == false)) {
    iVar5 = BuildObject("svturr",2,"post1",0);
    (this->field18_0xec)._s_0.cca1 = iVar5;
    (this->field16_0x40)._s_0.turret1_set = true;
    Defend(iVar5,1);
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccarecycle);
  if ((bVar4) && ((this->field16_0x40)._s_0.turret2_set == false)) {
    iVar5 = BuildObject("svturr",2,"post2",0);
    (this->field18_0xec)._s_0.cca2 = iVar5;
    (this->field16_0x40)._s_0.turret2_set = true;
    Defend(iVar5,1);
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccarecycle);
  if ((bVar4) && ((this->field16_0x40)._s_0.turret3_set == false)) {
    iVar5 = BuildObject("svturr",2,"post3",0);
    (this->field18_0xec)._s_0.cca3 = iVar5;
    (this->field16_0x40)._s_0.turret3_set = true;
    Defend(iVar5,1);
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccarecycle);
  if ((bVar4) && ((this->field16_0x40)._s_0.turret4_set == false)) {
    iVar5 = BuildObject("svturr",2,"post4",0);
    (this->field18_0xec)._s_0.cca4 = iVar5;
    (this->field16_0x40)._s_0.turret4_set = true;
    Defend(iVar5,1);
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret1);
  if ((((!bVar4) && (bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret2), !bVar4)) &&
      (bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret3), !bVar4)) &&
     (((bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret4), !bVar4 &&
       (bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret5), !bVar4)) &&
      ((bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccaturret6), !bVar4 &&
       ((this->field16_0x40)._s_0.objective1 == false)))))) {
    AudioMessage("misn0904.wav");
    Stop((this->field18_0xec)._s_0.avscav1,0);
    Stop((this->field18_0xec)._s_0.avscav2,0);
    Stop((this->field18_0xec)._s_0.avscav3,0);
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0901.otf",DisplayInterface::colorGreen,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0902.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0903.otf",DisplayInterface::colorWhite,8.0);
    if ((this->field16_0x40)._s_0.third_warning == false) {
      SetAIP("misn09a.aip",2);
    }
    (this->field16_0x40)._s_0.objective1 = true;
  }
  if (((this->field16_0x40)._s_0.first_warning == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.first_warning_time < fVar6)) {
    AudioMessage("misn0901.wav");
    (this->field16_0x40)._s_0.first_warning = true;
  }
  if (((this->field16_0x40)._s_0.second_warning == false) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.second_warning_time < fVar6)) {
    AudioMessage("misn0902.wav");
    (this->field16_0x40)._s_0.second_warning = true;
  }
  if ((this->field16_0x40)._s_0.third_warning == false) {
    fVar6 = Get_Time();
    if ((this->field17_0x78)._s_0.third_warning_time < fVar6) {
      fVar6 = Get_Time();
      iVar5 = (this->field18_0xec)._s_0.convoy_geyser;
      iVar3 = (this->field18_0xec)._s_0.user;
      (this->field17_0x78)._s_0.third_warning_time = fVar6 + 11.0;
      fVar6 = GetDistance(iVar3,iVar5);
      if (500.0 < fVar6) {
        iVar5 = BuildObject("obdata",0,(this->field18_0xec)._s_0.convoy_geyser);
        (this->field18_0xec)._s_0.relic = iVar5;
        iVar5 = BuildObject("svhaul",2,"spawn1",0);
        (this->field18_0xec)._s_0.ccatug = iVar5;
        iVar5 = BuildObject("svfigh",2,"spawn2",0);
        (this->field18_0xec)._s_0.convoy1 = iVar5;
        iVar5 = BuildObject("svfigh",2,"spawn2",0);
        (this->field18_0xec)._s_0.convoy2 = iVar5;
        iVar5 = BuildObject("svfigh",2,"spawn2",0);
        (this->field18_0xec)._s_0.convoy3 = iVar5;
        iVar5 = BuildObject("svfigh",2,"spawn3",0);
        (this->field18_0xec)._s_0.convoy4 = iVar5;
        iVar5 = BuildObject("svtank",2,"spawn3",0);
        (this->field18_0xec)._s_0.convoy5 = iVar5;
        iVar5 = BuildObject("svtank",2,"spawn3",0);
        (this->field18_0xec)._s_0.convoy6 = iVar5;
        iVar5 = BuildObject("svtank",2,"spawn4",0);
        (this->field18_0xec)._s_0.convoy7 = iVar5;
        iVar5 = BuildObject("svtank",2,"spawn4",0);
        (this->field18_0xec)._s_0.convoy8 = iVar5;
        iVar5 = BuildObject("svapc",2,"spawn4",0);
        (this->field18_0xec)._s_0.convoy9 = iVar5;
        iVar5 = BuildObject("svapc",2,"spawn4",0);
        (this->field18_0xec)._s_0.convoy0 = iVar5;
        Defend((this->field18_0xec)._s_0.convoy1,1);
        Defend((this->field18_0xec)._s_0.convoy2,1);
        Defend((this->field18_0xec)._s_0.convoy3,1);
        Defend((this->field18_0xec)._s_0.convoy4,1);
        Defend((this->field18_0xec)._s_0.convoy5,1);
        Defend((this->field18_0xec)._s_0.convoy6,1);
        Defend((this->field18_0xec)._s_0.convoy7,1);
        Defend((this->field18_0xec)._s_0.convoy8,1);
        Defend((this->field18_0xec)._s_0.convoy9,1);
        Defend((this->field18_0xec)._s_0.convoy0,1);
        if ((this->field16_0x40)._s_0.objective1 == false) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          InfoDisplay::AddObjective(&infoDisplay,"misn0901.otf",DisplayInterface::colorRed,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn0902.otf",DisplayInterface::colorWhite,8.0);
          InfoDisplay::AddObjective(&infoDisplay,"misn0903.otf",DisplayInterface::colorWhite,8.0);
        }
        fVar6 = Get_Time();
        (this->field17_0x78)._s_0.win_check = fVar6 + 5.0;
        SetAIP("misn09b.aip",2);
        (this->field16_0x40)._s_0.relic_free = true;
        (this->field16_0x40)._s_0.third_warning = true;
      }
    }
    if ((this->field16_0x40)._s_0.third_warning != false) goto LAB_0042ec14;
LAB_0042ed06:
    if ((this->field16_0x40)._s_0.convoy_started != false) goto LAB_0042ed0b;
LAB_0042ed47:
    if ((this->field16_0x40)._s_0.convoy_cam_ready != false) goto LAB_0042ed4c;
  }
  else {
LAB_0042ec14:
    if ((this->field16_0x40)._s_0.relic_seized == false) goto LAB_0042ed06;
    if ((this->field16_0x40)._s_0.convoy_started == false) {
      piVar1 = &(this->field18_0xec)._s_0.relic;
      SetObjectiveOn(*piVar1);
      SetObjectiveName(*piVar1,"Alien Relic");
      piVar1 = &(this->field18_0xec)._s_0.ccatug;
      Goto(*piVar1,"soviet_path",1);
      Follow((this->field18_0xec)._s_0.convoy1,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy2,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy3,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy4,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy5,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy6,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy7,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy8,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy9,*piVar1,1);
      Follow((this->field18_0xec)._s_0.convoy0,*piVar1,1);
      fVar6 = Get_Time();
      (this->field16_0x40)._s_0.convoy_started = true;
      (this->field17_0x78)._s_0.convoy_cam_time = fVar6 + 7.0;
      goto LAB_0042ed06;
    }
LAB_0042ed0b:
    if ((this->field16_0x40)._s_0.convoy_cam_ready == false) {
      fVar6 = Get_Time();
      if ((this->field17_0x78)._s_0.convoy_cam_time < fVar6) {
        AudioMessage("misn0903.wav");
        CameraReady();
        fVar6 = Get_Time();
        (this->field16_0x40)._s_0.convoy_cam_ready = true;
        (this->field17_0x78)._s_0.convoy_cam_time = fVar6 + 18.0;
      }
      goto LAB_0042ed47;
    }
LAB_0042ed4c:
    if ((this->field16_0x40)._s_0.convoy_cam_off == false) {
      piVar1 = &(this->field19_0x1c8)._s_0.y;
      CameraPath("convoy_cam_path",*piVar1,0x47e,(this->field18_0xec)._s_0.ccatug);
      *piVar1 = *piVar1 + -4;
    }
    if ((((this->field16_0x40)._s_0.convoy_cam_ready != false) &&
        ((this->field16_0x40)._s_0.convoy_cam_off == false)) &&
       ((fVar6 = Get_Time(), (this->field17_0x78)._s_0.convoy_cam_time < fVar6 ||
        (bVar4 = CameraCancelled(), bVar4)))) {
      CameraFinish();
      (this->field16_0x40)._s_0.convoy_cam_off = true;
    }
  }
  piVar1 = &(this->field18_0xec)._s_0.charon;
  bVar4 = IsAlive(piVar1);
  if (bVar4) {
    if ((this->field16_0x40)._s_0.charon_found == false) {
      fVar6 = Get_Time();
      if ((this->field17_0x78)._s_0.charon_check < fVar6) {
        fVar6 = Get_Time();
        iVar5 = *piVar1;
        iVar3 = (this->field18_0xec)._s_0.user;
        (this->field17_0x78)._s_0.charon_check = fVar6 + 2.0;
        fVar6 = GetDistance(iVar3,iVar5);
        if (fVar6 < 70.0) {
          AudioMessage("misn0915.wav");
          (this->field16_0x40)._s_0.charon_found = true;
        }
      }
      goto LAB_0042ee06;
    }
  }
  else {
LAB_0042ee06:
    if ((this->field16_0x40)._s_0.charon_found == false) goto LAB_0042ee53;
  }
  bVar4 = IsInfo("hbchar");
  if ((bVar4) && ((this->field16_0x40)._s_0.charon_build == false)) {
    AudioMessage("misn0916.wav");
    iVar5 = BuildObject("apcamr",1,"charon_spawn",0);
    (this->field18_0xec)._s_0.charon_nav = iVar5;
    SetObjectiveName(iVar5,"Alien Relic");
    (this->field16_0x40)._s_0.charon_build = true;
  }
LAB_0042ee53:
  if (((((this->field16_0x40)._s_0.objective1 != false) ||
       ((this->field16_0x40)._s_0.third_warning != false)) &&
      ((this->field16_0x40)._s_0.muf_deployed_good == false)) &&
     (fVar6 = Get_Time(), (this->field17_0x78)._s_0.deploy_check < fVar6)) {
    fVar6 = Get_Time();
    piVar1 = &(this->field18_0xec)._s_0.nsdfmuf;
    (this->field17_0x78)._s_0.deploy_check = fVar6 + 2.0;
    bVar4 = IsAlive(piVar1);
    if (((bVar4) && (bVar4 = IsDeployed(*piVar1), bVar4)) &&
       (fVar6 = GetDistance(*piVar1,(this->field18_0xec)._s_0.convoy_geyser), fVar6 < 1400.0)) {
      if ((this->field16_0x40)._s_0.objective1 == false) {
        InfoDisplay::ClearObjectives(&infoDisplay);
        lVar7 = DisplayInterface::colorRed;
      }
      else {
        InfoDisplay::ClearObjectives(&infoDisplay);
        lVar7 = DisplayInterface::colorGreen;
      }
      InfoDisplay::AddObjective(&infoDisplay,"misn0901.otf",lVar7,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0902.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0903.otf",DisplayInterface::colorWhite,8.0);
      (this->field16_0x40)._s_0.muf_deployed_good = true;
    }
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccarecycle);
  if (((!bVar4) && (bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccamuf), !bVar4)) &&
     ((this->field16_0x40)._s_0.ccadead == false)) {
    AudioMessage("misn0908.wav");
    (this->field16_0x40)._s_0.ccadead = true;
  }
  if (((((((this->field16_0x40)._s_0.scavs_alive != false) &&
         (bVar4 = IsAlive(&(this->field18_0xec)._s_0.avscav1), !bVar4)) &&
        (bVar4 = IsAlive(&(this->field18_0xec)._s_0.avscav2), !bVar4)) &&
       ((bVar4 = IsAlive(&(this->field18_0xec)._s_0.avscav3), !bVar4 &&
        ((this->field16_0x40)._s_0.game_over == false)))) &&
      ((this->field16_0x40)._s_0.objective1 == false)) &&
     ((this->field16_0x40)._s_0.first_warning == false)) {
    iVar5 = GetScrap(1);
    (this->field19_0x1c8)._s_0.scrap = iVar5;
    if (iVar5 < 10) {
      pcVar8 = "misn09f4.des";
      fVar6 = Get_Time();
      FailMission(fVar6 + 6.0,pcVar8);
      (this->field16_0x40)._s_0.game_over = true;
    }
  }
  if ((((this->field16_0x40)._s_0.convoy_started != false) &&
      (bVar4 = IsAlive(&(this->field18_0xec)._s_0.relic), !bVar4)) &&
     ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn0906.wav");
    pcVar8 = "misn09f1.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar8);
    (this->field16_0x40)._s_0.game_over = true;
  }
  if ((this->field16_0x40)._s_0.relic_seized != false) {
    piVar1 = &(this->field18_0xec)._s_0.ccalaunch;
    bVar4 = IsAlive(piVar1);
    if (((bVar4) && (fVar6 = GetDistance((this->field18_0xec)._s_0.ccatug,*piVar1), fVar6 < 100.0))
       && ((this->field16_0x40)._s_0.game_over == false)) {
      AudioMessage("misn0907.wav");
      pcVar8 = "misn09f2.des";
      fVar6 = Get_Time();
      FailMission(fVar6 + 15.0,pcVar8);
      (this->field16_0x40)._s_0.game_over = true;
    }
  }
  if ((((this->field16_0x40)._s_0.convoy_started != false) &&
      (fVar6 = Get_Time(), (this->field17_0x78)._s_0.unit_check < fVar6)) &&
     ((this->field16_0x40)._s_0.game_over5 == false)) {
    fVar6 = Get_Time();
    (this->field17_0x78)._s_0.unit_check = fVar6 + 10.0;
    iVar5 = CountUnitsNearObject((this->field18_0xec)._s_0.convoy_geyser,5000.0,2,(char *)0x0);
    (this->field19_0x1c8)._s_0.stuff = iVar5;
    if (iVar5 == 0) {
      AudioMessage("misn0908.wav");
      (this->field16_0x40)._s_0.game_over5 = true;
    }
  }
  piVar1 = &(this->field18_0xec)._s_0.relic;
  bVar4 = IsAlive(piVar1);
  if (((bVar4) && ((this->field16_0x40)._s_0.relic_seized == false)) &&
     ((fVar6 = Get_Time(), (this->field17_0x78)._s_0.win_check < fVar6 &&
      ((this->field16_0x40)._s_0.game_over == false)))) {
    fVar6 = Get_Time();
    piVar2 = &(this->field18_0xec)._s_0.nsdfmuf;
    (this->field17_0x78)._s_0.win_check = fVar6 + 2.0;
    bVar4 = IsAlive(piVar2);
    if ((bVar4) && (fVar6 = GetDistance(*piVar1,*piVar2), fVar6 < 100.0)) {
      AudioMessage("misn0909.wav");
      pcVar8 = "misn09w1.des";
      fVar6 = Get_Time();
      SucceedMission(fVar6 + 15.0,pcVar8);
      (this->field16_0x40)._s_0.game_over = true;
    }
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.nsdfmuf);
  if ((!bVar4) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn0911.wav");
    pcVar8 = "misn09f3.des";
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar8);
    (this->field16_0x40)._s_0.game_over = true;
  }
  bVar4 = IsAlive(&(this->field18_0xec)._s_0.ccalaunch);
  if ((!bVar4) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn0918.wav");
    pcVar8 = (char *)0x0;
    fVar6 = Get_Time();
    FailMission(fVar6 + 15.0,pcVar8);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
