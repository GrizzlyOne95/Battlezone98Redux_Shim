/*
 * Entry: 004bd201
 * Name: InitKeyboard
 * Namespace: Global
 * Signature: void InitKeyboard(char * * param_1, char * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl InitKeyboard(char **param_1,char **param_2)

{
  char **ppcVar1;
  char *pcVar2;
  int iVar3;
  UINT UVar4;
  UINT uCode;
  
  if (done == 0) {
    done = 1;
    if (param_1 != (char **)0x0) {
      ppcVar1 = discreteNames;
      do {
        *ppcVar1 = *(char **)((int)(param_1 + -0x18a428) + (int)ppcVar1);
        ppcVar1 = ppcVar1 + 1;
      } while ((int)ppcVar1 < 0x629294);
    }
    if (param_2 == (char **)0x0) {
      param_2 = (char **)&e_discreteDescriptions;
    }
    ppcVar1 = discreteDescriptions;
    do {
      pcVar2 = (char *)_StrLookupFind(_DAT_00224566,
                                      *(undefined4 *)((int)(param_2 + -0x350350) + (int)ppcVar1));
      *ppcVar1 = pcVar2;
      ppcVar1 = ppcVar1 + 1;
    } while ((int)ppcVar1 < 0xd40f34);
    iVar3 = IsGerman();
    if (iVar3 != 0) {
      virtualKeyToGI[0xba] = 0xfc;
      virtualKeyToGI[0xbb] = 0x2b;
      virtualKeyToGI[0xbd] = 0x2d;
      virtualKeyToGI[0xbf] = 0xe4;
      virtualKeyToGI[0xc0] = 0xf6;
      virtualKeyToGI[0xdb] = 0xdf;
      virtualKeyToGI[0xdc] = 0x60;
      virtualKeyToGI[0xde] = 0xe4;
      virtualKeyToGI[0xdd] = 0x27;
      virtualKeyToGI[0xe2] = 0x3c;
    }
    uCode = 0;
    do {
      if (virtualKeyToGI[uCode] == 0) {
        UVar4 = MapVirtualKeyA(uCode,2);
        iVar3 = tolower((int)(char)UVar4);
        virtualKeyToGI[uCode] = (ushort)iVar3;
      }
      uCode = uCode + 1;
    } while ((int)uCode < 0x100);
  }
  return;
}
