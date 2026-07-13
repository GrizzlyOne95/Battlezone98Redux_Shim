
void __fastcall FUN_00565f80(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x14c) = uVar2;
  cVar1 = FUN_005c84d0(param_1 + 0x220);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xbe) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x224);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xbf) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x228);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xc0) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x22c);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xc1) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x230);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xc2) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x234);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xc3) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1c4);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x8f) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1cc);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x90) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x240);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x91) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x16c);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x77) == '\0')) &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x124) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x124))) {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x16c),0x43480000);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x124) = (float)fVar4 + 1.0;
  }
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cadd0(1,0x19);
    FUN_005cadd0(2,0x28);
    FUN_005cacb0(1,10);
    FUN_005cacb0(2,0x3c);
    FUN_00437d30("misns800.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misns800.otf",DAT_0091755c,0x41000000,0);
    uVar2 = FUN_005c8250("bvsca8",2,"american_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    uVar2 = FUN_005c8250("bvsca8",2,"american_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1bc) = uVar2;
    uVar2 = FUN_005c8250("bvsca8",2,"american_spawn",0,0);
    *(undefined4 *)(param_1 + 0x1c0) = uVar2;
    uVar2 = FUN_005c8250("bvra8",2,"american_spawn",0,0);
    *(undefined4 *)(param_1 + 0x288) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x150),"Black Dog Base");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x154),"Drop Zone");
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x118) = (float)fVar4 + 60.0;
    FUN_005cb2d0("misns8.aip",2);
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x160);
  if (((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x164), cVar1 != '\0')) &&
     (*(char *)(param_1 + 0x66) == '\0')) {
    FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"abwpow",1);
    FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"abtowe",1);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe4) = (float)fVar4 + 10.0;
    FUN_005cb2d0("misns8a.aip",2);
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  if (((*(char *)(param_1 + 0x66) != '\0') && (*(char *)(param_1 + 0x58) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xe4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xe4))) {
    FUN_005cada0(2,0x3c);
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 != '\0') {
      FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"rpower1",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"rtower1",1);
    }
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if ((((*(char *)(param_1 + 0x58) != '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x1e8), cVar1 != '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x1f0), cVar1 != '\0')) && (*(char *)(param_1 + 0x65) == '\0')
     ) {
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x160),"center_path",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x164),"center_path",1);
    }
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd8) = (float)fVar4 + 90.0;
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  if ((*(char *)(param_1 + 0x7b) == '\0') && (*(char *)(param_1 + 0x65) != '\0')) {
    uVar2 = FUN_005c8250("avart8",2,"american_spawn",0,0);
    *(undefined4 *)(param_1 + 0x284) = uVar2;
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  if ((*(char *)(param_1 + 0x7a) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x284), cVar1 != '\0'))
  {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x284),*(undefined4 *)(param_1 + 0x1a4),1);
    *(undefined1 *)(param_1 + 0x7a) = 1;
  }
  if ((*(char *)(param_1 + 0x73) == '\0') &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xd8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd8))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xdc) = (float)fVar4 + 5.0;
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 != '\0') {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"absilo",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"absilo",1);
    }
    *(undefined1 *)(param_1 + 0x73) = 1;
  }
  if (((*(char *)(param_1 + 0x73) != '\0') && (*(char *)(param_1 + 0x74) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xdc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xdc))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xdc) = (float)fVar4 + 5.0;
    uVar2 = FUN_005cae10(2);
    *(undefined4 *)(param_1 + 0x294) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x164);
      if (cVar1 != '\0') {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x164),
                                      *(undefined4 *)(param_1 + 0x1a4));
        *(float *)(param_1 + 0x144) = (float)fVar4;
      }
    }
    else {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x160),
                                    *(undefined4 *)(param_1 + 0x1a4));
      *(float *)(param_1 + 0x144) = (float)fVar4;
    }
    if ((float)*(int *)(param_1 + 0x294) <= 8.0) {
      if (100.0 < *(float *)(param_1 + 0x144) || *(float *)(param_1 + 0x144) == 100.0) {
        cVar1 = FUN_005c84d0(param_1 + 0x160);
        if (cVar1 != '\0') {
          FUN_005cb9d0(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x1a4),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if (cVar1 != '\0') {
          FUN_005cb9d0(*(undefined4 *)(param_1 + 0x164),*(undefined4 *)(param_1 + 0x1a4),1);
        }
      }
      else {
        cVar1 = FUN_005c84d0(param_1 + 0x160);
        if (cVar1 != '\0') {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x160),1);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if (cVar1 != '\0') {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x164),1);
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if (cVar1 != '\0') {
          FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"center_silo",1);
          *(undefined1 *)(param_1 + 0x74) = 1;
        }
      }
      else {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"center_silo",1);
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if (cVar1 != '\0') {
          FUN_005cb960(*(undefined4 *)(param_1 + 0x164),"center_silo",1);
        }
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
  }
  if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x75) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x208), cVar1 != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x160);
    if (cVar1 != '\0') {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"abwpow",1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x164);
    if (cVar1 != '\0') {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"abtowe",1);
    }
    FUN_005cb2d0("misns8b.aip",2);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd8) = (float)fVar4 + 10.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x100) = (float)fVar4 + 10.0;
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if (((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x68) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xd8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xd8))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd8) = (float)fVar4 + 5.0;
    uVar2 = FUN_005cae10(2);
    *(undefined4 *)(param_1 + 0x294) = uVar2;
    if ((float)*(int *)(param_1 + 0x294) <= 14.0) {
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if ((cVar1 == '\0') ||
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x160),
                                        *(undefined4 *)(param_1 + 0x1a4)), 200.0 <= (float)fVar4)) {
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if ((cVar1 != '\0') &&
           (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x164),
                                          *(undefined4 *)(param_1 + 0x1a4)), (float)fVar4 < 200.0))
        {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x164),1);
        }
      }
      else {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x160),1);
        cVar1 = FUN_005c84d0(param_1 + 0x164);
        if (cVar1 != '\0') {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x164),1);
        }
      }
      FUN_005cada0(2,2);
    }
    else {
      FUN_005cb2d0("misns8g.aip",2);
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 != '\0') {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"main_field2",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x164);
      if (cVar1 != '\0') {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"main_field1",1);
      }
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1ec);
  if (((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 500), cVar1 != '\0')) &&
     (*(char *)(param_1 + 0x76) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 300) = (float)fVar4 + 20.0;
    FUN_005cb2d0("misns8b.aip",2);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x11c) = (float)fVar4 + 5.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x120) = (float)fVar4 + 60.0;
    *(undefined1 *)(param_1 + 0x72) = 1;
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1dc);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x1dc),*(undefined4 *)(param_1 + 0x168),1);
    cVar1 = FUN_005c84d0(param_1 + 0x1d8);
    if (cVar1 != '\0') {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x1d8),*(undefined4 *)(param_1 + 0x168),1);
    }
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x110) = (float)fVar4 + 30.0;
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  if (((*(char *)(param_1 + 0x8e) != '\0') &&
      (fVar4 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x110) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x110)))
     && (*(char *)(param_1 + 0x8d) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x110) = (float)fVar4 + 30.0;
    cVar1 = FUN_005c84d0(param_1 + 0x1e0);
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x8d) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x8d) != '\0') && (*(char *)(param_1 + 0x76) != '\0')) &&
     (*(char *)(param_1 + 0x5b) != '\0')) {
    *(undefined1 *)(param_1 + 0x5b) = 0;
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  if (*(char *)(param_1 + 0x5c) != '\0') {
    if (((*(char *)(param_1 + 100) != '\0') &&
        (fVar4 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0xf8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xf8)))
       && (cVar1 = FUN_005c84d0(param_1 + 0x284), cVar1 != '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xf8) = (float)fVar4 + 180.0;
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x284),1);
    }
    if (((*(char *)(param_1 + 0x7c) == '\0') &&
        (cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x100)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x100) = (float)fVar4 + 10.0;
      uVar2 = FUN_005cae10(2);
      *(undefined4 *)(param_1 + 0x294) = uVar2;
      if (0xb < *(int *)(param_1 + 0x294)) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0x168),0,1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x100) = (float)fVar4 + 10.0;
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x55) == '\0') && (*(char *)(param_1 + 0x7c) != '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x100)))
    {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x168),"convoy_path",1);
      FUN_005cb2d0("misns8d.aip",2);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x100) = (float)fVar4 + 60.0;
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x10c) = (float)fVar4 + 10.0;
      cVar1 = FUN_005c84d0(param_1 + 0x238);
      if (cVar1 != '\0') {
        FUN_005cbc20(*(undefined4 *)(param_1 + 0x238),*(undefined4 *)(param_1 + 0x168),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x23c);
      if (cVar1 != '\0') {
        FUN_005cbc20(*(undefined4 *)(param_1 + 0x23c),*(undefined4 *)(param_1 + 0x168),1);
      }
      *(undefined1 *)(param_1 + 0x55) = 1;
    }
    if (((*(char *)(param_1 + 0x8c) == '\0') && (*(char *)(param_1 + 0x55) != '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0' &&
        (fVar4 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0x10c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x10c)))
       )) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x10c) = (float)fVar4 + 6.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x14c),
                                    *(undefined4 *)(param_1 + 0x168));
      if (100.0 <= (float)fVar4) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x168),
                                      *(undefined4 *)(param_1 + 0x1ac));
        if ((float)fVar4 < 100.0) {
          FUN_00437d30("misns801.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam_spawn",0,0);
          *(undefined4 *)(param_1 + 0x158) = uVar2;
          FUN_005c9640(*(undefined4 *)(param_1 + 0x158),"Choke Point");
          FUN_004f6aa0();
          FUN_004f6ab0("misns800.otf",DAT_0091755c,0x41000000,0);
          FUN_004f6ab0("misns801.otf",DAT_0091755c,0x41000000,0);
          *(undefined1 *)(param_1 + 0x8c) = 1;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x8c) = 1;
      }
    }
    if (((*(char *)(param_1 + 0x56) == '\0') && (*(char *)(param_1 + 0x55) != '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0' &&
        (fVar4 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0x100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x100)))
       )) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x100) = (float)fVar4 + 5.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x168),*(undefined4 *)(param_1 + 400))
      ;
      if ((float)fVar4 < 100.0) {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x168),*(undefined4 *)(param_1 + 400),1);
        *(undefined1 *)(param_1 + 0x56) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x56) != '\0') && (*(char *)(param_1 + 0x5a) == '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0')) &&
       (cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x168)), cVar1 != '\0')) {
      *(undefined1 *)(param_1 + 0x5a) = 1;
    }
    if (((*(char *)(param_1 + 0x55) != '\0') &&
        (cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 == '\0')) &&
       (*(char *)(param_1 + 0x96) == '\0')) {
      uVar2 = FUN_005c8250("bvtavk",2,"t1post",0,0);
      *(undefined4 *)(param_1 + 0x260) = uVar2;
      uVar2 = FUN_005c8250("bvtavk",2,"t1post",0,0);
      *(undefined4 *)(param_1 + 0x264) = uVar2;
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x260),*(undefined4 *)(param_1 + 0x178),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x264),*(undefined4 *)(param_1 + 0x178),1);
      }
      uVar2 = FUN_005c8250("bvmuf",2,"american_spawn",0,0);
      *(undefined4 *)(param_1 + 0x168) = uVar2;
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x168),*(undefined4 *)(param_1 + 0x1b4),1);
      *(undefined1 *)(param_1 + 0x5a) = 0;
      *(undefined1 *)(param_1 + 0x96) = 1;
    }
    if ((*(char *)(param_1 + 0x7d) == '\0') && (*(char *)(param_1 + 0x5a) != '\0')) {
      FUN_005cb2d0("misns8c.aip",2);
      *(undefined1 *)(param_1 + 0x7d) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1c4);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8f) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x178),1);
      }
      *(undefined1 *)(param_1 + 0x8f) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1cc);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x90) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1cc),*(undefined4 *)(param_1 + 0x178),1);
      }
      *(undefined1 *)(param_1 + 0x90) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x240);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x91) == '\0')) {
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x240),*(undefined4 *)(param_1 + 0x178),0);
      }
      *(undefined1 *)(param_1 + 0x91) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x5d) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && (fVar4 = (float10)FUN_00822d80(),
           *(float *)(param_1 + 0x118) <= (float)fVar4 &&
           (float)fVar4 != *(float *)(param_1 + 0x118))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x118) = (float)fVar4 + 5.0;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x16c),0x43480000,2,"abtowe");
    *(undefined4 *)(param_1 + 0x29c) = uVar2;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x16c),0x43480000,2,"abwpow");
    *(undefined4 *)(param_1 + 0x2a0) = uVar2;
    uVar2 = FUN_005cae10(2);
    *(undefined4 *)(param_1 + 0x294) = uVar2;
    if (((*(int *)(param_1 + 0x29c) == 0) || (*(int *)(param_1 + 0x2a0) == 0)) &&
       ((float)*(int *)(param_1 + 0x294) < 10.0)) {
      *(undefined1 *)(param_1 + 0x5b) = 0;
      *(undefined1 *)(param_1 + 0x5c) = 0;
      *(undefined1 *)(param_1 + 0x5d) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5d) != '\0') {
    if (((*(char *)(param_1 + 0xae) != '\0') || (*(char *)(param_1 + 0xbb) != '\0')) &&
       ((*(char *)(param_1 + 0x7e) == '\0' && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
        ))) {
      FUN_005cada0(2,0x14);
      FUN_005cb2d0("misns8c.aip",2);
      FUN_005cc280(*(undefined4 *)(param_1 + 0x16c),0,1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar4 + 10.0;
      *(undefined1 *)(param_1 + 0x7e) = 1;
    }
    if ((((*(char *)(param_1 + 0x77) == '\0') && (*(char *)(param_1 + 0x7e) != '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0xfc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xfc))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0x16c),"escape_route",1);
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar4 + 60.0;
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x16c),1);
      cVar1 = FUN_005c84d0(param_1 + 600);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 600),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x25c);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x25c),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1e8);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x1e8),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x250);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x250),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x254);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x254),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1f0);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x1f0),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x168);
      if (cVar1 != '\0') {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x168),1);
      }
      *(undefined1 *)(param_1 + 0x77) = 1;
    }
    if (((*(char *)(param_1 + 0x77) != '\0') &&
        (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0xfc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xfc))) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar4 + 10.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x16c),
                                    *(undefined4 *)(param_1 + 0x198));
      if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x78) == '\0')) {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x16c),*(undefined4 *)(param_1 + 0x198),1);
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x16c),2);
        *(undefined1 *)(param_1 + 0x78) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x78) != '\0') && (*(char *)(param_1 + 0x79) == '\0')) &&
        (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0xfc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xfc))) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar4 + 5.0;
      cVar1 = FUN_005caec0(*(undefined4 *)(param_1 + 0x16c));
      if (cVar1 != '\0') {
        FUN_005cb2d0("misns8a.aip",2);
        *(undefined1 *)(param_1 + 0x79) = 1;
      }
    }
    if (((*(char *)(param_1 + 0x79) != '\0') && (*(char *)(param_1 + 0x93) == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x180), cVar1 != '\0' &&
        (cVar1 = FUN_005c84d0(param_1 + 0x184), cVar1 != '\0')))) {
      FUN_005cb2d0("misns8f.aip",2);
      *(undefined1 *)(param_1 + 0x93) = 1;
    }
  }
  if (((*(char *)(param_1 + 0x76) != '\0') &&
      (fVar4 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 300) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 300))) &&
     (*(char *)(param_1 + 0x9d) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x208);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 != '\0') {
        FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"absilo",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x164);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x164),"go_path",1);
      }
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0x160);
      if (cVar1 != '\0') {
        FUN_005cbc20(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x208),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x164);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x164),"go_path",1);
      }
    }
    *(undefined1 *)(param_1 + 0x9d) = 1;
  }
  if (((*(char *)(param_1 + 0x9d) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x160), cVar1 != '\0')
      ) && (fVar4 = (float10)FUN_00822d80(),
           *(float *)(param_1 + 0x11c) <= (float)fVar4 &&
           (float)fVar4 != *(float *)(param_1 + 0x11c))) {
    if (((*(char *)(param_1 + 0x80) == '\0') && (*(char *)(param_1 + 0x81) == '\0')) &&
       (*(char *)(param_1 + 0x82) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x11c) = (float)fVar4 + 10.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"absilo");
      *(undefined4 *)(param_1 + 0x2a4) = uVar2;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"abwpow");
      *(undefined4 *)(param_1 + 0x2ac) = uVar2;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"abtowe");
      *(undefined4 *)(param_1 + 0x2a8) = uVar2;
      if (*(int *)(param_1 + 0x2a4) == 0) {
        FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"absilo",1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
        *(undefined1 *)(param_1 + 0x80) = 1;
      }
      else if (*(int *)(param_1 + 0x2ac) == 0) {
        FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"abwpow",1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
        *(undefined1 *)(param_1 + 0x81) = 1;
      }
      else if (*(int *)(param_1 + 0x2a8) == 0) {
        FUN_005cc660(*(undefined4 *)(param_1 + 0x160),"abtowe",1);
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
        *(undefined1 *)(param_1 + 0x82) = 1;
      }
      else {
        FUN_005cbc80(*(undefined4 *)(param_1 + 0x160),1);
      }
    }
    if (((*(char *)(param_1 + 0x80) != '\0') && (*(char *)(param_1 + 0x83) == '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x104) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x104)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
      uVar2 = FUN_005cae10(2);
      *(undefined4 *)(param_1 + 0x294) = uVar2;
      if (8 < *(int *)(param_1 + 0x294)) {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"center_silo",1);
        *(undefined1 *)(param_1 + 0x83) = 1;
      }
    }
    if (((*(char *)(param_1 + 0x81) != '\0') && (*(char *)(param_1 + 0x84) == '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x104) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x104)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
      uVar2 = FUN_005cae10(2);
      *(undefined4 *)(param_1 + 0x294) = uVar2;
      if (10 < *(int *)(param_1 + 0x294)) {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"main_field2",1);
        *(undefined1 *)(param_1 + 0x84) = 1;
      }
    }
    if (((*(char *)(param_1 + 0x82) != '\0') && (*(char *)(param_1 + 0x85) == '\0')) &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x104) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x104)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x104) = (float)fVar4 + 5.0;
      uVar2 = FUN_005cae10(2);
      *(undefined4 *)(param_1 + 0x294) = uVar2;
      if (10 < *(int *)(param_1 + 0x294)) {
        FUN_005cc5f0(*(undefined4 *)(param_1 + 0x160),"main_field1",1);
        *(undefined1 *)(param_1 + 0x85) = 1;
      }
    }
    if ((*(char *)(param_1 + 0x83) != '\0') &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x11c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x11c)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x11c) = (float)fVar4 + 10.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"absilo");
      *(undefined4 *)(param_1 + 0x2a4) = uVar2;
      if (*(int *)(param_1 + 0x2a4) == 1) {
        *(undefined1 *)(param_1 + 0x80) = 0;
        *(undefined1 *)(param_1 + 0x83) = 0;
      }
    }
    if ((*(char *)(param_1 + 0x84) != '\0') &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x11c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x11c)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x11c) = (float)fVar4 + 10.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"abwpow");
      *(undefined4 *)(param_1 + 0x2ac) = uVar2;
      if (*(int *)(param_1 + 0x2ac) == 1) {
        *(undefined1 *)(param_1 + 0x81) = 0;
        *(undefined1 *)(param_1 + 0x84) = 0;
      }
    }
    if ((*(char *)(param_1 + 0x85) != '\0') &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x11c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x11c)))
    {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x11c) = (float)fVar4 + 10.0;
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x1a4),0x44610000,2,"abtowe");
      *(undefined4 *)(param_1 + 0x2a8) = uVar2;
      if (*(int *)(param_1 + 0x2a8) == 1) {
        *(undefined1 *)(param_1 + 0x82) = 0;
        *(undefined1 *)(param_1 + 0x85) = 0;
      }
    }
  }
  if ((*(char *)(param_1 + 0x76) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x164), cVar1 != '\0'))
  {
    if (*(char *)(param_1 + 0x9b) == '\0') {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"absilo",1);
      *(undefined1 *)(param_1 + 0x9b) = 1;
    }
    fVar4 = (float10)FUN_00822d80();
    if ((*(float *)(param_1 + 0x120) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x120))
       && (*(char *)(param_1 + 0x9c) == '\0')) {
      fVar4 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x120) = (float)fVar4 + 10.0;
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x164),
                                    *(undefined4 *)(param_1 + 0x198));
      if ((float)fVar4 < 300.0) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
        *(undefined1 *)(param_1 + 0x9c) = 1;
      }
    }
    if ((*(char *)(param_1 + 0x9c) != '\0') &&
       (fVar4 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x120) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x120)))
    {
      if ((*(char *)(param_1 + 0x86) == '\0') &&
         ((*(char *)(param_1 + 0x87) == '\0' && (*(char *)(param_1 + 0x88) == '\0')))) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x120) = (float)fVar4 + 10.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"absilo");
        *(undefined4 *)(param_1 + 0x2b0) = uVar2;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"abwpow");
        *(undefined4 *)(param_1 + 0x2b8) = uVar2;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"abtowe");
        *(undefined4 *)(param_1 + 0x2b4) = uVar2;
        if (*(int *)(param_1 + 0x2b0) == 0) {
          FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"absilo",1);
          fVar4 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
          *(undefined1 *)(param_1 + 0x86) = 1;
        }
        else if (*(int *)(param_1 + 0x2b8) == 0) {
          FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"abwpow",1);
          fVar4 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
          *(undefined1 *)(param_1 + 0x87) = 1;
        }
        else if (*(int *)(param_1 + 0x2b4) == 0) {
          FUN_005cc660(*(undefined4 *)(param_1 + 0x164),"abtowe",1);
          fVar4 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
          *(undefined1 *)(param_1 + 0x88) = 1;
        }
        else {
          FUN_005cbc80(*(undefined4 *)(param_1 + 0x164),1);
          if (*(char *)(param_1 + 0x7f) == '\0') {
            cVar1 = FUN_005c84d0(param_1 + 0x1b8);
            if (cVar1 != '\0') {
              FUN_005cb960(*(undefined4 *)(param_1 + 0x1b8),"go_path",1);
            }
            *(undefined1 *)(param_1 + 0x7f) = 1;
          }
        }
      }
      if (((*(char *)(param_1 + 0x86) != '\0') && (*(char *)(param_1 + 0x89) == '\0')) &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x108) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x108))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
        uVar2 = FUN_005cae10(2);
        *(undefined4 *)(param_1 + 0x294) = uVar2;
        if (8 < *(int *)(param_1 + 0x294)) {
          FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"alt_silo",1);
          *(undefined1 *)(param_1 + 0x89) = 1;
        }
      }
      if (((*(char *)(param_1 + 0x87) != '\0') && (*(char *)(param_1 + 0x8a) == '\0')) &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x108) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x108))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
        uVar2 = FUN_005cae10(2);
        *(undefined4 *)(param_1 + 0x294) = uVar2;
        if (10 < *(int *)(param_1 + 0x294)) {
          FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"alt_power",1);
          *(undefined1 *)(param_1 + 0x8a) = 1;
        }
      }
      if (((*(char *)(param_1 + 0x88) != '\0') && (*(char *)(param_1 + 0x8b) == '\0')) &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x108) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x108))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x108) = (float)fVar4 + 5.0;
        uVar2 = FUN_005cae10(2);
        *(undefined4 *)(param_1 + 0x294) = uVar2;
        if (10 < *(int *)(param_1 + 0x294)) {
          FUN_005cc5f0(*(undefined4 *)(param_1 + 0x164),"alt_tower",1);
          *(undefined1 *)(param_1 + 0x8b) = 1;
        }
      }
      if ((*(char *)(param_1 + 0x89) != '\0') &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x120) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x120))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x120) = (float)fVar4 + 10.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"absilo");
        *(undefined4 *)(param_1 + 0x2b0) = uVar2;
        if (*(int *)(param_1 + 0x2b0) == 1) {
          *(undefined1 *)(param_1 + 0x86) = 0;
          *(undefined1 *)(param_1 + 0x89) = 0;
        }
      }
      if ((*(char *)(param_1 + 0x8a) != '\0') &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x120) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x120))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x120) = (float)fVar4 + 10.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"abwpow");
        *(undefined4 *)(param_1 + 0x2b8) = uVar2;
        if (*(int *)(param_1 + 0x2b8) == 1) {
          *(undefined1 *)(param_1 + 0x87) = 0;
          *(undefined1 *)(param_1 + 0x8a) = 0;
        }
      }
      if ((*(char *)(param_1 + 0x8b) != '\0') &&
         (fVar4 = (float10)FUN_00822d80(),
         *(float *)(param_1 + 0x120) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x120))
         ) {
        fVar4 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x120) = (float)fVar4 + 10.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x198),0x43c80000,2,"abtowe");
        *(undefined4 *)(param_1 + 0x2b4) = uVar2;
        if (*(int *)(param_1 + 0x2b4) == 1) {
          *(undefined1 *)(param_1 + 0x88) = 0;
          *(undefined1 *)(param_1 + 0x8b) = 0;
        }
      }
    }
  }
  if ((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x95) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x220);
    if ((cVar1 == '\0') &&
       ((((cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 == '\0' &&
          (cVar1 = FUN_005c84d0(param_1 + 0x228), cVar1 == '\0')) &&
         (cVar1 = FUN_005c84d0(param_1 + 0x22c), cVar1 == '\0')) &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x230), cVar1 == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0x234), cVar1 == '\0')))))) {
      FUN_00437d30("misns815.wav");
      *(undefined1 *)(param_1 + 0x95) = 1;
    }
    else {
      FUN_00437d30("misns816.wav");
      *(undefined1 *)(param_1 + 0xac) = 1;
      *(undefined1 *)(param_1 + 0x95) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x5d) != '\0') && (*(char *)(param_1 + 0x9e) == '\0')) {
    uVar2 = FUN_005c8250("svtank",1,"romeski_spawn",0,0);
    *(undefined4 *)(param_1 + 0x268) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 0x16c);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x16c),1);
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x268),*(undefined4 *)(param_1 + 0x19c),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 600);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 600),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x25c);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x25c),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1e8);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x1e8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x250);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x250),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x254);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x254),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x1f0);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x1f0),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x168);
    if (cVar1 != '\0') {
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x168),1);
    }
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x130) = (float)fVar4 + 5.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x134) = (float)fVar4 + 10.0;
    *(undefined1 *)(param_1 + 0x9e) = 1;
  }
  if (((*(char *)(param_1 + 0x9e) != '\0') && (*(char *)(param_1 + 0xae) == '\0')) &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0x130) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x130))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x130) = (float)fVar4 + 2.0;
    cVar1 = FUN_005c84d0(param_1 + 0x268);
    if ((cVar1 != '\0') &&
       (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x14c),
                                      *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 150.0)) {
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x268));
      FUN_005c9640(*(undefined4 *)(param_1 + 0x268),"Romeski");
      if (*(char *)(param_1 + 0xbb) == '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x268),*(undefined4 *)(param_1 + 0x16c),1);
      }
      *(undefined1 *)(param_1 + 0xae) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x9e) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0'))
  {
    if ((*(char *)(param_1 + 0xa6) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x220), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x220),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xa6) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
    if ((*(char *)(param_1 + 0xa7) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x224),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xa7) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
    if ((*(char *)(param_1 + 0xa8) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x228), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x228),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xa8) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
    if ((*(char *)(param_1 + 0xa9) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x22c), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x22c),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xa9) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
    if ((*(char *)(param_1 + 0xaa) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x230), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x230),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xaa) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
    if ((*(char *)(param_1 + 0xab) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x234), cVar1 != '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x234),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xab) = 1;
      if ((*(char *)(param_1 + 0xac) == '\0') && (*(char *)(param_1 + 0xad) == '\0')) {
        FUN_00437d30("misns807.wav");
        *(undefined1 *)(param_1 + 0xac) = 1;
      }
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0x134) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x134)) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x134) = (float)fVar4 + 10.0;
    cVar1 = FUN_005c84d0(param_1 + 0x220);
    if ((((cVar1 != '\0') && (*(char *)(param_1 + 0xa6) != '\0')) &&
        (*(char *)(param_1 + 0xb4) == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x220),
                                       *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x220),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb4) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0xa7) != '\0')) &&
       ((*(char *)(param_1 + 0xb5) == '\0' &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x224),
                                        *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))))
       ) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x224),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb5) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x228);
    if ((((cVar1 != '\0') && (*(char *)(param_1 + 0xa8) != '\0')) &&
        (*(char *)(param_1 + 0xb6) == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x228),
                                       *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x228),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb6) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x22c);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0xa9) != '\0')) &&
       ((*(char *)(param_1 + 0xb7) == '\0' &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x22c),
                                        *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))))
       ) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x22c),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb7) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x230);
    if ((((cVar1 != '\0') && (*(char *)(param_1 + 0xaa) != '\0')) &&
        (*(char *)(param_1 + 0xb8) == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x230),
                                       *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x230),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb8) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x234);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0xab) != '\0')) &&
       ((*(char *)(param_1 + 0xb9) == '\0' &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0' &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x234),
                                        *(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 200.0)))))
       ) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x234),*(undefined4 *)(param_1 + 0x268),1);
      *(undefined1 *)(param_1 + 0xc4) = 1;
      *(undefined1 *)(param_1 + 0xb9) = 1;
    }
  }
  if (((((*(char *)(param_1 + 0xa6) != '\0') || (*(char *)(param_1 + 0xa7) != '\0')) ||
       (*(char *)(param_1 + 0xa8) != '\0')) ||
      (((*(char *)(param_1 + 0xa9) != '\0' || (*(char *)(param_1 + 0xaa) != '\0')) ||
       (*(char *)(param_1 + 0xab) != '\0')))) && (*(char *)(param_1 + 0xbd) == '\0')) {
    FUN_00437d30("misns805.wav");
    FUN_00437d30("misns818.wav");
    *(undefined1 *)(param_1 + 0xbd) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x268);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x9f) == '\0')) &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x128) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x128))) {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0x268),0x43960000);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x128) = (float)fVar4 + 1.0;
  }
  if ((((*(char *)(param_1 + 0xba) == '\0') && (*(char *)(param_1 + 0xbb) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0')) &&
     (iVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x268)), iVar3 != 0)) {
    if (*(int *)(param_1 + 0x14c) == iVar3) {
      FUN_00437d30("misns819.wav");
      FUN_005cb820(*(undefined4 *)(param_1 + 0x268),*(undefined4 *)(param_1 + 0x14c),1);
      *(undefined1 *)(param_1 + 0x9f) = 1;
      *(undefined1 *)(param_1 + 0xba) = 1;
    }
    else if (((*(int *)(param_1 + 0x26c) == iVar3) || (*(int *)(param_1 + 0x270) == iVar3)) ||
            (((*(int *)(param_1 + 0x274) == iVar3 ||
              ((*(int *)(param_1 + 0x278) == iVar3 || (*(int *)(param_1 + 0x27c) == iVar3)))) ||
             (*(int *)(param_1 + 0x280) == iVar3)))) {
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x13c) = (float)fVar4 + 5.0;
      *(undefined1 *)(param_1 + 0x9f) = 1;
      *(undefined1 *)(param_1 + 0xbb) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0xbb) != '\0') && (*(char *)(param_1 + 0xb0) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 != '\0')) &&
     ((fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 0.8 &&
      (*(char *)(param_1 + 0xaf) == '\0')))) {
    FUN_00437d30("misns817.wav");
    *(undefined1 *)(param_1 + 0xb0) = 1;
  }
  if (((*(char *)(param_1 + 0xbb) != '\0') && (*(char *)(param_1 + 0xaf) == '\0')) &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x13c) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x13c))) {
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x13c) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0x268);
    if ((cVar1 != '\0') &&
       (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x268),
                                      *(undefined4 *)(param_1 + 0x14c)), (float)fVar4 < 130.0)) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x268),*(undefined4 *)(param_1 + 0x14c),1);
      FUN_00437d30("misns810.wav");
      *(undefined1 *)(param_1 + 0xaf) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x268);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0xbc) == '\0')) &&
     (fVar4 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x268)), (float)fVar4 < 0.1)) {
    FUN_00437d30("misns812.wav");
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x138) = (float)fVar4 + 3.0;
    *(undefined1 *)(param_1 + 0xbc) = 1;
  }
  if (((*(char *)(param_1 + 0xbc) != '\0') &&
      (fVar4 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x138) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0x138)))
     && (*(char *)(param_1 + 0xad) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x268);
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0xad) = 1;
    }
    else {
      FUN_005cb1c0(*(undefined4 *)(param_1 + 0x268),0x447a0000);
      *(undefined1 *)(param_1 + 0xad) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x9e) != '\0') &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x268), cVar1 == '\0' || (*(char *)(param_1 + 0xc4) != '\0')))
     ) {
    if ((*(char *)(param_1 + 0xbe) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x220), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x220),0);
      *(undefined4 *)(param_1 + 0x26c) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x26c),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x220));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x26c),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xbe) = 1;
    }
    if ((*(char *)(param_1 + 0xbf) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x224),0);
      *(undefined4 *)(param_1 + 0x270) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x270),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x224));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x270),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xbf) = 1;
    }
    if ((*(char *)(param_1 + 0xc0) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x228), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x228),0);
      *(undefined4 *)(param_1 + 0x274) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x274),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x228));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x274),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xc0) = 1;
    }
    if ((*(char *)(param_1 + 0xc1) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x22c), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x22c),0);
      *(undefined4 *)(param_1 + 0x278) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x278),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x22c));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x278),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xc1) = 1;
    }
    if ((*(char *)(param_1 + 0xc2) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x230), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x230),0);
      *(undefined4 *)(param_1 + 0x27c) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x27c),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x230));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x27c),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xc2) = 1;
    }
    if ((*(char *)(param_1 + 0xc3) == '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x234), cVar1 != '\0')) {
      uVar2 = FUN_005c8080("savs8",2,*(undefined4 *)(param_1 + 0x234),0);
      *(undefined4 *)(param_1 + 0x280) = uVar2;
      FUN_005cb620(*(undefined4 *)(param_1 + 0x280),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x234));
      cVar1 = FUN_005c84d0(param_1 + 0x268);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x280),*(undefined4 *)(param_1 + 0x268),1);
      }
      if (*(char *)(param_1 + 0xbd) == '\0') {
        FUN_00437d30("misns805.wav");
        *(undefined1 *)(param_1 + 0xbd) = 1;
      }
      *(undefined1 *)(param_1 + 0xc3) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x16c);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x94) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x26c);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x26c),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x270);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x270),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x274);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x274),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x278);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x278),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x27c);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x27c),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x280);
    if (cVar1 != '\0') {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x280),*(undefined4 *)(param_1 + 0x194),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x268);
    if (cVar1 == '\0') {
      FUN_00437d30("misns814.wav");
      fVar4 = (float10)FUN_00822d80("misns8w1.des");
      FUN_0045c110((float)fVar4 + 25.0);
      *(undefined1 *)(param_1 + 0x94) = 1;
    }
    else {
      FUN_00437d30("misns803.wav");
      FUN_00437d30("misns808.wav");
      fVar4 = (float10)FUN_00822d80("misns8w1.des");
      FUN_0045c110((float)fVar4 + 35.0);
      *(undefined1 *)(param_1 + 0x94) = 1;
    }
  }
  return;
}

