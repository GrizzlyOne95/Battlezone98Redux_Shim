
void __fastcall FUN_00535270(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  if ((*(char *)(param_1 + 0x62) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xdc), cVar1 != '\0'))
  {
    uVar2 = FUN_005cd240(*(undefined4 *)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xd8) = uVar2;
    cVar1 = FUN_005c84d0(param_1 + 0xd8);
    if (cVar1 != '\0') {
      iVar3 = FUN_005c8800(*(undefined4 *)(param_1 + 0xd8));
      if (iVar3 == 1) {
        *(undefined1 *)(param_1 + 0x62) = 0;
        *(undefined1 *)(param_1 + 99) = 1;
      }
      else {
        *(undefined1 *)(param_1 + 0x62) = 0;
        *(undefined1 *)(param_1 + 0x61) = 1;
        *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0xd4);
      }
    }
  }
  if (((*(char *)(param_1 + 99) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xd8), cVar1 == '\0'))
     && (*(char *)(param_1 + 0x61) == '\0')) {
    *(undefined1 *)(param_1 + 0x62) = 1;
    *(undefined1 *)(param_1 + 0x92) = 0;
    *(undefined1 *)(param_1 + 0x87) = 0;
    *(undefined1 *)(param_1 + 99) = 0;
    *(undefined1 *)(param_1 + 0x88) = 0;
    *(undefined1 *)(param_1 + 0x89) = 0;
  }
  if ((*(char *)(param_1 + 0x61) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xd4), cVar1 == '\0'))
  {
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if ((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xdc), cVar1 != '\0')) {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xdc),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x11c);
    if ((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0xdc), cVar1 != '\0')) {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xdc),1);
    }
    *(undefined1 *)(param_1 + 0x61) = 0;
    *(undefined1 *)(param_1 + 0x87) = 0;
    *(undefined1 *)(param_1 + 0x62) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd4);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 100) = 0;
    *(undefined1 *)(param_1 + 0x65) = 0;
    *(undefined1 *)(param_1 + 0x66) = 0;
    *(undefined1 *)(param_1 + 0x67) = 0;
    *(undefined1 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x69) = 0;
    *(undefined1 *)(param_1 + 0x6a) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x73) = 0;
    *(undefined1 *)(param_1 + 0x6b) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined1 *)(param_1 + 0x6d) = 0;
    *(undefined1 *)(param_1 + 0x6e) = 0;
    *(undefined1 *)(param_1 + 0x6f) = 0;
    *(undefined1 *)(param_1 + 0x70) = 0;
    *(undefined1 *)(param_1 + 0x71) = 0;
    *(undefined1 *)(param_1 + 0x72) = 0;
    *(undefined1 *)(param_1 + 0x76) = 0;
    *(undefined1 *)(param_1 + 0x87) = 0;
    *(undefined1 *)(param_1 + 0x93) = 0;
  }
  if ((*(char *)(param_1 + 0x61) != '\0') && (*(char *)(param_1 + 0x93) == '\0')) {
    FUN_00437d30("misn1005.wav");
    *(undefined1 *)(param_1 + 0x93) = 1;
  }
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(param_1 + 0xd0) = uVar2;
  cVar1 = FUN_005c84d0(param_1 + 0xf8);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x7c) = 0;
    *(undefined1 *)(param_1 + 0x7f) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xfc);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x7d) = 0;
    *(undefined1 *)(param_1 + 0x80) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xec);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x81) = 0;
    *(undefined1 *)(param_1 + 0x84) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(undefined1 *)(param_1 + 0x85) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf4);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x83) = 0;
    *(undefined1 *)(param_1 + 0x86) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x110);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x88) = 0;
    *(undefined1 *)(param_1 + 0x92) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x114);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x89) = 0;
    *(undefined1 *)(param_1 + 0x92) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x118);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x8a) = 0;
    *(undefined1 *)(param_1 + 0x8c) = 0;
    *(undefined1 *)(param_1 + 0x92) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x11c);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x8b) = 0;
    *(undefined1 *)(param_1 + 0x8d) = 0;
    *(undefined1 *)(param_1 + 0x92) = 0;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd4);
  if (((cVar1 == '\0') || (*(char *)(param_1 + 0x62) == '\0')) ||
     (*(char *)(param_1 + 0x87) != '\0')) goto LAB_005369c6;
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
  fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
  if ((float)fVar5 <= (float)fVar4) {
LAB_005359b6:
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    if ((float)fVar4 < (float)fVar5) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x130)
                                   );
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300)
                                     );
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x134));
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 300));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x138));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 300));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x13c));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 300));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x140));
              if ((float)fVar4 < (float)fVar5) {
                *(undefined1 *)(param_1 + 0x5a) = 0;
                *(undefined1 *)(param_1 + 0x5b) = 1;
                *(undefined1 *)(param_1 + 0x5c) = 0;
                *(undefined1 *)(param_1 + 0x5d) = 0;
                *(undefined1 *)(param_1 + 0x5e) = 0;
                *(undefined1 *)(param_1 + 0x5f) = 0;
                *(undefined1 *)(param_1 + 0x60) = 0;
                goto LAB_005369bc;
              }
            }
          }
        }
      }
    }
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x130));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    if ((float)fVar4 < (float)fVar5) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x130)
                                   );
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x130));
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x134));
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x130));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x138));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x130));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x13c));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x130));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x140));
              if ((float)fVar4 < (float)fVar5) {
                *(undefined1 *)(param_1 + 0x5a) = 0;
                *(undefined1 *)(param_1 + 0x5b) = 0;
                *(undefined1 *)(param_1 + 0x5c) = 1;
                *(undefined1 *)(param_1 + 0x5d) = 0;
                *(undefined1 *)(param_1 + 0x5e) = 0;
                *(undefined1 *)(param_1 + 0x5f) = 0;
                *(undefined1 *)(param_1 + 0x60) = 0;
                goto LAB_005369bc;
              }
            }
          }
        }
      }
    }
    if (*(char *)(param_1 + 0x61) == '\0') {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x134)
                                   );
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128)
                                   );
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x134));
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300)
                                     );
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x134));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x130));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x134));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x138));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x134));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x13c));
              if ((float)fVar4 < (float)fVar5) {
                fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                              *(undefined4 *)(param_1 + 0x134));
                fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                              *(undefined4 *)(param_1 + 0x140));
                if ((float)fVar4 < (float)fVar5) {
                  *(undefined1 *)(param_1 + 0x5a) = 0;
                  *(undefined1 *)(param_1 + 0x5b) = 0;
                  *(undefined1 *)(param_1 + 0x5c) = 0;
                  *(undefined1 *)(param_1 + 0x5d) = 1;
                  *(undefined1 *)(param_1 + 0x5e) = 0;
                  *(undefined1 *)(param_1 + 0x5f) = 0;
                  *(undefined1 *)(param_1 + 0x60) = 0;
                  goto LAB_005369bc;
                }
              }
            }
          }
        }
      }
    }
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x138));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    if ((float)fVar4 < (float)fVar5) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x138)
                                   );
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x138));
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x130));
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x138));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x134));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x138));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x13c));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x138));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x140));
              if ((float)fVar4 < (float)fVar5) {
                *(undefined1 *)(param_1 + 0x5a) = 0;
                *(undefined1 *)(param_1 + 0x5b) = 0;
                *(undefined1 *)(param_1 + 0x5c) = 0;
                *(undefined1 *)(param_1 + 0x5d) = 0;
                *(undefined1 *)(param_1 + 0x5e) = 1;
                *(undefined1 *)(param_1 + 0x5f) = 0;
                *(undefined1 *)(param_1 + 0x60) = 0;
                goto LAB_005369bc;
              }
            }
          }
        }
      }
    }
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x13c));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    if ((float)fVar4 < (float)fVar5) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x13c)
                                   );
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x13c));
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x130));
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x13c));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x134));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x13c));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x138));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x13c));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x140));
              if ((float)fVar4 < (float)fVar5) {
                *(undefined1 *)(param_1 + 0x5a) = 0;
                *(undefined1 *)(param_1 + 0x5b) = 0;
                *(undefined1 *)(param_1 + 0x5c) = 0;
                *(undefined1 *)(param_1 + 0x5d) = 0;
                *(undefined1 *)(param_1 + 0x5e) = 0;
                *(undefined1 *)(param_1 + 0x5f) = 1;
                *(undefined1 *)(param_1 + 0x60) = 0;
                goto LAB_005369bc;
              }
            }
          }
        }
      }
    }
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x140));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    if ((float)fVar4 < (float)fVar5) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x140)
                                   );
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 300));
      if ((float)fVar4 < (float)fVar5) {
        fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x140));
        fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                      *(undefined4 *)(param_1 + 0x130));
        if ((float)fVar4 < (float)fVar5) {
          fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x140));
          fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                        *(undefined4 *)(param_1 + 0x134));
          if ((float)fVar4 < (float)fVar5) {
            fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x140));
            fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                          *(undefined4 *)(param_1 + 0x138));
            if ((float)fVar4 < (float)fVar5) {
              fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x140));
              fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                            *(undefined4 *)(param_1 + 0x13c));
              if ((float)fVar4 < (float)fVar5) {
                *(undefined1 *)(param_1 + 0x5a) = 0;
                *(undefined1 *)(param_1 + 0x5b) = 0;
                *(undefined1 *)(param_1 + 0x5c) = 0;
                *(undefined1 *)(param_1 + 0x5d) = 0;
                *(undefined1 *)(param_1 + 0x5e) = 0;
                *(undefined1 *)(param_1 + 0x5f) = 0;
                *(undefined1 *)(param_1 + 0x60) = 1;
              }
            }
          }
        }
      }
    }
  }
  else {
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x130));
    if ((float)fVar5 <= (float)fVar4) goto LAB_005359b6;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x134));
    if ((float)fVar5 <= (float)fVar4) goto LAB_005359b6;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x138));
    if ((float)fVar5 <= (float)fVar4) goto LAB_005359b6;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x13c));
    if ((float)fVar5 <= (float)fVar4) goto LAB_005359b6;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x128));
    fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x140));
    if ((float)fVar5 <= (float)fVar4) goto LAB_005359b6;
    *(undefined1 *)(param_1 + 0x5a) = 1;
    *(undefined1 *)(param_1 + 0x5b) = 0;
    *(undefined1 *)(param_1 + 0x5c) = 0;
    *(undefined1 *)(param_1 + 0x5d) = 0;
    *(undefined1 *)(param_1 + 0x5e) = 0;
    *(undefined1 *)(param_1 + 0x5f) = 0;
    *(undefined1 *)(param_1 + 0x60) = 0;
  }
LAB_005369bc:
  *(undefined1 *)(param_1 + 0x87) = 1;
LAB_005369c6:
  if (*(char *)(param_1 + 0x54) == '\0') {
    FUN_00437d30("misn1000.wav");
    FUN_004f6aa0();
    FUN_004f6ab0("misn1000.otf",DAT_0091755c,0x41000000,0);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x144),1);
    FUN_005cb620(*(undefined4 *)(param_1 + 0x148),1);
    FUN_005cadd0(1,0x1e);
    FUN_005cacb0(1,10);
    FUN_005cadd0(2,0x28);
    FUN_005cacb0(2,0x28);
    FUN_005cb2d0("misn10.aip",2);
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xbc) = (float)fVar4 + 19.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xc0) = (float)fVar4 + 20.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 21.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb4) = (float)fVar4 + 22.0;
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb8) = (float)fVar4 + 23.0;
    FUN_005c9640(*(undefined4 *)(param_1 + 0xe0),"Relic Site");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xe4),"CCA Base");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xe8),"Drop Zone");
    FUN_005c9640(*(undefined4 *)(param_1 + 0xdc),"Alien Relic");
    *(undefined1 *)(param_1 + 0x77) = 1;
    *(undefined1 *)(param_1 + 0x54) = 1;
  }
  fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0xdc));
  if (((float)fVar4 < 100.0) && (*(char *)(param_1 + 0x75) == '\0')) {
    FUN_005c95e0(*(undefined4 *)(param_1 + 0xdc));
    *(undefined1 *)(param_1 + 0x75) = 1;
  }
  if (((*(char *)(param_1 + 0x77) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x110), cVar1 != '\0')
      ) && (*(char *)(param_1 + 0x88) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0xdc),1);
    *(undefined1 *)(param_1 + 0x88) = 1;
  }
  if (((*(char *)(param_1 + 0x77) != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x114), cVar1 != '\0')
      ) && (*(char *)(param_1 + 0x89) == '\0')) {
    FUN_005cbc20(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0xdc),1);
    *(undefined1 *)(param_1 + 0x89) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf8);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7c) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf8),"relic_path1",1);
    *(undefined1 *)(param_1 + 0x7c) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xfc);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x7d) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0xfc),"relic_path1",1);
    *(undefined1 *)(param_1 + 0x7d) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x100);
  if ((((cVar1 != '\0') && (*(char *)(param_1 + 0x7e) == '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0x104), cVar1 != '\0')) &&
     (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0x100),
                                    *(undefined4 *)(param_1 + 0x104)), 30.0 < (float)fVar4)) {
    FUN_005cbc80(*(undefined4 *)(param_1 + 0x100),1);
    *(undefined1 *)(param_1 + 0x7e) = 1;
  }
  if ((*(char *)(param_1 + 0x7c) != '\0') &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xbc) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xbc))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xbc) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0xf8);
    if ((cVar1 != '\0') &&
       ((*(char *)(param_1 + 0x7f) == '\0' &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf8),
                                       *(undefined4 *)(param_1 + 0x128)), (float)fVar4 < 50.0)))) {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0xf8),1);
      *(undefined1 *)(param_1 + 0x7f) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x7d) != '\0') &&
     (fVar4 = (float10)FUN_00822d80(),
     *(float *)(param_1 + 0xc0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc0))) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xc0) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0xfc);
    if ((cVar1 != '\0') &&
       ((*(char *)(param_1 + 0x80) == '\0' &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xfc),
                                       *(undefined4 *)(param_1 + 300)), (float)fVar4 < 50.0)))) {
      FUN_005caf20(*(undefined4 *)(param_1 + 0xfc));
      FUN_005cbc80(*(undefined4 *)(param_1 + 0xfc),1);
      *(undefined1 *)(param_1 + 0x80) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0x110);
  if ((((cVar1 != '\0') && (cVar1 = FUN_005c84d0(param_1 + 0x114), cVar1 != '\0')) &&
      (cVar1 = FUN_005c84d0(param_1 + 0xf8), cVar1 != '\0')) &&
     (((cVar1 = FUN_005c84d0(param_1 + 0xfc), cVar1 != '\0' && (*(char *)(param_1 + 0x8e) == '\0'))
      && (iVar3 = FUN_005cae10(2), 0xf < iVar3)))) {
    FUN_005cb2d0("misn10a.aip",2);
    *(undefined1 *)(param_1 + 0x8e) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xec);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x84) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0xec),"artil1_path",1);
    *(undefined1 *)(param_1 + 0x84) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf0);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x85) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf0),"artil2_path",1);
    *(undefined1 *)(param_1 + 0x85) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xf4);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x86) == '\0')) {
    FUN_005cb960(*(undefined4 *)(param_1 + 0xf4),"relic_path1",1);
    *(undefined1 *)(param_1 + 0x86) = 1;
  }
  fVar4 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0xb0) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb0)) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb0) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0x81) == '\0')) &&
       (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xec),
                                      *(undefined4 *)(param_1 + 0x120)), (float)fVar4 < 20.0)) {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0xec),1);
      *(undefined1 *)(param_1 + 0x81) = 1;
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0xb4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb4)) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb4) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0x82) == '\0')) &&
       (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf0),
                                      *(undefined4 *)(param_1 + 0x124)), (float)fVar4 < 20.0)) {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0xf0),1);
      *(undefined1 *)(param_1 + 0x82) = 1;
    }
  }
  fVar4 = (float10)FUN_00822d80();
  if (*(float *)(param_1 + 0xb8) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xb8)) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0xb8) = (float)fVar4 + 3.0;
    cVar1 = FUN_005c84d0(param_1 + 0xf4);
    if (((cVar1 != '\0') && (*(char *)(param_1 + 0x83) == '\0')) &&
       (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 300)
                                     ), (float)fVar4 < 50.0)) {
      FUN_005cbc80(*(undefined4 *)(param_1 + 0xf4),1);
      *(undefined1 *)(param_1 + 0x83) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xd4);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 0x87) != '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8a) == '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xd4),1);
      *(undefined1 *)(param_1 + 0x8a) = 1;
    }
    cVar1 = FUN_005c84d0(param_1 + 0x11c);
    if ((cVar1 != '\0') && (*(char *)(param_1 + 0x8b) == '\0')) {
      FUN_005cbc20(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xd4),1);
      *(undefined1 *)(param_1 + 0x8b) = 1;
    }
    if ((((*(char *)(param_1 + 100) == '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (*(char *)(param_1 + 0x5a) != '\0')) && (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"relic_path1",1);
      *(undefined1 *)(param_1 + 100) = 1;
    }
    if ((*(char *)(param_1 + 100) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x128)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        cVar1 = FUN_005c84d0(param_1 + 0x118);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xd4),0);
        }
        cVar1 = FUN_005c84d0(param_1 + 0x11c);
        if (cVar1 != '\0') {
          FUN_005cbc20(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xd4),0);
        }
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 100) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x128)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5b) != '\0')) &&
       ((*(char *)(param_1 + 0x65) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"relic_path1",1);
      *(undefined1 *)(param_1 + 0x65) = 1;
    }
    if ((*(char *)(param_1 + 0x65) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 300));
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x65) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 300)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5c) != '\0')) &&
       ((*(char *)(param_1 + 0x66) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"attack_path_central",1);
      *(undefined1 *)(param_1 + 0x66) = 1;
    }
    if ((*(char *)(param_1 + 0x66) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x130)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x66) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x130)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5d) != '\0')) &&
       ((*(char *)(param_1 + 0x67) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"attack_path_central",1);
      *(undefined1 *)(param_1 + 0x67) = 1;
    }
    if ((*(char *)(param_1 + 0x67) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x134)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x67) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x134)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5e) != '\0')) &&
       ((*(char *)(param_1 + 0x68) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"attack_path_south",1);
      *(undefined1 *)(param_1 + 0x68) = 1;
    }
    if ((*(char *)(param_1 + 0x68) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x138)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x68) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x138)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x5f) != '\0')) &&
       ((*(char *)(param_1 + 0x69) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"attack_path_north",1);
      *(undefined1 *)(param_1 + 0x69) = 1;
    }
    if ((*(char *)(param_1 + 0x69) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x13c)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x69) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x13c)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x62) != '\0') && (*(char *)(param_1 + 0x60) != '\0')) &&
       ((*(char *)(param_1 + 0x6a) == '\0' && (*(char *)(param_1 + 0x74) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"attack_path_south",1);
      *(undefined1 *)(param_1 + 0x6a) = 1;
    }
    if ((*(char *)(param_1 + 0x6a) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) {
      fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc))
      ;
      fVar5 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x140)
                                   );
      if (((float)fVar4 < (float)fVar5) &&
         ((fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                         *(undefined4 *)(param_1 + 0xdc)), (float)fVar4 < 100.0 &&
          (*(char *)(param_1 + 0x74) == '\0')))) {
        FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
        *(undefined1 *)(param_1 + 0x74) = 1;
      }
    }
    if ((((*(char *)(param_1 + 0x6a) != '\0') && (*(char *)(param_1 + 0x62) != '\0')) &&
        (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                       *(undefined4 *)(param_1 + 0x140)), (float)fVar4 < 100.0)) &&
       (*(char *)(param_1 + 0x74) == '\0')) {
      FUN_005cc280(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0xdc),1);
      *(undefined1 *)(param_1 + 0x74) = 1;
    }
    if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 100) != '\0')) &&
       ((*(char *)(param_1 + 0x61) != '\0' && (*(char *)(param_1 + 0x73) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"main_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
       ((*(char *)(param_1 + 0x61) != '\0' && (*(char *)(param_1 + 0x73) == '\0')))) {
      FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x104),1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if ((((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
        (*(char *)(param_1 + 0x61) != '\0')) && (*(char *)(param_1 + 0x73) == '\0')) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"lsouth_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
       ((*(char *)(param_1 + 0x61) != '\0' && (*(char *)(param_1 + 0x73) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"main_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x68) != '\0')) &&
       ((*(char *)(param_1 + 0x61) != '\0' && (*(char *)(param_1 + 0x73) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"ssouth_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if ((((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x69) != '\0')) &&
        (*(char *)(param_1 + 0x61) != '\0')) && (*(char *)(param_1 + 0x73) == '\0')) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"main_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
    if (((*(char *)(param_1 + 0x74) != '\0') && (*(char *)(param_1 + 0x6a) != '\0')) &&
       ((*(char *)(param_1 + 0x61) != '\0' && (*(char *)(param_1 + 0x73) == '\0')))) {
      FUN_005cb960(*(undefined4 *)(param_1 + 0xd4),"msouth_return_path",1);
      *(undefined1 *)(param_1 + 0x73) = 1;
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (cVar1 == '\0') {
    if ((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 100) == '\0')) {
      *(undefined1 *)(param_1 + 0x72) = 1;
    }
    if ((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 100) != '\0')) {
      *(undefined1 *)(param_1 + 100) = 0;
      *(undefined1 *)(param_1 + 0x6b) = 1;
    }
    if ((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x65) == '\0')) {
      *(undefined1 *)(param_1 + 0x72) = 1;
    }
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 300))
      , (float)fVar4 < 50.0)) && (*(char *)(param_1 + 0x6c) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 300),1);
    *(undefined1 *)(param_1 + 0x65) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x65) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x6c) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 300),1);
    *(undefined1 *)(param_1 + 0x65) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x6c) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 99) != '\0')) && (*(char *)(param_1 + 0x66) == '\0'))
  {
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                     *(undefined4 *)(param_1 + 0x130)), (float)fVar4 < 50.0)) &&
     (*(char *)(param_1 + 0x6d) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x130),1);
    *(undefined1 *)(param_1 + 0x66) = 0;
    *(undefined1 *)(param_1 + 0x6d) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x66) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x6d) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x130),1);
    *(undefined1 *)(param_1 + 0x66) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x6d) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 99) != '\0')) && (*(char *)(param_1 + 0x67) == '\0'))
  {
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                     *(undefined4 *)(param_1 + 0x134)), (float)fVar4 < 50.0)) &&
     (*(char *)(param_1 + 0x6e) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x134),1);
    *(undefined1 *)(param_1 + 0x67) = 0;
    *(undefined1 *)(param_1 + 0x6e) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x67) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x6e) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x134),1);
    *(undefined1 *)(param_1 + 0x67) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x6e) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 99) != '\0')) && (*(char *)(param_1 + 0x68) == '\0'))
  {
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x68) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                     *(undefined4 *)(param_1 + 0x138)), (float)fVar4 < 50.0)) &&
     (*(char *)(param_1 + 0x6f) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x138),1);
    *(undefined1 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x6f) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x68) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x6f) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x138),1);
    *(undefined1 *)(param_1 + 0x68) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x6f) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 99) != '\0')) && (*(char *)(param_1 + 0x69) == '\0'))
  {
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x69) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                     *(undefined4 *)(param_1 + 0x13c)), (float)fVar4 < 50.0)) &&
     (*(char *)(param_1 + 0x70) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x13c),1);
    *(undefined1 *)(param_1 + 0x69) = 0;
    *(undefined1 *)(param_1 + 0x70) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x69) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x70) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x13c),1);
    *(undefined1 *)(param_1 + 0x69) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x70) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if (((cVar1 == '\0') && (*(char *)(param_1 + 99) != '\0')) && (*(char *)(param_1 + 0x6a) == '\0'))
  {
    *(undefined1 *)(param_1 + 0x61) = 1;
    *(undefined1 *)(param_1 + 0x72) = 1;
  }
  if ((((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x6a) != '\0')) &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd4),
                                     *(undefined4 *)(param_1 + 0x140)), (float)fVar4 < 50.0)) &&
     (*(char *)(param_1 + 0x71) == '\0')) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x140),1);
    *(undefined1 *)(param_1 + 0x6a) = 0;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  if (((*(char *)(param_1 + 99) != '\0') && (*(char *)(param_1 + 0x6a) != '\0')) &&
     ((*(char *)(param_1 + 0x74) != '\0' && (*(char *)(param_1 + 0x71) == '\0')))) {
    FUN_005cb9d0(*(undefined4 *)(param_1 + 0xd4),*(undefined4 *)(param_1 + 0x140),1);
    *(undefined1 *)(param_1 + 0x6a) = 0;
    *(undefined1 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x71) = 1;
  }
  if ((*(int *)(param_1 + 0xd8) != 0) && (*(char *)(param_1 + 0x92) == '\0')) {
    cVar1 = FUN_005c84d0(param_1 + 0x110);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x110),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x114);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x118);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x118),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x11c);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x11c),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x144);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0x148);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xec);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xf0);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf0),*(undefined4 *)(param_1 + 0xd8),1);
    }
    cVar1 = FUN_005c84d0(param_1 + 0xf4);
    if (cVar1 != '\0') {
      FUN_005cb820(*(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xd8),1);
    }
    *(undefined1 *)(param_1 + 0x92) = 1;
  }
  fVar4 = (float10)FUN_00822d80();
  if ((*(float *)(param_1 + 200) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 200)) &&
     (*(char *)(param_1 + 0x92) == '\0')) {
    fVar4 = (float10)FUN_00822d80();
    *(float *)(param_1 + 200) = (float)fVar4 + 150.0;
    fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0x128));
    if (200.0 <= (float)fVar4) {
      cVar1 = FUN_005c84d0(param_1 + 0x144);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x128),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x148);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0x128),1);
      }
    }
    else {
      cVar1 = FUN_005c84d0(param_1 + 0x144);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0xd0),1);
      }
      cVar1 = FUN_005c84d0(param_1 + 0x148);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x148),*(undefined4 *)(param_1 + 0xd0),1);
      }
    }
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if ((cVar1 != '\0') &&
     (fVar4 = (float10)FUN_004b1670(),
     *(float *)(param_1 + 0xc4) <= (float)fVar4 && (float)fVar4 != *(float *)(param_1 + 0xc4))) {
    FUN_005ccfd0(*(undefined4 *)(param_1 + 0xdc),0x42c80000);
    fVar4 = (float10)FUN_004b1670();
    *(float *)(param_1 + 0xc4) = (float)fVar4 + 1.0;
  }
  if (((*(char *)(param_1 + 99) != '\0') &&
      (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),
                                     *(undefined4 *)(param_1 + 0x10c)), (float)fVar4 < 100.0)) &&
     (*(char *)(param_1 + 0x91) == '\0')) {
    FUN_00437d30("misn1001.wav");
    fVar4 = (float10)FUN_00822d80("misn10w1.des");
    FUN_0045c110((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  if (((*(char *)(param_1 + 0x61) != '\0') && (*(char *)(param_1 + 0x91) == '\0')) &&
     (fVar4 = (float10)FUN_005c9780(*(undefined4 *)(param_1 + 0xdc),*(undefined4 *)(param_1 + 0x104)
                                   ), (float)fVar4 < 100.0)) {
    FUN_00437d30("misn1002.wav");
    fVar4 = (float10)FUN_00822d80("misn10f1.des");
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0xdc);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x91) == '\0')) {
    FUN_00437d30("misn1003.wav");
    fVar4 = (float10)FUN_00822d80("misn10f2.des");
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  cVar1 = FUN_005c84d0(param_1 + 0x10c);
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x91) == '\0')) {
    FUN_00437d30("misn1004.wav");
    fVar4 = (float10)FUN_00822d80("misn10f3.des");
    FUN_0045c0f0((float)fVar4 + 15.0);
    *(undefined1 *)(param_1 + 0x91) = 1;
  }
  return;
}

