/*
 * Entry: 004113aa
 * Name: DemoMission::Execute
 * Namespace: DemoMission
 * Signature: void Execute(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DemoMission::Execute(DemoMission *this)

{
  DemoMission_u_204 *pDVar1;
  int iVar2;
  GameObject *pGVar3;
  bool bVar4;
  int iVar5;
  GameObject *pGVar6;
  uint uVar7;
  FILE *_File;
  int *piVar8;
  float fVar9;
  longlong lVar10;
  
  piVar8 = &(this->field20_0xcc)._s_0.frame_count;
  *piVar8 = *piVar8 + 1;
  pGVar3 = GameObject::userObject;
  if ((this->field16_0x40)._s_0.start_done == false) {
    fVar9 = Get_Time();
    (this->field17_0x54)._s_0.cycle_time = fVar9;
    if ((this->field16_0x40)._s_0.first_start == false) {
      (this->field16_0x40)._s_0.first_start = true;
      fVar9 = Get_Time();
      (this->field17_0x54)._s_0.time = fVar9;
      CameraReady();
    }
    StartProfiler(0);
    iVar5 = BuildObject("avdemo",1,"spawn_point",0);
    (this->field18_0x70)._s_0.target = iVar5;
    Goto(iVar5,"go_path",1);
    (this->field16_0x40)._s_0.start_done = true;
    (this->field16_0x40)._s_0.camera1 = true;
    iVar5 = BuildObject("svhraz",2,"foe1",0);
    (this->field18_0x70)._s_0.foe1 = iVar5;
    iVar5 = BuildObject("svltnk",2,"foe2",0);
    (this->field18_0x70)._s_0.foe2 = iVar5;
    iVar5 = BuildObject("svltnk",2,"foe2",0);
    (this->field18_0x70)._s_0.foe3 = iVar5;
    iVar5 = BuildObject("svrckt",2,"foe2",0);
    (this->field18_0x70)._s_0.foe4 = iVar5;
    iVar5 = BuildObject("avhraz",1,"friend1",0);
    (this->field18_0x70)._s_0.friend1 = iVar5;
    iVar5 = BuildObject("avartl",1,"art1",0);
    (this->field18_0x70)._s_0.art1 = iVar5;
    iVar5 = BuildObject("sbcomm",2,"build1",0);
    (this->field18_0x70)._s_0.build1 = iVar5;
    iVar5 = BuildObject("sbspow",2,"build2",0);
    (this->field18_0x70)._s_0.build2 = iVar5;
    iVar5 = BuildObject("sbhang",2,"build3",0);
    (this->field18_0x70)._s_0.build3 = iVar5;
    iVar5 = BuildObject("sblpow",2,"build4",0);
    (this->field18_0x70)._s_0.build4 = iVar5;
    iVar5 = BuildObject("sbhqcp",2,"build5",0);
    (this->field18_0x70)._s_0.build5 = iVar5;
    iVar5 = BuildObject("sbwpow",2,"build6",0);
    (this->field18_0x70)._s_0.build6 = iVar5;
    iVar5 = BuildObject("sbwpow",2,"build7",0);
    (this->field18_0x70)._s_0.build7 = iVar5;
    iVar5 = BuildObject("sbwpow",2,"build8",0);
    (this->field18_0x70)._s_0.build8 = iVar5;
    Goto((this->field18_0x70)._s_0.foe1,(this->field18_0x70)._s_0.build1,1);
    Goto((this->field18_0x70)._s_0.foe2,(this->field18_0x70)._s_0.build1,1);
    Goto((this->field18_0x70)._s_0.foe3,(this->field18_0x70)._s_0.build1,1);
    Goto((this->field18_0x70)._s_0.foe4,(this->field18_0x70)._s_0.build1,1);
    Follow((this->field18_0x70)._s_0.friend1,(this->field18_0x70)._s_0.target,1);
  }
  if ((this->field16_0x40)._s_0.camera1 != false) {
    pGVar6 = GameObjectHandle::GetObj((this->field18_0x70)._s_0.target);
    (**(code **)(pGVar3->_padding_ + 0xc))();
    (**(code **)(pGVar6->_padding_ + 0xc))();
    iVar5 = (this->field20_0xcc)._s_0.angle;
    if (iVar5 == 0) {
      uVar7 = (this->field18_0x70)._s_0.target;
      lVar10 = CONCAT44(uVar7,0xfffffa24);
LAB_00411612:
      iVar5 = 0;
LAB_00411618:
      CameraObject(uVar7,iVar5,800,(int)lVar10,(int)((ulonglong)lVar10 >> 0x20));
    }
    else {
      if (iVar5 == 1) {
        uVar7 = (this->field18_0x70)._s_0.target;
        lVar10 = (ulonglong)uVar7 << 0x20;
        iVar5 = -0x5dc;
        goto LAB_00411618;
      }
      if (iVar5 == 2) {
        uVar7 = (this->field18_0x70)._s_0.target;
        lVar10 = CONCAT44(uVar7,0x5dc);
        goto LAB_00411612;
      }
    }
    fVar9 = Get_Time();
    if ((this->field17_0x54)._s_0.camera_time < fVar9) {
      fVar9 = Get_Time();
      piVar8 = &(this->field20_0xcc)._s_0.angle;
      *piVar8 = *piVar8 + 1;
      iVar5 = (this->field20_0xcc)._s_0.angle;
      (this->field17_0x54)._s_0.camera_time = fVar9 + 7.0;
      if (2 < iVar5) {
        (this->field20_0xcc)._s_0.angle = 0;
      }
    }
    fVar9 = GetDistance((this->field18_0x70)._s_0.foe1,(this->field18_0x70)._s_0.target);
    if (fVar9 < 200.0) {
      iVar5 = (this->field18_0x70)._s_0.foe1;
      (this->field16_0x40)._s_0.camera1 = false;
      iVar2 = (this->field18_0x70)._s_0.art1;
      (this->field16_0x40)._s_0.camera2 = true;
      Attack(iVar2,iVar5,1);
    }
    fVar9 = Get_Time();
    if ((this->field17_0x54)._s_0.camera_time < fVar9) {
      fVar9 = Get_Time();
      piVar8 = &(this->field20_0xcc)._s_0.angle;
      *piVar8 = *piVar8 + 1;
      iVar5 = (this->field20_0xcc)._s_0.angle;
      (this->field17_0x54)._s_0.camera_time = fVar9 + 7.0;
      if (2 < iVar5) {
        (this->field20_0xcc)._s_0.angle = 0;
      }
    }
  }
  if ((this->field16_0x40)._s_0.camera2 == false) goto LAB_0041176a;
  piVar8 = &(this->field18_0x70)._s_0.build2;
  bVar4 = IsAlive(piVar8);
  if (bVar4) {
    Damage(*piVar8,0x32);
  }
  iVar5 = (this->field20_0xcc)._s_0.angle;
  if (iVar5 == 0) {
    CameraPath("camera1",1000,0,(this->field18_0x70)._s_0.target);
  }
  else if (iVar5 == 1) {
    piVar8 = &(this->field18_0x70)._s_0.foe1;
    bVar4 = IsAlive(piVar8);
    if (!bVar4) {
      piVar8 = &(this->field18_0x70)._s_0.foe2;
      bVar4 = IsAlive(piVar8);
      if (!bVar4) goto LAB_00411738;
    }
    CameraObject((this->field18_0x70)._s_0.target,-600,400,0,*piVar8);
  }
LAB_00411738:
  fVar9 = Get_Time();
  if ((this->field17_0x54)._s_0.camera_time < fVar9) {
    fVar9 = Get_Time();
    piVar8 = &(this->field20_0xcc)._s_0.angle;
    *piVar8 = *piVar8 + 1;
    iVar5 = (this->field20_0xcc)._s_0.angle;
    (this->field17_0x54)._s_0.camera_time = fVar9 + 7.0;
    if (1 < iVar5) {
      (this->field20_0xcc)._s_0.angle = 0;
    }
  }
LAB_0041176a:
  bVar4 = IsAlive(&(this->field18_0x70)._s_0.target);
  if ((bVar4) && (fVar9 = Get_Time(), fVar9 <= (this->field17_0x54)._s_0.cycle_time + 55.0)) {
    return;
  }
  pDVar1 = &this->field20_0xcc;
  (pDVar1->_s_0).cycle_count = (pDVar1->_s_0).cycle_count + 1;
  if ((pDVar1->_s_0).cycle_count < 5) {
    KillStuff();
    (this->field16_0x40)._s_0.start_done = false;
    (this->field16_0x40)._s_0.camera1 = false;
    (this->field16_0x40)._s_0.camera2 = false;
  }
  else if ((this->field16_0x40)._s_0.lost == false) {
    _File = fopen("addon\\bzbench.des","w+");
    fprintf(_File,"Battlezone Benchmark Test \n\n");
    fVar9 = Get_Time();
    fVar9 = fVar9 - (this->field17_0x54)._s_0.time;
    fprintf(_File,"Total time : %f \n",(double)fVar9);
    fprintf(_File,"Average frame rate : %f \n\n",
            (double)((float)(this->field20_0xcc)._s_0.frame_count / fVar9));
    fprintf(_File,"This benchmark was created by George Collins.\n");
    fclose(_File);
    (this->field16_0x40)._s_0.lost = true;
                    /* WARNING: Subroutine does not return */
    QuickExit();
  }
  return;
}
