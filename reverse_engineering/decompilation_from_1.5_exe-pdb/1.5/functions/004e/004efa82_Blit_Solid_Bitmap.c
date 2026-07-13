/*
 * Entry: 004efa82
 * Name: Blit_Solid_Bitmap
 * Namespace: Global
 * Signature: void Blit_Solid_Bitmap(char * param_1, char * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blit_Solid_Bitmap(char *param_1,char *param_2,long param_3,long param_4,long param_5,long param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  iVar2 = param_3;
  pcVar5 = param_2;
  pcVar4 = param_1;
  if (param_3 < 8) {
    do {
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        *pcVar4 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar4 = pcVar4 + 1;
      }
      pcVar4 = param_1 + param_5;
      pcVar5 = param_2 + param_6;
      param_4 = param_4 + -1;
      iVar2 = param_3;
      param_2 = pcVar5;
      param_1 = pcVar4;
    } while (param_4 != 0);
  }
  else {
    do {
      uVar1 = -(int)param_1 & 3;
      uVar3 = param_3 - uVar1;
      pcVar4 = param_2;
      pcVar5 = param_1;
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      uVar1 = uVar3 & 3;
      for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      param_1 = param_1 + param_5;
      param_2 = param_2 + param_6;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}
