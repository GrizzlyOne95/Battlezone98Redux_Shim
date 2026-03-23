
void __fastcall FUN_005424c0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xc0) = uVar2;
  if (*(char *)(param_1 + 0x70) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x154);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x73) = 0;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x74) = 0;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x75) = 0;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x6f) = 0;
        *(undefined1 *)(param_1 + 0x70) = 0;
        *(undefined1 *)(param_1 + 0x71) = 0;
        *(undefined1 *)(param_1 + 0x72) = 0;
        *(undefined4 *)(param_1 + 0xa8) = 0x47c34f80;
        *(undefined1 *)(param_1 + 0x7c) = 0;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x17c);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x7d) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x180);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x7e) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x184);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x7f) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x188);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x80) = 0;
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_00437d30("misn1300.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misn1300.otf",DAT_0091755c,0x41000000,0);
    FUN_005cacb0(1,10);
    FUN_005cacb0(2,0x28);
    FUN_005cadd0(1,0x28);
    FUN_005cadd0(2,200);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x17c),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x180),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 300),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x130),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x134),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x138),1);
    uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(param_1 + 300),0);
    *(undefined4 *)(param_1 + 0x1dc) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0xcc),"Drop Zone");
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x1dc),1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x90) = (float)fVar4 + 5.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x98) = (float)fVar4 + 300.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 900.0;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    iVar3 = FUN_005cae10(2);
    if ((0x96 < iVar3) && (*(char *)(param_1 + 0x6b) == '\0')) {
      FUN_005cadd0(2,0x96);
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe8);
  if (cVar1 == '\0') {
    iVar3 = FUN_005cae10(2);
    if ((0x96 < iVar3) && (*(char *)(param_1 + 0x6b) == '\0')) {
      FUN_005cadd0(2,0x96);
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xec);
  if (cVar1 == '\0') {
    iVar3 = FUN_005cae10(2);
    if ((0x96 < iVar3) && (*(char *)(param_1 + 0x6b) == '\0')) {
      FUN_005cadd0(2,0x96);
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if (cVar1 == '\0') {
    iVar3 = FUN_005cae10(2);
    if ((0x96 < iVar3) && (*(char *)(param_1 + 0x6b) == '\0')) {
      FUN_005cadd0(2,0x96);
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xe8);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe8);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe8);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xec);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 == '\0') {
      iVar3 = FUN_005cae10(2);
      if ((100 < iVar3) && (*(char *)(param_1 + 0x6c) == '\0')) {
        FUN_005cadd0(2,100);
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xe8);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xec);
      if (cVar1 == '\0') {
        iVar3 = FUN_005cae10(2);
        if ((0x32 < iVar3) && (*(char *)(param_1 + 0x6d) == '\0')) {
          FUN_005cadd0(2,0x32);
          *(undefined1 *)(param_1 + 0x6d) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xe8);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xf0);
      if (cVar1 == '\0') {
        iVar3 = FUN_005cae10(2);
        if ((0x32 < iVar3) && (*(char *)(param_1 + 0x6d) == '\0')) {
          FUN_005cadd0(2,0x32);
          *(undefined1 *)(param_1 + 0x6d) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xf0);
      if (cVar1 == '\0') {
        iVar3 = FUN_005cae10(2);
        if ((0x32 < iVar3) && (*(char *)(param_1 + 0x6d) == '\0')) {
          FUN_005cadd0(2,0x32);
          *(undefined1 *)(param_1 + 0x6d) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe8);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xf0);
      if (cVar1 == '\0') {
        iVar3 = FUN_005cae10(2);
        if ((0x32 < iVar3) && (*(char *)(param_1 + 0x6d) == '\0')) {
          FUN_005cadd0(2,0x32);
          *(undefined1 *)(param_1 + 0x6d) = 1;
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0xe8);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0xec);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0xf0);
        if (cVar1 == '\0') {
          iVar3 = FUN_005cae10(2);
          if ((0 < iVar3) && (*(char *)(param_1 + 0x55) == '\0')) {
            *(undefined1 *)(param_1 + 0x55) = 1;
            FUN_005cadd0(2,0);
          }
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x54) != '\0') && (*(char *)(param_1 + 0x56) == '\0')) {
    FUN_005cc100(*(undefined4 *)(param_1 + 0x114),"turret_path1",1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0x118),"turret_path1",1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x11c),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x120),1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0x124),"turret_path2",1);
    FUN_005cc100(*(undefined4 *)(param_1 + 0x128),"turret_path2",1);
    FUN_005cb960(*(undefined4 *)(param_1 + 0x10c),"slf_path",1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xac) = (float)fVar4 + 120.0;
    *(undefined1 *)(param_1 + 0x56) = 1;
  }
  if (*(char *)(param_1 + 0x56) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))
       && (*(char *)(param_1 + 0x82) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xac) = (float)fVar4 + 3.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x124),*(undefined4 *)(param_1 + 0xe4)
                                   );
      if ((float)fVar4 < 60.0) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x128),
                                      *(undefined4 *)(param_1 + 0xe4));
        if ((float)fVar4 < 60.0) {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x124),1);
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x128),1);
          *(undefined1 *)(param_1 + 0x82) = 1;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x56) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))
       && (*(char *)(param_1 + 0x59) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x114),
                                    *(undefined4 *)(param_1 + 0x19c));
      if ((float)fVar4 < 100.0) {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x19c),1);
        *(undefined1 *)(param_1 + 0x59) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x56) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xac) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xac))
       && (*(char *)(param_1 + 0x5a) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x118),
                                    *(undefined4 *)(param_1 + 0x19c));
      if ((float)fVar4 < 100.0) {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x1a0),1);
        *(undefined1 *)(param_1 + 0x5a) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x54) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x90) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x90))
       && (*(char *)(param_1 + 0x57) == '\0')) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x14c),*(undefined4 *)(param_1 + 0xc4),1);
      FUN_005cb820(*(undefined4 *)(param_1 + 0x150),*(undefined4 *)(param_1 + 0xc4),1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x94) = (float)fVar4 + 5.0;
      *(undefined1 *)(param_1 + 0x57) = 1;
    }
  }
  if (*(char *)(param_1 + 0x57) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x94) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x94))
       && (*(char *)(param_1 + 0x58) == '\0')) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x13c),"choke_point1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x140),"choke_point1",1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x19c),1);
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0x1a0),1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa4) = (float)fVar4 + 60.0;
      *(undefined1 *)(param_1 + 0x58) = 1;
    }
  }
  if (*(char *)(param_1 + 0x7a) == '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (((*(float *)(param_1 + 0xa4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa4))
        && (*(char *)(param_1 + 0x7b) == '\0')) && (*(char *)(param_1 + 0x83) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xa4) = (float)fVar4 + 240.0;
      FUN_005cb2d0("misn13.aip",2);
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x17c);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7d) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x17c),*(undefined4 *)(param_1 + 0x108),1);
    *(undefined1 *)(param_1 + 0x7d) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x180);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7e) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x180),*(undefined4 *)(param_1 + 0x108),1);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x184);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7f) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x1b8),1);
    *(undefined1 *)(param_1 + 0x7f) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x188);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x80) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x1b8),1);
    *(undefined1 *)(param_1 + 0x80) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1b0);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x1b4);
    if (cVar1 == '\0') goto LAB_00543446;
  }
  if ((*(char *)(param_1 + 0x6f) == '\0') && (*(char *)(param_1 + 0x83) == '\0')) {
    FUN_005cb2d0("misn13a.aip",2);
    *(undefined1 *)(param_1 + 0x7b) = 1;
    *(undefined1 *)(param_1 + 0x6f) = 1;
  }
LAB_00543446:
  if ((*(char *)(param_1 + 0x6f) != '\0') && (*(char *)(param_1 + 0x70) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x74) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 200);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1b4);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x1b4),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 200),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x18c);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 0x160),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x1b0),1);
      }
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x154);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x73) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x1b0);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 200);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 200),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 0x1b0),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 0x1b4),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 400);
      if (cVar1 != '\0') {
        FUN_005cbc20(*(undefined4 *)(param_1 + 400),*(undefined4 *)(param_1 + 0x154),1);
      }
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x15c);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x75) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 200);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1b4);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 0x1b4),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 200),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x194);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x15c),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 0x1b0),1);
      }
      *(undefined1 *)(param_1 + 0x75) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0x73) != '\0') && (*(char *)(param_1 + 0x75) != '\0')) &&
      (*(char *)(param_1 + 0x74) != '\0')) && (*(char *)(param_1 + 0x70) == '\0')) {
    *(undefined1 *)(param_1 + 0x7b) = 0;
    *(undefined1 *)(param_1 + 0x70) = 1;
  }
  if (*(char *)(param_1 + 0x70) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x1b0);
    if ((cVar1 == '\0') && (*(char *)(param_1 + 0x71) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 200);
        if (cVar1 != '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x154);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 200),1);
          }
          cVar1 = FUN_005c84d0(param_1 + 0x15c);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 200),1);
          }
          cVar1 = FUN_005c84d0(param_1 + 0x160);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 200),1);
          }
          *(undefined1 *)(param_1 + 0x71) = 1;
        }
      }
      else {
        cVar1 = FUN_005c84d0(param_1 + 0x154);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x154),*(undefined4 *)(param_1 + 0x1b4),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x15c);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x15c),*(undefined4 *)(param_1 + 0x1b4),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x160);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x1b4),1);
        }
        *(undefined1 *)(param_1 + 0x71) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe4);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xe4));
    if ((float)fVar4 < 0.95) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 2.0;
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xe8);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xe8));
    if ((float)fVar4 < 0.95) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 2.0;
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xec);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xec));
    if ((float)fVar4 < 0.95) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 2.0;
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xf0));
    if ((float)fVar4 < 0.95) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 2.0;
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  if (*(char *)(param_1 + 0x81) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0)) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb0) = (float)fVar4 + 120.0;
      cVar1 = FUN_005c84d0(param_1 + 0x17c);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x17c),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x180);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x180),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x184);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x184),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x188),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x114);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x114),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x118);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x118),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x124);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x124),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x128);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x128),"silo_spot",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x188);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x188),"silo_spot",1);
      }
      if ((*(char *)(param_1 + 0x7c) != '\0') || (*(char *)(param_1 + 0x70) != '\0')) {
        cVar1 = FUN_005c84d0(param_1 + 0x154);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x154),"silo_spot",1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x15c);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x15c),"silo_spot",1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x160);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x160),"silo_spot",1);
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x108);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x83) == '\0')) {
    fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x108));
    if (((float)fVar4 < 0.9) && (*(char *)(param_1 + 0x84) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x114);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x108),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x118);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0x108),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x124);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x124),*(undefined4 *)(param_1 + 0x108),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x128);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x108),1);
      }
      FUN_005cada0(2,0x28);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar4 + 120.0;
      FUN_005cb2d0("misn13c.aip",2);
      *(undefined1 *)(param_1 + 0x83) = 1;
    }
  }
  if (*(char *)(param_1 + 0x83) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x114);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x85) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x114),
                                    *(undefined4 *)(param_1 + 0x108));
      if ((float)fVar4 < 60.0) {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x114),1);
        *(undefined1 *)(param_1 + 0x85) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x83) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x86) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x118),
                                    *(undefined4 *)(param_1 + 0x108));
      if ((float)fVar4 < 60.0) {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x118),1);
        *(undefined1 *)(param_1 + 0x86) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x83) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x124);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x124),
                                    *(undefined4 *)(param_1 + 0x108));
      if ((float)fVar4 < 60.0) {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x124),1);
        *(undefined1 *)(param_1 + 0x87) = 1;
      }
    }
  }
  if (*(char *)(param_1 + 0x83) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x128);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x88) == '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x128),
                                    *(undefined4 *)(param_1 + 0x108));
      if ((float)fVar4 < 60.0) {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x128),1);
        *(undefined1 *)(param_1 + 0x88) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x8c) == '\0') && (*(char *)(param_1 + 0x83) != '\0')) {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0xb4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb4))
       && (*(char *)(param_1 + 0x84) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar4 + 60.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x108),0x43c80000,1,0);
      *(undefined4 *)(param_1 + 500) = uVar2;
      if ((float)*(int *)(param_1 + 500) < 2.0) {
        *(undefined1 *)(param_1 + 0x84) = 1;
        *(undefined1 *)(param_1 + 0x83) = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x1ac) == 0) {
    cVar1 = FUN_005c84d0(param_1 + 0x11c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x120);
      if (cVar1 == '\0') {
        *(undefined4 *)(param_1 + 0x1ac) = 1;
      }
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c)) &&
     (*(char *)(param_1 + 0x5b) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x9c) = (float)fVar4 + 10.0;
    cVar1 = FUN_005c84d0(param_1 + 300);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 300),"artil_path1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x130),"artil_path1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x134);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x134),"artil_path1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x138);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x138),"artil_path1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1dc);
    if (cVar1 != '\0') {
      FUN_005cc100(*(undefined4 *)(param_1 + 0x1dc),"artil_path1",1);
    }
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
  if (*(char *)(param_1 + 0x5b) != '\0') {
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x9c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x9c))
       && (*(char *)(param_1 + 0x5c) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x9c) = (float)fVar4 + 5.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x138),
                                    *(undefined4 *)(param_1 + 0x1a4));
      if ((float)fVar4 < 20.0) {
        cVar1 = FUN_005c84d0(param_1 + 300);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 300),"artil_point1",1);
          FUN_005cb620(*(undefined4 *)(param_1 + 300),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x130);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x130),"artil_point2",1);
          FUN_005cb620(*(undefined4 *)(param_1 + 0x130),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x134);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x134),"artil_point3",1);
          FUN_005cb620(*(undefined4 *)(param_1 + 0x134),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x138);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x138),"artil_point4",1);
          FUN_005cb620(*(undefined4 *)(param_1 + 0x138),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x1dc);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0x1dc),*(undefined4 *)(param_1 + 300),1);
        }
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xa0) = (float)fVar4 + 120.0;
        *(undefined1 *)(param_1 + 0x5c) = 1;
      }
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xa0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xa0)) &&
     (*(char *)(param_1 + 0x5d) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 300);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1e4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x1e8);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1ec);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0x1ec),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0x1e8),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0x1e4),1);
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x1ec);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x1e8);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(param_1 + 0x1e4);
          if (cVar1 != '\0') {
            FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x1e4),1);
          }
        }
        else {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x1e8),1);
        }
      }
      else {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x130),*(undefined4 *)(param_1 + 0x1ec),1);
      }
    }
    *(undefined1 *)(param_1 + 0x5d) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 300);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x130);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x134);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x138);
        if (cVar1 == '\0') {
          *(undefined1 *)(param_1 + 0x8b) = 1;
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x5c) != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0xc4);
    if (cVar1 != '\0') {
      uVar2 = FUN_005cd130(*(undefined4 *)(param_1 + 0xc4));
      *(undefined4 *)(param_1 + 0x1fc) = uVar2;
      if ((*(int *)(param_1 + 0x1fc) != 0) &&
         ((((*(int *)(param_1 + 300) == *(int *)(param_1 + 0x1fc) ||
            (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 0x1fc))) ||
           (*(int *)(param_1 + 0x134) == *(int *)(param_1 + 0x1fc))) ||
          (*(int *)(param_1 + 0x138) == *(int *)(param_1 + 0x1fc))))) {
        FUN_00437d30("misn1302.wav");
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 200);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) {
      uVar2 = FUN_005cd130(*(undefined4 *)(param_1 + 200));
      *(undefined4 *)(param_1 + 0x1fc) = uVar2;
      if ((*(int *)(param_1 + 0x1fc) != 0) &&
         (((*(int *)(param_1 + 300) == *(int *)(param_1 + 0x1fc) ||
           (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 0x1fc))) ||
          ((*(int *)(param_1 + 0x134) == *(int *)(param_1 + 0x1fc) ||
           (*(int *)(param_1 + 0x138) == *(int *)(param_1 + 0x1fc))))))) {
        FUN_00437d30("misn1302.wav");
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1e4);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) {
      uVar2 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1e4));
      *(undefined4 *)(param_1 + 0x1fc) = uVar2;
      if ((*(int *)(param_1 + 0x1fc) != 0) &&
         ((((*(int *)(param_1 + 300) == *(int *)(param_1 + 0x1fc) ||
            (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 0x1fc))) ||
           (*(int *)(param_1 + 0x134) == *(int *)(param_1 + 0x1fc))) ||
          (*(int *)(param_1 + 0x138) == *(int *)(param_1 + 0x1fc))))) {
        FUN_00437d30("misn1302.wav");
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1e8);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) {
      uVar2 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1e8));
      *(undefined4 *)(param_1 + 0x1fc) = uVar2;
      if ((*(int *)(param_1 + 0x1fc) != 0) &&
         (((*(int *)(param_1 + 300) == *(int *)(param_1 + 0x1fc) ||
           (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 0x1fc))) ||
          ((*(int *)(param_1 + 0x134) == *(int *)(param_1 + 0x1fc) ||
           (*(int *)(param_1 + 0x138) == *(int *)(param_1 + 0x1fc))))))) {
        FUN_00437d30("misn1302.wav");
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1ec);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) {
      uVar2 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1ec));
      *(undefined4 *)(param_1 + 0x1fc) = uVar2;
      if ((*(int *)(param_1 + 0x1fc) != 0) &&
         ((((*(int *)(param_1 + 300) == *(int *)(param_1 + 0x1fc) ||
            (*(int *)(param_1 + 0x130) == *(int *)(param_1 + 0x1fc))) ||
           (*(int *)(param_1 + 0x134) == *(int *)(param_1 + 0x1fc))) ||
          (*(int *)(param_1 + 0x138) == *(int *)(param_1 + 0x1fc))))) {
        FUN_00437d30("misn1302.wav");
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xb8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb8)) &&
     (*(char *)(param_1 + 0x8d) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb8) = (float)fVar4 + 60.0;
    uVar2 = FUN_005cae10(2);
    *(undefined4 *)(param_1 + 0x1f8) = uVar2;
    if (*(int *)(param_1 + 0x1f8) < 0x28) {
      if (*(int *)(param_1 + 0x1bc) != 0) {
        uVar2 = FUN_005c8080("svscav",2,*(undefined4 *)(param_1 + 0x1bc),0);
        *(undefined4 *)(param_1 + 0x1cc) = uVar2;
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1bc));
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1cc),*(undefined4 *)(param_1 + 0x1a8),1);
      }
      if (*(int *)(param_1 + 0x1c0) != 0) {
        uVar2 = FUN_005c8080("svscav",2,*(undefined4 *)(param_1 + 0x1c0),0);
        *(undefined4 *)(param_1 + 0x1d0) = uVar2;
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c0));
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1d0),*(undefined4 *)(param_1 + 0x1a8),1);
      }
      if (*(int *)(param_1 + 0x1c4) != 0) {
        uVar2 = FUN_005c8080("svscav",2,*(undefined4 *)(param_1 + 0x1c4),0);
        *(undefined4 *)(param_1 + 0x1d4) = uVar2;
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c4));
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1d4),*(undefined4 *)(param_1 + 0x1a8),1);
      }
      if (*(int *)(param_1 + 0x1c8) != 0) {
        uVar2 = FUN_005c8080("svscav",2,*(undefined4 *)(param_1 + 0x1c8),0);
        *(undefined4 *)(param_1 + 0x1d8) = uVar2;
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c8));
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1d8),*(undefined4 *)(param_1 + 0x1a8),1);
      }
      *(undefined1 *)(param_1 + 0x8d) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xc4);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x8c) == '\0')) {
    FUN_00437d30("misn1304.wav");
    fVar4 = (float10)FUN_00822d80("misn13f1.des");
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x8c) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x108);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x8c) == '\0')) {
    FUN_00437d30("misn1303.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misn1300.otf",DAT_009175b0,0x41000000,0);
    fVar4 = (float10)FUN_00822d80("misn13w1.des");
    FUN_0045c110((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x8c) = 1;
  }
  return;
}

