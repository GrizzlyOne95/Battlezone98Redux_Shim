
void __fastcall FUN_0065c7b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  int local_c;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x70) = uVar2;
  if ((((*(int *)(param_1 + 0x180) < 100) && (0x12 < *(int *)(param_1 + 0x180))) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x178), cVar1 == '\0')) {
    fVar4 = (float10)FUN_004b1670("ch08lsea.des");
    FUN_0045c0f0((float)fVar4 + 2.0);
    *(undefined4 *)(param_1 + 0x180) = 100;
  }
  if ((*(int *)(param_1 + 0x180) == 1) || (*(int *)(param_1 + 0x74) != *(int *)(param_1 + 0x70))) {
    for (local_c = 0; local_c < 0x1a; local_c = local_c + 1) {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x108 + local_c * 4),*(undefined4 *)(param_1 + 0x70),1)
      ;
    }
  }
  if (((4 < *(int *)(param_1 + 0x180)) && (*(int *)(param_1 + 0x180) < 0xb)) &&
     ((*(int *)(param_1 + 0x188) != 0 &&
      (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x188)), cVar1 != '\0')))) {
    *(undefined4 *)(param_1 + 0x188) = 0;
    uVar2 = FUN_005c8250(&DAT_00878c18,1,"apc_nav",0,0);
    FUN_005cd7f0(uVar2,"APC Convoy");
    FUN_005c88e0(uVar2);
  }
  if (*(int *)(param_1 + 0x184) == 0) {
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x70),"east_cloak",0);
    if (((float)fVar4 < 200.0) ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x70),"west_cloak",0),
       (float)fVar4 < 200.0)) {
      cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0x70));
      if (cVar1 != '\0') {
        uVar2 = FUN_00437d30("ch04002.wav");
        *(undefined4 *)(param_1 + 0x18c) = uVar2;
        FUN_005cd6c0(*(undefined4 *)(param_1 + 0x70));
      }
      *(undefined4 *)(param_1 + 0x184) = 1;
      FUN_005cd790(*(undefined4 *)(param_1 + 0x70),0);
    }
  }
  else if (*(int *)(param_1 + 0x18c) == 0) {
    cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0x70));
    if (cVar1 != '\0') {
      uVar2 = FUN_00437d30("ch04002.wav");
      *(undefined4 *)(param_1 + 0x18c) = uVar2;
      FUN_005cd6c0(*(undefined4 *)(param_1 + 0x70));
    }
  }
  else {
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x18c));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x18c) = 0;
    }
  }
  switch(*(undefined4 *)(param_1 + 0x180)) {
  case 1:
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
    FUN_005cb2d0("chmisn08.aip",2);
    FUN_005cadd0(1,0);
    FUN_005cacb0(1,10);
    FUN_005cadd0(2,0);
    FUN_00437d30("ch08001.wav");
    *(undefined4 *)(param_1 + 0x180) = 3;
    FUN_005cd690(*(undefined4 *)(param_1 + 0x78));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x7c));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x80));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x84));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x88));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x8c));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x90));
    FUN_005cd690(*(undefined4 *)(param_1 + 0x94));
    FUN_005cd2a0();
    break;
  case 3:
    FUN_005cd300("cut_1",2000,0,*(undefined4 *)(param_1 + 0x78));
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x78),"cut_trigger",0);
    if (((float)fVar4 < 50.0) ||
       (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x88),"cut_trigger",0),
       (float)fVar4 < 50.0)) {
      *(undefined4 *)(param_1 + 0x180) = 4;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 22.0;
    }
    break;
  case 4:
    FUN_005cd300("cut_1",2000,0,*(undefined4 *)(param_1 + 0x78));
    if ((*(float *)(param_1 + 100) != 0.0) &&
       (fVar4 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100))) {
      FUN_005cd4e0();
      *(undefined4 *)(param_1 + 0x180) = 5;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 30.0;
      FUN_00437d30("ch08002.wav");
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x78));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x7c));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x80));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x84));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x88));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x8c));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x90));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x94));
      FUN_005c83e0(*(undefined4 *)(param_1 + 0xb8));
    }
    break;
  case 5:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      uVar2 = FUN_00437d30("ch08003.wav");
      *(undefined4 *)(param_1 + 0x188) = uVar2;
      uVar2 = FUN_005c8250("svapc",2,"apc_spawn",0,0);
      *(undefined4 *)(param_1 + 0xbc) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xbc),"apc_1");
      FUN_005cb960(*(undefined4 *)(param_1 + 0xbc),"apc_path",1);
      uVar2 = FUN_005c8250("svfigh",2,"apc_escort",0,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0xbc),1);
      uVar2 = FUN_005c8250("svfigh",2,"apc_escort",0,0);
      FUN_005cbce0(uVar2,*(undefined4 *)(param_1 + 0xbc),1);
      *(undefined4 *)(param_1 + 0x180) = 6;
      FUN_0065c2c0();
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
    }
    break;
  case 6:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      uVar2 = FUN_005c8250("svapc",2,"apc_spawn",0,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xc0),"apc_2");
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc0),"apc_path",1);
      *(undefined4 *)(param_1 + 0x180) = 7;
      FUN_0065c2c0();
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
    }
    break;
  case 7:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      uVar2 = FUN_005c8250("svapc",2,"apc_spawn",0,0);
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xc4),"apc_3");
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc4),"apc_path",1);
      *(undefined4 *)(param_1 + 0x180) = 8;
      FUN_0065c2c0();
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
    }
    break;
  case 8:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      uVar2 = FUN_005c8250("svapc",2,"apc_spawn",0,0);
      *(undefined4 *)(param_1 + 200) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 200),"apc_4");
      FUN_005cb960(*(undefined4 *)(param_1 + 200),"apc_path",1);
      *(undefined4 *)(param_1 + 0x180) = 9;
      FUN_0065c2c0();
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
    }
    break;
  case 9:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      uVar2 = FUN_005c8250("svapc",2,"apc_spawn",0,0);
      *(undefined4 *)(param_1 + 0xcc) = uVar2;
      FUN_005cd7f0(*(undefined4 *)(param_1 + 0xcc),"apc_5");
      FUN_005cb960(*(undefined4 *)(param_1 + 0xcc),"apc_path",1);
      *(undefined4 *)(param_1 + 0x180) = 10;
      FUN_0065c2c0();
      *(undefined1 *)(param_1 + 0x5f) = 0;
    }
    break;
  case 10:
    cVar1 = FUN_0065b910();
    if (cVar1 == '\0') {
      if ((*(int *)(param_1 + 0xcc) == *(int *)(param_1 + 0x70)) &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xcc),
                                        *(undefined4 *)(param_1 + 0x170)), (float)fVar4 <= 30.0)) {
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
        *(undefined4 *)(param_1 + 0x180) = 0xb;
        FUN_0065c2c0();
      }
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0);
      if (((float)fVar4 < 30.0) ||
         ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"trigger_1",0),
          (float)fVar4 < 30.0 &&
          (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0),
          300.0 < (float)fVar4)))) {
        FUN_00437d30("ch08005.wav");
        *(undefined4 *)(param_1 + 0x180) = 100;
        fVar4 = (float10)FUN_004b1670("ch08lsec.des");
        FUN_0045c0f0((float)fVar4 + 20.0);
      }
    }
    break;
  case 0xb:
    cVar1 = FUN_0065b910();
    if (cVar1 == '\0') {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0);
      if ((((float)fVar4 < 50.0) &&
          ((*(int *)(param_1 + 0xcc) != *(int *)(param_1 + 0x70) ||
           (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                          *(undefined4 *)(param_1 + 0x70)), 75.0 < (float)fVar4))))
         || ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"trigger_1",0),
             (float)fVar4 < 30.0 &&
             (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0),
             300.0 < (float)fVar4)))) {
        FUN_00437d30("ch08005.wav");
        *(undefined4 *)(param_1 + 0x180) = 100;
        fVar4 = (float10)FUN_004b1670("ch08lsec.des");
        FUN_0045c0f0((float)fVar4 + 20.0);
      }
      else {
        fVar4 = (float10)FUN_004b1670();
        if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100))
        {
          FUN_005cadd0(1,100);
          uVar2 = FUN_00437d30("ch08004.wav");
          *(undefined4 *)(param_1 + 0x188) = uVar2;
          *(undefined4 *)(param_1 + 0x180) = 0xc;
          FUN_0065c2c0();
          *(undefined4 *)(param_1 + 0x180) = 0xd;
          FUN_005c95e0(*(undefined4 *)(param_1 + 200));
          *(undefined1 *)(param_1 + 0x60) = 1;
        }
      }
    }
    break;
  case 0xd:
    cVar1 = FUN_0065b910();
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x60) != '\0') &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                        *(undefined4 *)(param_1 + 0x70)), (float)fVar4 < 100.0)) {
        *(undefined1 *)(param_1 + 0x60) = 0;
        FUN_005c9610(*(undefined4 *)(param_1 + 200));
      }
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0);
      if ((((float)fVar4 < 50.0) &&
          ((*(int *)(param_1 + 0xcc) != *(int *)(param_1 + 0x70) ||
           (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                          *(undefined4 *)(param_1 + 0x70)), 75.0 < (float)fVar4))))
         || ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"trigger_1",0),
             (float)fVar4 < 30.0 &&
             (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0),
             300.0 < (float)fVar4)))) {
        FUN_00437d30("ch08005.wav");
        *(undefined4 *)(param_1 + 0x180) = 100;
        fVar4 = (float10)FUN_004b1670("ch08lsec.des");
        FUN_0045c0f0((float)fVar4 + 20.0);
      }
      else {
        cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x188));
        if (cVar1 != '\0') {
          *(undefined4 *)(param_1 + 0x180) = 0xe;
          FUN_0065c2c0();
          *(undefined4 *)(param_1 + 0x180) = 0xf;
        }
      }
    }
    break;
  case 0xf:
    cVar1 = FUN_0065b910();
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x60) != '\0') &&
         (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                        *(undefined4 *)(param_1 + 0x70)), (float)fVar4 < 100.0)) {
        *(undefined1 *)(param_1 + 0x60) = 0;
        FUN_005c9610(*(undefined4 *)(param_1 + 200));
      }
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0);
      if ((((float)fVar4 < 50.0) &&
          ((*(int *)(param_1 + 0xcc) != *(int *)(param_1 + 0x70) ||
           (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 200),
                                          *(undefined4 *)(param_1 + 0x70)), 75.0 < (float)fVar4))))
         || ((fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xcc),"trigger_1",0),
             (float)fVar4 < 30.0 &&
             (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 200),"apc_fail",0),
             300.0 < (float)fVar4)))) {
        FUN_00437d30("ch08005.wav");
        *(undefined4 *)(param_1 + 0x180) = 100;
        fVar4 = (float10)FUN_004b1670("ch08lsec.des");
        FUN_0045c0f0((float)fVar4 + 20.0);
      }
      else if ((*(int *)(param_1 + 0xcc) == *(int *)(param_1 + 0x70)) &&
              (fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x70),"trigger_1",0),
              (float)fVar4 < 30.0)) {
        FUN_00437d30("ch08006.wav");
        *(undefined4 *)(param_1 + 0x180) = 0x10;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 20.0;
      }
    }
    break;
  case 0x10:
    fVar4 = (float10)FUN_004b1670();
    if ((float)fVar4 < *(float *)(param_1 + 100) || (float)fVar4 == *(float *)(param_1 + 100)) {
      if (*(int *)(param_1 + 0xcc) != *(int *)(param_1 + 0x70)) {
        FUN_005c88b0(*(undefined4 *)(param_1 + 0x70),2);
        *(undefined4 *)(param_1 + 0x180) = 0x11;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 30.0;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x180) = 100;
      fVar4 = (float10)FUN_004b1670("ch08lseg.des");
      FUN_0045c0f0((float)fVar4 + 2.0);
    }
    break;
  case 0x11:
    if (*(int *)(param_1 + 0xcc) == *(int *)(param_1 + 0x70)) {
      *(undefined4 *)(param_1 + 0x180) = 100;
      fVar4 = (float10)FUN_004b1670("ch08lseg.des");
      FUN_0045c0f0((float)fVar4 + 2.0);
    }
    else {
      fVar4 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
        FUN_005cd2a0();
        *(undefined4 *)(param_1 + 0x180) = 0x12;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
      }
    }
    break;
  case 0x12:
    FUN_005cd300("cut_bang",2000,0,*(undefined4 *)(param_1 + 0xcc));
    cVar1 = FUN_005cd560();
    fVar4 = (float10)FUN_004b1670();
    if ((*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) ||
       (cVar1 != '\0')) {
      FUN_005ce2f0(*(undefined4 *)(param_1 + 0xcc),"xpltrsr");
      FUN_005ce330("wrecker_1","xpltrsd");
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x70),1);
      for (local_c = 0; local_c < 6; local_c = local_c + 1) {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0xd0 + local_c * 4));
      }
      uVar2 = FUN_005c8250("cvrecy",1,"military_spawn",0,0);
      *(undefined4 *)(param_1 + 0x174) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0x174),"military_path",1);
      uVar2 = FUN_005c8250("cvmuf",1,"military_spawn",0,0);
      *(undefined4 *)(param_1 + 0x178) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0x178),"military_path",1);
      uVar2 = FUN_005c8250("cvslf",1,"military_spawn",0,0,"military_path",1);
      FUN_005cb960(uVar2);
      uVar2 = FUN_005caea0(1);
      FUN_005cadd0(1,uVar2);
      if (cVar1 == '\0') {
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 5.0;
        *(undefined4 *)(param_1 + 0x180) = 0x13;
      }
      else {
        FUN_005cd4e0();
        *(undefined4 *)(param_1 + 0x180) = 0x14;
        FUN_0065c2c0();
        *(undefined4 *)(param_1 + 0x180) = 0x15;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 300.0;
      }
    }
    break;
  case 0x13:
    FUN_005cd300("cut_bang",2000,0,*(undefined4 *)(param_1 + 0xcc));
    fVar4 = (float10)FUN_004b1670();
    if ((*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) ||
       (cVar1 = FUN_005cd560(), cVar1 != '\0')) {
      FUN_005cd4e0();
      *(undefined4 *)(param_1 + 0x180) = 0x14;
      FUN_0065c2c0();
      *(undefined4 *)(param_1 + 0x180) = 0x15;
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 300.0;
    }
    break;
  case 0x15:
    if ((*(float *)(param_1 + 100) != 0.0) &&
       (fVar4 = (float10)FUN_004b1670(),
       *(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100))) {
      *(undefined4 *)(param_1 + 100) = 0;
      FUN_005cadd0(2,100);
    }
    fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x70),"nw_trigger",0);
    if (60.0 < (float)fVar4) {
      fVar4 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x70),"ne_trigger",0);
      if ((float)fVar4 <= 60.0) {
        FUN_00437d30("ch08007.wav");
        FUN_00437d30("ch08008.wav");
        FUN_005c95e0(*(undefined4 *)(param_1 + 0x98));
        FUN_005c95e0(*(undefined4 *)(param_1 + 0x9c));
        *(undefined1 *)(param_1 + 0x61) = 1;
        FUN_005c95e0(*(undefined4 *)(param_1 + 0xa0));
        FUN_005c95e0(*(undefined4 *)(param_1 + 0xa4));
        FUN_005c95e0(*(undefined4 *)(param_1 + 0xa8));
        FUN_005c95e0(*(undefined4 *)(param_1 + 0xac));
        *(undefined4 *)(param_1 + 0x180) = 0x16;
        FUN_0065c2c0();
        *(undefined4 *)(param_1 + 0x180) = 0x17;
        FUN_005c88e0(*(undefined4 *)(param_1 + 0x9c));
      }
    }
    else {
      FUN_00437d30("ch08007.wav");
      FUN_00437d30("ch08008.wav");
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x98));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0x9c));
      *(undefined1 *)(param_1 + 0x61) = 1;
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xa0));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xa4));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xa8));
      FUN_005c95e0(*(undefined4 *)(param_1 + 0xac));
      *(undefined4 *)(param_1 + 0x180) = 0x16;
      FUN_0065c2c0();
      *(undefined4 *)(param_1 + 0x180) = 0x17;
      FUN_005c88e0(*(undefined4 *)(param_1 + 0x98));
    }
    break;
  case 0x17:
    if (((((*(char *)(param_1 + 0x5b) == '\0') && (*(char *)(param_1 + 0x5c) == '\0')) &&
         (*(char *)(param_1 + 0x5d) == '\0')) && (*(char *)(param_1 + 0x5e) == '\0')) ||
       (iVar3 = FUN_004f6b10(), 0 < iVar3)) {
      if ((*(float *)(param_1 + 100) != 0.0) &&
         (fVar4 = (float10)FUN_004b1670(),
         *(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100))) {
        *(undefined4 *)(param_1 + 100) = 0;
        FUN_005cadd0(2,0x32);
      }
      if ((*(char *)(param_1 + 0x61) != '\0') &&
         ((*(int *)(param_1 + 0x70) == *(int *)(param_1 + 0x98) ||
          (*(int *)(param_1 + 0x70) == *(int *)(param_1 + 0x9c))))) {
        *(undefined1 *)(param_1 + 0x61) = 0;
        FUN_005c9610(*(undefined4 *)(param_1 + 0x98));
        FUN_005c9610(*(undefined4 *)(param_1 + 0x9c));
      }
      if ((*(char *)(param_1 + 0x5b) == '\0') &&
         (cVar1 = FUN_005c84d0(param_1 + 0xa0), cVar1 == '\0')) {
        *(undefined1 *)(param_1 + 0x5b) = 1;
        if ((*(char *)(param_1 + 0x5c) == '\0') &&
           ((*(char *)(param_1 + 0x5d) == '\0' && (*(char *)(param_1 + 0x5e) == '\0')))) {
          FUN_004f6ae0(0x10e,0x80000000,0x80000000);
        }
        for (local_c = 0; local_c < 4; local_c = local_c + 1) {
          FUN_005c83e0(*(undefined4 *)(param_1 + 0xe8 + local_c * 4));
        }
        FUN_005c83e0(*(undefined4 *)(param_1 + 0xb0));
      }
      if ((((*(char *)(param_1 + 0x5d) == '\0') &&
           (cVar1 = FUN_005c84d0(param_1 + 0xa8), cVar1 == '\0')) &&
          (*(undefined1 *)(param_1 + 0x5d) = 1, *(char *)(param_1 + 0x5c) == '\0')) &&
         ((*(char *)(param_1 + 0x5b) == '\0' && (*(char *)(param_1 + 0x5e) == '\0')))) {
        FUN_004f6ae0(0x10e,0x80000000,0x80000000);
      }
      if ((*(char *)(param_1 + 0x5c) == '\0') &&
         (cVar1 = FUN_005c84d0(param_1 + 0xa4), cVar1 == '\0')) {
        *(undefined1 *)(param_1 + 0x5c) = 1;
        if ((*(char *)(param_1 + 0x5b) == '\0') &&
           ((*(char *)(param_1 + 0x5e) == '\0' && (*(char *)(param_1 + 0x5d) == '\0')))) {
          FUN_004f6ae0(0x10e,0x80000000,0x80000000);
        }
        for (local_c = 0; local_c < 4; local_c = local_c + 1) {
          FUN_005c83e0(*(undefined4 *)(param_1 + 0xf8 + local_c * 4));
        }
        FUN_005c83e0(*(undefined4 *)(param_1 + 0xb0));
      }
      if ((((*(char *)(param_1 + 0x5e) == '\0') &&
           (cVar1 = FUN_005c84d0(param_1 + 0xac), cVar1 == '\0')) &&
          (*(undefined1 *)(param_1 + 0x5e) = 1, *(char *)(param_1 + 0x5c) == '\0')) &&
         ((*(char *)(param_1 + 0x5b) == '\0' && (*(char *)(param_1 + 0x5d) == '\0')))) {
        FUN_004f6ae0(0x10e,0x80000000,0x80000000);
      }
      if (((*(char *)(param_1 + 0x5b) != '\0') && (*(char *)(param_1 + 0x5c) != '\0')) &&
         ((*(char *)(param_1 + 0x5d) != '\0' && (*(char *)(param_1 + 0x5e) != '\0')))) {
        FUN_004ff160();
        *(undefined4 *)(param_1 + 0x180) = 0x18;
        FUN_0065c2c0();
        *(undefined4 *)(param_1 + 0x180) = 0x1b;
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 40.0;
      }
    }
    else {
      fVar4 = (float10)FUN_004b1670("ch08lsef.des");
      FUN_0045c0f0((float)fVar4 + 2.0);
      *(undefined4 *)(param_1 + 0x180) = 100;
    }
    break;
  case 0x19:
    cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x188));
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x180) = 0x1a;
      FUN_004f6ae0(100,0x80000000,0x80000000);
    }
    break;
  case 0x1a:
    iVar3 = FUN_004f6b10();
    if (iVar3 < 1) {
      fVar4 = (float10)FUN_004b1670("ch08lsef.des");
      FUN_0045c0f0((float)fVar4 + 2.0);
      *(undefined4 *)(param_1 + 0x180) = 100;
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0xa8);
      if ((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xac), cVar1 == '\0')) {
        FUN_004ff160();
        *(undefined4 *)(param_1 + 0x180) = 0x1b;
        FUN_0065c2c0();
        fVar4 = (float10)FUN_004b1670();
        *(float *)(param_1 + 100) = (float)fVar4 + 10.0;
      }
    }
    break;
  case 0x1b:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_1","xpltrsd");
      FUN_005ce330("day_1a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 12.0;
      *(undefined4 *)(param_1 + 0x180) = 0x1c;
    }
    break;
  case 0x1c:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_2","xpltrsd");
      FUN_005ce330("day_2a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 11.0;
      *(undefined4 *)(param_1 + 0x180) = 0x1d;
    }
    break;
  case 0x1d:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_3","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 9.0;
      *(undefined4 *)(param_1 + 0x180) = 0x1e;
    }
    break;
  case 0x1e:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_4","xpltrsd");
      FUN_005ce330("day_4a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 13.0;
      *(undefined4 *)(param_1 + 0x180) = 0x1f;
    }
    break;
  case 0x1f:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_5","xpltrsd");
      FUN_005ce330("day_5a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 15.0;
      *(undefined4 *)(param_1 + 0x180) = 0x20;
    }
    break;
  case 0x20:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_6","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 15.0;
      *(undefined4 *)(param_1 + 0x180) = 0x21;
    }
    break;
  case 0x21:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_7","xpltrsd");
      FUN_005ce330("day_7a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 7.0;
      *(undefined4 *)(param_1 + 0x180) = 0x22;
    }
    break;
  case 0x22:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_8","xpltrsd");
      FUN_005ce330("day_8a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 8.0;
      *(undefined4 *)(param_1 + 0x180) = 0x23;
    }
    break;
  case 0x23:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_9","xpltrsd");
      FUN_005ce330("day_9a","xpltrsd");
      fVar4 = (float10)FUN_004b1670();
      *(float *)(param_1 + 100) = (float)fVar4 + 6.0;
      *(undefined4 *)(param_1 + 0x180) = 0x24;
    }
    break;
  case 0x24:
    fVar4 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 100) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 100)) {
      FUN_005ce330("day_10","xpltrsd");
      FUN_00437d30("ch08009.wav");
      *(undefined4 *)(param_1 + 0x180) = 100;
      FUN_0065c2c0();
      fVar4 = (float10)FUN_004b1670("ch08win.des");
      FUN_0045c110((float)fVar4 + 13.0);
    }
  }
  FUN_0065bc40();
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
  return;
}

