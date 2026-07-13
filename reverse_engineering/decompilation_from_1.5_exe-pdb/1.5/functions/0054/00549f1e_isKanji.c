/*
 * Entry: 00549f1e
 * Name: isKanji
 * Namespace: Global
 * Signature: int isKanji(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isKanji(char *param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  bVar1 = *param_1;
  if ((((bVar1 < 0x88) || (0x9f < bVar1)) && ((bVar1 < 0xe0 || (0xea < bVar1)))) &&
     ((bVar1 < 0xed || (0xee < bVar1)))) {
    if (bVar1 < 0xfa) {
      return 0;
    }
    if (0xfc < bVar1) {
      return 0;
    }
  }
  bVar2 = param_1[1];
  if (bVar1 == 0x88) {
    bVar3 = bVar2 < 0x9f;
LAB_00549fc0:
    if (bVar3) {
      return 0;
    }
    bVar3 = bVar2 < 0xfc;
    bVar4 = bVar2 == 0xfc;
LAB_00549fc5:
    if (!bVar3 && !bVar4) {
      return 0;
    }
  }
  else {
    if (bVar1 == 0x98) {
      if ((0x72 < bVar2) && (bVar2 < 0x9f)) {
        return 0;
      }
      if (0xfb < bVar2) {
        return 0;
      }
    }
    else {
      if (bVar1 != 0xea) {
        if (bVar1 == 0xee) {
          if (bVar2 < 0x40) {
            return 0;
          }
          if (bVar2 == 0x7f) {
            return 0;
          }
          bVar3 = bVar2 < 0xec;
          bVar4 = bVar2 == 0xec;
        }
        else {
          if (bVar1 != 0xfc) {
            if (bVar2 == 0x7f) {
              return 0;
            }
            bVar3 = bVar2 < 0x40;
            goto LAB_00549fc0;
          }
          if (bVar2 < 0x40) {
            return 0;
          }
          bVar3 = bVar2 < 0x4b;
          bVar4 = bVar2 == 0x4b;
        }
        goto LAB_00549fc5;
      }
      if (bVar2 == 0x7f) {
        return 0;
      }
      if (0xa4 < bVar2) {
        return 0;
      }
    }
    if (bVar2 < 0x40) {
      return 0;
    }
  }
  return 1;
}
