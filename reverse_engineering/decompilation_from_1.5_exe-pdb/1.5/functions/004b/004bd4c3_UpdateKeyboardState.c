/*
 * Entry: 004bd4c3
 * Name: UpdateKeyboardState
 * Namespace: Global
 * Signature: void UpdateKeyboardState(uint param_1, long param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

void __cdecl UpdateKeyboardState(uint param_1,long param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = param_2 >> 0x10 & 0xff;
  if (uVar4 == 0) {
    return;
  }
  if ((((uint)param_2 >> 0x10 & 0x100) != 0) && (uVar4 < 0x59)) {
    uVar4 = ExtendedCodes[uVar4];
  }
  if (uVar4 == 0) {
    return;
  }
  iVar5 = uVar4 - 1;
  iVar2 = (int)(iVar5 + (iVar5 >> 0x1f & 0x1fU)) >> 5;
  if (param_3 == 0) {
    discreteClrMap[iVar2] = discreteClrMap[iVar2] | 1 << ((byte)iVar5 & 0x1f);
  }
  else {
    uVar3 = 1 << ((byte)iVar5 & 0x1f);
    uVar1 = discreteClrMap[iVar2];
    if ((uVar3 & uVar1) != 0) {
      discreteClrMap[iVar2] = ~uVar3 & uVar1;
    }
    discreteSetMap[iVar2] = discreteSetMap[iVar2] | uVar3;
  }
  if ((LocaleInfo != (LOCALE_INFO *)0x0) && (LocaleInfo->KeyNames == (char **)&jn_discreteNames)) {
    return;
  }
  if (uVar4 == 0x1d) {
LAB_004bd5d1:
    if (param_3 == 0) {
      discreteClrMap[3] = discreteClrMap[3] | 0x800000;
      return;
    }
    uVar4 = 0x800000;
    if ((discreteClrMap[3] & 0x800000) != 0) {
      discreteClrMap[3] = discreteClrMap[3] & 0xff7fffff;
    }
  }
  else {
    if ((uVar4 == 0x2a) || (uVar4 == 0x36)) {
      if (param_3 == 0) {
        discreteClrMap[3] = discreteClrMap[3] | 0x400000;
        return;
      }
      uVar4 = 0x400000;
      if ((discreteClrMap[3] & 0x400000) != 0) {
        discreteClrMap[3] = discreteClrMap[3] & 0xffbfffff;
      }
      goto LAB_004bd5ed;
    }
    if (uVar4 != 0x38) {
      if (uVar4 == 0x70) goto LAB_004bd5d1;
      if (uVar4 != 0x71) {
        return;
      }
    }
    if (param_3 == 0) {
      discreteClrMap[3] = discreteClrMap[3] | 0x1000000;
      return;
    }
    uVar4 = 0x1000000;
    if ((discreteClrMap[3] & 0x1000000) != 0) {
      discreteClrMap[3] = discreteClrMap[3] & 0xfeffffff;
    }
  }
LAB_004bd5ed:
  discreteSetMap[3] = discreteSetMap[3] | uVar4;
  return;
}
