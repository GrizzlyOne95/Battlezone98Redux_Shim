
void __fastcall FUN_0054b010(int param_1)

{
  float fVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(char *)(param_1 + 0x54) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x9c) = (float)fVar5 + 10.0;
    uVar3 = FUN_00437d30("misn1701.wav");
    *(undefined4 *)(param_1 + 0x1a4) = uVar3;
    uVar3 = FUN_005c7e90("avrecy18_recycler");
    *(undefined4 *)(param_1 + 500) = uVar3;
    uVar3 = FUN_005c7e90("savfactory1");
    *(undefined4 *)(param_1 + 0x124) = uVar3;
    uVar3 = FUN_005c7e90("savfactory2");
    *(undefined4 *)(param_1 + 0x128) = uVar3;
    uVar3 = FUN_005c7e90("savfactory3");
    *(undefined4 *)(param_1 + 300) = uVar3;
    uVar3 = FUN_005c7e90("savfactory4");
    *(undefined4 *)(param_1 + 0x130) = uVar3;
    uVar3 = FUN_005c7e90("factorypart1");
    *(undefined4 *)(param_1 + 0x1cc) = uVar3;
    uVar3 = FUN_005c7e90("factorypart2");
    *(undefined4 *)(param_1 + 0x1d0) = uVar3;
    uVar3 = FUN_005c7e90("factorypart3");
    *(undefined4 *)(param_1 + 0x1d4) = uVar3;
    uVar3 = FUN_005c7e90("factorynav");
    *(undefined4 *)(param_1 + 0x144) = uVar3;
    uVar3 = FUN_005c7e90("basenav");
    *(undefined4 *)(param_1 + 0x148) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer1",0,0);
    *(undefined4 *)(param_1 + 0x340) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer2",0,0);
    *(undefined4 *)(param_1 + 0x344) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer3",0,0);
    *(undefined4 *)(param_1 + 0x348) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer4",0,0);
    *(undefined4 *)(param_1 + 0x34c) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer5",0,0);
    *(undefined4 *)(param_1 + 0x350) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer6",0,0);
    *(undefined4 *)(param_1 + 0x354) = uVar3;
    uVar3 = FUN_005c8250("hbptow",2,"geizer7",0,0);
    *(undefined4 *)(param_1 + 0x358) = uVar3;
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x340));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x344));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x348));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x34c));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x350));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x354));
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x358));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x340),"Tower 1");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x344),"Tower 2");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x348),"Tower 3");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x34c),"Tower 4");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x350),"Tower 5");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x354),"Tower 6");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x358),"Tower 7 ");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x144),"Furies Factory");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x148),"Home Base");
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(undefined1 *)(param_1 + 0x6e) = 1;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x104) = (float)fVar5 + 35.0;
    FUN_005cadd0(1,0x28);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar5 + 10.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar5 + 100.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar5 + 220.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar5 + 340.0;
    FUN_005cb2d0("misn17.aip",2);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x98) = (float)fVar5 + 30.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb4) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb8) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xbc) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc0) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc4) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 200) = (float)fVar5 + 3.0;
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xcc) = (float)fVar5 + 3.0;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x318);
  if (cVar2 != '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x32c);
    if (cVar2 == '\0') {
      uVar3 = FUN_005c8250("hvsav",2,"counter",0,0);
      *(undefined4 *)(param_1 + 0x32c) = uVar3;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x32c),*(undefined4 *)(param_1 + 0x318),1);
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x31c);
  if (cVar2 != '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x330);
    if (cVar2 == '\0') {
      uVar3 = FUN_005c8250("hvsav",2,"counter",0,0);
      *(undefined4 *)(param_1 + 0x330) = uVar3;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x330),*(undefined4 *)(param_1 + 0x31c),1);
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 800);
  if (cVar2 != '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x334);
    if (cVar2 == '\0') {
      uVar3 = FUN_005c8250("hvsav",2,"counter",0,0);
      *(undefined4 *)(param_1 + 0x334) = uVar3;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x334),*(undefined4 *)(param_1 + 800),1);
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x324);
  if (cVar2 != '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x338);
    if (cVar2 == '\0') {
      uVar3 = FUN_005c8250("hvsav",2,"counter",0,0);
      *(undefined4 *)(param_1 + 0x338) = uVar3;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x338),*(undefined4 *)(param_1 + 0x324),1);
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x328);
  if (cVar2 != '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x33c);
    if (cVar2 == '\0') {
      uVar3 = FUN_005c8250("hvsav",2,"counter",0,0);
      *(undefined4 *)(param_1 + 0x33c) = uVar3;
      FUN_005cb820(*(undefined4 *)(param_1 + 0x33c),*(undefined4 *)(param_1 + 0x328),1);
    }
  }
  if (*(char *)(param_1 + 0x5d) == '\0') {
    FUN_005cd2a0();
    *(undefined1 *)(param_1 + 0x5e) = 1;
    *(undefined1 *)(param_1 + 0x5d) = 1;
  }
  if (*(char *)(param_1 + 0x5f) == '\x01') {
    cVar2 = FUN_005cd300("cineractive2",500,2000,*(undefined4 *)(param_1 + 0x340));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 0x5f) = 0;
      *(undefined1 *)(param_1 + 0x60) = 1;
    }
  }
  if (*(char *)(param_1 + 0x60) == '\x01') {
    cVar2 = FUN_005cd300("cineractive3",1000,2000,*(undefined4 *)(param_1 + 0x354));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 0x60) = 0;
      *(undefined1 *)(param_1 + 0x61) = 1;
    }
  }
  if (*(char *)(param_1 + 0x61) == '\x01') {
    cVar2 = FUN_005cd300("cineractive5",1000,2000,*(undefined4 *)(param_1 + 0x348));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 0x61) = 0;
      *(undefined1 *)(param_1 + 0x62) = 1;
    }
  }
  if (*(char *)(param_1 + 0x62) == '\x01') {
    cVar2 = FUN_005cd300("cineractive6",1000,2000,*(undefined4 *)(param_1 + 0x34c));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 0x62) = 0;
      *(undefined1 *)(param_1 + 99) = 1;
    }
  }
  if (*(char *)(param_1 + 99) == '\x01') {
    cVar2 = FUN_005cd300("cineractive4",1000,2000,*(undefined4 *)(param_1 + 0x350));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 99) = 0;
      *(undefined1 *)(param_1 + 100) = 1;
    }
  }
  if (*(char *)(param_1 + 100) == '\x01') {
    cVar2 = FUN_005cd300("cineractive7",1000,0x6a4,*(undefined4 *)(param_1 + 0x358));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 100) = 0;
    }
  }
  if (*(char *)(param_1 + 0x5e) == '\x01') {
    cVar2 = FUN_005cd300("cineractive1",1000,2000,*(undefined4 *)(param_1 + 0x124));
    if (cVar2 != '\0') {
      *(undefined1 *)(param_1 + 0x5e) = 0;
      *(undefined1 *)(param_1 + 0x5f) = 1;
    }
  }
  if (*(char *)(param_1 + 0x69) == '\0') {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x1a4));
    if (cVar2 == '\0') {
      cVar2 = FUN_005cd560();
      if (cVar2 == '\0') goto LAB_0054ba1b;
    }
    FUN_005cd4e0();
    FUN_00437d80(*(undefined4 *)(param_1 + 0x1a4));
    *(undefined1 *)(param_1 + 0x69) = 1;
    *(undefined1 *)(param_1 + 0x5e) = 0;
    *(undefined1 *)(param_1 + 0x5f) = 0;
    *(undefined1 *)(param_1 + 0x60) = 0;
    *(undefined1 *)(param_1 + 0x61) = 0;
    *(undefined1 *)(param_1 + 0x62) = 0;
    *(undefined1 *)(param_1 + 99) = 0;
    *(undefined1 *)(param_1 + 100) = 0;
  }
LAB_0054ba1b:
  if (*(char *)(param_1 + 0x8a) == '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x1cc);
    if (cVar2 == '\0') {
      FUN_005c8250("eggeizr1",0,"part1geizer",0,0);
      *(undefined1 *)(param_1 + 0x8a) = 1;
    }
  }
  if (*(char *)(param_1 + 0x8b) == '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x1d0);
    if (cVar2 == '\0') {
      FUN_005c8250("eggeizr1",0,"part2geizer",0,0);
      *(undefined1 *)(param_1 + 0x8b) = 1;
    }
  }
  if (*(char *)(param_1 + 0x8c) == '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x1d4);
    if (cVar2 == '\0') {
      FUN_005c8250("eggeizr1",0,"part3geizer",0,0);
      *(undefined1 *)(param_1 + 0x8c) = 1;
    }
  }
  if (*(char *)(param_1 + 0x5c) == '\0') {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x9c) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x9c)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x128));
      *(undefined4 *)(param_1 + 0x1f0) = uVar3;
      fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1f0),&DAT_008816fc,0);
      if ((float)fVar5 < 610.0) {
LAB_0054bbd6:
        uVar3 = FUN_005c8250("boltmine2",2,"mine54",0,0);
        *(undefined4 *)(param_1 + 0x238) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine1",0,0);
        *(undefined4 *)(param_1 + 0x23c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine2",0,0);
        *(undefined4 *)(param_1 + 0x240) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine3",0,0);
        *(undefined4 *)(param_1 + 0x244) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine4",0,0);
        *(undefined4 *)(param_1 + 0x248) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine5",0,0);
        *(undefined4 *)(param_1 + 0x24c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine6",0,0);
        *(undefined4 *)(param_1 + 0x250) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine7",0,0);
        *(undefined4 *)(param_1 + 0x254) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine8",0,0);
        *(undefined4 *)(param_1 + 600) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine9",0,0);
        *(undefined4 *)(param_1 + 0x25c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine10",0,0);
        *(undefined4 *)(param_1 + 0x260) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine11",0,0);
        *(undefined4 *)(param_1 + 0x264) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine12",0,0);
        *(undefined4 *)(param_1 + 0x268) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine13",0,0);
        *(undefined4 *)(param_1 + 0x26c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine14",0,0);
        *(undefined4 *)(param_1 + 0x270) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine15",0,0);
        *(undefined4 *)(param_1 + 0x274) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine16",0,0);
        *(undefined4 *)(param_1 + 0x278) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine17",0,0);
        *(undefined4 *)(param_1 + 0x27c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine18",0,0);
        *(undefined4 *)(param_1 + 0x280) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine19",0,0);
        *(undefined4 *)(param_1 + 0x284) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine20",0,0);
        *(undefined4 *)(param_1 + 0x288) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine21",0,0);
        *(undefined4 *)(param_1 + 0x28c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine22",0,0);
        *(undefined4 *)(param_1 + 0x290) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine23",0,0);
        *(undefined4 *)(param_1 + 0x294) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine24",0,0);
        *(undefined4 *)(param_1 + 0x298) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine25",0,0);
        *(undefined4 *)(param_1 + 0x29c) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine26",0,0);
        *(undefined4 *)(param_1 + 0x2a0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine27",0,0);
        *(undefined4 *)(param_1 + 0x2a4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine28",0,0);
        *(undefined4 *)(param_1 + 0x2a8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine29",0,0);
        *(undefined4 *)(param_1 + 0x2ac) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine30",0,0);
        *(undefined4 *)(param_1 + 0x2b0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine31",0,0);
        *(undefined4 *)(param_1 + 0x2b4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine32",0,0);
        *(undefined4 *)(param_1 + 0x2b8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine33",0,0);
        *(undefined4 *)(param_1 + 700) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine34",0,0);
        *(undefined4 *)(param_1 + 0x2c0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine35",0,0);
        *(undefined4 *)(param_1 + 0x2c4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine36",0,0);
        *(undefined4 *)(param_1 + 0x2c8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine37",0,0);
        *(undefined4 *)(param_1 + 0x2cc) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine38",0,0);
        *(undefined4 *)(param_1 + 0x2d0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine39",0,0);
        *(undefined4 *)(param_1 + 0x2d4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine40",0,0);
        *(undefined4 *)(param_1 + 0x2d8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine41",0,0);
        *(undefined4 *)(param_1 + 0x2dc) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine42",0,0);
        *(undefined4 *)(param_1 + 0x2e0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine43",0,0);
        *(undefined4 *)(param_1 + 0x2e4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine44",0,0);
        *(undefined4 *)(param_1 + 0x2e8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine45",0,0);
        *(undefined4 *)(param_1 + 0x2ec) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine46",0,0);
        *(undefined4 *)(param_1 + 0x2f0) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine47",0,0);
        *(undefined4 *)(param_1 + 0x2f4) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine48",0,0);
        *(undefined4 *)(param_1 + 0x2f8) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine49",0,0);
        *(undefined4 *)(param_1 + 0x2fc) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine55",0,0);
        *(undefined4 *)(param_1 + 0x300) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine56",0,0);
        *(undefined4 *)(param_1 + 0x304) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine52",0,0);
        *(undefined4 *)(param_1 + 0x308) = uVar3;
        uVar3 = FUN_005c8250("boltmine2",2,"mine53",0,0);
        *(undefined4 *)(param_1 + 0x30c) = uVar3;
        *(undefined1 *)(param_1 + 0x5c) = 1;
      }
      else {
        fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1f0),&DAT_008816f8,0);
        if ((float)fVar5 < 610.0) goto LAB_0054bbd6;
        fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1f0),&DAT_00881708,0);
        if ((float)fVar5 < 610.0) goto LAB_0054bbd6;
      }
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x9c) = (float)fVar5 + 3.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x340);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x7b) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xb4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xb4)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x340));
      *(undefined4 *)(param_1 + 0x1a8) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x340),
                                    *(undefined4 *)(param_1 + 0x1a8));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x340),0);
        *(undefined4 *)(param_1 + 0x134) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x340),0);
        *(undefined4 *)(param_1 + 0x138) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x340),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x340),1000);
        *(undefined1 *)(param_1 + 0x7b) = 1;
      }
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xb4) = (float)fVar5 + 2.0;
      *(undefined4 *)(param_1 + 0x1a8) = 0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x134);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x134));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x134));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x134));
        *(undefined4 *)(param_1 + 0x14c) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x134),*(undefined4 *)(param_1 + 0x14c),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x138);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x138));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x138));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x138));
        *(undefined4 *)(param_1 + 0x150) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x138),*(undefined4 *)(param_1 + 0x150),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x13c);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x13c));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x13c));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x13c));
        *(undefined4 *)(param_1 + 0x154) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x154),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x140);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x140));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x140));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x140));
        *(undefined4 *)(param_1 + 0x158) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x158),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x184);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x184));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x184));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x184));
        *(undefined4 *)(param_1 + 0x15c) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x15c),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x188);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x188));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x188));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x188));
        *(undefined4 *)(param_1 + 0x160) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x160),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x18c);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x18c));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x18c));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x18c));
        *(undefined4 *)(param_1 + 0x164) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 0x164),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 400);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 400));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 400));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 400));
        *(undefined4 *)(param_1 + 0x168) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 400),*(undefined4 *)(param_1 + 0x168),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x194);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x194));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x194));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x194));
        *(undefined4 *)(param_1 + 0x16c) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x16c),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x198);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x198));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x198));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x198));
        *(undefined4 *)(param_1 + 0x170) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x170),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x19c);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x19c));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x19c));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x19c));
        *(undefined4 *)(param_1 + 0x174) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x19c),*(undefined4 *)(param_1 + 0x174),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x1a0);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x1a0));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1a0));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1a0));
        *(undefined4 *)(param_1 + 0x178) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0x178),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x1c4);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x1c4));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1c4));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1c4));
        *(undefined4 *)(param_1 + 0x17c) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x180),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x1c8);
  if (cVar2 != '\0') {
    iVar4 = FUN_005cb5c0(*(undefined4 *)(param_1 + 0x1c8));
    if (iVar4 == 0xf) {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1c8));
      if (0.0 < (float)fVar5) {
        uVar3 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1c8));
        *(undefined4 *)(param_1 + 0x180) = uVar3;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x180),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x344);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xb8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xb8)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x344));
      *(undefined4 *)(param_1 + 0x1ac) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x344),
                                    *(undefined4 *)(param_1 + 0x1ac));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x344),0);
        *(undefined4 *)(param_1 + 0x13c) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x344),0);
        *(undefined4 *)(param_1 + 0x140) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x344),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x344),1000);
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
      *(undefined4 *)(param_1 + 0x1ac) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xb8) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x348);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x7d) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xbc) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xbc)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x348));
      *(undefined4 *)(param_1 + 0x1b0) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x348),
                                    *(undefined4 *)(param_1 + 0x1b0));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x348),0);
        *(undefined4 *)(param_1 + 0x184) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x348),0);
        *(undefined4 *)(param_1 + 0x188) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x184),*(undefined4 *)(param_1 + 0x348),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x188),*(undefined4 *)(param_1 + 0x348),1000);
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
      *(undefined4 *)(param_1 + 0x1b0) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xbc) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x34c);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x7e) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xc0) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xc0)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x34c));
      *(undefined4 *)(param_1 + 0x1b4) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x34c),
                                    *(undefined4 *)(param_1 + 0x1b4));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x34c),0);
        *(undefined4 *)(param_1 + 0x18c) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x34c),0);
        *(undefined4 *)(param_1 + 400) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x18c),*(undefined4 *)(param_1 + 0x34c),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 400),*(undefined4 *)(param_1 + 0x34c),1000);
        *(undefined1 *)(param_1 + 0x7e) = 1;
      }
      *(undefined4 *)(param_1 + 0x1b4) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xc0) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x350);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x7f) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xc4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xc4)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x350));
      *(undefined4 *)(param_1 + 0x1b8) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x350),
                                    *(undefined4 *)(param_1 + 0x1b8));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x350),0);
        *(undefined4 *)(param_1 + 0x194) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x350),0);
        *(undefined4 *)(param_1 + 0x198) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x194),*(undefined4 *)(param_1 + 0x350),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x198),*(undefined4 *)(param_1 + 0x350),1000);
        *(undefined1 *)(param_1 + 0x7f) = 1;
      }
      *(undefined4 *)(param_1 + 0x1b8) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xc4) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x354);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x80) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 200) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 200)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x354));
      *(undefined4 *)(param_1 + 0x1bc) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x354),
                                    *(undefined4 *)(param_1 + 0x1bc));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x354),0);
        *(undefined4 *)(param_1 + 0x19c) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x354),0);
        *(undefined4 *)(param_1 + 0x1a0) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x19c),*(undefined4 *)(param_1 + 0x354),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x1a0),*(undefined4 *)(param_1 + 0x354),1000);
        *(undefined1 *)(param_1 + 0x80) = 1;
      }
      *(undefined4 *)(param_1 + 0x1bc) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 200) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x358);
  if ((cVar2 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    fVar5 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0xcc) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xcc)) {
      uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x358));
      *(undefined4 *)(param_1 + 0x1c0) = uVar3;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x358),
                                    *(undefined4 *)(param_1 + 0x1c0));
      if ((float)fVar5 < 400.0) {
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x358),0);
        *(undefined4 *)(param_1 + 0x1c4) = uVar3;
        uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x358),0);
        *(undefined4 *)(param_1 + 0x1c8) = uVar3;
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x1c4),*(undefined4 *)(param_1 + 0x358),1000);
        FUN_005cbce0(*(undefined4 *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x358),1000);
        *(undefined1 *)(param_1 + 0x81) = 1;
      }
      *(undefined4 *)(param_1 + 0x1c0) = 0;
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0xcc) = (float)fVar5 + 2.0;
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 0x340);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x82) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer1",0,0);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x344);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x83) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer2",0,0);
    *(undefined1 *)(param_1 + 0x83) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x348);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x84) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer3",0,0);
    *(undefined1 *)(param_1 + 0x84) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x34c);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x85) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer4",0,0);
    *(undefined1 *)(param_1 + 0x85) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x350);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x86) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer5",0,0);
    *(undefined1 *)(param_1 + 0x86) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x354);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer6",0,0);
    *(undefined1 *)(param_1 + 0x87) = 1;
  }
  cVar2 = FUN_005c84d0(param_1 + 0x358);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x88) == '\0')) {
    FUN_005c8250("eggeizr1",0,"geizer7",0,0);
    *(undefined1 *)(param_1 + 0x88) = 1;
  }
  if (*(char *)(param_1 + 0x6e) == '\x01') {
    FUN_004f6aa0();
    if (*(char *)(param_1 + 0x7a) == '\0') {
      FUN_004f6ab0("misn1701.otf",DAT_0091755c,0x41000000,0);
    }
    if ((*(char *)(param_1 + 0x7a) == '\x01') && (*(char *)(param_1 + 0x76) == '\0')) {
      FUN_004f6ab0("misn1701.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1702.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x76) == '\x01') {
      FUN_004f6ab0("misn1701.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn1702.otf",DAT_009175b0,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x6e) = 0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xa4)) {
    FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x124),0);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa4) = (float)fVar5 + 400.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xa8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xa8)) {
    FUN_005c8080("hvsav",2,*(undefined4 *)(param_1 + 0x128),0);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xa8) = (float)fVar5 + 400.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xac) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xac)) {
    FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 300),0);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xac) = (float)fVar5 + 400.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if (*(float *)(param_1 + 0xb0) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xb0)) {
    FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x130),0);
    fVar5 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xb0) = (float)fVar5 + 400.0;
  }
  fVar5 = (float10)FUN_004b1670();
  if ((*(float *)(param_1 + 0x98) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0x98)) &&
     (*(char *)(param_1 + 0x77) == '\0')) {
    uVar3 = FUN_005ca150(*(undefined4 *)(param_1 + 0x124));
    *(undefined4 *)(param_1 + 0x1f8) = uVar3;
    fVar5 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x1f8),"savspawn",1);
    if (450.0 <= (float)fVar5) {
      fVar5 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x98) = (float)fVar5 + 5.0;
    }
    else {
      uVar3 = FUN_005c8080("hvsav",2,*(undefined4 *)(param_1 + 0x124),0);
      *(undefined4 *)(param_1 + 0x1fc) = uVar3;
      uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 0x128),0);
      *(undefined4 *)(param_1 + 0x200) = uVar3;
      uVar3 = FUN_005c8080("hvsat",2,*(undefined4 *)(param_1 + 300),0);
      *(undefined4 *)(param_1 + 0x204) = uVar3;
      uVar3 = FUN_005c8080("hvsav",2,*(undefined4 *)(param_1 + 0x130),0);
      *(undefined4 *)(param_1 + 0x208) = uVar3;
      *(undefined1 *)(param_1 + 0x77) = 1;
      FUN_005cbce0(*(undefined4 *)(param_1 + 0x1fc),*(undefined4 *)(param_1 + 0x124),1);
      FUN_005cbce0(*(undefined4 *)(param_1 + 0x200),*(undefined4 *)(param_1 + 0x128),1);
      FUN_005cbce0(*(undefined4 *)(param_1 + 0x204),*(undefined4 *)(param_1 + 300),1);
      FUN_005cbce0(*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 0x130),1);
      *(undefined4 *)(param_1 + 0x14c) = 0;
      *(undefined4 *)(param_1 + 0x150) = 0;
      *(undefined4 *)(param_1 + 0x154) = 0;
      *(undefined4 *)(param_1 + 0x158) = 0;
      *(undefined4 *)(param_1 + 0x98) = 0;
    }
  }
  if (*(char *)(param_1 + 0x77) != '\0') {
    fVar5 = (float10)FUN_004b1670();
    fVar1 = (float)fVar5;
    cVar2 = FUN_005c84d0(param_1 + 0x124);
    if (cVar2 == '\0') {
LAB_0054dd71:
      local_4c = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x124));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054dd71;
      local_4c = FUN_005cd130(*(undefined4 *)(param_1 + 0x124));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x128);
    if (cVar2 == '\0') {
LAB_0054dddc:
      local_64 = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x128));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054dddc;
      local_64 = FUN_005cd130(*(undefined4 *)(param_1 + 0x128));
    }
    cVar2 = FUN_005c84d0(param_1 + 300);
    if (cVar2 == '\0') {
LAB_0054de47:
      local_60 = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 300));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054de47;
      local_60 = FUN_005cd130(*(undefined4 *)(param_1 + 300));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x130);
    if (cVar2 == '\0') {
LAB_0054deb1:
      local_58 = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x130));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054deb1;
      local_58 = FUN_005cd130(*(undefined4 *)(param_1 + 0x130));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x1cc);
    if (cVar2 == '\0') {
LAB_0054df1c:
      local_50 = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1cc));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054df1c;
      local_50 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1cc));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x1d0);
    if (cVar2 == '\0') {
LAB_0054df87:
      local_54 = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1d0));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054df87;
      local_54 = FUN_005cd130(*(undefined4 *)(param_1 + 0x1d0));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x1d4);
    if (cVar2 == '\0') {
LAB_0054dff1:
      local_5c = 0;
    }
    else {
      fVar5 = (float10)FUN_005cd170(*(undefined4 *)(param_1 + 0x1d4));
      if ((float)fVar5 + 20.0 <= fVar1) goto LAB_0054dff1;
      local_5c = FUN_005cd130(*(undefined4 *)(param_1 + 0x1d4));
    }
    cVar2 = FUN_005c84d0(param_1 + 0x1fc);
    if (cVar2 != '\0') {
      local_28 = *(int *)(param_1 + 0x14c);
      if (local_4c == 0) {
        if (local_64 == 0) {
          if (local_60 == 0) {
            if (local_58 == 0) {
              if (local_50 == 0) {
                if (local_54 == 0) {
                  if (local_5c != 0) {
                    local_28 = local_5c;
                  }
                }
                else {
                  local_28 = local_54;
                }
              }
              else {
                local_28 = local_50;
              }
            }
            else {
              local_28 = local_58;
            }
          }
          else {
            local_28 = local_60;
          }
        }
        else {
          local_28 = local_64;
        }
      }
      else {
        local_28 = local_4c;
      }
      if (*(int *)(param_1 + 0x14c) != local_28) {
        *(int *)(param_1 + 0x14c) = local_28;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x1fc),*(undefined4 *)(param_1 + 0x14c),1);
      }
    }
    cVar2 = FUN_005c84d0(param_1 + 0x200);
    if (cVar2 != '\0') {
      local_1c = *(int *)(param_1 + 0x150);
      if (local_64 == 0) {
        if (local_4c == 0) {
          if (local_60 == 0) {
            if (local_58 == 0) {
              if (local_50 == 0) {
                if (local_54 == 0) {
                  if (local_5c != 0) {
                    local_1c = local_5c;
                  }
                }
                else {
                  local_1c = local_54;
                }
              }
              else {
                local_1c = local_50;
              }
            }
            else {
              local_1c = local_58;
            }
          }
          else {
            local_1c = local_60;
          }
        }
        else {
          local_1c = local_4c;
        }
      }
      else {
        local_1c = local_64;
      }
      if (*(int *)(param_1 + 0x150) != local_1c) {
        *(int *)(param_1 + 0x150) = local_1c;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x200),*(undefined4 *)(param_1 + 0x150),1);
      }
    }
    cVar2 = FUN_005c84d0(param_1 + 0x204);
    if (cVar2 != '\0') {
      local_24 = *(int *)(param_1 + 0x154);
      if (local_60 == 0) {
        if (local_58 == 0) {
          if (local_64 == 0) {
            if (local_4c == 0) {
              if (local_5c == 0) {
                if (local_54 == 0) {
                  if (local_50 != 0) {
                    local_24 = local_50;
                  }
                }
                else {
                  local_24 = local_54;
                }
              }
              else {
                local_24 = local_5c;
              }
            }
            else {
              local_24 = local_4c;
            }
          }
          else {
            local_24 = local_64;
          }
        }
        else {
          local_24 = local_58;
        }
      }
      else {
        local_24 = local_60;
      }
      if (*(int *)(param_1 + 0x154) != local_24) {
        *(int *)(param_1 + 0x154) = local_24;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x204),*(undefined4 *)(param_1 + 0x154),1);
      }
    }
    cVar2 = FUN_005c84d0(param_1 + 0x208);
    if (cVar2 != '\0') {
      local_20 = *(int *)(param_1 + 0x158);
      if (local_58 == 0) {
        if (local_60 == 0) {
          if (local_64 == 0) {
            if (local_4c == 0) {
              if (local_5c == 0) {
                if (local_54 == 0) {
                  if (local_50 != 0) {
                    local_20 = local_50;
                  }
                }
                else {
                  local_20 = local_54;
                }
              }
              else {
                local_20 = local_5c;
              }
            }
            else {
              local_20 = local_4c;
            }
          }
          else {
            local_20 = local_64;
          }
        }
        else {
          local_20 = local_60;
        }
      }
      else {
        local_20 = local_58;
      }
      if (*(int *)(param_1 + 0x158) != local_20) {
        *(int *)(param_1 + 0x158) = local_20;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 0x158),1);
      }
    }
  }
  cVar2 = FUN_005c84d0(param_1 + 500);
  if ((cVar2 == '\0') && (*(char *)(param_1 + 0x75) == '\0')) {
    fVar5 = (float10)FUN_004b1670("misn17l1.des");
    FUN_0045c0f0((float)fVar5 + 20.0);
    FUN_00437d30("misn1704.wav");
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if (((((*(char *)(param_1 + 0x82) == '\x01') && (*(char *)(param_1 + 0x83) == '\x01')) &&
       (*(char *)(param_1 + 0x84) == '\x01')) &&
      ((*(char *)(param_1 + 0x85) == '\x01' && (*(char *)(param_1 + 0x86) == '\x01')))) &&
     ((*(char *)(param_1 + 0x87) == '\x01' &&
      ((*(char *)(param_1 + 0x88) == '\x01' && (*(char *)(param_1 + 0x7a) == '\0')))))) {
    if (*(char *)(param_1 + 0x5c) == '\0') {
      FUN_005ca9e0(300);
      uVar3 = FUN_005c8250("boltmine2",2,"mine54",0,0);
      *(undefined4 *)(param_1 + 0x238) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine1",0,0);
      *(undefined4 *)(param_1 + 0x23c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine2",0,0);
      *(undefined4 *)(param_1 + 0x240) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine3",0,0);
      *(undefined4 *)(param_1 + 0x244) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine4",0,0);
      *(undefined4 *)(param_1 + 0x248) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine5",0,0);
      *(undefined4 *)(param_1 + 0x24c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine6",0,0);
      *(undefined4 *)(param_1 + 0x250) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine7",0,0);
      *(undefined4 *)(param_1 + 0x254) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine8",0,0);
      *(undefined4 *)(param_1 + 600) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine9",0,0);
      *(undefined4 *)(param_1 + 0x25c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine10",0,0);
      *(undefined4 *)(param_1 + 0x260) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine11",0,0);
      *(undefined4 *)(param_1 + 0x264) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine12",0,0);
      *(undefined4 *)(param_1 + 0x268) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine13",0,0);
      *(undefined4 *)(param_1 + 0x26c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine14",0,0);
      *(undefined4 *)(param_1 + 0x270) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine15",0,0);
      *(undefined4 *)(param_1 + 0x274) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine16",0,0);
      *(undefined4 *)(param_1 + 0x278) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine17",0,0);
      *(undefined4 *)(param_1 + 0x27c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine18",0,0);
      *(undefined4 *)(param_1 + 0x280) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine19",0,0);
      *(undefined4 *)(param_1 + 0x284) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine20",0,0);
      *(undefined4 *)(param_1 + 0x288) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine21",0,0);
      *(undefined4 *)(param_1 + 0x28c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine22",0,0);
      *(undefined4 *)(param_1 + 0x290) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine23",0,0);
      *(undefined4 *)(param_1 + 0x294) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine24",0,0);
      *(undefined4 *)(param_1 + 0x298) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine25",0,0);
      *(undefined4 *)(param_1 + 0x29c) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine26",0,0);
      *(undefined4 *)(param_1 + 0x2a0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine27",0,0);
      *(undefined4 *)(param_1 + 0x2a4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine28",0,0);
      *(undefined4 *)(param_1 + 0x2a8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine29",0,0);
      *(undefined4 *)(param_1 + 0x2ac) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine30",0,0);
      *(undefined4 *)(param_1 + 0x2b0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine31",0,0);
      *(undefined4 *)(param_1 + 0x2b4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine32",0,0);
      *(undefined4 *)(param_1 + 0x2b8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine33",0,0);
      *(undefined4 *)(param_1 + 700) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine34",0,0);
      *(undefined4 *)(param_1 + 0x2c0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine35",0,0);
      *(undefined4 *)(param_1 + 0x2c4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine36",0,0);
      *(undefined4 *)(param_1 + 0x2c8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine37",0,0);
      *(undefined4 *)(param_1 + 0x2cc) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine38",0,0);
      *(undefined4 *)(param_1 + 0x2d0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine39",0,0);
      *(undefined4 *)(param_1 + 0x2d4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine40",0,0);
      *(undefined4 *)(param_1 + 0x2d8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine41",0,0);
      *(undefined4 *)(param_1 + 0x2dc) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine42",0,0);
      *(undefined4 *)(param_1 + 0x2e0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine43",0,0);
      *(undefined4 *)(param_1 + 0x2e4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine44",0,0);
      *(undefined4 *)(param_1 + 0x2e8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine45",0,0);
      *(undefined4 *)(param_1 + 0x2ec) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine46",0,0);
      *(undefined4 *)(param_1 + 0x2f0) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine47",0,0);
      *(undefined4 *)(param_1 + 0x2f4) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine48",0,0);
      *(undefined4 *)(param_1 + 0x2f8) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine49",0,0);
      *(undefined4 *)(param_1 + 0x2fc) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine55",0,0);
      *(undefined4 *)(param_1 + 0x300) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine56",0,0);
      *(undefined4 *)(param_1 + 0x304) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine52",0,0);
      *(undefined4 *)(param_1 + 0x308) = uVar3;
      uVar3 = FUN_005c8250("boltmine2",2,"mine53",0,0);
      *(undefined4 *)(param_1 + 0x30c) = uVar3;
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
    FUN_005cd2a0();
    *(undefined1 *)(param_1 + 0x6e) = 1;
    *(undefined1 *)(param_1 + 0x7a) = 1;
    *(undefined1 *)(param_1 + 0x79) = 1;
    *(undefined1 *)(param_1 + 0x89) = 1;
    *(undefined4 *)(param_1 + 0x364) = 0;
    uVar3 = FUN_00437d30("misn1730.wav");
    *(undefined4 *)(param_1 + 0x310) = uVar3;
  }
  if ((*(char *)(param_1 + 0x79) == '\x01') && (*(char *)(param_1 + 0x5c) == '\x01')) {
    FUN_005cb1c0(*(undefined4 *)(param_1 + 0x238 + *(int *)(param_1 + 0x364) * 4),0x461c4000);
    *(int *)(param_1 + 0x364) = *(int *)(param_1 + 0x364) + 1;
    if (0x35 < *(int *)(param_1 + 0x364)) {
      *(undefined1 *)(param_1 + 0x79) = 0;
    }
  }
  if ((*(char *)(param_1 + 0x79) == '\x01') && (*(char *)(param_1 + 0x78) == '\0')) {
    FUN_005cd300("minecin",1000,500,*(undefined4 *)(param_1 + 0x128));
  }
  if (*(char *)(param_1 + 0x89) == '\x01') {
    cVar2 = FUN_00437d60(*(undefined4 *)(param_1 + 0x310));
    if (cVar2 == '\0') {
      cVar2 = FUN_005cd560();
      if (cVar2 == '\0') goto LAB_0054ee3e;
    }
    FUN_005cd4e0();
    *(undefined1 *)(param_1 + 0x78) = 1;
    FUN_00437d80(*(undefined4 *)(param_1 + 0x310));
    *(undefined1 *)(param_1 + 0x89) = 0;
  }
LAB_0054ee3e:
  if (*(char *)(param_1 + 0x76) == '\0') {
    cVar2 = FUN_005c84d0(param_1 + 0x1cc);
    if (cVar2 == '\0') {
      cVar2 = FUN_005c84d0(param_1 + 0x1d0);
      if (cVar2 == '\0') {
        cVar2 = FUN_005c84d0(param_1 + 0x1d4);
        if (cVar2 == '\0') {
          FUN_00437d30("misn1703.wav");
          *(undefined1 *)(param_1 + 0x76) = 1;
          fVar5 = (float10)FUN_004b1670("misn17w1.des");
          FUN_0045c110((float)fVar5 + 7.0);
          FUN_005cd2a0();
          uVar3 = FUN_005c8250("eggeizr1",3,"cinscrap",0,0);
          *(undefined4 *)(param_1 + 0x314) = uVar3;
          if (*(int *)(param_1 + 0x124) == 0) {
            local_14 = 0x453ae000;
            local_10 = 0x42800000;
            local_c = 0x47c60000;
            uVar3 = FUN_005c8380("eggeizr1",3,&local_14,0);
            *(undefined4 *)(param_1 + 0x124) = uVar3;
          }
          FUN_005cd440(*(undefined4 *)(param_1 + 0x314),1000,8000,1000,
                       *(undefined4 *)(param_1 + 0x124));
          fVar5 = (float10)FUN_004b1670();
          *(float *)(param_1 + 0xd0) = (float)fVar5 + 1.0;
          fVar5 = (float10)FUN_004b1670();
          *(float *)(param_1 + 0xd8) = (float)fVar5 + 2.5;
          fVar5 = (float10)FUN_004b1670();
          *(float *)(param_1 + 0xd4) = (float)fVar5 + 3.2;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x76) == '\x01') {
    if (*(char *)(param_1 + 0x8d) == '\0') {
      fVar5 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0xd0) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xd0))
      {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x128),0x48435000);
        *(undefined1 *)(param_1 + 0x8d) = 1;
      }
    }
    if (*(char *)(param_1 + 0x8e) == '\0') {
      fVar5 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0xd4) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xd4))
      {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 300),0x48435000);
        *(undefined1 *)(param_1 + 0x8e) = 1;
      }
    }
    if (*(char *)(param_1 + 0x8f) == '\0') {
      fVar5 = (float10)FUN_004b1670();
      if (*(float *)(param_1 + 0xd8) <= (float)fVar5 && (float)fVar5 != *(float *)(param_1 + 0xd8))
      {
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x124),0x48435000);
        FUN_005cb1c0(*(undefined4 *)(param_1 + 0x130),0x48435000);
        *(undefined1 *)(param_1 + 0x8f) = 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

