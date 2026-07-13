
void __fastcall FUN_005156d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xf0) = uVar2;
  if (*(char *)(param_1 + 0x60) == '\0') {
    FUN_005cadd0(1,8);
    FUN_005cacb0(1,10);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x1b4));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x1b4),"Command Tower");
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x1b8));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x1b8),"Solar Array");
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf4),"recycle_point",1);
    FUN_004f6aa0();
    FUN_004f6ab0("misn0301.otf",DAT_0091755c,0x41000000,0);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 200.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xac) = (float)fVar4 + 310.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 430.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa4) = (float)fVar4 + 530.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 200) = (float)fVar4 + 430.0;
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x8c) = (float)fVar4 + 1.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe0) = (float)fVar4 + 60.0;
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1b4);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x8c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x8c)) {
      FUN_005ccfd0(*(undefined4 *)(param_1 + 0x1b4),0x42480000);
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x8c) = (float)fVar4 + 1.0;
    }
  }
  if ((*(char *)(param_1 + 0x71) == '\0') && (*(char *)(param_1 + 0x60) != '\0')) {
    uVar2 = FUN_00437d30("misn0311.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  if (*(char *)(param_1 + 0x60) != '\0') {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"recycle_point",0);
    if (((float)fVar4 < 50.0) && (*(char *)(param_1 + 0x70) == '\0')) {
      FUN_005cbd40(*(undefined4 *)(param_1 + 0xf4),0);
      *(undefined1 *)(param_1 + 0x70) = 1;
    }
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x1b4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x1b4),1);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if ((*(char *)(param_1 + 0x54) != '\0') && (*(char *)(param_1 + 0x66) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x134);
    if (cVar1 == '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x138),"retreat_path",1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa0) = (float)fVar4 + 13.0;
      *(undefined1 *)(param_1 + 0x66) = 1;
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0x138);
      if (cVar1 == '\0') {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x134),"retreat_path",1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xa0) = (float)fVar4 + 10.0;
        *(undefined1 *)(param_1 + 0x66) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x66) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xa0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa0))
       && (*(char *)(param_1 + 0x67) == '\0')) {
      FUN_00437d30("misn0312.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0302.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0301.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x67) = 1;
    }
  }
  if (*(char *)(param_1 + 0x85) == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x1b4);
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_00822d80();
      if (*(float *)(param_1 + 0xe0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe0))
      {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xe0) = (float)fVar4 + 5.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1b4),0x43480000,1,"avturr");
        *(undefined4 *)(param_1 + 0x254) = uVar2;
        if (3 < *(int *)(param_1 + 0x254)) {
          FUN_004f6aa0();
          FUN_004f6ab0("misn0302.otf",DAT_009175b0,0x41000000,0);
          FUN_004f6ab0("misn0301.otf",DAT_0091755c,0x41000000,0);
          *(undefined1 *)(param_1 + 0x85) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x98) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x98)) {
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x140) = uVar2;
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x144) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x1b4),1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x1b4),1);
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
  }
  if (*(char *)(param_1 + 0x56) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac)) {
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x14c) = uVar2;
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x150) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x14c),*(undefined4 *)(param_1 + 0x1b4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x150),*(undefined4 *)(param_1 + 0x1b4),1);
      *(undefined1 *)(param_1 + 0x56) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x72) == '\0') && (*(char *)(param_1 + 0x56) != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x134);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x104),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x104),1);
    }
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if (*(char *)(param_1 + 0x57) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0)) {
      uVar2 = FUN_005c8250("svapc",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x158) = uVar2;
      uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x15c) = uVar2;
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x164) = uVar2;
      cVar1 = FUN_005c84d0(param_1 + 0xf4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x1bc);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1c0);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x158),*(undefined4 *)(param_1 + 0x1c0),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x158),*(undefined4 *)(param_1 + 0x1bc),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x158),*(undefined4 *)(param_1 + 0xf4),1);
      }
      FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 0x1b8),1);
      *(undefined1 *)(param_1 + 0x57) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x73) == '\0') && (*(char *)(param_1 + 0x57) != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x104);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x108);
        if (cVar1 == '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x164),*(undefined4 *)(param_1 + 0x108),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x164),*(undefined4 *)(param_1 + 0x104),1);
      }
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 200) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 200)) {
      uVar2 = FUN_005c8250("avfigh",1,"spawn_scrap2",0,0);
      *(undefined4 *)(param_1 + 0x1c4) = uVar2;
      uVar2 = FUN_005c8250("avtank",1,"spawn_scrap2",0,0);
      *(undefined4 *)(param_1 + 0x1c8) = uVar2;
      FUN_00437d30("misn0314.wav");
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x1b8),1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x1b8),1);
      *(undefined1 *)(param_1 + 0x5b) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x5b) != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x1c4);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1b8);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1c4),
                                      *(undefined4 *)(param_1 + 0x1b8));
        if ((float)fVar4 < 75.0) {
          FUN_005cbd40(*(undefined4 *)(param_1 + 0x1c4),0);
          *(undefined1 *)(param_1 + 0x6e) = 1;
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x5b) != '\0') && (*(char *)(param_1 + 0x6f) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x1c8);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1b8);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1c8),
                                      *(undefined4 *)(param_1 + 0x1b8));
        if ((float)fVar4 < 75.0) {
          FUN_005cbd40(*(undefined4 *)(param_1 + 0x1c8),0);
          *(undefined1 *)(param_1 + 0x6f) = 1;
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x5b) != '\0') && (*(char *)(param_1 + 0x5c) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0xf0));
    if (50.0 <= (float)fVar4) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0xf0)
                                   );
      if (50.0 <= (float)fVar4) goto LAB_00516328;
    }
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x1b8),0);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x1b8),0);
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
LAB_00516328:
  if (*(char *)(param_1 + 0x62) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xa4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa4)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa4) = (float)fVar4 + 1.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0xf0),0x43fa0000,2,"svtank");
      *(undefined4 *)(param_1 + 0x254) = uVar2;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0xf0),0x43fa0000,2,"svfigh");
      *(undefined4 *)(param_1 + 600) = uVar2;
      if ((*(int *)(param_1 + 0x254) == 0) && (*(int *)(param_1 + 600) == 0)) {
        uVar2 = FUN_00437d30("misn0305.wav");
        *(undefined4 *)(param_1 + 0x25c) = uVar2;
        *(undefined1 *)(param_1 + 0x62) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x75) == '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
    FUN_005cd2a0();
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xcc) = (float)fVar4 + 14.5;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd0) = (float)fVar4 + 7.5;
    uVar2 = FUN_005c8250("svrecy",2,"recy_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1e4) = uVar2;
    uVar2 = FUN_005c8250("svmuf",2,"muf_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1e8) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"tank1_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1ec) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"tank2_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1f0) = uVar2;
    uVar2 = FUN_005c8250("svfigh",2,"fighter1_spawn",0,0);
    *(undefined4 *)(param_1 + 500) = uVar2;
    uVar2 = FUN_005c8250("sssold",2,"guy1_spawn",0,0);
    *(undefined4 *)(param_1 + 0x20c) = uVar2;
    uVar2 = FUN_005c8250("sssold",2,"guy2_spawn",0,0);
    *(undefined4 *)(param_1 + 0x210) = uVar2;
    uVar2 = FUN_005c8250("sssold",2,"guy1_spawn",0,0);
    *(undefined4 *)(param_1 + 0x214) = uVar2;
    uVar2 = FUN_005c8250("sssold",2,"guy2_spawn",0,0);
    *(undefined4 *)(param_1 + 0x218) = uVar2;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x1e4),1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1e8),"tank1_spawn",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1ec),"that_path",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x1f0),"cool_path",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 500),"cool_path",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x20c),"guy_spot",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x210),"guy_spot",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x214),"guy_spot",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x218),"guy_spot",1);
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if ((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x77) == '\0')) {
    FUN_005cd300("movie_path",0xaf,0x352,*(undefined4 *)(param_1 + 0x1e4));
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x1e4),1);
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  if (((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x79) == '\0')) &&
     (*(char *)(param_1 + 0x77) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xd0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd0)) {
      uVar2 = FUN_005c8250("svfigh",2,"muf_spawn",0,0);
      *(undefined4 *)(param_1 + 0x200) = uVar2;
      uVar2 = FUN_005c8250("svfigh",2,"muf_spawn",0,0);
      *(undefined4 *)(param_1 + 0x204) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0x200),"tank2_spawn",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x204),"fighter1_spawn",1);
      *(undefined1 *)(param_1 + 0x79) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x76) != '\0') && (*(char *)(param_1 + 0x77) == '\0')) {
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_00822d80();
      if (*(float *)(param_1 + 0xcc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xcc))
      {
        cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x25c));
        if (cVar1 != '\0') goto LAB_00516801;
      }
    }
    else {
LAB_00516801:
      FUN_005cd4e0();
      FUN_00437d80(*(undefined4 *)(param_1 + 0x25c));
      uVar2 = FUN_005c8250("avapc",1,"apc1_spawn",0,0);
      *(undefined4 *)(param_1 + 0x128) = uVar2;
      uVar2 = FUN_005c8250("avapc",1,"apc2_spawn",0,0);
      *(undefined4 *)(param_1 + 300) = uVar2;
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa8) = (float)fVar4 + 28.0;
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb8) = (float)fVar4 + 30.0;
      FUN_005c9610(*(undefined4 *)(param_1 + 0x1b4));
      FUN_005c9610(*(undefined4 *)(param_1 + 0x1b8));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x128));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x128),"Transport 1");
      FUN_005caff0(*(undefined4 *)(param_1 + 0x128),1);
      FUN_005c95e0(*(undefined4 *)(param_1 + 300));
      FUN_005c9640(*(undefined4 *)(param_1 + 300),"Transport 2");
      FUN_005caff0(*(undefined4 *)(param_1 + 300),1);
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x1ac));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x1ac),"Launch Pad");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0311.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0312.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0303.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x77) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x77) != '\0') && (*(char *)(param_1 + 0x78) == '\0')) {
    uVar2 = FUN_00437d30("misn0306.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1e4));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1e8));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1ec));
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1f0));
    FUN_005c83e0(*(undefined4 *)(param_1 + 500));
    cVar1 = FUN_005c84d0(param_1 + 0x200);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x200));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x204);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x204));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x20c);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x20c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x210);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x210));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x214);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x214));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x218);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x218));
    }
    *(undefined1 *)(param_1 + 0x78) = 1;
  }
  if ((*(char *)(param_1 + 0x78) != '\0') && (*(char *)(param_1 + 0x5e) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xa8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa8)) {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x128),"rescue_path",1);
      FUN_005cc100(*(undefined4 *)(param_1 + 300),"rescue_path",1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x9c) = (float)fVar4 + 15.0;
      *(undefined1 *)(param_1 + 0x5e) = 1;
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
  }
  if (*(char *)(param_1 + 0x78) != '\0') {
    if (*(char *)(param_1 + 0x59) == '\0') {
      fVar4 = (float10)FUN_00822d80();
      if (*(float *)(param_1 + 0xb8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb8))
      {
        FUN_005cc100(*(undefined4 *)(param_1 + 0x194),"turret_path1",1);
        FUN_005cc100(*(undefined4 *)(param_1 + 0x198),"turret_path2",1);
        FUN_005cc100(*(undefined4 *)(param_1 + 0x19c),"turret_path3",1);
        FUN_005cc100(*(undefined4 *)(param_1 + 0x1a0),&DAT_0087e0f0,1);
        *(undefined1 *)(param_1 + 0x59) = 1;
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 0x134);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x128),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x128),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x164),*(undefined4 *)(param_1 + 300),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x168);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x168),*(undefined4 *)(param_1 + 0x128),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x16c);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x16c),*(undefined4 *)(param_1 + 300),1);
    }
  }
  if (*(char *)(param_1 + 0x5e) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c))
       && (*(char *)(param_1 + 0x5f) == '\0')) {
      FUN_00437d30("misn0315.wav");
      uVar2 = FUN_005c8250("svfigh",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x170) = uVar2;
      uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x174) = uVar2;
      uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x178) = uVar2;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x170),*(undefined4 *)(param_1 + 0x1b8),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x1b4),1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x178),&DAT_0087e0f0,1);
      *(undefined1 *)(param_1 + 0x5f) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x78) != '\0') && (*(char *)(param_1 + 0x74) == '\0')) &&
     (*(char *)(param_1 + 99) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x1ac))
    ;
    if ((float)fVar4 < 100.0) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0x1ac))
      ;
      if ((float)fVar4 < 100.0) {
        FUN_00437d30("misn0310.wav");
        cVar1 = FUN_005c84d0(param_1 + 0x128);
        if (cVar1 != '\0') {
          FUN_005c9610(*(undefined4 *)(param_1 + 0x128));
        }
        cVar1 = FUN_005c84d0(param_1 + 0x128);
        if (cVar1 != '\0') {
          FUN_005c9610(*(undefined4 *)(param_1 + 300));
        }
        FUN_004f6aa0();
        FUN_004f6ab0("misn0313.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0304.otf",DAT_0091755c,0x41000000,0);
        uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
        *(undefined4 *)(param_1 + 0x17c) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
        *(undefined4 *)(param_1 + 0x180) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
        *(undefined4 *)(param_1 + 0x184) = uVar2;
        FUN_005cb960(*(undefined4 *)(param_1 + 0x17c),&DAT_0087e0f0,1);
        FUN_005cb960(*(undefined4 *)(param_1 + 0x180),&DAT_0087e0f0,1);
        FUN_005cb960(*(undefined4 *)(param_1 + 0x184),&DAT_0087e0f0,1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xe8) = (float)fVar4 + 120.0;
        *(undefined1 *)(param_1 + 99) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 100) == '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xe8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe8)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xe8) = (float)fVar4 + 120.0;
      FUN_004f6aa0();
      FUN_004f6ab0("misn0313.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0304.otf",DAT_0091755c,0x41000000,0);
      FUN_00437d30("misn0310.wav");
      *(undefined1 *)(param_1 + 0x87) = 1;
    }
  }
  if (((*(char *)(param_1 + 100) == '\0') && (*(char *)(param_1 + 0x87) != '\0')) &&
     (*(char *)(param_1 + 0x88) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xe8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe8)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xe8) = (float)fVar4 + 120.0;
      FUN_004f6aa0();
      FUN_004f6ab0("misn0313.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0304.otf",DAT_0091755c,0x41000000,0);
      FUN_00437d30("misn0310.wav");
      *(undefined1 *)(param_1 + 0x88) = 1;
    }
  }
  if (((*(char *)(param_1 + 100) == '\0') && (*(char *)(param_1 + 99) != '\0')) &&
     (*(char *)(param_1 + 100) == '\0')) {
    iVar3 = FUN_005ca520(*(undefined4 *)(param_1 + 0xf8),0x459c4000,2,"svtank");
    if ((float)iVar3 < 5.0) {
      uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x188) = uVar2;
      uVar2 = FUN_005c8250("svtank",2,"spawn_scrap1",0,0);
      *(undefined4 *)(param_1 + 0x18c) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0x188),&DAT_0087e0f0,1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x18c),&DAT_0087e0f0,1);
    }
  }
  if (*(char *)(param_1 + 99) != '\0') {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0x1ac));
    if ((((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x74) == '\0')) &&
       (*(char *)(param_1 + 100) == '\0')) {
      *(undefined1 *)(param_1 + 100) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x84) == '\0') && (*(char *)(param_1 + 100) != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0xf4);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xf4));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x104);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x104) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x104));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x108);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x108) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x108));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x10c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x10c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x10c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x110);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x110) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x110));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x114);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x114) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x114));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x118) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x118));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x224) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x224));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x228);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x228) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x228));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x22c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x22c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x22c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x230);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x230) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x230));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x234);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x234) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x234));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x238);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x238) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x238));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x23c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x23c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x23c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x240);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x240) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x240));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x244);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x244) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x244));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x248);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x248) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x248));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1c4);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x1c4) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c4));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1c8);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x1c8) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c8));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x158);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x158) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x158));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x15c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x15c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x170);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x170) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x170));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x174);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x174) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x174));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x178);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x178) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x178));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x17c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x17c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x17c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x180);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x180) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x180));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x184);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x184) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x184));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x188);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x188) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x188));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x18c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x18c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x18c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x194);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x194) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x194));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x198);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x198) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x198));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x19c);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x19c) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x19c));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1a0);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x1a0) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x1a0));
    }
    cVar1 = FUN_005c84d0(param_1 + 0x158);
    if ((cVar1 != '\0') && (*(int *)(param_1 + 0x158) != *(int *)(param_1 + 0xf0))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x158));
    }
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe4) = (float)fVar4 + 14.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd4) = (float)fVar4 + 18.5;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd0) = (float)fVar4 + 2.0;
    uVar2 = FUN_00437d30("misn0316.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"spawna",0,0);
    *(undefined4 *)(param_1 + 0x1e4) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"spawnb",0,0);
    *(undefined4 *)(param_1 + 0x1e8) = uVar2;
    uVar2 = FUN_005c8250("svtank",2,"spawnc",0,0);
    *(undefined4 *)(param_1 + 0x1ec) = uVar2;
    FUN_005cd2a0();
    *(undefined1 *)(param_1 + 0x84) = 1;
  }
  if ((*(char *)(param_1 + 0x84) != '\0') && (*(char *)(param_1 + 0x7b) == '\0')) {
    FUN_005cd300("camera_path",*(undefined4 *)(param_1 + 0x250),0xdac,
                 *(undefined4 *)(param_1 + 0xfc));
    fVar4 = (float10)FUN_00822d60();
    uVar2 = FUN_0043d130(0xa0,*(int *)(param_1 + 0x250) - (int)((float)fVar4 * 240.0));
    *(undefined4 *)(param_1 + 0x250) = uVar2;
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  if ((*(char *)(param_1 + 0x84) != '\0') && (*(char *)(param_1 + 0x7a) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if ((float)fVar4 < *(float *)(param_1 + 0xd0) || (float)fVar4 == *(float *)(param_1 + 0xd0)) {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x1e4),1);
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x1e8),1);
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x1ec),1);
    }
    else {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x1e4),"line1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x1e8),"line2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x1ec),"line3",1);
      *(undefined1 *)(param_1 + 0x7a) = 1;
    }
  }
  if (*(char *)(param_1 + 0x84) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xe4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe4))
       && (*(char *)(param_1 + 0x83) == '\0')) {
      *(undefined1 *)(param_1 + 0x83) = 1;
    }
  }
  if (*(char *)(param_1 + 0x84) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xd4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd4))
       && (*(char *)(param_1 + 0x6d) == '\0')) {
      FUN_005cd300("inbase_path",0xa0,0x5a,*(undefined4 *)(param_1 + 0x1e4));
      *(undefined1 *)(param_1 + 0x7b) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x86) == '\0')) {
    uVar2 = FUN_00437d30("misn0317.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x86) = 1;
  }
  if ((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1e4),*(undefined4 *)(param_1 + 0x100))
    ;
    if ((float)fVar4 < 20.0) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b4);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1e4),*(undefined4 *)(param_1 + 0x1b4),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(param_1 + 0x1b4),1);
        cVar1 = FUN_005c84d0(param_1 + 0x1b8);
        if (cVar1 != '\0') {
          FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1b8),0x469c4000);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x1bc);
        if (cVar1 != '\0') {
          FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1bc),0x469c4000);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x1c0);
        if (cVar1 != '\0') {
          FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1c0),0x469c4000);
        }
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xd8) = (float)fVar4 + 7.0;
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x7c) != '\0') && (*(char *)(param_1 + 0x7d) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xd8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd8)) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b4);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1b4),0x46c35000);
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x7d) != '\0') && (*(char *)(param_1 + 0x7e) == '\0')) {
    FUN_005cc100(*(undefined4 *)(param_1 + 0x1e4),"climax_path1",1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0x1e8),"spawn_scrap1",1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0x1ec),"spawn_scrap1",1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xdc) = (float)fVar4 + 6.0;
    uVar2 = FUN_00437d30("misn0318.wav");
    *(undefined4 *)(param_1 + 0x25c) = uVar2;
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  if ((*(char *)(param_1 + 0x7e) != '\0') && (*(char *)(param_1 + 0x80) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xdc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xdc)) {
      cVar1 = FUN_005c84d0(param_1 + 0x1d4);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1d4),0x469c4000);
      }
      uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(param_1 + 0xfc),0);
      *(undefined4 *)(param_1 + 0x200) = uVar2;
      FUN_005cc100(*(undefined4 *)(param_1 + 0x200),"climax_path2",1);
      *(undefined1 *)(param_1 + 0x80) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7e) != '\0') && (*(char *)(param_1 + 0x7f) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1e4),*(undefined4 *)(param_1 + 0xfc));
    if ((float)fVar4 < 100.0) {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x1e4),"climax_path2",1);
      uVar2 = FUN_005c8250("svfigh",2,"solar_spot",0,0);
      *(undefined4 *)(param_1 + 0x204) = uVar2;
      uVar2 = FUN_005c8250("svfigh",2,"solar_spot",0,0);
      *(undefined4 *)(param_1 + 0x208) = uVar2;
      FUN_005cc100(*(undefined4 *)(param_1 + 0x204),"camera_pass",1);
      FUN_005cc100(*(undefined4 *)(param_1 + 0x208),"camera_pass",1);
      cVar1 = FUN_005c84d0(param_1 + 0x1e0);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1e0),0x469c4000);
      }
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xdc) = (float)fVar4 + 3.0;
      *(undefined1 *)(param_1 + 0x7f) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7f) != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xdc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xdc)) {
      cVar1 = FUN_005c84d0(param_1 + 0x21c);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x21c),0x469c4000);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1cc);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x1cc),0x469c4000);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x11c);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x11c),0x469c4000);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x120);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x120),0x469c4000);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x124);
      if (cVar1 != '\0') {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x124),0x469c4000);
      }
      FUN_005cc100(*(undefined4 *)(param_1 + 0x1e8),"solar_spot",1);
      FUN_005cc100(*(undefined4 *)(param_1 + 0x200),"spawn_scrap1",1);
      uVar2 = FUN_005c8250("abwpow",1,"sucker_spot",0,0);
      *(undefined4 *)(param_1 + 0x220) = uVar2;
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x81) != '\0') && (*(char *)(param_1 + 0x82) == '\0')) {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1e4),*(undefined4 *)(param_1 + 0x220))
    ;
    if ((float)fVar4 < 65.0) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x1e4),*(undefined4 *)(param_1 + 0x220),1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc4) = (float)fVar4 + 1.5;
      *(undefined1 *)(param_1 + 0x82) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x6c) != '\0') && (*(char *)(param_1 + 0x6d) == '\0')) {
    cVar1 = FUN_005cd560();
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_00822d80();
      if ((float)fVar4 < *(float *)(param_1 + 0xc4) || (float)fVar4 == *(float *)(param_1 + 0xc4))
      goto LAB_0051869d;
    }
    *(undefined1 *)(param_1 + 0x84) = 0;
    FUN_005cd4e0();
    FUN_00437d80(*(undefined4 *)(param_1 + 0x25c));
    FUN_0045c110(0x3dcccccd,"misn03w1.des");
    *(undefined1 *)(param_1 + 0x6d) = 1;
  }
LAB_0051869d:
  if (*(char *)(param_1 + 0x88) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xe8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe8))
        && (*(char *)(param_1 + 100) == '\0')) && (*(char *)(param_1 + 0x74) == '\0')) {
      fVar4 = (float10)FUN_00822d80("misn03f5.des");
      FUN_0045c0f0((float)fVar4 + 1.0);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x69) == '\0') && (*(char *)(param_1 + 0x7c) == '\0')) &&
     (*(char *)(param_1 + 0x62) == '\0')) {
    cVar1 = FUN_005c8490(param_1 + 0x1b4);
    if (cVar1 == '\0') {
      FUN_00437d30("misn0302.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0311.otf",DAT_0091757c,0x41000000,0);
      FUN_004f6ab0("misn0312.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x74) = 1;
      *(undefined1 *)(param_1 + 0x69) = 1;
      if (*(char *)(param_1 + 0x85) == '\0') {
        fVar4 = (float10)FUN_00822d80("misn03f1.des");
        FUN_0045c0f0((float)fVar4 + 10.0);
      }
      else {
        fVar4 = (float10)FUN_00822d80("misn03f2.des");
        FUN_0045c0f0((float)fVar4 + 10.0);
      }
    }
  }
  if (((*(char *)(param_1 + 0x6a) == '\0') && (*(char *)(param_1 + 0x7a) == '\0')) &&
     (*(char *)(param_1 + 0x62) == '\0')) {
    cVar1 = FUN_005c8490(param_1 + 0x1b8);
    if (cVar1 == '\0') {
      FUN_00437d30("misn0303.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0311.otf",DAT_0091757c,0x41000000,0);
      FUN_004f6ab0("misn0312.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x74) = 1;
      *(undefined1 *)(param_1 + 0x6a) = 1;
      if (*(char *)(param_1 + 0x85) == '\0') {
        fVar4 = (float10)FUN_00822d80("misn03f3.des");
        FUN_0045c0f0((float)fVar4 + 10.0);
      }
      else {
        fVar4 = (float10)FUN_00822d80("misn03f3.des");
        FUN_0045c0f0((float)fVar4 + 10.0);
      }
    }
  }
  if ((*(char *)(param_1 + 0x77) != '\0') && (*(char *)(param_1 + 0x6b) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x128);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 99) == '\0')) {
      FUN_00437d30("misn0304.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0311.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0312.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0303.otf",DAT_0091757c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x74) = 1;
      *(undefined1 *)(param_1 + 0x6b) = 1;
      fVar4 = (float10)FUN_00822d80("misn03f4.des");
      FUN_0045c0f0((float)fVar4 + 10.0);
    }
  }
  if ((*(char *)(param_1 + 0x77) != '\0') && (*(char *)(param_1 + 0x6b) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 300);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 99) == '\0')) {
      FUN_00437d30("misn0304.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0311.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0312.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0303.otf",DAT_0091757c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x74) = 1;
      *(undefined1 *)(param_1 + 0x6b) = 1;
      fVar4 = (float10)FUN_00822d80("misn03f4.des");
      FUN_0045c0f0((float)fVar4 + 10.0);
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1ac);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x74) == '\0')) {
    fVar4 = (float10)FUN_00822d80(0);
    FUN_0045c0f0((float)fVar4 + 1.0);
    *(undefined1 *)(param_1 + 0x74) = 1;
  }
  return;
}

