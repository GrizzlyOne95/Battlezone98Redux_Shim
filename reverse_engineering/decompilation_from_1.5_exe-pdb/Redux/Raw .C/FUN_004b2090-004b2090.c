
void __fastcall FUN_004b2090(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *_Filename;
  FILE *_File;
  Root *pRVar5;
  RenderSystem *pRVar6;
  float10 fVar7;
  float fVar8;
  char *_Mode;
  undefined4 uVar9;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849758;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0xe4) = *(int *)(param_1 + 0xe4) + 1;
  iVar3 = FUN_00417c70(uVar2);
  if (*(char *)(param_1 + 0x56) == '\0') {
    uVar9 = 0;
    fVar7 = (float10)FUN_004b1670(uVar2,0);
    *(float *)(param_1 + 0x7c) = (float)fVar7;
    if (*(char *)(param_1 + 0x66) == '\0') {
      *(undefined1 *)(param_1 + 0x66) = 1;
      fVar7 = (float10)FUN_004b1670(uVar2,uVar9);
      *(float *)(param_1 + 0x78) = (float)fVar7;
      FUN_005cd2a0();
    }
    uVar9 = FUN_005c8250("avdemo",1,"spawn_point",0);
    *(undefined4 *)(param_1 + 0x88) = uVar9;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x88),"go_path");
    *(undefined1 *)(param_1 + 0x56) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
    uVar9 = FUN_005c8250("svhraz",2,&DAT_00878670,0);
    *(undefined4 *)(param_1 + 0x90) = uVar9;
    uVar9 = FUN_005c8250("svltnk",2,&DAT_008786e4,0);
    *(undefined4 *)(param_1 + 0x94) = uVar9;
    uVar9 = FUN_005c8250("svltnk",2,&DAT_008786e4,0);
    *(undefined4 *)(param_1 + 0x98) = uVar9;
    uVar9 = FUN_005c8250("svrckt",2,&DAT_008786e4,0);
    *(undefined4 *)(param_1 + 0x9c) = uVar9;
    uVar9 = FUN_005c8250("avhraz",1,"friend1",0);
    *(undefined4 *)(param_1 + 0xa0) = uVar9;
    uVar9 = FUN_005c8250("avartl",1,&DAT_008786cc,0);
    *(undefined4 *)(param_1 + 0xa4) = uVar9;
    uVar9 = FUN_005c8250("sbcomm",2,"build1",0);
    *(undefined4 *)(param_1 + 0xa8) = uVar9;
    uVar9 = FUN_005c8250("sbspow",2,"build2",0);
    *(undefined4 *)(param_1 + 0xac) = uVar9;
    uVar9 = FUN_005c8250("sbhang",2,"build3",0);
    *(undefined4 *)(param_1 + 0xb0) = uVar9;
    uVar9 = FUN_005c8250("sblpow",2,"build4",0);
    *(undefined4 *)(param_1 + 0xb4) = uVar9;
    uVar9 = FUN_005c8250("sbhqcp",2,"build5",0);
    *(undefined4 *)(param_1 + 0xb8) = uVar9;
    uVar9 = FUN_005c8250("sbwpow",2,"build6",0);
    *(undefined4 *)(param_1 + 0xbc) = uVar9;
    uVar9 = FUN_005c8250("sbwpow",2,"build7",0);
    *(undefined4 *)(param_1 + 0xc0) = uVar9;
    uVar9 = FUN_005c8250("sbwpow",2,"build8",0);
    *(undefined4 *)(param_1 + 0xc4) = uVar9;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0xa8));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xa8));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xa8));
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x9c),*(undefined4 *)(param_1 + 0xa8));
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0x88));
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    iVar4 = FUN_00462630();
    (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
    (**(code **)(*(int *)(iVar4 + 0x18) + 0xc))();
    iVar3 = *(int *)(param_1 + 0xe8);
    if (iVar3 == 0) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x88),0,800,0xfffffa24);
    }
    else if (iVar3 == 1) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x88),0xfffffa24,800,0);
    }
    else if (iVar3 == 2) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x88),0,800,0x5dc);
    }
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x68)) {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar7 + 7.0;
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (2 < *(int *)(param_1 + 0xe8)) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
    }
    fVar7 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x90));
    if ((float)fVar7 < 200.0) {
      *(undefined1 *)(param_1 + 0x54) = 0;
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cb820(*(undefined4 *)(param_1 + 0xa4),*(undefined4 *)(param_1 + 0x90));
    }
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x68)) {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar7 + 7.0;
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (2 < *(int *)(param_1 + 0xe8)) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    cVar1 = FUN_005c84d0();
    if (cVar1 != '\0') {
      FUN_005cb1c0(*(undefined4 *)(param_1 + 0xac));
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_005cd300("camera1",1000,0);
    }
    else if (*(int *)(param_1 + 0xe8) == 1) {
      cVar1 = FUN_005c84d0();
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0();
        if (cVar1 != '\0') {
          FUN_005cd440(*(undefined4 *)(param_1 + 0x88),0xfffffda8,400,0);
        }
      }
      else {
        FUN_005cd440(*(undefined4 *)(param_1 + 0x88),0xfffffda8,400,0);
      }
    }
    fVar7 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x68) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x68)) {
      fVar7 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x68) = (float)fVar7 + 7.0;
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (1 < *(int *)(param_1 + 0xe8)) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
    }
  }
  cVar1 = FUN_005c84d0();
  if ((cVar1 == '\0') ||
     (fVar7 = (float10)FUN_004b1670(), *(float *)(param_1 + 0x7c) + 55.0 < (float)fVar7)) {
    *(int *)(param_1 + 0xe0) = *(int *)(param_1 + 0xe0) + 1;
    if (*(int *)(param_1 + 0xe0) < 5) {
      FUN_004b1f70();
      *(undefined1 *)(param_1 + 0x56) = 0;
      *(undefined1 *)(param_1 + 0x54) = 0;
      *(undefined1 *)(param_1 + 0x55) = 0;
    }
    else if (*(char *)(param_1 + 0x65) == '\0') {
      FUN_00426a60(&DAT_02cf3000,0);
      local_8 = 0;
      FUN_00426af0();
      FUN_00417fd0();
      _Mode = "w+";
      _Filename = (char *)FUN_0041f870();
      _File = fopen(_Filename,_Mode);
      ~basic_string<>();
      fprintf(_File,"Battlezone Benchmark Test \n\n");
      fVar7 = (float10)FUN_004b1670();
      fVar8 = (float)fVar7 - *(float *)(param_1 + 0x78);
      cVar1 = *(char *)(DAT_0094672c + 0x25);
      basic_string<>();
      local_8._0_1_ = 1;
      pRVar5 = Ogre::Root::getSingleton();
      pRVar6 = Ogre::Root::getRenderSystem(pRVar5);
      (**(code **)(*(int *)pRVar6 + 0xc))();
      FUN_004b2f10();
      FUN_0041f870();
      fprintf(_File,"Resolution: %s\n");
      local_8._0_1_ = 0;
      ~basic_string<>();
      basic_string<>();
      local_8._0_1_ = 2;
      pRVar5 = Ogre::Root::getSingleton();
      pRVar6 = Ogre::Root::getRenderSystem(pRVar5);
      (**(code **)(*(int *)pRVar6 + 0xc))();
      FUN_004b2f10();
      FUN_0041f870();
      fprintf(_File,"Full Screen: %s\n");
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      fprintf(_File,"Detail Level: %s\n");
      if (cVar1 < '\0') {
        fprintf(_File,"Shadow Level : Off\n");
      }
      else {
        fprintf(_File,"Shadow Level : %d\n");
      }
      fprintf(_File,"Total time : %f \n",(double)fVar8);
      fprintf(_File,"Average frame rate : %f \n\n",(double)((float)*(int *)(param_1 + 0xe4) / fVar8)
             );
      fprintf(_File,"This benchmark was created by George Collins.\n");
      fclose(_File);
      fVar7 = (float10)FUN_004b1670();
      FUN_0045c110((float)fVar7 + 1.0);
      *(undefined1 *)(param_1 + 0x65) = 1;
      local_8 = 0xffffffff;
      FUN_004180b0();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

