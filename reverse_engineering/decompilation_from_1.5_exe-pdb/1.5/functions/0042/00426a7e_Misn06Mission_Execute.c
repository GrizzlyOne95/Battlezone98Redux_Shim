/*
 * Entry: 00426a7e
 * Name: Misn06Mission::Execute
 * Namespace: Misn06Mission
 * Signature: void Execute(Misn06Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn06Mission::Execute(Misn06Mission *this)

{
  int *piVar1;
  bool *pbVar2;
  int *piVar3;
  Misn06Mission_u_784 *pMVar4;
  int *piVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  char *pcVar10;
  char *pcVar11;
  
  if ((this->field16_0x40)._s_0.missionstart == true) {
    iVar7 = AudioMessage("misn0601.wav");
    (this->field19_0x310)._s_0.audmsg = iVar7;
    (this->field16_0x40)._s_0.missionstart = false;
    iVar7 = GetPlayerHandle();
    (this->field18_0x130)._s_0.player = iVar7;
    iVar7 = GetHandle("eggeizr1-1_geyser");
    (this->field18_0x130)._s_0.rendezvous = iVar7;
    SetObjectiveName(iVar7,"5th Platoon");
    iVar7 = GetHandle("obheph0_i76building");
    (this->field18_0x130)._s_0.haephestus = iVar7;
    iVar7 = GetHandle("avrecy-1_recycler");
    (this->field18_0x130)._s_0.avrec = iVar7;
    iVar7 = GetHandle("svrecy-1_recycler");
    (this->field18_0x130)._s_0.svrec = iVar7;
    iVar7 = GetHandle("sblpad0_i76building");
    (this->field18_0x130)._s_0.launchpad = iVar7;
    iVar7 = GetHandle("svfigh568_wingman");
    (this->field18_0x130)._s_0.wAu1 = iVar7;
    iVar7 = GetHandle("svfigh566_wingman");
    (this->field18_0x130)._s_0.wAu2 = iVar7;
    iVar7 = GetHandle("turret");
    (this->field18_0x130)._s_0.turret = iVar7;
    iVar7 = GetHandle("obstp25_i76building");
    (this->field18_0x130)._s_0.star2 = iVar7;
    iVar7 = GetHandle("obstp10_i76building");
    (this->field18_0x130)._s_0.star6 = iVar7;
    iVar7 = GetHandle("obstp33_i76building");
    (this->field18_0x130)._s_0.star8 = iVar7;
    iVar7 = GetHandle("svturr649_turrettank");
    (this->field18_0x130)._s_0.blockade1 = iVar7;
    iVar7 = GetHandle("svu1");
    (this->field18_0x130)._s_0.svu1 = iVar7;
    iVar7 = GetHandle("svu2");
    (this->field18_0x130)._s_0.svu2 = iVar7;
    iVar7 = GetHandle("svu3");
    (this->field18_0x130)._s_0.svu3 = iVar7;
    iVar7 = GetHandle("svu4");
    (this->field18_0x130)._s_0.svu4 = iVar7;
    iVar7 = GetHandle("avtank13_wingman");
    (this->field18_0x130)._s_0.p5u3 = iVar7;
    iVar7 = GetHandle("avtank11_wingman");
    (this->field18_0x130)._s_0.p5u4 = iVar7;
    iVar7 = GetHandle("avtank12_wingman");
    (this->field18_0x130)._s_0.p5u6 = iVar7;
    iVar7 = GetHandle("avfigh7_wingman");
    (this->field18_0x130)._s_0.p5u9 = iVar7;
    iVar7 = GetHandle("avfigh10_wingman");
    (this->field18_0x130)._s_0.p5u12 = iVar7;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.patrol1time = fVar9 + 30.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.patrol2time = fVar9 + 30.0;
    fVar9 = Get_Time();
    iVar7 = (this->field18_0x130)._s_0.rendezvous;
    (this->field17_0xa4)._s_0.patrol3time = fVar9 + 30.0;
    SetObjectiveOn(iVar7);
    InfoDisplay::AddObjective(&infoDisplay,"misn0600.otf",DisplayInterface::colorWhite,8.0);
    CameraReady();
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.opencamtime = fVar9 + 28.0;
    iVar7 = IsJapanese();
    if (iVar7 != 0) {
      fVar9 = Get_Time();
      (this->field17_0xa4)._s_0.opencamtime = fVar9 + 30.0;
    }
    (this->field16_0x40)._s_0.opencamdone = true;
    (this->field16_0x40)._s_0.newobjective = true;
    SetScrap(1,5);
    iVar7 = GetHandle("svartl648_howitzer");
    (this->field18_0x130)._s_0.art1 = iVar7;
    Defend(iVar7,1);
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.check1 = fVar9 + 20.0;
  }
  iVar7 = GetPlayerHandle();
  piVar1 = &(this->field18_0x130)._s_0.star2;
  (this->field18_0x130)._s_0.player = iVar7;
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    AddHealth(*piVar1,10000.0);
  }
  piVar1 = &(this->field18_0x130)._s_0.star6;
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    AddHealth(*piVar1,10000.0);
  }
  piVar1 = &(this->field18_0x130)._s_0.star8;
  bVar6 = IsAlive(piVar1);
  if (bVar6) {
    AddHealth(*piVar1,10000.0);
  }
  if ((this->field16_0x40)._s_0.trigger1 == false) {
    piVar1 = &(this->field18_0x130)._s_0.turret;
    iVar7 = GetNearestEnemy(*piVar1);
    (this->field18_0x130)._s_0.trigger = iVar7;
    fVar9 = GetDistance(iVar7,*piVar1);
    if ((fVar9 < 200.0) || (bVar6 = IsAlive(piVar1), !bVar6)) {
      if ((this->field16_0x40)._s_0.patrol1set == false) {
        iVar7 = (this->field19_0x310)._s_0.patrol1start;
        if (iVar7 == 0) {
          pcVar11 = "pat1sp1";
LAB_00426de5:
          pcVar10 = "svfigh";
LAB_00426de8:
          iVar7 = BuildObject(pcVar10,2,pcVar11,0);
          (this->field18_0x130)._s_0.pu1p1 = iVar7;
        }
        else {
          if (iVar7 == 1) {
            pcVar11 = "pat1sp2";
            goto LAB_00426de5;
          }
          if (iVar7 == 2) {
            pcVar11 = "pat1sp3";
            pcVar10 = "svtank";
            goto LAB_00426de8;
          }
          if (iVar7 == 3) {
            pcVar11 = "pat1sp4";
            goto LAB_00426de5;
          }
        }
        (this->field16_0x40)._s_0.patrol1set = true;
      }
      if ((this->field16_0x40)._s_0.patrol2set == false) {
        iVar7 = (this->field19_0x310)._s_0.patrol2start;
        if (iVar7 == 0) {
          pcVar11 = "pat2sp1";
LAB_00426e37:
          pcVar10 = "svfigh";
LAB_00426e3a:
          iVar7 = BuildObject(pcVar10,2,pcVar11,0);
          (this->field18_0x130)._s_0.pu1p2 = iVar7;
        }
        else {
          if (iVar7 == 1) {
            pcVar11 = "pat2sp2";
            goto LAB_00426e37;
          }
          if (iVar7 == 2) {
            pcVar11 = "pat2sp3";
            pcVar10 = "svtank";
            goto LAB_00426e3a;
          }
          if (iVar7 == 3) {
            pcVar11 = "pat2sp4";
            goto LAB_00426e37;
          }
        }
        (this->field16_0x40)._s_0.patrol2set = true;
      }
      if ((this->field16_0x40)._s_0.patrol3set == false) {
        iVar7 = (this->field19_0x310)._s_0.patrol3start;
        if (iVar7 == 0) {
          pcVar11 = "pat3sp1";
LAB_00426e89:
          pcVar10 = "svfigh";
LAB_00426e8c:
          iVar7 = BuildObject(pcVar10,2,pcVar11,0);
          (this->field18_0x130)._s_0.pu1p3 = iVar7;
        }
        else {
          if (iVar7 == 1) {
            pcVar11 = "pat3sp2";
            goto LAB_00426e89;
          }
          if (iVar7 == 2) {
            pcVar11 = "pat3sp3";
            pcVar10 = "svtank";
            goto LAB_00426e8c;
          }
          if (iVar7 == 3) {
            pcVar11 = "pat3sp4";
            goto LAB_00426e89;
          }
        }
        (this->field16_0x40)._s_0.patrol3set = true;
      }
      if (((this->field16_0x40)._s_0.patrol1set == true) &&
         ((this->field16_0x40)._s_0.startpat1 == false)) {
        Patrol((this->field18_0x130)._s_0.pu1p1,"patrol1",1);
        (this->field16_0x40)._s_0.startpat1 = true;
      }
      if (((this->field16_0x40)._s_0.patrol2set == true) &&
         ((this->field16_0x40)._s_0.startpat2 == false)) {
        Patrol((this->field18_0x130)._s_0.pu1p2,"patrol2",1);
        (this->field16_0x40)._s_0.startpat2 = true;
      }
      if (((this->field16_0x40)._s_0.patrol3set == true) &&
         ((this->field16_0x40)._s_0.startpat3 == false)) {
        Patrol((this->field18_0x130)._s_0.pu1p3,"patrol3",1);
        (this->field16_0x40)._s_0.startpat3 = true;
      }
      if ((this->field16_0x40)._s_0.startpat4 == false) {
        Patrol((this->field18_0x130)._s_0.pu1p4,"patrol4",1);
        Patrol((this->field18_0x130)._s_0.pu2p4,"patrol4",1);
        Patrol((this->field18_0x130)._s_0.pu3p4,"patrol4",1);
        (this->field16_0x40)._s_0.startpat4 = true;
      }
      (this->field16_0x40)._s_0.trigger1 = true;
    }
  }
  if ((this->field16_0x40)._s_0.trigger1 == true) {
    fVar9 = Get_Time();
    if (((this->field17_0xa4)._s_0.patrol1time < fVar9) &&
       ((this->field16_0x40)._s_0.patrol1spawned == false)) {
      fVar9 = Get_Time();
      piVar1 = &(this->field18_0x130)._s_0.pu1p1;
      (this->field17_0xa4)._s_0.patrol1time = fVar9 + 2.0;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (iVar7 = GetNearestEnemy(*piVar1), (float)iVar7 < 450.0)) {
        iVar7 = BuildObject("svtank",2,*piVar1);
        (this->field18_0x130)._s_0.pu2p1 = iVar7;
        (this->field16_0x40)._s_0.patrol1spawned = true;
        Patrol(iVar7,"patrol1",1);
      }
    }
    fVar9 = Get_Time();
    if (((this->field17_0xa4)._s_0.patrol2time < fVar9) &&
       ((this->field16_0x40)._s_0.patrol2spawned == false)) {
      fVar9 = Get_Time();
      piVar1 = &(this->field18_0x130)._s_0.pu1p2;
      (this->field17_0xa4)._s_0.patrol2time = fVar9 + 2.0;
      bVar6 = IsAlive(piVar1);
      if ((bVar6) && (iVar7 = GetNearestEnemy(*piVar1), (float)iVar7 < 450.0)) {
        iVar7 = BuildObject("svfigh",2,*piVar1);
        (this->field18_0x130)._s_0.pu2p2 = iVar7;
        (this->field16_0x40)._s_0.patrol2spawned = true;
        Patrol(iVar7,"patrol2",1);
      }
    }
    fVar9 = Get_Time();
    if (((this->field17_0xa4)._s_0.patrol3time < fVar9) &&
       ((this->field16_0x40)._s_0.patrol3spawned == false)) {
      fVar9 = Get_Time();
      piVar1 = &(this->field18_0x130)._s_0.pu1p3;
      iVar7 = *piVar1;
      (this->field17_0xa4)._s_0.patrol3time = fVar9 + 2.0;
      iVar7 = GetNearestEnemy(iVar7);
      if ((float)iVar7 < 450.0) {
        iVar7 = BuildObject("svfigh",2,*piVar1);
        (this->field18_0x130)._s_0.pu2p3 = iVar7;
        (this->field16_0x40)._s_0.patrol3spawned = true;
        Patrol(iVar7,"patrol3",1);
      }
    }
  }
  bVar6 = IsAlive(&(this->field18_0x130)._s_0.avrec);
  if ((!bVar6) && ((this->field16_0x40)._s_0.missionfail1 == false)) {
    iVar7 = AudioMessage("misn0653.wav");
    (this->field18_0x130)._s_0.aud20 = iVar7;
    iVar7 = AudioMessage("misn0651.wav");
    (this->field18_0x130)._s_0.aud21 = iVar7;
    (this->field16_0x40)._s_0.missionfail1 = true;
  }
  if ((((this->field16_0x40)._s_0.missionfail1 == true) &&
      (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud20), bVar6)) &&
     (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud21), bVar6)) {
    pcVar11 = "misn06l5.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  if ((this->field16_0x40)._s_0.opencamdone == true) {
    piVar1 = &(this->field18_0x130)._s_0.p5u3;
    CameraPath("openingcampath",1000,500,*piVar1);
    AddHealth(*piVar1,50.0);
    AddHealth((this->field18_0x130)._s_0.p5u4,50.0);
    AddHealth((this->field18_0x130)._s_0.p5u6,50.0);
    AddHealth((this->field18_0x130)._s_0.p5u9,50.0);
    AddHealth((this->field18_0x130)._s_0.p5u12,50.0);
    if (((this->field16_0x40)._s_0.opencamdone == true) &&
       ((fVar9 = Get_Time(), (this->field17_0xa4)._s_0.opencamtime < fVar9 ||
        (bVar6 = CameraCancelled(), bVar6)))) {
      piVar1 = &(this->field19_0x310)._s_0.audmsg;
      StopAudioMessage(*piVar1);
      *piVar1 = 0;
      CameraFinish();
      piVar1 = &(this->field18_0x130)._s_0.svu1;
      (this->field16_0x40)._s_0.opencamdone = false;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.svu2;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.svu3;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.svu4;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u1;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u2;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u3;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u4;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u5;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u6;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u7;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u8;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u9;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u10;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u11;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
      piVar1 = &(this->field18_0x130)._s_0.p5u12;
      bVar6 = IsAlive(piVar1);
      if (bVar6) {
        RemoveObject(*piVar1);
      }
    }
  }
  if ((this->field16_0x40)._s_0.newobjective == true) {
    InfoDisplay::ClearObjectives(&infoDisplay);
    if ((this->field16_0x40)._s_0.bugout == true) {
      if ((this->field16_0x40)._s_0.missionwon == true) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0606.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0605.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0604.otf",DisplayInterface::colorGreen,8.0);
      }
      if (((this->field16_0x40)._s_0.bugout == true) &&
         ((this->field16_0x40)._s_0.missionwon == false)) {
        InfoDisplay::AddObjective(&infoDisplay,"misn0606.otf",DisplayInterface::colorWhite,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0605.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0604.otf",DisplayInterface::colorGreen,8.0);
      }
    }
    if (((this->field16_0x40)._s_0.lprecon == true) && ((this->field16_0x40)._s_0.bugout == false))
    {
      InfoDisplay::AddObjective(&infoDisplay,"misn0605.otf",DisplayInterface::colorWhite,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0604.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((((this->field16_0x40)._s_0.starportreconed == true) &&
        ((this->field16_0x40)._s_0.transarrive == false)) &&
       ((this->field16_0x40)._s_0.safebreak == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0604.otf",DisplayInterface::colorWhite,8.0);
    }
    if (((this->field16_0x40)._s_0.neworders == true) &&
       ((this->field16_0x40)._s_0.starportreconed == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0603.otf",DisplayInterface::colorWhite,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0602.otf",DisplayInterface::colorGreen,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0601.otf",DisplayInterface::colorGreen,8.0);
    }
    if (((this->field16_0x40)._s_0.reconheaphestus == true) &&
       ((this->field16_0x40)._s_0.neworders == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0602.otf",DisplayInterface::colorWhite,8.0);
      InfoDisplay::AddObjective(&infoDisplay,"misn0601.otf",DisplayInterface::colorGreen,8.0);
    }
    if ((((this->field16_0x40)._s_0.haephestusdisc == true) &&
        ((this->field16_0x40)._s_0.reconheaphestus == false)) &&
       ((this->field16_0x40)._s_0.hephikey == false)) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0601.otf",DisplayInterface::colorWhite,8.0);
    }
    if ((this->field16_0x40)._s_0.fifthplatoon == true) {
      InfoDisplay::AddObjective(&infoDisplay,"misn0600.otf",DisplayInterface::colorWhite,8.0);
    }
    (this->field16_0x40)._s_0.newobjective = false;
  }
  if (((this->field16_0x40)._s_0.haephestusdisc == false) &&
     (fVar9 = GetDistance((this->field18_0x130)._s_0.haephestus,(this->field18_0x130)._s_0.player),
     fVar9 < 1000.0)) {
    iVar7 = AudioMessage("misn0602.wav");
    (this->field18_0x130)._s_0.aud1 = iVar7;
    (this->field16_0x40)._s_0.haephestusdisc = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.hephdisctime = fVar9 + 60.0;
  }
  if ((this->field16_0x40)._s_0.loopbreaker == false) {
    if ((this->field16_0x40)._s_0.haephestusdisc == true) {
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud1);
      if (bVar6) {
        SetObjectiveOn((this->field18_0x130)._s_0.haephestus);
        SetObjectiveName((this->field18_0x130)._s_0.haephestus,"Object");
        (this->field16_0x40)._s_0.newobjective = true;
        (this->field16_0x40)._s_0.loopbreaker = true;
      }
      goto LAB_00427673;
    }
LAB_004276c4:
    iVar7 = (this->field19_0x310)._s_0.hephwarn;
  }
  else {
LAB_00427673:
    if ((((this->field16_0x40)._s_0.haephestusdisc != true) ||
        ((this->field16_0x40)._s_0.reconheaphestus != false)) ||
       (((this->field16_0x40)._s_0.hephikey != false ||
        (fVar9 = Get_Time(), fVar9 <= (this->field17_0xa4)._s_0.hephdisctime)))) goto LAB_004276c4;
    iVar7 = (this->field19_0x310)._s_0.hephwarn;
    if (iVar7 < 2) {
      AudioMessage("misn0690.wav");
      fVar9 = Get_Time();
      piVar1 = &(this->field19_0x310)._s_0.hephwarn;
      *piVar1 = *piVar1 + 1;
      (this->field17_0xa4)._s_0.hephdisctime = fVar9 + 20.0;
      goto LAB_004276c4;
    }
  }
  if (((iVar7 == 2) && ((this->field16_0x40)._s_0.missionfail4 == false)) &&
     (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.hephdisctime < fVar9)) {
    iVar7 = AudioMessage("misn0694.wav");
    (this->field19_0x310)._s_0.aud105 = iVar7;
    (this->field16_0x40)._s_0.missionfail4 = true;
  }
  if (((this->field16_0x40)._s_0.missionfail4 == true) &&
     (bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud105), bVar6)) {
    pcVar11 = "misn06l1.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  if ((((this->field16_0x40)._s_0.reconheaphestus == false) &&
      (fVar9 = GetDistance((this->field18_0x130)._s_0.player,(this->field18_0x130)._s_0.haephestus),
      fVar9 < 125.0)) && ((this->field16_0x40)._s_0.hephikey == false)) {
    iVar7 = AudioMessage("misn0603.wav");
    (this->field18_0x130)._s_0.heph1 = iVar7;
    iVar8 = AudioMessage("misn0604.wav");
    iVar7 = (this->field18_0x130)._s_0.haephestus;
    (this->field18_0x130)._s_0.heph2 = iVar8;
    (this->field16_0x40)._s_0.reconheaphestus = true;
    SetObjectiveOff(iVar7);
    CameraReady();
    fVar9 = Get_Time();
    (this->field16_0x40)._s_0.cam1done = true;
    (this->field17_0xa4)._s_0.cam1time = fVar9 + 12.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.identtime = fVar9 + 20.0;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.identtime < fVar9) &&
      ((this->field16_0x40)._s_0.hephikey == false)) &&
     (piVar1 = &(this->field19_0x310)._s_0.ident, *piVar1 < 2)) {
    AudioMessage("misn0691.wav");
    *piVar1 = *piVar1 + 1;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.identtime = fVar9 + 10.0;
  }
  if ((((this->field19_0x310)._s_0.ident == 2) &&
      (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.identtime < fVar9)) &&
     (((this->field16_0x40)._s_0.hephikey == false &&
      ((this->field16_0x40)._s_0.missionfail == false)))) {
    iVar7 = AudioMessage("misn0694.wav");
    (this->field19_0x310)._s_0.aud100 = iVar7;
    (this->field16_0x40)._s_0.missionfail = true;
  }
  if (((this->field16_0x40)._s_0.missionfail == true) &&
     (bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud100), bVar6)) {
    pcVar11 = "misn06l2.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  bVar6 = IsInfo("obheph");
  if ((bVar6) && (pbVar2 = &(this->field16_0x40)._s_0.hephikey, *pbVar2 == false)) {
    fVar9 = Get_Time();
    iVar7 = (this->field18_0x130)._s_0.haephestus;
    *pbVar2 = true;
    (this->field17_0xa4)._s_0.processtime = fVar9 + 5.0;
    (this->field16_0x40)._s_0.reconheaphestus = true;
    SetObjectiveOff(iVar7);
    (this->field16_0x40)._s_0.newobjective = true;
  }
  if (((this->field16_0x40)._s_0.neworders == false) &&
     (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.processtime < fVar9)) {
    iVar7 = AudioMessage("misn0605.wav");
    (this->field18_0x130)._s_0.aud2 = iVar7;
    (this->field16_0x40)._s_0.fifthplatoon = false;
    (this->field16_0x40)._s_0.neworders = true;
    (this->field16_0x40)._s_0.buildcam = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.discstar = fVar9 + 80.0;
  }
  if (((this->field16_0x40)._s_0.buildcam == true) &&
     (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud2), bVar6)) {
    SetObjectiveOff((this->field18_0x130)._s_0.rendezvous);
    iVar7 = BuildObject("apcamr",1,"cam1spawn",0);
    (this->field18_0x130)._s_0.starportcam = iVar7;
    SetObjectiveName(iVar7,"Starport");
    (this->field16_0x40)._s_0.buildcam = false;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  piVar1 = &(this->field18_0x130)._s_0.player;
  fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.blockade1);
  if ((fVar9 < 420.0) && ((this->field16_0x40)._s_0.blockadefound == false)) {
    AudioMessage("misn0636.wav");
    (this->field16_0x40)._s_0.blockadefound = true;
  }
  bVar6 = IsInfo("obstp1");
  if ((bVar6) && ((this->field16_0x40)._s_0.star1recon == false)) {
    (this->field16_0x40)._s_0.star1recon = true;
  }
  bVar6 = IsInfo("obstp8");
  if ((bVar6) && ((this->field16_0x40)._s_0.star4recon == false)) {
    (this->field16_0x40)._s_0.star4recon = true;
  }
  bVar6 = IsInfo("obstp3");
  if ((bVar6) && ((this->field16_0x40)._s_0.star6recon == false)) {
    (this->field16_0x40)._s_0.star6recon = true;
  }
  if (((this->field16_0x40)._s_0.fail3 == false) && ((this->field17_0xa4)._s_0.spfail == 4.0)) {
    (this->field16_0x40)._s_0.fail3 = true;
    iVar7 = AudioMessage("misn0694.wav");
    (this->field18_0x130)._s_0.aud54 = iVar7;
  }
  if (((this->field16_0x40)._s_0.fail3 == true) &&
     (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud54), bVar6)) {
    pcVar11 = "misn06l6.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  if (((((this->field16_0x40)._s_0.starportreconed == false) &&
       (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.reconsptime < fVar9)) &&
      ((this->field16_0x40)._s_0.fail3 == false)) && ((this->field17_0xa4)._s_0.spfail < 4.0)) {
    AudioMessage("misn0654.wav");
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.reconsptime = fVar9 + 15.0;
    (this->field17_0xa4)._s_0.spfail = (this->field17_0xa4)._s_0.spfail + 1.0;
  }
  if ((((this->field16_0x40)._s_0.star1recon == true) &&
      ((this->field16_0x40)._s_0.star4recon == true)) &&
     (((this->field16_0x40)._s_0.star6recon == true &&
      ((this->field16_0x40)._s_0.starportreconed == false)))) {
    iVar7 = AudioMessage("misn0650.wav");
    (this->field18_0x130)._s_0.aud3 = iVar7;
    iVar7 = AudioMessage("misn0606.wav");
    (this->field18_0x130)._s_0.aud4 = iVar7;
    iVar7 = AudioMessage("misn0607.wav");
    (this->field18_0x130)._s_0.aud5 = iVar7;
    (this->field16_0x40)._s_0.starportreconed = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.start1 = fVar9 + 15.0;
  }
  if ((((this->field16_0x40)._s_0.star == false) &&
      ((this->field16_0x40)._s_0.starportreconed == true)) &&
     ((bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud3), bVar6 &&
      ((bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud4), bVar6 &&
       (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud5), bVar6)))))) {
    (this->field16_0x40)._s_0.newobjective = true;
    (this->field16_0x40)._s_0.star = true;
  }
  if (((this->field16_0x40)._s_0.starportdisc == false) &&
     (fVar9 = GetDistance((this->field18_0x130)._s_0.star8,*piVar1), fVar9 < 200.0)) {
    AudioMessage("misn0608.wav");
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.searchtime = fVar9 + 15.0;
    (this->field16_0x40)._s_0.starportdisc = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.reconsptime = fVar9 + 20.0;
  }
  if ((((this->field16_0x40)._s_0.neworders != true) ||
      ((this->field16_0x40)._s_0.starportdisc != false)) ||
     (fVar9 = Get_Time(), fVar9 <= (this->field17_0xa4)._s_0.discstar)) {
LAB_00427bb5:
    iVar7 = (this->field19_0x310)._s_0.stardisc;
  }
  else {
    iVar7 = (this->field19_0x310)._s_0.stardisc;
    if (iVar7 < 3) {
      AudioMessage("misn0695.wav");
      fVar9 = Get_Time();
      (this->field17_0xa4)._s_0.discstar = fVar9 + 40.0;
      piVar3 = &(this->field19_0x310)._s_0.stardisc;
      *piVar3 = *piVar3 + 1;
      goto LAB_00427bb5;
    }
  }
  if (((iVar7 == 3) && (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.discstar < fVar9)) &&
     (pbVar2 = &(this->field16_0x40)._s_0.missionfail3, *pbVar2 == false)) {
    *pbVar2 = true;
    iVar7 = AudioMessage("misn0694.wav");
    (this->field19_0x310)._s_0.aud101 = iVar7;
  }
  if (((this->field16_0x40)._s_0.missionfail3 == true) &&
     (bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud101), bVar6)) {
    pcVar11 = "misn06l3.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  if (((this->field16_0x40)._s_0.ccaattack == false) &&
     (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.check1 < fVar9)) {
    iVar7 = GetNearestEnemy((this->field18_0x130)._s_0.wAu1);
    (this->field18_0x130)._s_0.enemy = iVar7;
    fVar9 = GetDistance(iVar7,(this->field18_0x130)._s_0.wAu1);
    if (fVar9 < 410.0) {
      Attack((this->field18_0x130)._s_0.wAu1,(this->field18_0x130)._s_0.enemy,1);
      piVar3 = &(this->field18_0x130)._s_0.wAu2;
      Attack(*piVar3,(this->field18_0x130)._s_0.enemy,1);
      SetIndependence(*piVar3,1);
      (this->field16_0x40)._s_0.ccaattack = true;
      fVar9 = Get_Time();
      (this->field17_0xa4)._s_0.start1 = fVar9 - 1.0;
    }
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.check1 = fVar9 + 1.5;
  }
  if (((this->field16_0x40)._s_0.starportreconed == true) &&
     ((this->field16_0x40)._s_0.ccaattack == false)) {
    Attack((this->field18_0x130)._s_0.wAu1,*piVar1,1);
    Attack((this->field18_0x130)._s_0.wAu2,*piVar1,1);
    SetIndependence((this->field18_0x130)._s_0.wAu1,1);
    SetIndependence((this->field18_0x130)._s_0.wAu2,1);
    (this->field16_0x40)._s_0.ccaattack = true;
  }
  piVar1 = &(this->field18_0x130)._s_0.wAu1;
  fVar9 = GetDistance(*piVar1,"cam1spawn",0);
  if ((((fVar9 < 400.0) ||
       (fVar9 = GetDistance((this->field18_0x130)._s_0.wAu2,"cam1spawn",0), fVar9 < 400.0)) &&
      ((this->field16_0x40)._s_0.ccaattack == true)) &&
     ((((this->field16_0x40)._s_0.loopbreak1 == false &&
       (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.start1 < fVar9)) &&
      (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud5), bVar6)))) {
    iVar7 = AudioMessage("misn0611.wav");
    (this->field18_0x130)._s_0.aud500 = iVar7;
    CameraReady();
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.cam3time = fVar9 + 5.0;
    (this->field16_0x40)._s_0.cam3done = true;
    (this->field16_0x40)._s_0.ccaattack = false;
    (this->field16_0x40)._s_0.loopbreak1 = true;
  }
  if ((this->field16_0x40)._s_0.cam1done == true) {
    pMVar4 = &this->field19_0x310;
    CameraPath("cam1path",(pMVar4->_s_0).cam1hgt,1000,(this->field18_0x130)._s_0.haephestus);
    (pMVar4->_s_0).cam1hgt = (pMVar4->_s_0).cam1hgt + 0xf;
    if (((this->field16_0x40)._s_0.cam1done == true) &&
       (((bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.heph1), bVar6 &&
         (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.heph2), bVar6)) ||
        (bVar6 = CameraCancelled(), bVar6)))) {
      CameraFinish();
      iVar7 = (this->field18_0x130)._s_0.heph1;
      (this->field16_0x40)._s_0.cam1done = false;
      StopAudioMessage(iVar7);
      StopAudioMessage((this->field18_0x130)._s_0.heph2);
      (this->field16_0x40)._s_0.newobjective = true;
    }
  }
  if (((((this->field16_0x40)._s_0.cam3done == true) &&
       (CameraObject(*piVar1,300,100,-900,*piVar1), (this->field16_0x40)._s_0.cam3done == true)) &&
      (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud500), bVar6)) ||
     (bVar6 = CameraCancelled(), bVar6)) {
    CameraFinish();
    (this->field16_0x40)._s_0.cam3done = false;
  }
  if ((this->field16_0x40)._s_0.ccapullout == false) {
    IsAlive(piVar1);
    IsAlive(piVar1);
  }
  bVar6 = IsAlive(piVar1);
  if (((!bVar6) && (bVar6 = IsAlive(&(this->field18_0x130)._s_0.wAu2), !bVar6)) &&
     (((this->field16_0x40)._s_0.ccapullout == false &&
      ((this->field16_0x40)._s_0.starportreconed == true)))) {
    iVar7 = AudioMessage("misn0612.wav");
    (this->field18_0x130)._s_0.aud15 = iVar7;
    iVar7 = AudioMessage("misn0613.wav");
    (this->field18_0x130)._s_0.aud16 = iVar7;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.transportarrive = fVar9 + 50.0;
    (this->field16_0x40)._s_0.transarrive = true;
    (this->field16_0x40)._s_0.safebreak = true;
    (this->field16_0x40)._s_0.ccapullout = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.wave1 = fVar9 + 60.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.wave2 = fVar9 + 180.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.wave3 = fVar9 + 300.0;
  }
  if ((((this->field16_0x40)._s_0.breaker19 == false) &&
      ((this->field16_0x40)._s_0.ccapullout == true)) &&
     ((bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud15), bVar6 &&
      (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud16), bVar6)))) {
    (this->field16_0x40)._s_0.breaker19 = true;
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.wave1 < fVar9) && ((this->field16_0x40)._s_0.wave1start == false))
  {
    piVar1 = &(this->field18_0x130)._s_0.svrec;
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w1u1 = iVar7;
      iVar7 = BuildObject("svtank",2,*piVar1);
      (this->field18_0x130)._s_0.w1u2 = iVar7;
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w1u3 = iVar7;
      piVar1 = &(this->field18_0x130)._s_0.avrec;
      Attack((this->field18_0x130)._s_0.w1u1,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w1u2,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w1u3,*piVar1,1);
      SetIndependence((this->field18_0x130)._s_0.w1u1,1);
      SetIndependence((this->field18_0x130)._s_0.w1u2,1);
      SetIndependence((this->field18_0x130)._s_0.w1u3,1);
      (this->field16_0x40)._s_0.wave1start = true;
    }
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.wave2 < fVar9) && ((this->field16_0x40)._s_0.wave2start == false))
  {
    piVar1 = &(this->field18_0x130)._s_0.svrec;
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w2u1 = iVar7;
      iVar7 = BuildObject("svtank",2,*piVar1);
      (this->field18_0x130)._s_0.w2u2 = iVar7;
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w2u3 = iVar7;
      piVar1 = &(this->field18_0x130)._s_0.avrec;
      Attack((this->field18_0x130)._s_0.w2u1,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w2u2,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w2u3,*piVar1,1);
      SetIndependence((this->field18_0x130)._s_0.w2u1,1);
      SetIndependence((this->field18_0x130)._s_0.w2u2,1);
      SetIndependence((this->field18_0x130)._s_0.w2u3,1);
      (this->field16_0x40)._s_0.wave2start = true;
    }
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.wave3 < fVar9) && ((this->field16_0x40)._s_0.wave3start == false))
  {
    piVar1 = &(this->field18_0x130)._s_0.svrec;
    bVar6 = IsAlive(piVar1);
    if (bVar6) {
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w3u1 = iVar7;
      iVar7 = BuildObject("svtank",2,*piVar1);
      (this->field18_0x130)._s_0.w3u2 = iVar7;
      iVar7 = BuildObject("svfigh",2,*piVar1);
      (this->field18_0x130)._s_0.w3u3 = iVar7;
      piVar1 = &(this->field18_0x130)._s_0.avrec;
      Attack((this->field18_0x130)._s_0.w3u1,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w3u2,*piVar1,1);
      Attack((this->field18_0x130)._s_0.w3u3,*piVar1,1);
      SetIndependence((this->field18_0x130)._s_0.w3u1,1);
      SetIndependence((this->field18_0x130)._s_0.w3u2,1);
      SetIndependence((this->field18_0x130)._s_0.w3u3,1);
      (this->field16_0x40)._s_0.wave3start = true;
    }
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.transportarrive < fVar9) &&
     ((this->field16_0x40)._s_0.transarrive == true)) {
    iVar7 = AudioMessage("misn0614.wav");
    (this->field18_0x130)._s_0.aud6 = iVar7;
    iVar7 = AudioMessage("misn0628.wav");
    (this->field18_0x130)._s_0.aud7 = iVar7;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.lincolndestroyed = fVar9 + 60.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.oneminstrans = fVar9 + 60.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.transaway = fVar9 + 90.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.platoonarrive = fVar9 + 1410.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.threeminsplatoon = fVar9 + 390.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.tenminsplatoon = fVar9 + 810.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.fiveminsplatoon = fVar9 + 1110.0;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.twominsplatoon = fVar9 + 1260.0;
    (this->field16_0x40)._s_0.transarrive = false;
    (this->field16_0x40)._s_0.touchdown = true;
    (this->field16_0x40)._s_0.threemin = true;
    (this->field16_0x40)._s_0.tenmin = true;
    (this->field16_0x40)._s_0.fivemin = true;
    (this->field16_0x40)._s_0.twomin = true;
    (this->field16_0x40)._s_0.platoonhere = true;
    (this->field16_0x40)._s_0.newobjective = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.timerstart = fVar9 + 27.42;
    (this->field16_0x40)._s_0.lincolndes = true;
  }
  if (((((this->field16_0x40)._s_0.lprecon == false) &&
       ((this->field16_0x40)._s_0.lincolndes == true)) &&
      (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud6), bVar6)) &&
     (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.aud7), bVar6)) {
    (this->field16_0x40)._s_0.lprecon = true;
    StartCockpitTimer(0x21c,0x16a,0xb4);
    SetObjectiveOn((this->field18_0x130)._s_0.launchpad);
    (this->field16_0x40)._s_0.newobjective = true;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.threeminsplatoon < fVar9) &&
      ((this->field16_0x40)._s_0.threemin == true)) &&
     ((this->field16_0x40)._s_0.launchpadreconed == false)) {
    piVar1 = &(this->field18_0x130)._s_0.player;
    iVar7 = GetNearestEnemy(*piVar1);
    (this->field18_0x130)._s_0.bogey = iVar7;
    fVar9 = GetDistance(iVar7,*piVar1);
    if (400.0 < fVar9) {
      iVar7 = BuildObject("avtank",3,"sim1",0);
      (this->field18_0x130)._s_0.sim1 = iVar7;
      iVar7 = BuildObject("avtank",3,"sim2",0);
      (this->field18_0x130)._s_0.sim2 = iVar7;
      iVar7 = BuildObject("avtank",3,"sim3",0);
      (this->field18_0x130)._s_0.sim3 = iVar7;
      iVar7 = BuildObject("avtank",3,"sim4",0);
      (this->field18_0x130)._s_0.sim4 = iVar7;
      iVar7 = BuildObject("avtank",3,"sim5",0);
      (this->field18_0x130)._s_0.sim5 = iVar7;
      iVar7 = BuildObject("avfigh",3,"sim6",0);
      (this->field18_0x130)._s_0.sim6 = iVar7;
      iVar7 = BuildObject("avfigh",3,"sim7",0);
      (this->field18_0x130)._s_0.sim7 = iVar7;
      iVar7 = BuildObject("avfigh",3,"sim8",0);
      (this->field18_0x130)._s_0.sim8 = iVar7;
      iVar7 = BuildObject("avfigh",3,"sim9",0);
      (this->field18_0x130)._s_0.sim9 = iVar7;
      iVar7 = BuildObject("avfigh",3,"sim10",0);
      (this->field18_0x130)._s_0.sim10 = iVar7;
      Goto((this->field18_0x130)._s_0.sim1,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim2,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim3,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim4,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim5,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim6,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim7,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim8,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim9,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim10,"simpoint5",1);
      CameraReady();
      iVar7 = AudioMessage("misn0631.wav");
      (this->field18_0x130)._s_0.simaud1 = iVar7;
      iVar7 = AudioMessage("misn0642.wav");
      (this->field18_0x130)._s_0.simaud2 = iVar7;
      iVar7 = AudioMessage("misn0643.wav");
      (this->field18_0x130)._s_0.simaud3 = iVar7;
      iVar7 = AudioMessage("misn0644.wav");
      (this->field18_0x130)._s_0.simaud4 = iVar7;
      iVar7 = AudioMessage("misn0645.wav");
      (this->field18_0x130)._s_0.simaud5 = iVar7;
      (this->field16_0x40)._s_0.simcam = true;
      (this->field16_0x40)._s_0.threemin = false;
      CockpitTimer::HideTimer(&cockpitTimer);
    }
  }
  if ((this->field16_0x40)._s_0.simcam == true) {
    iVar7 = (this->field18_0x130)._s_0.sim5;
    CameraObject(iVar7,0,1000,-4000,iVar7);
    if (((this->field16_0x40)._s_0.attack == false) &&
       (bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud4), bVar6)) {
      Goto((this->field18_0x130)._s_0.sim1,"simpoint1",1);
      Goto((this->field18_0x130)._s_0.sim2,"simpoint1",1);
      Goto((this->field18_0x130)._s_0.sim4,"simpoint1",1);
      Goto((this->field18_0x130)._s_0.sim7,"simpoint1",1);
      Goto((this->field18_0x130)._s_0.sim3,"simpoint3",1);
      Goto((this->field18_0x130)._s_0.sim6,"simpoint3",1);
      Goto((this->field18_0x130)._s_0.sim10,"simpoint3",1);
      Goto((this->field18_0x130)._s_0.sim5,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim8,"simpoint5",1);
      Goto((this->field18_0x130)._s_0.sim9,"simpoint5",1);
      (this->field16_0x40)._s_0.attack = true;
    }
    if (((this->field16_0x40)._s_0.simcam == true) && ((this->field16_0x40)._s_0.breakout1 == false)
       ) {
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud1);
      if (bVar6) {
        (this->field16_0x40)._s_0.doneaud1 = true;
      }
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud2);
      if (bVar6) {
        (this->field16_0x40)._s_0.doneaud2 = true;
      }
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud3);
      if (bVar6) {
        (this->field16_0x40)._s_0.doneaud3 = true;
      }
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud4);
      if (bVar6) {
        (this->field16_0x40)._s_0.doneaud4 = true;
      }
      bVar6 = IsAudioMessageDone((this->field18_0x130)._s_0.simaud5);
      if (bVar6) {
        (this->field16_0x40)._s_0.doneaud5 = true;
      }
      if ((((((this->field16_0x40)._s_0.doneaud1 != false) &&
            ((this->field16_0x40)._s_0.doneaud2 != false)) &&
           ((this->field16_0x40)._s_0.doneaud3 != false)) &&
          (((this->field16_0x40)._s_0.doneaud4 != false &&
           ((this->field16_0x40)._s_0.doneaud5 != false)))) || (bVar6 = CameraCancelled(), bVar6)) {
        CameraFinish();
        (this->field16_0x40)._s_0.breakout1 = true;
        (this->field16_0x40)._s_0.simcam = false;
        StopAudioMessage((this->field18_0x130)._s_0.simaud1);
        StopAudioMessage((this->field18_0x130)._s_0.simaud2);
        StopAudioMessage((this->field18_0x130)._s_0.simaud3);
        StopAudioMessage((this->field18_0x130)._s_0.simaud4);
        StopAudioMessage((this->field18_0x130)._s_0.simaud5);
      }
    }
  }
  if (((this->field16_0x40)._s_0.breakout1 == true) && ((this->field16_0x40)._s_0.removal == false))
  {
    RemoveObject((this->field18_0x130)._s_0.sim1);
    RemoveObject((this->field18_0x130)._s_0.sim2);
    RemoveObject((this->field18_0x130)._s_0.sim3);
    RemoveObject((this->field18_0x130)._s_0.sim4);
    RemoveObject((this->field18_0x130)._s_0.sim5);
    RemoveObject((this->field18_0x130)._s_0.sim6);
    RemoveObject((this->field18_0x130)._s_0.sim7);
    RemoveObject((this->field18_0x130)._s_0.sim8);
    RemoveObject((this->field18_0x130)._s_0.sim9);
    RemoveObject((this->field18_0x130)._s_0.sim10);
    (this->field16_0x40)._s_0.removal = true;
    cockpitTimer.active = false;
    CockpitTimer::HideTimer(&cockpitTimer);
  }
  fVar9 = Get_Time();
  if (((((this->field17_0xa4)._s_0.tenminsplatoon < fVar9) &&
       ((this->field16_0x40)._s_0.tenmin == true)) &&
      ((this->field16_0x40)._s_0.launchpadreconed == false)) &&
     ((this->field16_0x40)._s_0.reminder == false)) {
    AudioMessage("misn0632.wav");
    (this->field16_0x40)._s_0.tenmin = false;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.fiveminsplatoon < fVar9) &&
      ((this->field16_0x40)._s_0.fivemin == true)) &&
     (((this->field16_0x40)._s_0.launchpadreconed == false &&
      ((this->field16_0x40)._s_0.reminder == false)))) {
    AudioMessage("misn0633.wav");
    (this->field16_0x40)._s_0.fivemin = false;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.twominsplatoon < fVar9) &&
      ((this->field16_0x40)._s_0.twomin == true)) &&
     (((this->field16_0x40)._s_0.launchpadreconed == false &&
      ((this->field16_0x40)._s_0.reminder == false)))) {
    AudioMessage("misn0634.wav");
    (this->field16_0x40)._s_0.twomin = false;
  }
  piVar1 = &(this->field18_0x130)._s_0.player;
  fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.svrec);
  if (((fVar9 < 250.0) && (pbVar2 = &(this->field16_0x40)._s_0.reminder, *pbVar2 == false)) &&
     ((this->field16_0x40)._s_0.launchpadreconed == false)) {
    AudioMessage("misn0638.wav");
    *pbVar2 = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.end = fVar9 + 120.0;
  }
  if ((((this->field16_0x40)._s_0.reminder == true) &&
      (fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.launchpad), 400.0 < fVar9)) &&
     (((this->field16_0x40)._s_0.launchpadreconed == false &&
      ((fVar9 = Get_Time(), (this->field17_0xa4)._s_0.end < fVar9 &&
       ((this->field16_0x40)._s_0.breaker == false)))))) {
    iVar7 = AudioMessage("misn0635.wav");
    (this->field19_0x310)._s_0.aud102 = iVar7;
    iVar7 = AudioMessage("misn0646.wav");
    (this->field19_0x310)._s_0.aud103 = iVar7;
    iVar7 = AudioMessage("misn0651.wav");
    (this->field19_0x310)._s_0.aud104 = iVar7;
    (this->field16_0x40)._s_0.platoonhere = false;
    (this->field16_0x40)._s_0.endme = true;
    (this->field16_0x40)._s_0.breaker = true;
  }
  bVar6 = IsInfo("sblpad");
  if ((bVar6) && ((this->field16_0x40)._s_0.launchpadreconed == false)) {
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.time1 = fVar9 + 2.0;
    (this->field16_0x40)._s_0.bugout = true;
    (this->field16_0x40)._s_0.launchpadreconed = true;
    CockpitTimer::HideTimer(&cockpitTimer);
    SetObjectiveOff((this->field18_0x130)._s_0.launchpad);
  }
  if ((this->field16_0x40)._s_0.bugout == true) {
    if (((((this->field16_0x40)._s_0.corbettalive == true) &&
         (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.time1 < fVar9)) &&
        ((this->field16_0x40)._s_0.threemin == true)) &&
       ((this->field16_0x40)._s_0.bustout == false)) {
      AudioMessage("misn0629.wav");
      AudioMessage("misn0630.wav");
      AudioMessage("misn0647.wav");
      iVar7 = BuildObject("svfigh",2,"ccaplatoonspawn",0);
      piVar3 = &(this->field18_0x130)._s_0.ccap1;
      *piVar3 = iVar7;
      Attack(iVar7,(this->field18_0x130)._s_0.avrec,1);
      SetIndependence(*piVar3,1);
      (this->field16_0x40)._s_0.platoonhere = false;
      (this->field16_0x40)._s_0.pickupset = true;
      (this->field17_0xa4)._s_0.platoonarrive = 1e+12;
      (this->field17_0xa4)._s_0.twominsplatoon = 1e+12;
      (this->field17_0xa4)._s_0.tenminsplatoon = 1e+12;
      (this->field17_0xa4)._s_0.fiveminsplatoon = 1e+12;
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field16_0x40)._s_0.bustout = true;
    }
    if ((((this->field16_0x40)._s_0.bugout == true) &&
        ((this->field16_0x40)._s_0.corbettalive == true)) &&
       ((fVar9 = Get_Time(), (this->field17_0xa4)._s_0.time1 < fVar9 &&
        (((this->field16_0x40)._s_0.threemin == false &&
         ((this->field16_0x40)._s_0.bustout == false)))))) {
      AudioMessage("misn0629.wav");
      AudioMessage("misn0630.wav");
      iVar7 = BuildObject("svfigh",2,"ccaplatoonspawn",0);
      piVar3 = &(this->field18_0x130)._s_0.ccap1;
      *piVar3 = iVar7;
      Attack(iVar7,(this->field18_0x130)._s_0.avrec,1);
      SetIndependence(*piVar3,1);
      (this->field16_0x40)._s_0.platoonhere = false;
      (this->field16_0x40)._s_0.pickupset = true;
      (this->field17_0xa4)._s_0.platoonarrive = 1e+12;
      (this->field17_0xa4)._s_0.twominsplatoon = 1e+12;
      (this->field17_0xa4)._s_0.tenminsplatoon = 1e+12;
      (this->field17_0xa4)._s_0.fiveminsplatoon = 1e+12;
      (this->field16_0x40)._s_0.newobjective = true;
      (this->field16_0x40)._s_0.bustout = true;
    }
  }
  if (((((this->field16_0x40)._s_0.breakme == false) && ((this->field16_0x40)._s_0.bugout == true))
      && ((this->field16_0x40)._s_0.corbettalive == false)) &&
     (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.time1 < fVar9)) {
    AudioMessage("misn0629.wav");
    AudioMessage("misn0630.wav");
    SetIndependence((this->field18_0x130)._s_0.ccap1,1);
    (this->field16_0x40)._s_0.platoonhere = false;
    (this->field16_0x40)._s_0.breakme = true;
    (this->field16_0x40)._s_0.pickupset = true;
    (this->field17_0xa4)._s_0.platoonarrive = 1e+12;
    (this->field17_0xa4)._s_0.twominsplatoon = 1e+12;
    (this->field17_0xa4)._s_0.tenminsplatoon = 1e+12;
    (this->field17_0xa4)._s_0.fiveminsplatoon = 1e+12;
    (this->field16_0x40)._s_0.newobjective = true;
    fVar9 = Get_Time();
    (this->field17_0xa4)._s_0.deathtime = fVar9 + 30.0;
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.deathtime < fVar9) &&
     (pbVar2 = &(this->field16_0x40)._s_0.death, *pbVar2 == false)) {
    *pbVar2 = true;
    (this->field17_0xa4)._s_0.deathtime = 1e+14;
    AudioMessage("misn0635.wav");
    iVar7 = BuildObject("svfigh",2,"ccaplatoonspawn",0);
    (this->field18_0x130)._s_0.ccap1 = iVar7;
    Attack(iVar7,(this->field18_0x130)._s_0.avrec,1);
  }
  if ((this->field16_0x40)._s_0.pickupset != true) goto LAB_00428c59;
  iVar7 = (this->field19_0x310)._s_0.extractpoint;
  if (iVar7 == 0) {
    pcVar11 = "bugout1";
LAB_00428c1a:
    iVar7 = BuildObject("apcamr",1,pcVar11,0);
    (this->field18_0x130)._s_0.dustoffcam = iVar7;
  }
  else {
    if (iVar7 == 1) {
      pcVar11 = "bugout2";
      goto LAB_00428c1a;
    }
    if (iVar7 == 2) {
      pcVar11 = "bugout3";
      goto LAB_00428c1a;
    }
    if (iVar7 == 3) {
      pcVar11 = "bugout4";
      goto LAB_00428c1a;
    }
  }
  SetObjectiveName((this->field18_0x130)._s_0.dustoffcam,"Dust Off");
  (this->field16_0x40)._s_0.pickupset = false;
  (this->field16_0x40)._s_0.pickupreached = true;
  SetObjectiveOff((this->field18_0x130)._s_0.launchpad);
LAB_00428c59:
  if (((this->field16_0x40)._s_0.bustout == true) &&
     (bVar6 = IsAlive(&(this->field18_0x130)._s_0.dustoffcam), !bVar6)) {
    (this->field16_0x40)._s_0.pickupset = true;
  }
  piVar3 = &(this->field18_0x130)._s_0.avrec;
  fVar9 = GetDistance(*piVar3,(this->field18_0x130)._s_0.dustoffcam);
  if (((fVar9 < 100.0) &&
      (fVar9 = GetDistance(*piVar1,(this->field18_0x130)._s_0.dustoffcam), fVar9 < 100.0)) &&
     ((this->field16_0x40)._s_0.pickupreached == true)) {
    AudioMessage("misn0649.wav");
    pcVar11 = "misn06w1.des";
    fVar9 = Get_Time();
    SucceedMission(fVar9 + 5.0,pcVar11);
    (this->field16_0x40)._s_0.pickupreached = false;
    (this->field16_0x40)._s_0.dustoff = true;
    (this->field16_0x40)._s_0.newobjective = true;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.platoonarrive < fVar9) &&
      ((this->field16_0x40)._s_0.platoonhere == true)) &&
     (((this->field16_0x40)._s_0.reminder == true &&
      (fVar9 = Get_Time(), (this->field17_0xa4)._s_0.time1 < fVar9)))) {
    AudioMessage("misn0635.wav");
    AudioMessage("misn0648.wav");
    iVar7 = BuildObject("svfigh",2,"ccaplatoonspawn",0);
    piVar5 = &(this->field18_0x130)._s_0.ccap1;
    *piVar5 = iVar7;
    Attack(iVar7,*piVar3,1);
    SetIndependence(*piVar5,1);
    (this->field16_0x40)._s_0.platoonhere = false;
    (this->field17_0xa4)._s_0.twominsplatoon = 1e+12;
    (this->field16_0x40)._s_0.corbettalive = false;
  }
  piVar5 = &(this->field18_0x130)._s_0.ccap1;
  bVar6 = IsAlive(piVar5);
  if (bVar6) {
    iVar7 = GetNearestEnemy(*piVar5);
    (this->field18_0x130)._s_0.spawnme = iVar7;
  }
  fVar9 = GetDistance(*piVar5,(this->field18_0x130)._s_0.spawnme);
  if ((fVar9 < 410.0) && ((this->field16_0x40)._s_0.economyccaplatoon == false)) {
    iVar7 = BuildObject("svfigh",2,*piVar5);
    (this->field18_0x130)._s_0.ccap2 = iVar7;
    iVar7 = BuildObject("svfigh",2,*piVar5);
    (this->field18_0x130)._s_0.ccap3 = iVar7;
    iVar7 = BuildObject("svfigh",2,*piVar5);
    (this->field18_0x130)._s_0.ccap4 = iVar7;
    iVar7 = BuildObject("svfigh",2,*piVar5);
    (this->field18_0x130)._s_0.ccap5 = iVar7;
    iVar7 = BuildObject("svtank",2,*piVar5);
    (this->field18_0x130)._s_0.ccap6 = iVar7;
    iVar7 = BuildObject("svtank",2,*piVar5);
    (this->field18_0x130)._s_0.ccap7 = iVar7;
    iVar7 = BuildObject("svtank",2,*piVar5);
    (this->field18_0x130)._s_0.ccap8 = iVar7;
    iVar7 = BuildObject("svtank",2,*piVar5);
    (this->field18_0x130)._s_0.ccap9 = iVar7;
    Attack((this->field18_0x130)._s_0.ccap2,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap3,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap4,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap5,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap6,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap7,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap8,*piVar3,1);
    Attack((this->field18_0x130)._s_0.ccap9,*piVar3,1);
    SetIndependence((this->field18_0x130)._s_0.ccap2,1);
    SetIndependence((this->field18_0x130)._s_0.ccap3,1);
    SetIndependence((this->field18_0x130)._s_0.ccap4,1);
    SetIndependence((this->field18_0x130)._s_0.ccap5,1);
    SetIndependence((this->field18_0x130)._s_0.ccap6,1);
    SetIndependence((this->field18_0x130)._s_0.ccap7,1);
    SetIndependence((this->field18_0x130)._s_0.ccap8,1);
    SetIndependence((this->field18_0x130)._s_0.ccap9,1);
    (this->field16_0x40)._s_0.economyccaplatoon = true;
  }
  if ((((((this->field16_0x40)._s_0.platoonhere == true) &&
        ((this->field16_0x40)._s_0.respawn == false)) && (bVar6 = IsAlive(piVar5), !bVar6)) &&
      (((bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap2), !bVar6 &&
        (bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap3), !bVar6)) &&
       ((bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap4), !bVar6 &&
        ((bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap5), !bVar6 &&
         (bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap6), !bVar6)))))))) &&
     ((bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap7), !bVar6 &&
      ((bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap8), !bVar6 &&
       (bVar6 = IsAlive(&(this->field18_0x130)._s_0.ccap9), !bVar6)))))) {
    iVar7 = BuildObject("svfigh",2,"ccaplatoonspawn",0);
    *piVar5 = iVar7;
    (this->field16_0x40)._s_0.respawn = true;
    (this->field16_0x40)._s_0.economyccaplatoon = false;
  }
  fVar9 = Get_Time();
  if (((this->field17_0xa4)._s_0.twominsplatoon < fVar9) &&
     ((this->field16_0x40)._s_0.corbettalive == true)) {
    (this->field16_0x40)._s_0.corbettalive = false;
  }
  fVar9 = Get_Time();
  if ((((this->field17_0xa4)._s_0.platoonarrive < fVar9) &&
      ((this->field16_0x40)._s_0.platoonhere == true)) &&
     ((this->field16_0x40)._s_0.reminder == false)) {
    iVar7 = AudioMessage("misn0635.wav");
    (this->field19_0x310)._s_0.aud102 = iVar7;
    iVar7 = AudioMessage("misn0646.wav");
    (this->field19_0x310)._s_0.aud103 = iVar7;
    iVar7 = AudioMessage("misn0651.wav");
    (this->field19_0x310)._s_0.aud104 = iVar7;
    (this->field16_0x40)._s_0.platoonhere = false;
    (this->field16_0x40)._s_0.endme = true;
  }
  if ((((this->field16_0x40)._s_0.endme == true) &&
      (bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud102), bVar6)) &&
     ((bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud103), bVar6 &&
      (bVar6 = IsAudioMessageDone((this->field19_0x310)._s_0.aud104), bVar6)))) {
    pcVar11 = "misn06l4.des";
    fVar9 = Get_Time();
    FailMission(fVar9,pcVar11);
  }
  bVar6 = IsAlive(piVar1);
  if ((!bVar6) && (bVar6 = IsOdf(*piVar1,"asuser"), bVar6)) {
    pcVar11 = (char *)0x0;
    fVar9 = Get_Time();
    FailMission(fVar9 + 5.0,pcVar11);
  }
  return;
}
