
void __fastcall FUN_00559e00(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  if (*(char *)(param_1 + 0x5e) == '\0') {
    FUN_00437d30("misns301.wav");
    *(undefined1 *)(param_1 + 0x5b) = 1;
    *(undefined1 *)(param_1 + 0x5e) = 1;
    uVar2 = FUN_005c7e90("avrecy1_recycler");
    *(undefined4 *)(param_1 + 0xf0) = uVar2;
    uVar2 = FUN_005c7fb0();
    *(undefined4 *)(param_1 + 0xf4) = uVar2;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x70) = (float)fVar3 + 600.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x74) = (float)fVar3 + 120.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x78) = (float)fVar3 + 280.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x7c) = (float)fVar3 + 380.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar3 + 5.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x84) = (float)fVar3 + 5.0;
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar3 + 15.0;
    uVar2 = FUN_005c7e90("bomb1");
    *(undefined4 *)(param_1 + 0xf8) = uVar2;
    uVar2 = FUN_005c7e90("bomb2");
    *(undefined4 *)(param_1 + 0xfc) = uVar2;
    uVar2 = FUN_005c7e90("bomb3");
    *(undefined4 *)(param_1 + 0x100) = uVar2;
    uVar2 = FUN_005c7e90("bomb4");
    *(undefined4 *)(param_1 + 0x104) = uVar2;
    uVar2 = FUN_005c7e90("basenav");
    *(undefined4 *)(param_1 + 0x118) = uVar2;
    uVar2 = FUN_005c7e90("avrecy");
    *(undefined4 *)(param_1 + 0x11c) = uVar2;
    FUN_005c9640(*(undefined4 *)(param_1 + 0x118),"Home Base");
    FUN_005c9640(*(undefined4 *)(param_1 + 0x11c),"Black Dog Outpost");
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xf4) = uVar2;
  if (*(char *)(param_1 + 0x5b) == '\x01') {
    FUN_004f6aa0();
    if (*(char *)(param_1 + 0x62) == '\x01') {
      FUN_004f6ab0("misns302.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misns301.otf",DAT_009175b0,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x62) == '\0') {
      FUN_004f6ab0("misns301.otf",DAT_0091755c,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x5f) == '\x01') {
      FUN_004f6ab0("misns302.otf",DAT_009175b0,0x41000000,0);
    }
    *(undefined1 *)(param_1 + 0x5b) = 0;
  }
  fVar3 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0x74) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x74)) &&
      (*(char *)(param_1 + 0x65) == '\0')) && (*(char *)(param_1 + 0x62) == '\0')) {
    FUN_00437d30("misns307.wav");
    *(undefined1 *)(param_1 + 0x65) = 1;
  }
  fVar3 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0x78) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x78)) &&
      (*(char *)(param_1 + 0x66) == '\0')) && (*(char *)(param_1 + 0x62) == '\0')) {
    FUN_00437d30("misns308.wav");
    *(undefined1 *)(param_1 + 0x66) = 1;
  }
  fVar3 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0x7c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x7c)) &&
      (*(char *)(param_1 + 0x67) == '\0')) && (*(char *)(param_1 + 0x62) == '\0')) {
    FUN_00437d30("misns309.wav");
    *(undefined1 *)(param_1 + 0x67) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if (((cVar1 != '\0') &&
      (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"bdspawntrig",0),
      (float)fVar3 < 200.0)) && (*(char *)(param_1 + 0x61) == '\0')) {
    uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
    *(undefined4 *)(param_1 + 0x90) = uVar2;
    uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
    *(undefined4 *)(param_1 + 0x94) = uVar2;
    uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
    *(undefined4 *)(param_1 + 0x98) = uVar2;
    uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
    *(undefined4 *)(param_1 + 0x9c) = uVar2;
    uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
    *(undefined4 *)(param_1 + 0xa0) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0xf4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xf4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xf4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0x9c),*(undefined4 *)(param_1 + 0xf4),1);
    FUN_005cb820(*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0xf4),1);
    *(undefined1 *)(param_1 + 0x61) = 1;
    FUN_00437d30("misns310.wav");
  }
  if (*(char *)(param_1 + 0x61) == '\x01') {
    FUN_005c84d0(param_1 + 0x90);
    FUN_005c84d0(param_1 + 0x90);
    FUN_005c84d0(param_1 + 0x90);
    FUN_005c84d0(param_1 + 0x90);
    FUN_005c84d0(param_1 + 0x90);
  }
  if ((*(char *)(param_1 + 0x61) == '\x01') &&
     (fVar3 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0x88) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x88))) {
    cVar1 = FUN_005c84d0(param_1 + 0x90);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x94);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x98);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x98),*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x9c);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x9c),*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xa0);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0xf4),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x90);
    if (((cVar1 == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x94), cVar1 == '\0')) &&
       ((cVar1 = FUN_005c84d0(param_1 + 0x98), cVar1 == '\0' &&
        ((cVar1 = FUN_005c84d0(param_1 + 0x9c), cVar1 == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0xa0), cVar1 == '\0')))))) {
      uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0x90) = uVar2;
      uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0x94) = uVar2;
      uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0x98) = uVar2;
      uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0x9c) = uVar2;
      uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0xa0) = uVar2;
    }
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x88) = (float)fVar3 + 8.0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x62) == '\0')) {
    FUN_00437d30("misns302.wav");
    if (*(char *)(param_1 + 0x5d) == '\0') {
      uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar2;
      uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0xc4) = uVar2;
      uVar2 = FUN_005c8250("avfigh",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 200) = uVar2;
      uVar2 = FUN_005c8250("avtank",2,"bdspawn1",0,0);
      *(undefined4 *)(param_1 + 0xcc) = uVar2;
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc0),"bdpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xc4),"bdpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 200),"bdpath3",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0xcc),"bdpath4",1);
      *(undefined1 *)(param_1 + 0x5d) = 1;
      *(undefined1 *)(param_1 + 0x61) = 0;
    }
    *(undefined1 *)(param_1 + 0x54) = 1;
    *(undefined1 *)(param_1 + 0x55) = 1;
    *(undefined1 *)(param_1 + 0x56) = 1;
    *(undefined1 *)(param_1 + 0x57) = 1;
    *(undefined1 *)(param_1 + 0x62) = 1;
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
  if (((*(char *)(param_1 + 0x54) == '\x01') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xc0)
                                    ), (float)fVar3 < 410.0)) && (*(char *)(param_1 + 0x58) == '\0')
     ) {
    uVar2 = FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 0xc0),0);
    *(undefined4 *)(param_1 + 0xd0) = uVar2;
    uVar2 = FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 0xc0),0);
    *(undefined4 *)(param_1 + 0xd4) = uVar2;
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0xc0),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xc0),1);
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if (((*(char *)(param_1 + 0x55) == '\x01') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xc4)
                                    ), (float)fVar3 < 410.0)) && (*(char *)(param_1 + 0x59) == '\0')
     ) {
    uVar2 = FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 0xc4),0);
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    uVar2 = FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 0xc4),0);
    *(undefined4 *)(param_1 + 0xdc) = uVar2;
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xd8),*(undefined4 *)(param_1 + 0xc4),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0xc4),1);
    *(undefined1 *)(param_1 + 0x59) = 1;
  }
  if (((*(char *)(param_1 + 0x56) == '\x01') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 200))
      , (float)fVar3 < 410.0)) && (*(char *)(param_1 + 0x5a) == '\0')) {
    uVar2 = FUN_005c8080("avfigh",2,*(undefined4 *)(param_1 + 200),0);
    *(undefined4 *)(param_1 + 0xe0) = uVar2;
    uVar2 = FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 200),0);
    *(undefined4 *)(param_1 + 0xe4) = uVar2;
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xe0),*(undefined4 *)(param_1 + 200),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 200),1);
    *(undefined1 *)(param_1 + 0x5a) = 1;
  }
  if (((*(char *)(param_1 + 0x57) == '\x01') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xcc)
                                    ), (float)fVar3 < 410.0)) && (*(char *)(param_1 + 0x5c) == '\0')
     ) {
    uVar2 = FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 0xcc),0);
    *(undefined4 *)(param_1 + 0xe8) = uVar2;
    uVar2 = FUN_005c8080("avtank",2,*(undefined4 *)(param_1 + 0xcc),0);
    *(undefined4 *)(param_1 + 0xec) = uVar2;
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xe8),*(undefined4 *)(param_1 + 0xcc),1);
    FUN_005cbc20(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xcc),1);
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"homesweethome",0);
  if ((((float)fVar3 < 200.0) && (*(char *)(param_1 + 0x5f) == '\0')) &&
     (*(char *)(param_1 + 0x62) == '\x01')) {
    uVar2 = FUN_00437d30("misns303.wav");
    *(undefined4 *)(param_1 + 0x130) = uVar2;
    *(undefined1 *)(param_1 + 0x5f) = 1;
  }
  if ((*(char *)(param_1 + 0x5f) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x130)), cVar1 != '\0')) {
    fVar3 = (float10)FUN_004b1670("misns3w1.des");
    FUN_0045c110((float)fVar3 + 0.0);
  }
  fVar3 = (float10)FUN_004b1670();
  if (((*(float *)(param_1 + 0x70) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x70)) &&
      (*(char *)(param_1 + 0x62) == '\0')) && (*(char *)(param_1 + 0x60) == '\0')) {
    uVar2 = FUN_00437d30("misns304.wav");
    *(undefined4 *)(param_1 + 300) = uVar2;
    *(undefined1 *)(param_1 + 0x60) = 1;
  }
  if ((*(char *)(param_1 + 0x60) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 300)), cVar1 != '\0')) {
    fVar3 = (float10)FUN_004b1670("misns3l1.des");
    FUN_0045c0f0((float)fVar3);
  }
  fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"don\'tgohere",0);
  if ((((float)fVar3 < 50.0) && (*(char *)(param_1 + 99) == '\0')) &&
     (*(char *)(param_1 + 0x62) == '\0')) {
    FUN_00437d30("misns305.wav");
    *(undefined1 *)(param_1 + 99) = 1;
  }
  fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"iwarnedyou",0);
  if ((((float)fVar3 < 50.0) && (*(char *)(param_1 + 100) == '\0')) &&
     (*(char *)(param_1 + 0x62) == '\0')) {
    uVar2 = FUN_00437d30("misns306.wav");
    *(undefined4 *)(param_1 + 0x128) = uVar2;
    *(undefined1 *)(param_1 + 100) = 1;
  }
  if ((*(char *)(param_1 + 100) == '\x01') &&
     (cVar1 = FUN_00437d60(*(undefined4 *)(param_1 + 0x128)), cVar1 != '\0')) {
    fVar3 = (float10)FUN_004b1670("misns3l2.des");
    FUN_0045c0f0((float)fVar3);
  }
  if (((*(char *)(param_1 + 0x6d) == '\0') && (*(char *)(param_1 + 0x61) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0xf0), cVar1 != '\0' &&
      (fVar3 = (float10)FUN_004b1670(),
      *(float *)(param_1 + 0x80) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x80))))) {
    fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf8),"patroltrig1",0);
    if (((((float)fVar3 < 100.0) ||
         (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xfc),"patroltrig1",0),
         (float)fVar3 < 100.0)) ||
        (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x100),"patroltrig1",0),
        (float)fVar3 < 100.0)) ||
       ((fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x104),"patroltrig1",0),
        (float)fVar3 < 100.0 ||
        (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"patroltrig1",0),
        (float)fVar3 < 100.0)))) {
      uVar2 = FUN_005c8250("bvraz",2,"patrolspawn1",0,0);
      *(undefined4 *)(param_1 + 0x108) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"patrolspawn1",0,0);
      *(undefined4 *)(param_1 + 0x10c) = uVar2;
      FUN_00437d30("misns219.wav");
      FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"patrolpath1",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x10c),"patrolpath1",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x108),0);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),0);
      *(undefined1 *)(param_1 + 0x6d) = 1;
    }
    fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf8),"patroltrig2",0);
    if ((((float)fVar3 < 100.0) ||
        (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xfc),"patroltrig2",0),
        (float)fVar3 < 100.0)) ||
       ((fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x100),"patroltrig2",0),
        (float)fVar3 < 100.0 ||
        ((fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0x104),"patroltrig2",0),
         (float)fVar3 < 100.0 ||
         (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"patroltrig2",0),
         (float)fVar3 < 100.0)))))) {
      uVar2 = FUN_005c8250("bvraz",2,"patrolspawn2",0,0);
      *(undefined4 *)(param_1 + 0x108) = uVar2;
      uVar2 = FUN_005c8250("bvraz",2,"patrolspawn2",0,0);
      *(undefined4 *)(param_1 + 0x10c) = uVar2;
      FUN_00437d30("misns219.wav");
      FUN_005cb960(*(undefined4 *)(param_1 + 0x108),"patrolpath2",1);
      FUN_005cb960(*(undefined4 *)(param_1 + 0x10c),"patrolpath2",1);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x108),0);
      FUN_005cb620(*(undefined4 *)(param_1 + 0x10c),0);
      *(undefined1 *)(param_1 + 0x6d) = 1;
    }
    fVar3 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0x80) = (float)fVar3 + 3.0;
  }
  if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x6d) == '\x01')) &&
     (*(char *)(param_1 + 0x61) == '\0')) {
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x108));
    *(undefined4 *)(param_1 + 0x110) = uVar2;
    uVar2 = FUN_005ca150(*(undefined4 *)(param_1 + 0x10c));
    *(undefined4 *)(param_1 + 0x114) = uVar2;
    fVar3 = (float10)FUN_004b1670();
    if (*(float *)(param_1 + 0x84) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x84)) {
      fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x108),
                                    *(undefined4 *)(param_1 + 0x110));
      if ((float)fVar3 < 180.0) {
        *(undefined1 *)(param_1 + 0x61) = 1;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x110),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x110),1);
        *(undefined1 *)(param_1 + 0x69) = 1;
      }
      fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x10c),
                                    *(undefined4 *)(param_1 + 0x114));
      if ((float)fVar3 < 180.0) {
        *(undefined1 *)(param_1 + 0x61) = 1;
        FUN_005cb820(*(undefined4 *)(param_1 + 0x10c),*(undefined4 *)(param_1 + 0x114),1);
        FUN_005cb820(*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x114),1);
        *(undefined1 *)(param_1 + 0x69) = 1;
      }
      fVar3 = (float10)FUN_004b1670();
      *(float *)(param_1 + 0x84) = (float)fVar3 + 3.0;
      if ((*(char *)(param_1 + 0x69) == '\x01') && (*(char *)(param_1 + 0x68) == '\0')) {
        FUN_00437d30("misns220.wav");
        *(undefined1 *)(param_1 + 0x68) = 1;
      }
    }
  }
  if ((*(char *)(param_1 + 0x6a) == '\0') &&
     ((fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig1",0),
      (float)fVar3 < 200.0 ||
      (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig1b",0),
      (float)fVar3 < 200.0)))) {
    FUN_005c8250("proxmine",2,"path_1",0,0);
    FUN_005c8250("proxmine",2,"path_2",0,0);
    FUN_005c8250("proxmine",2,"path_3",0,0);
    FUN_005c8250("proxmine",2,"path_4",0,0);
    FUN_005c8250("proxmine",2,"path_5",0,0);
    FUN_005c8250("proxmine",2,"path_6",0,0);
    FUN_005c8250("proxmine",2,"path_7",0,0);
    FUN_005c8250("proxmine",2,"path_8",0,0);
    FUN_005c8250("proxmine",2,"path_9",0,0);
    FUN_005c8250("proxmine",2,"path_10",0,0);
    FUN_005c8250("proxmine",2,"path_11",0,0);
    *(undefined1 *)(param_1 + 0x6a) = 1;
  }
  if ((*(char *)(param_1 + 0x6b) == '\0') &&
     ((fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig2",0),
      (float)fVar3 < 200.0 ||
      (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig2b",0),
      (float)fVar3 < 200.0)))) {
    FUN_005c8250("proxmine",2,"path_12",0,0);
    FUN_005c8250("proxmine",2,"path_13",0,0);
    FUN_005c8250("proxmine",2,"path_14",0,0);
    FUN_005c8250("proxmine",2,"path_15",0,0);
    FUN_005c8250("proxmine",2,"path_16",0,0);
    FUN_005c8250("proxmine",2,"path_17",0,0);
    FUN_005c8250("proxmine",2,"path_18",0,0);
    FUN_005c8250("proxmine",2,"path_19",0,0);
    FUN_005c8250("proxmine",2,"path_20",0,0);
    FUN_005c8250("proxmine",2,"path_21",0,0);
    FUN_005c8250("proxmine",2,"path_22",0,0);
    *(undefined1 *)(param_1 + 0x6b) = 1;
  }
  if (*(char *)(param_1 + 0x6c) == '\0') {
    fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig3",0);
    if ((200.0 <= (float)fVar3) &&
       (fVar3 = (float10)FUN_005c9800(*(undefined4 *)(param_1 + 0xf4),"minetrig3b",0),
       200.0 <= (float)fVar3)) {
      return;
    }
    FUN_005c8250("proxmine",2,"path_23",0,0);
    FUN_005c8250("proxmine",2,"path_24",0,0);
    FUN_005c8250("proxmine",2,"path_25",0,0);
    FUN_005c8250("proxmine",2,"path_26",0,0);
    FUN_005c8250("proxmine",2,"path_27",0,0);
    FUN_005c8250("proxmine",2,"path_28",0,0);
    FUN_005c8250("proxmine",2,"path_29",0,0);
    FUN_005c8250("proxmine",2,"path_30",0,0);
    FUN_005c8250("proxmine",2,"path_31",0,0);
    FUN_005c8250("proxmine",2,"path_32",0,0);
    FUN_005c8250("proxmine",2,"path_33",0,0);
    FUN_005c8250("proxmine",2,"path_34",0,0);
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  return;
}

