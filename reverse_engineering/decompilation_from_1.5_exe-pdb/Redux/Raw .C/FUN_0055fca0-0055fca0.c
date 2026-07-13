
void __fastcall FUN_0055fca0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0x144) = uVar2;
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_005cacb0(1,8);
    FUN_005cadd0(2,0x28);
    FUN_005cacb0(2,0x28);
    FUN_005c95e0(*(undefined4 *)(param_1 + 0x1a8));
    FUN_005c9640(*(undefined4 *)(param_1 + 0x1a8),"Military Prison");
    FUN_00437d30("misns700.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misns700.otf",DAT_0091755c,0x41000000,0);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe8) = (float)fVar3 + 8.0;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x154),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x224),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x25c),1);
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x260),1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x13c) = (float)fVar3 + 60.0;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf4) = (float)fVar3 + 240.0;
    FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abtowe",1);
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0x13c) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x13c)) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x13c) = (float)fVar3 + 180.0;
    cVar1 = FUN_005c84d0(param_1 + 0x25c);
    if (cVar1 != '\0') {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x25c),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x260);
    if (cVar1 != '\0') {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x260),1);
    }
  }
  if (((*(char *)(param_1 + 0x54) != '\0') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),
                                     *(undefined4 *)(param_1 + 0x1a8)), (float)fVar3 < 150.0)) &&
     (*(char *)(param_1 + 0x89) == '\0')) {
    FUN_00437d30("misns722.wav");
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xec) = (float)fVar3 + 120.0;
    *(undefined1 *)(param_1 + 0x89) = 1;
  }
  if (((*(char *)(param_1 + 0x54) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xe8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xe8))) &&
     (*(char *)(param_1 + 0x80) == '\0')) {
    uVar2 = FUN_005c8250("bvscav",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x170) = uVar2;
    uVar2 = FUN_005c8250("bvscav",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x170),*(undefined4 *)(param_1 + 0x14c),0);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x14c),0);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x130) = (float)fVar3 + 10.0;
    *(undefined1 *)(param_1 + 0x80) = 1;
  }
  if ((*(char *)(param_1 + 0x61) == '\0') &&
     ((((((cVar1 = FUN_005c84d0(param_1 + 0x170), cVar1 != '\0' &&
          (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x170)), (float)fVar3 < 0.91)) ||
         (((cVar1 = FUN_005c84d0(param_1 + 0x174), cVar1 != '\0' &&
           (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x174)), (float)fVar3 < 0.91))
          || ((cVar1 = FUN_005c84d0(param_1 + 0x194), cVar1 != '\0' &&
              (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x194)), (float)fVar3 < 0.95)
              ))))) ||
        ((cVar1 = FUN_005c84d0(param_1 + 0x168), cVar1 != '\0' &&
         (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x168)), (float)fVar3 < 0.95))))
       || ((cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0' &&
           (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x224)), (float)fVar3 < 0.95))))
      && (*(char *)(param_1 + 0x85) == '\0')))) {
    *(undefined1 *)(param_1 + 0x85) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1a8);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x8e) == '\0')) &&
     (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x1a8)), (float)fVar3 < 0.5)) {
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  if (((*(char *)(param_1 + 0x89) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xec) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xec))) &&
     ((*(char *)(param_1 + 0x85) == '\0' && (*(char *)(param_1 + 0x61) == '\0')))) {
    *(undefined1 *)(param_1 + 0x85) = 1;
  }
  if ((*(char *)(param_1 + 0x85) != '\0') && (*(char *)(param_1 + 0x81) == '\0')) {
    uVar2 = FUN_005c8250("bvraz",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x1f0) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 0x1f0),*(undefined4 *)(param_1 + 0x144),1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xdc) = (float)fVar3 + 20.0;
    *(undefined1 *)(param_1 + 0x81) = 1;
  }
  if ((((*(char *)(param_1 + 0x85) != '\0') && (*(char *)(param_1 + 0x81) != '\0')) &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xdc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xdc))) &&
     (*(char *)(param_1 + 0x82) == '\0')) {
    uVar2 = FUN_005c8250("bvraz",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 500) = uVar2;
    FUN_005cb820(*(undefined4 *)(param_1 + 500),*(undefined4 *)(param_1 + 0x144),1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xe0) = (float)fVar3 + 20.0;
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  if (((*(char *)(param_1 + 0x85) != '\0') && (*(char *)(param_1 + 0x82) != '\0')) &&
     ((fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xe0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xe0) &&
      (*(char *)(param_1 + 0x83) == '\0')))) {
    uVar2 = FUN_005c8250("bvraz",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x1f8) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 500);
    if (cVar1 == '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x1f8),*(undefined4 *)(param_1 + 0x144),1);
    }
    else {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x1f8),*(undefined4 *)(param_1 + 0x158),1);
    }
    FUN_005cadd0(2,0x28);
    *(undefined1 *)(param_1 + 0x83) = 1;
  }
  if (((*(char *)(param_1 + 0x85) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x1f8), cVar1 != '\0')
      ) && ((*(char *)(param_1 + 0x61) == '\0' && (*(char *)(param_1 + 0x8b) == '\0')))) {
    uVar2 = FUN_005c8250("bvturr",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x214) = uVar2;
    *(undefined1 *)(param_1 + 0x8b) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1a8);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x61) == '\0')) {
    FUN_005cd2a0();
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb8) = (float)fVar3 + 1.5;
    *(undefined1 *)(param_1 + 0x61) = 1;
  }
  if ((*(char *)(param_1 + 0x61) != '\0') && (*(char *)(param_1 + 0x5b) == '\0')) {
    FUN_005cd440(*(undefined4 *)(param_1 + 0x198),0xfffffa24,1000,0xffffec78,
                 *(undefined4 *)(param_1 + 0x1c4));
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xbc) = (float)fVar3 + 3.5;
    *(undefined1 *)(param_1 + 0x5b) = 1;
  }
  if (((*(char *)(param_1 + 0x61) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xb8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb8))) &&
     (*(char *)(param_1 + 0x5a) == '\0')) {
    uVar2 = FUN_005c8250("sssold",1,"con1_spot",0,0);
    *(undefined4 *)(param_1 + 0x1b8) = uVar2;
    uVar2 = FUN_005c8250("sssold",1,"con2_spot",0,0);
    *(undefined4 *)(param_1 + 0x1bc) = uVar2;
    uVar2 = FUN_005c8250("sssold",1,"con3_spot",0,0);
    *(undefined4 *)(param_1 + 0x1c0) = uVar2;
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1b8),0);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1bc),0);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x1c0),0);
    FUN_005cc180(*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x158),1);
    FUN_005cc180(*(undefined4 *)(param_1 + 0x1bc),*(undefined4 *)(param_1 + 0x158),1);
    FUN_005cc180(*(undefined4 *)(param_1 + 0x1c0),*(undefined4 *)(param_1 + 0x158),1);
    *(undefined1 *)(param_1 + 0x5a) = 1;
  }
  if (((*(char *)(param_1 + 0x5b) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xbc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xbc))) &&
     (*(char *)(param_1 + 0x5c) == '\0')) {
    FUN_005cd4e0();
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x134) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x5c) = 1;
  }
  if ((*(char *)(param_1 + 0x5c) != '\0') && (*(char *)(param_1 + 0x8c) == '\0')) {
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x158),*(undefined4 *)(param_1 + 0x1c4))
    ;
    if ((float)fVar3 <= 70.0) {
      *(undefined1 *)(param_1 + 0x8c) = 1;
    }
    else {
      FUN_00437d30("misns710.wav");
      *(undefined1 *)(param_1 + 0x8c) = 1;
    }
  }
  if (((((*(char *)(param_1 + 0x5c) != '\0') &&
        (cVar1 = FUN_005c84d0(param_1 + 0x158), cVar1 != '\0')) &&
       (fVar3 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0xdc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xdc))) &&
      ((*(char *)(param_1 + 0x65) == '\0' &&
       (fVar3 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x158)), (float)fVar3 < 0.8)))) &&
     (*(char *)(param_1 + 0xb1) == '\0')) {
    FUN_00437d30("misns723.wav");
    *(undefined1 *)(param_1 + 0xb1) = 1;
  }
  if (((*(char *)(param_1 + 0x5c) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x134) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x134)))
     && (*(char *)(param_1 + 0x86) == '\0')) {
    uVar2 = FUN_005c8250("bvmuf",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x16c) = uVar2;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x16c),1);
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x16c),*(undefined4 *)(param_1 + 0x198),1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd8) = (float)fVar3 + 30.0;
    *(undefined1 *)(param_1 + 0x86) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x200);
  if (cVar1 != '\0') {
    *(undefined1 *)(param_1 + 0x9b) = 1;
  }
  if (((*(char *)(param_1 + 0x86) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xd8) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xd8))) &&
     (*(char *)(param_1 + 0x81) == '\0')) {
    uVar2 = FUN_005c8250("bvraz",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x1f0) = uVar2;
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xdc) = (float)fVar3 + 30.0;
    *(undefined1 *)(param_1 + 0x81) = 1;
  }
  if (((*(char *)(param_1 + 0x86) != '\0') && (*(char *)(param_1 + 0x81) != '\0')) &&
     ((fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xdc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xdc) &&
      (*(char *)(param_1 + 0x82) == '\0')))) {
    uVar2 = FUN_005c8250("bvraz",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 500) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 0x1f0);
    if ((cVar1 != '\0') &&
       (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x158),
                                      *(undefined4 *)(param_1 + 0x1c4)), (float)fVar3 < 200.0)) {
      FUN_005cb820(*(undefined4 *)(param_1 + 500),*(undefined4 *)(param_1 + 0x158),1);
    }
    FUN_005cb2d0("misns7.aip",2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    FUN_005cada0(2,0x28);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x214);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8a) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0x214),"turret_spot",1);
    *(undefined1 *)(param_1 + 0x8a) = 1;
  }
  if (((*(char *)(param_1 + 0x86) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 == '\0')
      ) && (*(char *)(param_1 + 0x90) == '\0')) {
    FUN_005cada0(2,0x14);
    FUN_005cb2d0("misns7c.aip",2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    *(undefined1 *)(param_1 + 0x91) = 0;
    *(undefined1 *)(param_1 + 0x90) = 1;
  }
  if (((*(char *)(param_1 + 0x90) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x16c), cVar1 != '\0')
      ) && (*(char *)(param_1 + 0x91) == '\0')) {
    if (*(char *)(param_1 + 0x8f) == '\0') {
      FUN_005cb2d0("misns7.aip",2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    }
    else {
      FUN_005cb2d0("misns7a.aip",2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
      FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    }
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0x16c),*(undefined4 *)(param_1 + 0x198),1);
    *(undefined1 *)(param_1 + 0x90) = 0;
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x1b8), cVar1 == '\0')
      ) && (*(char *)(param_1 + 0x62) == '\0')) {
    *(undefined1 *)(param_1 + 0x78) = 1;
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x1bc), cVar1 == '\0')
      ) && (*(char *)(param_1 + 99) == '\0')) {
    *(undefined1 *)(param_1 + 0x79) = 1;
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x1c0), cVar1 == '\0')
      ) && (*(char *)(param_1 + 100) == '\0')) {
    *(undefined1 *)(param_1 + 0x7a) = 1;
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1b8),
                                     *(undefined4 *)(param_1 + 0x158)), (float)fVar3 < 20.0)) &&
     ((*(char *)(param_1 + 0x78) == '\0' && (*(char *)(param_1 + 0x62) == '\0')))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 200) = (float)fVar3 + 0.2;
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  if (((*(char *)(param_1 + 0x62) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 200) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 200))) &&
     (*(char *)(param_1 + 0x75) == '\0')) {
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1b8));
    FUN_005cac80(1,1);
    FUN_00437d30((&PTR_s_misns701_wav_008723e4)
                 [(uint)*(byte *)(param_1 + 0x75) + (uint)*(byte *)(param_1 + 0x76) +
                  (uint)*(byte *)(param_1 + 0x77)]);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x138) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if (((*(char *)(param_1 + 0x5a) != '\0') &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1bc),
                                     *(undefined4 *)(param_1 + 0x158)), (float)fVar3 < 20.0)) &&
     ((*(char *)(param_1 + 0x79) == '\0' && (*(char *)(param_1 + 99) == '\0')))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xcc) = (float)fVar3 + 0.2;
    *(undefined1 *)(param_1 + 99) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xcc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xcc))) &&
     (*(char *)(param_1 + 0x76) == '\0')) {
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1bc));
    FUN_005cac80(1,1);
    FUN_00437d30((&PTR_s_misns701_wav_008723e4)
                 [(uint)*(byte *)(param_1 + 0x75) + (uint)*(byte *)(param_1 + 0x76) +
                  (uint)*(byte *)(param_1 + 0x77)]);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x138) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x76) = 1;
  }
  if ((((*(char *)(param_1 + 0x5a) != '\0') &&
       (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x1c0),
                                      *(undefined4 *)(param_1 + 0x158)), (float)fVar3 < 20.0)) &&
      (*(char *)(param_1 + 0x7a) == '\0')) && (*(char *)(param_1 + 100) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xd0) = (float)fVar3 + 0.2;
    *(undefined1 *)(param_1 + 100) = 1;
  }
  if (((*(char *)(param_1 + 100) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xd0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xd0))) &&
     (*(char *)(param_1 + 0x77) == '\0')) {
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c0));
    FUN_005cac80(1,1);
    FUN_00437d30((&PTR_s_misns701_wav_008723e4)
                 [(uint)*(byte *)(param_1 + 0x75) + (uint)*(byte *)(param_1 + 0x76) +
                  (uint)*(byte *)(param_1 + 0x77)]);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x138) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x77) = 1;
  }
  if (((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x76) != '\0')) &&
     (((*(char *)(param_1 + 0x77) != '\0' &&
       (((*(char *)(param_1 + 0x65) == '\0' && (*(char *)(param_1 + 0x7b) == '\0')) &&
        (*(char *)(param_1 + 0x55) == '\0')))) &&
      ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x6f) == '\0')))))) {
    FUN_00437d30("misns704.wav");
    *(undefined1 *)(param_1 + 0x65) = 1;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf0) = (float)fVar3 + 3.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x124) = (float)fVar3 + 1.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x128) = (float)fVar3 + 2.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 300) = (float)fVar3 + 3.0;
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  if (((((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x76) != '\0')) &&
       ((*(char *)(param_1 + 0x7a) != '\0' && (*(char *)(param_1 + 0x66) == '\0')))) ||
      ((((*(char *)(param_1 + 0x75) != '\0' && (*(char *)(param_1 + 0x79) != '\0')) &&
        (*(char *)(param_1 + 0x77) != '\0')) && (*(char *)(param_1 + 0x66) == '\0')))) ||
     (((*(char *)(param_1 + 0x78) != '\0' && (*(char *)(param_1 + 0x76) != '\0')) &&
      (((*(char *)(param_1 + 0x77) != '\0' &&
        ((*(char *)(param_1 + 0x66) == '\0' && (*(char *)(param_1 + 0x7b) == '\0')))) &&
       ((*(char *)(param_1 + 0x55) == '\0' &&
        ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x6f) == '\0')))))))))) {
    FUN_00437d30("misns705.wav");
    *(undefined1 *)(param_1 + 0x66) = 1;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf0) = (float)fVar3 + 3.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x124) = (float)fVar3 + 1.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x128) = (float)fVar3 + 2.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 300) = (float)fVar3 + 3.0;
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  if ((((((*(char *)(param_1 + 0x75) != '\0') && (*(char *)(param_1 + 0x79) != '\0')) &&
        (*(char *)(param_1 + 0x7a) != '\0')) && (*(char *)(param_1 + 0x67) == '\0')) ||
      (((*(char *)(param_1 + 0x78) != '\0' && (*(char *)(param_1 + 0x76) != '\0')) &&
       ((*(char *)(param_1 + 0x7a) != '\0' && (*(char *)(param_1 + 0x67) == '\0')))))) ||
     ((((*(char *)(param_1 + 0x78) != '\0' && (*(char *)(param_1 + 0x79) != '\0')) &&
       ((*(char *)(param_1 + 0x77) != '\0' &&
        (((*(char *)(param_1 + 0x67) == '\0' && (*(char *)(param_1 + 0x7b) == '\0')) &&
         (*(char *)(param_1 + 0x55) == '\0')))))) &&
      ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x6f) == '\0')))))) {
    FUN_00437d30("misns706.wav");
    *(undefined1 *)(param_1 + 0x67) = 1;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf0) = (float)fVar3 + 3.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x124) = (float)fVar3 + 1.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x128) = (float)fVar3 + 2.0;
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 300) = (float)fVar3 + 3.0;
    *(undefined1 *)(param_1 + 0x7b) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x158);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x87) != '\0')) &&
     ((fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x138) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x138) &&
      (*(char *)(param_1 + 0x7b) == '\0')))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x138) = (float)fVar3 + 5.0;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x158),0x43480000,2,0);
    *(undefined4 *)(param_1 + 0x278) = uVar2;
    if (*(int *)(param_1 + 0x278) == 0) {
      cVar1 = FUN_005c84d0(param_1 + 0x1b8);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1b8));
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1bc);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1bc));
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1c0);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x1c0));
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x158);
  if ((((cVar1 != '\0') && (*(char *)(param_1 + 0x7b) != '\0')) &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xf0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf0))) &&
     (*(char *)(param_1 + 0x8d) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf0) = (float)fVar3 + 3.0;
    uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x158),0x43480000,2,0);
    *(undefined4 *)(param_1 + 0x280) = uVar2;
    if (*(int *)(param_1 + 0x280) == 0) {
      if (*(char *)(param_1 + 0x65) == '\0') {
        if (*(char *)(param_1 + 0x66) == '\0') {
          if (*(char *)(param_1 + 0x67) != '\0') {
            FUN_00437d30("misns725.wav");
            FUN_00437d30("misns708.wav");
            fVar3 = (float10)FUN_00822d80();
            *(float *)(param_1 + 0xf0) = (float)fVar3 + 30.0;
          }
        }
        else {
          FUN_00437d30("misns725.wav");
          FUN_00437d30("misns718.wav");
          fVar3 = (float10)FUN_00822d80();
          *(float *)(param_1 + 0xf0) = (float)fVar3 + 30.0;
        }
      }
      else {
        FUN_00437d30("misns724.wav");
        FUN_00437d30("misns717.wav");
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xf0) = (float)fVar3 + 30.0;
      }
      FUN_004f6aa0();
      FUN_004f6ab0("misns703.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misns701.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(param_1 + 0x8d) = 1;
    }
  }
  if (((*(char *)(param_1 + 0xb2) == '\0') && (*(char *)(param_1 + 0x8d) != '\0')) &&
     (fVar3 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xf0) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf0))) {
    FUN_004f6aa0();
    FUN_004f6ab0("misns703.otf",DAT_009175b0,0x41000000,0);
    FUN_004f6ab0("misns701.otf",DAT_0091755c,0x41000000,0);
    FUN_004f6ab0("misns702.otf",DAT_0091755c,0x41000000,0);
    *(undefined1 *)(param_1 + 0xb2) = 1;
  }
  if (((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x55) == '\0')) &&
     ((fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x124) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x124) &&
      (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x158),
                                     *(undefined4 *)(param_1 + 0x150)), (float)fVar3 < 50.0)))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x124) = (float)fVar3 + 3.0;
    if ((((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
        (*(char *)(param_1 + 0x55) == '\0')) && (*(char *)(param_1 + 0x7c) == '\0')) {
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cd2a0();
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
      *(undefined1 *)(param_1 + 0x7c) = 1;
    }
    if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
       ((*(char *)(param_1 + 0x55) == '\0' && (*(char *)(param_1 + 0x7d) == '\0')))) {
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cd2a0();
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
      *(undefined1 *)(param_1 + 0x7d) = 1;
    }
    if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
       (*(char *)(param_1 + 0x55) == '\0')) {
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cd2a0();
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
    if ((((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7c) != '\0')) &&
        (*(char *)(param_1 + 0x55) == '\0')) && (*(char *)(param_1 + 0x7d) == '\0')) {
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cd2a0();
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
      *(undefined1 *)(param_1 + 0x7d) = 1;
    }
    if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7d) != '\0')) &&
       (*(char *)(param_1 + 0x55) == '\0')) {
      *(undefined1 *)(param_1 + 0x55) = 1;
      FUN_005cd2a0();
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x55) != '\0') && (*(char *)(param_1 + 0x57) == '\0')) {
    FUN_005cd440(*(undefined4 *)(param_1 + 0x150),0xfffff060,1000,2000,
                 *(undefined4 *)(param_1 + 0x150));
    *(undefined1 *)(param_1 + 0x56) = 1;
  }
  if (((*(char *)(param_1 + 0x56) != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xb4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb4))) &&
     (*(char *)(param_1 + 0x58) == '\0')) {
    uVar2 = FUN_005c8080("sssold",1,*(undefined4 *)(param_1 + 0x158),0);
    *(undefined4 *)(param_1 + 0x254) = uVar2;
    FUN_005cc140(*(undefined4 *)(param_1 + 0x254),*(undefined4 *)(param_1 + 0x150),1);
    FUN_005cac80(1,0xffffffff);
    *(undefined1 *)(param_1 + 0x58) = 1;
  }
  if (((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x59) == '\0')) &&
     (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x254),
                                    *(undefined4 *)(param_1 + 0x150)), (float)fVar3 < 25.0)) {
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
    *(undefined1 *)(param_1 + 0x59) = 1;
  }
  if (((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x57) == '\0')) &&
     ((*(char *)(param_1 + 0x59) != '\0' || (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
    FUN_005cd4e0();
    cVar1 = FUN_005c84d0(param_1 + 0x254);
    if (cVar1 != '\0') {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
    }
    uVar2 = FUN_005c8080("svmine",0,*(undefined4 *)(param_1 + 0x150),0);
    *(undefined4 *)(param_1 + 0x148) = uVar2;
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x148),1);
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x150));
    uVar2 = FUN_005c8080("svrecy",1,*(undefined4 *)(param_1 + 0x148),0);
    *(undefined4 *)(param_1 + 0x150) = uVar2;
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x148));
    if ((*(char *)(param_1 + 0x6e) == '\0') && (*(char *)(param_1 + 0x73) == '\0')) {
      FUN_004f6aa0();
      FUN_004f6ab0("misns708.otf",DAT_0091755c,0x41000000,0);
    }
    else if ((*(char *)(param_1 + 0x6e) == '\0') || (*(char *)(param_1 + 0x73) != '\0')) {
      if ((*(char *)(param_1 + 0x6e) != '\0') && (*(char *)(param_1 + 0x73) != '\0')) {
        FUN_004f6aa0();
        FUN_004f6ab0("misns708.otf",DAT_0091755c,0x41000000,0);
        FUN_004f6ab0("misns704.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns706.otf",DAT_009175b0,0x41000000,0);
      }
    }
    else {
      FUN_004f6aa0();
      FUN_004f6ab0("misns708.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misns704.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misns705.otf",DAT_0091755c,0x41000000,0);
    }
    FUN_00437d30("misns727.wav");
    FUN_005cada0(1,0x14);
    FUN_005cb2d0("misns7a.aip",2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  if (*(char *)(param_1 + 0xab) == '\0') {
    if ((((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x6a) == '\0')) &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0x128) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x128)))
       && (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x158),
                                         *(undefined4 *)(param_1 + 0x154)), (float)fVar3 < 40.0)) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x128) = (float)fVar3 + 3.0;
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
         ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x7c) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6a) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
         ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x7d) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6a) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
         (*(char *)(param_1 + 0x6a) == '\0')) {
        *(undefined1 *)(param_1 + 0x6a) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x68) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7c) != '\0')) &&
         ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x7d) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6a) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7d) != '\0')) &&
         (*(char *)(param_1 + 0x6a) == '\0')) {
        *(undefined1 *)(param_1 + 0x6a) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x68) = 1;
      }
    }
    if ((*(char *)(param_1 + 0x6a) != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x154),0xfffff448,1000,4000,
                   *(undefined4 *)(param_1 + 0x154));
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
    if (((*(char *)(param_1 + 0x6b) != '\0') &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0xb4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb4)))
       && (*(char *)(param_1 + 0x6c) == '\0')) {
      uVar2 = FUN_005c8080("sssold",1,*(undefined4 *)(param_1 + 0x158),0);
      *(undefined4 *)(param_1 + 0x254) = uVar2;
      FUN_005cc140(*(undefined4 *)(param_1 + 0x254),*(undefined4 *)(param_1 + 0x154),1);
      FUN_005cac80(1,0xffffffff);
      *(undefined1 *)(param_1 + 0x6c) = 1;
    }
    if (((*(char *)(param_1 + 0x6c) != '\0') && (*(char *)(param_1 + 0x6d) == '\0')) &&
       (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x254),
                                      *(undefined4 *)(param_1 + 0x154)), (float)fVar3 < 20.0)) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
      *(undefined1 *)(param_1 + 0x6d) = 1;
    }
    if (((*(char *)(param_1 + 0x6c) != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) &&
       ((*(char *)(param_1 + 0x6d) != '\0' || (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
      cVar1 = FUN_005c84d0(param_1 + 0x254);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
      }
      uVar2 = FUN_005c8080("svmine",0,*(undefined4 *)(param_1 + 0x154),0);
      *(undefined4 *)(param_1 + 0x148) = uVar2;
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x148),1);
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x154));
      uVar2 = FUN_005c8080("svmuf",1,*(undefined4 *)(param_1 + 0x148),0);
      *(undefined4 *)(param_1 + 0x154) = uVar2;
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x148));
      FUN_005cada0(1,0x14);
      FUN_005cd4e0();
      *(undefined1 *)(param_1 + 0x6e) = 1;
    }
    if ((*(char *)(param_1 + 0x6e) != '\0') && (*(char *)(param_1 + 0x74) == '\0')) {
      if (*(char *)(param_1 + 0x88) != '\0') {
        FUN_00437d30("misns709.wav");
      }
      if (*(char *)(param_1 + 0x88) == '\0') {
        FUN_00437d30("misns714.wav");
      }
      if (*(char *)(param_1 + 0x57) == '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misns703.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns701.otf",DAT_0091755c,0x41000000,0);
        FUN_004f6ab0("misns704.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns705.otf",DAT_0091755c,0x41000000,0);
      }
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
  }
  if (*(char *)(param_1 + 0x6e) != '\0') {
    if ((((*(char *)(param_1 + 0x7b) != '\0') && (*(char *)(param_1 + 0x6f) == '\0')) &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 300) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 300))) &&
       (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x158),
                                      *(undefined4 *)(param_1 + 0x1ac)), (float)fVar3 < 70.0)) {
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 300) = (float)fVar3 + 3.0;
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
         ((*(char *)(param_1 + 0x6f) == '\0' && (*(char *)(param_1 + 0x7c) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6f) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
         ((*(char *)(param_1 + 0x6f) == '\0' && (*(char *)(param_1 + 0x7d) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6f) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
         (*(char *)(param_1 + 0x6f) == '\0')) {
        *(undefined1 *)(param_1 + 0x6f) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x68) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7c) != '\0')) &&
         ((*(char *)(param_1 + 0x6f) == '\0' && (*(char *)(param_1 + 0x7d) == '\0')))) {
        *(undefined1 *)(param_1 + 0x6f) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x7d) = 1;
      }
      if (((*(char *)(param_1 + 0x68) == '\0') && (*(char *)(param_1 + 0x7d) != '\0')) &&
         (*(char *)(param_1 + 0x6f) == '\0')) {
        *(undefined1 *)(param_1 + 0x6f) = 1;
        FUN_005cd2a0();
        FUN_005cbd40(*(undefined4 *)(param_1 + 0x158),0);
        fVar3 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0xb4) = (float)fVar3 + 2.0;
        *(undefined1 *)(param_1 + 0x68) = 1;
      }
    }
    if ((*(char *)(param_1 + 0x6f) != '\0') && (*(char *)(param_1 + 0x73) == '\0')) {
      FUN_005cd440(*(undefined4 *)(param_1 + 0x1ac),1000,1000,8000,*(undefined4 *)(param_1 + 0x1ac))
      ;
      *(undefined1 *)(param_1 + 0x70) = 1;
    }
    if (((*(char *)(param_1 + 0x70) != '\0') &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0xb4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xb4)))
       && (*(char *)(param_1 + 0x71) == '\0')) {
      uVar2 = FUN_005c8080("sssold",1,*(undefined4 *)(param_1 + 0x158),0);
      *(undefined4 *)(param_1 + 0x254) = uVar2;
      FUN_005cc100(*(undefined4 *)(param_1 + 0x254),"con_path",1);
      FUN_005cac80(1,0xffffffff);
      *(undefined1 *)(param_1 + 0x71) = 1;
    }
    if (((*(char *)(param_1 + 0x71) != '\0') &&
        (cVar1 = FUN_005c84d0(param_1 + 0x254), cVar1 != '\0')) &&
       ((*(char *)(param_1 + 0x72) == '\0' &&
        (fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x254),
                                       *(undefined4 *)(param_1 + 600)), (float)fVar3 < 30.0)))) {
      FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
      *(undefined1 *)(param_1 + 0x72) = 1;
    }
    if (((*(char *)(param_1 + 0x71) != '\0') && (*(char *)(param_1 + 0x73) == '\0')) &&
       ((*(char *)(param_1 + 0x72) != '\0' || (cVar1 = FUN_005cd560(), cVar1 != '\0')))) {
      cVar1 = FUN_005c84d0(param_1 + 0x254);
      if (cVar1 != '\0') {
        FUN_005c83e0(*(undefined4 *)(param_1 + 0x254));
      }
      if (*(char *)(param_1 + 0x57) == '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misns703.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns701.otf",DAT_0091755c,0x41000000,0);
        FUN_004f6ab0("misns704.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns706.otf",DAT_009175b0,0x41000000,0);
      }
      else {
        FUN_004f6aa0();
        FUN_004f6ab0("misns708.otf",DAT_0091755c,0x41000000,0);
        FUN_004f6ab0("misns704.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misns706.otf",DAT_009175b0,0x41000000,0);
      }
      *(undefined1 *)(param_1 + 0x73) = 1;
      FUN_005cd4e0();
    }
    if ((*(char *)(param_1 + 0x73) != '\0') && (*(char *)(param_1 + 0xaf) == '\0')) {
      FUN_00437d30("misns707.wav");
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xc4) = (float)fVar3 + 15.0;
      *(undefined1 *)(param_1 + 0xaf) = 1;
    }
    if (((*(char *)(param_1 + 0xaf) != '\0') &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0xc4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xc4)))
       && (*(char *)(param_1 + 0x7f) == '\0')) {
      uVar2 = FUN_005c8250("svscav",1,"supply1",0,0);
      *(undefined4 *)(param_1 + 0x1cc) = uVar2;
      uVar2 = FUN_005c8250("svturr",1,"supply2",0,0);
      *(undefined4 *)(param_1 + 0x1d0) = uVar2;
      uVar2 = FUN_005c8250("svturr",1,"supply3",0,0);
      *(undefined4 *)(param_1 + 0x1d4) = uVar2;
      uVar2 = FUN_005c8250("svscav",1,"supply4",0,0);
      *(undefined4 *)(param_1 + 0x1d8) = uVar2;
      uVar2 = FUN_005c8250("spammo",1,"supply5",0,0);
      *(undefined4 *)(param_1 + 0x1dc) = uVar2;
      uVar2 = FUN_005c8250("spammo",1,"supply6",0,0);
      *(undefined4 *)(param_1 + 0x1e0) = uVar2;
      uVar2 = FUN_005c8250("spammo",1,"supply7",0,0);
      *(undefined4 *)(param_1 + 0x1e4) = uVar2;
      uVar2 = FUN_005c8250("sprepa",1,"supply8",0,0);
      *(undefined4 *)(param_1 + 0x1e8) = uVar2;
      uVar2 = FUN_005c8250("sprepa",1,"supply9",0,0);
      *(undefined4 *)(param_1 + 0x1ec) = uVar2;
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x1cc),0);
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x1d8),0);
      *(undefined1 *)(param_1 + 0x7f) = 1;
    }
    if ((*(char *)(param_1 + 0x7f) != '\0') && (*(char *)(param_1 + 0xae) == '\0')) {
      FUN_00437d30("misns721.wav");
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x1cc),0);
      FUN_005cbd40(*(undefined4 *)(param_1 + 0x1d8),0);
      *(undefined1 *)(param_1 + 0xae) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x1ac);
  if (((cVar1 != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) &&
     ((fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),
                                     *(undefined4 *)(param_1 + 0x1ac)), (float)fVar3 < 70.0 &&
      (*(char *)(param_1 + 0x88) == '\0')))) {
    FUN_00437d30("misns715.wav");
    *(undefined1 *)(param_1 + 0x88) = 1;
  }
  if (((*(char *)(param_1 + 0x88) != '\0') || (*(char *)(param_1 + 0x6e) != '\0')) &&
     (*(char *)(param_1 + 0x8f) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x178);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x170);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x170),*(undefined4 *)(param_1 + 0x178),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x174);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x178),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x214);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x214),"avsilo_spot1",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x218);
      if (cVar1 != '\0') {
        FUN_005cb960(*(undefined4 *)(param_1 + 0x218),"avsilo_spot2",1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x1f0);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x1f0),*(undefined4 *)(param_1 + 0x178),0);
      }
      cVar1 = FUN_005c84d0(param_1 + 500);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 500),*(undefined4 *)(param_1 + 0x178),0);
      }
    }
    FUN_005cb2d0("misns7b.aip",2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x160),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x164),2);
    FUN_005c88b0(*(undefined4 *)(param_1 + 0x150),2);
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if (cVar1 != '\0') {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x224),1);
    }
    *(undefined1 *)(param_1 + 0x8f) = 1;
  }
  fVar3 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 0xf4) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xf4)) &&
     (*(char *)(param_1 + 0x95) == '\0')) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xf4) = (float)fVar3 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0x154);
    if (cVar1 != '\0') {
      uVar2 = FUN_005ca520(*(undefined4 *)(param_1 + 0x154),0x43480000,2,0);
      *(undefined4 *)(param_1 + 0x27c) = uVar2;
      if (0 < *(int *)(param_1 + 0x27c)) {
        *(undefined1 *)(param_1 + 0x95) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x210);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x94) == '\0')) {
    if (*(char *)(param_1 + 0x95) == '\0') {
      cVar1 = FUN_005c84d0(param_1 + 0x178);
      if (cVar1 != '\0') {
        FUN_005cb9d0(*(undefined4 *)(param_1 + 0x210),*(undefined4 *)(param_1 + 0x178),0);
      }
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0x154);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x210),*(undefined4 *)(param_1 + 0x154),1);
      }
    }
    *(undefined1 *)(param_1 + 0x94) = 1;
  }
  if ((((*(char *)(param_1 + 0x94) != '\0') && (*(char *)(param_1 + 0x95) != '\0')) &&
      (*(char *)(param_1 + 0x96) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x210), cVar1 != '\0' &&
      (cVar1 = FUN_005c84d0(param_1 + 0x154), cVar1 != '\0')))) {
    FUN_005cb820(*(undefined4 *)(param_1 + 0x210),*(undefined4 *)(param_1 + 0x154),1);
    *(undefined1 *)(param_1 + 0x96) = 1;
  }
  if (((*(char *)(param_1 + 0x8e) != '\0') && (*(char *)(param_1 + 0x98) == '\0')) &&
     (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) {
    FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"tower1_spot",1);
    *(undefined1 *)(param_1 + 0x98) = 1;
  }
  if ((((*(char *)(param_1 + 0x98) != '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x180), cVar1 != '\0')) && (*(int *)(param_1 + 0x228) == 0))
     && (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) {
    FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abwpow",1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x108) = (float)fVar3 + 5.0;
    *(undefined4 *)(param_1 + 0x228) = 1;
  }
  if (((*(int *)(param_1 + 0x228) != 0) &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x108) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x108)))
     && ((*(char *)(param_1 + 0x99) == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')))) {
    FUN_005cada0(2,0x14);
    FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"power1_spot",1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x10c) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x99) = 1;
  }
  if (((*(char *)(param_1 + 0x99) != '\0') && (*(char *)(param_1 + 0xa3) == '\0')) &&
     (((*(char *)(param_1 + 0xa8) == '\0' &&
       (((cVar1 = FUN_005c84d0(param_1 + 0x1b0), cVar1 != '\0' && (*(int *)(param_1 + 0x22c) == 0))
        && (fVar3 = (float10)FUN_00822d80(),
           *(float *)(param_1 + 0x10c) <= (float)fVar3 &&
           (float)fVar3 != *(float *)(param_1 + 0x10c))))) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')))) {
    FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abtowe",1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x110) = (float)fVar3 + 5.0;
    *(undefined4 *)(param_1 + 0x22c) = 1;
  }
  if (((*(int *)(param_1 + 0x22c) != 0) &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x110) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x110)))
     && ((*(char *)(param_1 + 0x9a) == '\0' &&
         (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')))) {
    FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"tower2_spot",1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x114) = (float)fVar3 + 5.0;
    *(undefined1 *)(param_1 + 0x9a) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x184);
  if (((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) &&
     ((*(char *)(param_1 + 0x9d) == '\0' &&
      ((fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),
                                      *(undefined4 *)(param_1 + 0x224)), 400.0 < (float)fVar3 &&
       (fVar3 = (float10)FUN_00822d80(),
       *(float *)(param_1 + 0x114) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x114))))
      ))) {
    FUN_005c83e0(*(undefined4 *)(param_1 + 0x224));
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xfc) = (float)fVar3 + 10.0;
    *(undefined1 *)(param_1 + 0x9d) = 1;
  }
  if (*(char *)(param_1 + 0x9e) != '\0') {
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if (((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x194), cVar1 == '\0')) &&
       (*(char *)(param_1 + 0xa3) == '\0')) {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abwpow",1);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x104) = (float)fVar3 + 10.0;
      *(undefined1 *)(param_1 + 0xa3) = 1;
    }
    if (((*(char *)(param_1 + 0xa3) != '\0') &&
        (fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0x104) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x104)))
       && ((*(char *)(param_1 + 0xa5) == '\0' &&
           (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')))) {
      FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"main_power",1);
      *(undefined1 *)(param_1 + 0xa5) = 1;
    }
    if ((*(char *)(param_1 + 0xa5) != '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x194), cVar1 != '\0')) {
      *(undefined1 *)(param_1 + 0xa5) = 0;
      *(undefined1 *)(param_1 + 0xa3) = 0;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if ((((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 400), cVar1 == '\0')) &&
        (*(char *)(param_1 + 0xa3) == '\0')) && (*(char *)(param_1 + 0xa8) == '\0')) {
      FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abtowe",1);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x104) = (float)fVar3 + 10.0;
      *(undefined1 *)(param_1 + 0xa8) = 1;
    }
    if (((*(char *)(param_1 + 0xa8) != '\0') && (*(char *)(param_1 + 0xaa) == '\0')) &&
       ((fVar3 = (float10)FUN_00822d80(),
        *(float *)(param_1 + 0x104) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x104)
        && (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')))) {
      FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"main_tower",1);
      *(undefined1 *)(param_1 + 0xaa) = 1;
    }
    if ((*(char *)(param_1 + 0xaa) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 400), cVar1 != '\0'))
    {
      *(undefined1 *)(param_1 + 0xaa) = 0;
      *(undefined1 *)(param_1 + 0xa8) = 0;
    }
  }
  if ((*(char *)(param_1 + 0x9e) == '\0') &&
     (fVar3 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xfc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xfc))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xfc) = (float)fVar3 + 5.0;
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x168))
    ;
    if ((float)fVar3 < 400.0) {
      uVar2 = FUN_005c8250("avcns7",2,"barrack_spot",0,0);
      *(undefined4 *)(param_1 + 0x224) = uVar2;
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x224),1);
      FUN_005cc660(*(undefined4 *)(param_1 + 0x224),"abbarr",1);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0xfc) = (float)fVar3 + 20.0;
      *(undefined1 *)(param_1 + 0x9e) = 1;
    }
  }
  if ((((*(char *)(param_1 + 0x9e) != '\0') &&
       (cVar1 = FUN_005c84d0(param_1 + 0x224), cVar1 != '\0')) &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0xfc) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0xfc))) &&
     (*(char *)(param_1 + 0xb0) == '\0')) {
    FUN_005cc5f0(*(undefined4 *)(param_1 + 0x224),"barrack_spot",1);
    uVar2 = FUN_005c8250("bvturr",2,"muf_point",0,0);
    *(undefined4 *)(param_1 + 0x220) = uVar2;
    FUN_005cb960(*(undefined4 *)(param_1 + 0x220),"base_turret_spot1",1);
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x100) = (float)fVar3 + 60.0;
    *(undefined1 *)(param_1 + 0xb0) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x220);
  if (((cVar1 != '\0') &&
      (fVar3 = (float10)FUN_00822d80(),
      *(float *)(param_1 + 0x100) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x100)))
     && (*(char *)(param_1 + 0xa7) == '\0')) {
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x220),1);
    cVar1 = FUN_005c84d0(param_1 + 0x224);
    if (cVar1 != '\0') {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0x224),1);
    }
    *(undefined1 *)(param_1 + 0xa7) = 1;
  }
  if (((*(char *)(param_1 + 0x57) != '\0') && (*(char *)(param_1 + 0x6e) == '\0')) &&
     ((cVar1 = FUN_005c84d0(param_1 + 0x250), cVar1 != '\0' && (*(char *)(param_1 + 0xab) == '\0')))
     ) {
    *(undefined1 *)(param_1 + 0xab) = 1;
  }
  if (((*(char *)(param_1 + 0xac) == '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x15c), cVar1 != '\0')
      ) && (fVar3 = (float10)FUN_00822d80(),
           *(float *)(param_1 + 0x130) <= (float)fVar3 &&
           (float)fVar3 != *(float *)(param_1 + 0x130))) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x130) = (float)fVar3 + 5.0;
    fVar3 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x15c))
    ;
    if ((float)fVar3 < 90.0) {
      FUN_00437d30("misns720.wav");
      *(undefined1 *)(param_1 + 0xac) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x168);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x7e) == '\0')) {
    FUN_00437d30("misns712.wav");
    fVar3 = (float10)FUN_00822d80("misns7w1.des");
    FUN_0045c110((float)fVar3 + 10.0);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  if ((((((*(char *)(param_1 + 0x78) != '\0') && (*(char *)(param_1 + 0x79) != '\0')) &&
        ((*(char *)(param_1 + 0x7a) != '\0' && (*(char *)(param_1 + 0x65) == '\0')))) ||
       ((((*(char *)(param_1 + 0x78) != '\0' && (*(char *)(param_1 + 0x79) != '\0')) &&
         (*(char *)(param_1 + 0x7a) != '\0')) && (*(char *)(param_1 + 0x66) == '\0')))) ||
      (((*(char *)(param_1 + 0x78) != '\0' && (*(char *)(param_1 + 0x79) != '\0')) &&
       ((*(char *)(param_1 + 0x7a) != '\0' && (*(char *)(param_1 + 0x67) == '\0')))))) &&
     (*(char *)(param_1 + 0x7e) == '\0')) {
    FUN_00437d30("misns711.wav");
    fVar3 = (float10)FUN_00822d80("misns7f1.des");
    FUN_0045c0f0((float)fVar3 + 10.0);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x158);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 0x57) == '\0')) &&
     ((*(char *)(param_1 + 0x6e) == '\0' && (*(char *)(param_1 + 0x7e) == '\0')))) {
    FUN_00437d30("misns716.wav");
    fVar3 = (float10)FUN_00822d80("misns7f2.des");
    FUN_0045c0f0((float)fVar3 + 10.0);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  return;
}

