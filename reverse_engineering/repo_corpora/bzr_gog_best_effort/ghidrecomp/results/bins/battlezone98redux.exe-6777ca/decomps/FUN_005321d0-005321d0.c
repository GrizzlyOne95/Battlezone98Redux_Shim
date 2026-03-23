
void __fastcall FUN_005321d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  char local_9;
  
  if (*(char *)(param_1 + 0x6e) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x104);
    if (cVar1 != '\0') {
      uVar2 = FUN_005cd240(*(undefined4 *)(param_1 + 0x104));
      *(undefined4 *)(param_1 + 0x1a8) = uVar2;
      cVar1 = FUN_005c84d0(param_1 + 0x1a8);
      if (cVar1 != '\0') {
        iVar3 = FUN_005c8800(*(undefined4 *)(param_1 + 0x1a8));
        if (iVar3 == 1) {
          *(undefined1 *)(param_1 + 0x6e) = 0;
          *(undefined1 *)(param_1 + 0x6c) = 1;
        }
        else {
          *(undefined1 *)(param_1 + 0x6e) = 0;
          *(undefined1 *)(param_1 + 0x6d) = 1;
          *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_1 + 0x118);
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x6c) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x1a8);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x6e) = 1;
      *(undefined1 *)(param_1 + 0x6c) = 0;
    }
  }
  if (*(char *)(param_1 + 0x6d) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x6e) = 1;
      *(undefined1 *)(param_1 + 0x6d) = 0;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x104);
  if (cVar1 != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0x6e) != '\0')) &&
       (*(char *)(param_1 + 0x6f) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x104),1);
      *(undefined1 *)(param_1 + 0x6f) = 1;
    }
    if ((*(char *)(param_1 + 0x6d) != '\0') && (*(char *)(param_1 + 0x70) == '\0')) {
      FUN_005cc5f0(*(undefined4 *)(param_1 + 0x118),"soviet_path",1);
      *(undefined1 *)(param_1 + 0x70) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x118);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x6f) = 0;
    *(undefined1 *)(param_1 + 0x70) = 0;
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x100) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cd2a0();
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cadd0(2,0x28);
    FUN_005cacb0(2,0x28);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1a4),*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 400),*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x188),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0x1a4),0);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x128),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 300),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x130),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x134),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x138),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x13c),1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x90) = (float)fVar4 + 6.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa8) = (float)fVar4 + 3.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 700.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 1000.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xa0) = (float)fVar4 + 1300.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 1360.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 200) = (float)fVar4 + 15.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xcc) = (float)fVar4 + 11.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xec) = (float)fVar4 + 6.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf0) = (float)fVar4 + 30.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd0) = (float)fVar4 + 22.0;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x108),"Choke Point");
    *(undefined1 *)(param_1 + 0x88) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  if (*(char *)(param_1 + 0x88) != '\0') {
    FUN_005cd300("camera_circle",0x177,0x2ee,*(undefined4 *)(param_1 + 0x114));
  }
  local_9 = '\0';
  if (*(char *)(param_1 + 0x73) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((float)fVar4 < *(float *)(param_1 + 0xd0) || (float)fVar4 == *(float *)(param_1 + 0xd0)) {
      local_9 = FUN_005cd560();
      if (local_9 == '\0') goto LAB_00532790;
    }
    if (local_9 != '\0') {
      FUN_00437d80(*(undefined4 *)(param_1 + 0x1ec));
      *(undefined4 *)(param_1 + 0x1ec) = 0;
    }
    FUN_004f6aa0();
    FUN_004f6ab0("misn0900.otf",DAT_0091755c,0x41000000,0);
    FUN_005cd4e0();
    *(undefined1 *)(param_1 + 0x88) = 0;
    *(undefined1 *)(param_1 + 0x73) = 1;
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
LAB_00532790:
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0x90) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x90)) &&
     (*(char *)(param_1 + 0x82) == '\0')) {
    uVar2 = FUN_00437d30("misn0900.wav");
    *(undefined4 *)(param_1 + 0x1ec) = uVar2;
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  if ((*(char *)(param_1 + 0x82) != '\0') && (*(char *)(param_1 + 0x83) == '\0')) {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1ec));
    if (cVar1 != '\0') {
      FUN_004f6aa0();
      FUN_004f6ab0("misn0900.otf",DAT_0091755c,0x41000000,0);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x188),"return_path",1);
      *(undefined1 *)(param_1 + 0x83) = 1;
    }
  }
  if (*(char *)(param_1 + 0x83) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xa8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa8))
       && (*(char *)(param_1 + 0x5f) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa8) = (float)fVar4 + 1.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                    *(undefined4 *)(param_1 + 0x188));
      if ((float)fVar4 < 70.0) {
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x188),0);
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x1a0),0);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1a4),0);
        FUN_005cadd0(1,0x14);
        FUN_005cacb0(1,7);
        FUN_00437d30("misn0905.wav");
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xac) = (float)fVar4 + 7.0;
        *(undefined1 *)(param_1 + 0x5f) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x5a) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 200) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 200)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 200) = (float)fVar4 + 15.0;
      cVar1 = FUN_005c84d0(param_1 + 0x128);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x128),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 300);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 300),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x130);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x130),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x134);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x134),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x138);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x138),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x13c);
      if (cVar1 != '\0') {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x13c),1);
      }
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xec) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xec)) &&
     (*(char *)(param_1 + 0x7d) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xec) = (float)fVar4 + 2.0;
    cVar1 = FUN_005c84d0(param_1 + 0x188);
    if (cVar1 != '\0') {
      cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x188));
      if (cVar1 != '\0') {
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x7d) == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x110);
    if (cVar1 != '\0') goto LAB_00532b85;
  }
  else {
LAB_00532b85:
    if (*(char *)(param_1 + 0x7e) == '\0') {
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x18c),0);
      FUN_005cbd40(*(undefined4 *)(param_1 + 400),0);
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x194),0);
      *(undefined1 *)(param_1 + 0x7e) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x13c);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x5f) != '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))
       && (*(char *)(param_1 + 0x56) == '\0')) {
      FUN_005cd2a0();
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xe4) = (float)fVar4 + 7.0;
      *(undefined1 *)(param_1 + 0x56) = 1;
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xf8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xf8)) &&
     (*(char *)(param_1 + 0x84) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf8) = (float)fVar4 + 1.0;
    FUN_00437d30("misn0913.wav");
    *(undefined1 *)(param_1 + 0x84) = 1;
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xf8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xf8)) &&
     (*(char *)(param_1 + 0x85) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf8) = (float)fVar4 + 2.0;
    cVar1 = FUN_005c84d0(param_1 + 0x108);
    if (cVar1 == '\0') {
LAB_00532d50:
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                      *(undefined4 *)(param_1 + 0x160));
        if ((float)fVar4 < 400.0) goto LAB_00532de8;
      }
      cVar1 = FUN_005c84d0(param_1 + 0x164);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                      *(undefined4 *)(param_1 + 0x164));
        if ((float)fVar4 < 400.0) goto LAB_00532de8;
      }
    }
    else {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                    *(undefined4 *)(param_1 + 0x108));
      if (100.0 <= (float)fVar4) goto LAB_00532d50;
LAB_00532de8:
      FUN_00437d30("misn0914.wav");
      *(undefined1 *)(param_1 + 0x85) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x76) == '\0')) {
    FUN_005cd440(*(undefined4 *)(param_1 + 0x13c),3000,3000,3000,*(undefined4 *)(param_1 + 0x13c));
    if (*(char *)(param_1 + 0x75) == '\0') {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xd4) = (float)fVar4 + 2.0;
      *(undefined1 *)(param_1 + 0x75) = 1;
    }
  }
  if (*(char *)(param_1 + 0x75) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xd4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd4))
       && (*(char *)(param_1 + 0x77) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x138),3000,3000,3000,*(undefined4 *)(param_1 + 0x138))
      ;
      if (*(char *)(param_1 + 0x76) == '\0') {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xd8) = (float)fVar4 + 2.0;
        *(undefined1 *)(param_1 + 0x76) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x76) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xd8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd8))
       && (*(char *)(param_1 + 0x78) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x134),3000,3000,3000,*(undefined4 *)(param_1 + 0x134))
      ;
      if (*(char *)(param_1 + 0x77) == '\0') {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xdc) = (float)fVar4 + 2.0;
        *(undefined1 *)(param_1 + 0x77) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x77) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xdc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xdc))
       && (*(char *)(param_1 + 0x79) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x130),3000,3000,3000,*(undefined4 *)(param_1 + 0x130))
      ;
      if (*(char *)(param_1 + 0x78) == '\0') {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xe0) = (float)fVar4 + 2.0;
        *(undefined1 *)(param_1 + 0x78) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x78) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xe0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe0))
       && (*(char *)(param_1 + 0x7a) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 300),3000,3000,3000,*(undefined4 *)(param_1 + 300));
      if (*(char *)(param_1 + 0x79) == '\0') {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xe4) = (float)fVar4 + 2.0;
        *(undefined1 *)(param_1 + 0x79) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x79) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xe4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe4))
       && (*(char *)(param_1 + 0x7a) == '\0')) {
      FUN_005cd4e0();
      FUN_004f6aa0();
      FUN_004f6ab0("misn0900.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0901.otf",DAT_0091755c,0x41000000,0);
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x1a4),0);
      FUN_005cb2d0("misn09.aip",2);
      *(undefined1 *)(param_1 + 0x7a) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x140);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x67) == '\0')) {
    uVar2 = FUN_005c8250("svturr",2,"post1",0,0);
    *(undefined4 *)(param_1 + 0x150) = uVar2;
    *(undefined1 *)(param_1 + 0x67) = 1;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x150),1);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x140);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x68) == '\0')) {
    uVar2 = FUN_005c8250("svturr",2,"post2",0,0);
    *(undefined4 *)(param_1 + 0x154) = uVar2;
    *(undefined1 *)(param_1 + 0x68) = 1;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x154),1);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x140);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x69) == '\0')) {
    uVar2 = FUN_005c8250("svturr",2,"post3",0,0);
    *(undefined4 *)(param_1 + 0x158) = uVar2;
    *(undefined1 *)(param_1 + 0x69) = 1;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x158),1);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x140);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6a) == '\0')) {
    uVar2 = FUN_005c8250("svturr",2,"post4",0,0);
    *(undefined4 *)(param_1 + 0x15c) = uVar2;
    *(undefined1 *)(param_1 + 0x6a) = 1;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x15c),1);
  }
  cVar1 = FUN_005c84d0(param_1 + 0x128);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 300);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x130);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x134);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x138);
          if (cVar1 == '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x13c);
            if ((cVar1 == '\0') && (*(char *)(param_1 + 0x5a) == '\0')) {
              FUN_00437d30("misn0904.wav");
              FUN_005cbd40(*(undefined4 *)(param_1 + 0x18c),0);
              FUN_005cbd40(*(undefined4 *)(param_1 + 400),0);
              FUN_005cbd40(*(undefined4 *)(param_1 + 0x194),0);
              FUN_004f6aa0();
              FUN_004f6ab0("misn0901.otf",DAT_009175b0,0x41000000,0);
              FUN_004f6ab0("misn0902.otf",DAT_0091755c,0x41000000,0);
              FUN_004f6ab0("misn0903.otf",DAT_0091755c,0x41000000,0);
              if (*(char *)(param_1 + 0x5d) == '\0') {
                FUN_005cb2d0("misn09a.aip",2);
              }
              *(undefined1 *)(param_1 + 0x5a) = 1;
            }
          }
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x5b) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x98) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x98)) {
      FUN_00437d30("misn0901.wav");
      *(undefined1 *)(param_1 + 0x5b) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c)) {
      FUN_00437d30("misn0902.wav");
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5d) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xa0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa0)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa0) = (float)fVar4 + 11.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                    *(undefined4 *)(param_1 + 0x120));
      if (500.0 < (float)fVar4) {
        uVar2 = FUN_005c8080("obdata",0,*(undefined4 *)(param_1 + 0x120),0);
        *(undefined4 *)(param_1 + 0x104) = uVar2;
        uVar2 = FUN_005c8250("svhaul",2,"spawn1",0,0);
        *(undefined4 *)(param_1 + 0x118) = uVar2;
        uVar2 = FUN_005c8250("svfigh",2,"spawn2",0,0);
        *(undefined4 *)(param_1 + 0x1ac) = uVar2;
        uVar2 = FUN_005c8250("svfigh",2,"spawn2",0,0);
        *(undefined4 *)(param_1 + 0x1b0) = uVar2;
        uVar2 = FUN_005c8250("svfigh",2,"spawn2",0,0);
        *(undefined4 *)(param_1 + 0x1b4) = uVar2;
        uVar2 = FUN_005c8250("svfigh",2,"spawn3",0,0);
        *(undefined4 *)(param_1 + 0x1b8) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn3",0,0);
        *(undefined4 *)(param_1 + 0x1bc) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn3",0,0);
        *(undefined4 *)(param_1 + 0x1c0) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn4",0,0);
        *(undefined4 *)(param_1 + 0x1c4) = uVar2;
        uVar2 = FUN_005c8250("svtank",2,"spawn4",0,0);
        *(undefined4 *)(param_1 + 0x1c8) = uVar2;
        uVar2 = FUN_005c8250("svapc",2,"spawn4",0,0);
        *(undefined4 *)(param_1 + 0x1cc) = uVar2;
        uVar2 = FUN_005c8250("svapc",2,"spawn4",0,0);
        *(undefined4 *)(param_1 + 0x1d0) = uVar2;
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1ac),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1b0),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1b4),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1b8),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1bc),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1c0),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1c4),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1c8),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1cc),1);
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x1d0),1);
        if (*(char *)(param_1 + 0x5a) == '\0') {
          FUN_004f6aa0();
          FUN_004f6ab0("misn0901.otf",DAT_0091757c,0x41000000,0);
          FUN_004f6ab0("misn0902.otf",DAT_0091755c,0x41000000,0);
          FUN_004f6ab0("misn0903.otf",DAT_0091755c,0x41000000,0);
        }
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xc4) = (float)fVar4 + 5.0;
        FUN_005cb2d0("misn09b.aip",2);
        *(undefined1 *)(param_1 + 0x6e) = 1;
        *(undefined1 *)(param_1 + 0x5d) = 1;
      }
    }
  }
  if (((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x6d) != '\0')) &&
     (*(char *)(param_1 + 0x55) == '\0')) {
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x104));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x104),"Alien Relic");
    FUN_005cb960(*(undefined4 *)(param_1 + 0x118),"soviet_path",1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1ac),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1b0),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1b4),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1bc),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1c0),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1cc),*(undefined4 *)(param_1 + 0x118),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1d0),*(undefined4 *)(param_1 + 0x118),1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe8) = (float)fVar4 + 7.0;
    *(undefined1 *)(param_1 + 0x55) = 1;
  }
  if ((*(char *)(param_1 + 0x55) != '\0') && (*(char *)(param_1 + 0x7b) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xe8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe8)) {
      FUN_00437d30("misn0903.wav");
      FUN_005cd2a0();
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xe8) = (float)fVar4 + 18.0;
      *(undefined1 *)(param_1 + 0x7b) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    FUN_005cd300("convoy_cam_path",*(undefined4 *)(param_1 + 0x1e4),0x47e,
                 *(undefined4 *)(param_1 + 0x118));
    *(int *)(param_1 + 0x1e4) = *(int *)(param_1 + 0x1e4) + -4;
  }
  if ((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if ((float)fVar4 < *(float *)(param_1 + 0xe8) || (float)fVar4 == *(float *)(param_1 + 0xe8)) {
      cVar1 = FUN_005cd560();
      if (cVar1 == '\0') goto LAB_00533b4f;
    }
    FUN_005cd4e0();
    *(undefined1 *)(param_1 + 0x7c) = 1;
  }
LAB_00533b4f:
  cVar1 = FUN_005c84d0(param_1 + 0x10c);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7f) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xf0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xf0)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xf0) = (float)fVar4 + 2.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                    *(undefined4 *)(param_1 + 0x10c));
      if ((float)fVar4 < 70.0) {
        FUN_00437d30("misn0915.wav");
        *(undefined1 *)(param_1 + 0x7f) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x7f) != '\0') {
    cVar1 = FUN_005cd610("hbchar");
    if ((cVar1 == '\x01') && (*(char *)(param_1 + 0x80) == '\0')) {
      FUN_00437d30("misn0916.wav");
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"charon_spawn",0,0);
      *(undefined4 *)(param_1 + 0x1d4) = uVar2;
      FUN_005c9640(*(undefined4 *)(param_1 + 0x1d4),"Alien Relic");
      *(undefined1 *)(param_1 + 0x80) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') || (*(char *)(param_1 + 0x5d) != '\0')) &&
     (*(char *)(param_1 + 0x86) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xec) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xec)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xec) = (float)fVar4 + 2.0;
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x188));
        if (cVar1 != '\0') {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x188),
                                        *(undefined4 *)(param_1 + 0x120));
          if ((float)fVar4 < 1400.0) {
            if (*(char *)(param_1 + 0x5a) == '\0') {
              FUN_004f6aa0();
              FUN_004f6ab0("misn0901.otf",DAT_0091757c,0x41000000,0);
              FUN_004f6ab0("misn0902.otf",DAT_009175b0,0x41000000,0);
              FUN_004f6ab0("misn0903.otf",DAT_0091755c,0x41000000,0);
              *(undefined1 *)(param_1 + 0x86) = 1;
            }
            else {
              FUN_004f6aa0();
              FUN_004f6ab0("misn0901.otf",DAT_009175b0,0x41000000,0);
              FUN_004f6ab0("misn0902.otf",DAT_009175b0,0x41000000,0);
              FUN_004f6ab0("misn0903.otf",DAT_0091755c,0x41000000,0);
              *(undefined1 *)(param_1 + 0x86) = 1;
            }
          }
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x140);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x144);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
      FUN_00437d30("misn0908.wav");
      *(undefined1 *)(param_1 + 0x87) = 1;
    }
  }
  if (*(char *)(param_1 + 0x7e) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x18c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 400);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x194);
        if (((cVar1 == '\0') && (*(char *)(param_1 + 0x71) == '\0')) &&
           ((*(char *)(param_1 + 0x5a) == '\0' && (*(char *)(param_1 + 0x5b) == '\0')))) {
          uVar2 = FUN_005cae10(1);
          *(undefined4 *)(param_1 + 0x1e8) = uVar2;
          if (*(int *)(param_1 + 0x1e8) < 10) {
            fVar4 = (float10)FUN_00822d80("misn09f4.des");
            FUN_0045c0f0((float)fVar4 + 6.0);
            *(undefined1 *)(param_1 + 0x71) = 1;
          }
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x104);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x71) == '\0')) {
      FUN_00437d30("misn0906.wav");
      fVar4 = (float10)FUN_00822d80("misn09f1.des");
      FUN_0045c0f0((float)fVar4 + 15.0);
      *(undefined1 *)(param_1 + 0x71) = 1;
    }
  }
  if (*(char *)(param_1 + 0x6d) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x14c);
    if (cVar1 != '\0') {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x118),
                                    *(undefined4 *)(param_1 + 0x14c));
      if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x71) == '\0')) {
        FUN_00437d30("misn0907.wav");
        fVar4 = (float10)FUN_00822d80("misn09f2.des");
        FUN_0045c0f0((float)fVar4 + 15.0);
        *(undefined1 *)(param_1 + 0x71) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x55) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0))
       && (*(char *)(param_1 + 0x89) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 10.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x120),0x459c4000,2,0);
      *(undefined4 *)(param_1 + 0x1dc) = uVar2;
      if (*(int *)(param_1 + 0x1dc) == 0) {
        FUN_00437d30("misn0908.wav");
        *(undefined1 *)(param_1 + 0x89) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x104);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x6d) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xc4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc4))
       && (*(char *)(param_1 + 0x71) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc4) = (float)fVar4 + 2.0;
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x104),
                                      *(undefined4 *)(param_1 + 0x188));
        if ((float)fVar4 < 100.0) {
          FUN_00437d30("misn0909.wav");
          fVar4 = (float10)FUN_00822d80("misn09w1.des");
          FUN_0045c110((float)fVar4 + 15.0);
          *(undefined1 *)(param_1 + 0x71) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x188);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x71) == '\0')) {
    FUN_00437d30("misn0911.wav");
    fVar4 = (float10)FUN_00822d80("misn09f3.des");
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x14c);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x71) == '\0')) {
    FUN_00437d30("misn0918.wav");
    fVar4 = (float10)FUN_00822d80(0);
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  return;
}

