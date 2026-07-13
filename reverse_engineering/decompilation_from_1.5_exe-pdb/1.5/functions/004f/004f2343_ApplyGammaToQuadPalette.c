/*
 * Entry: 004f2343
 * Name: ApplyGammaToQuadPalette
 * Namespace: Global
 * Signature: void ApplyGammaToQuadPalette(tagRGBQUAD * param_1, long param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ApplyGammaToQuadPalette(tagRGBQUAD *param_1,long param_2,long param_3,long param_4)

{
  int iVar1;
  uchar *puVar2;
  int iVar3;
  
  if (((param_4 < 1) &&
      (param_4 = (long)(byte)((UserProfilePtr->graphicDetail).brightness + 1), param_4 == 0)) ||
     (10 < param_4)) {
    param_4 = 3;
  }
  iVar1 = param_4 * 0x100 + 0xd3f080;
  if (param_2 < param_3) {
    iVar3 = param_3 - param_2;
    puVar2 = &param_1[param_2].rgbRed;
    do {
      ((tagRGBQUAD *)(puVar2 + -2))->rgbBlue =
           *(byte *)((uint)((tagRGBQUAD *)(puVar2 + -2))->rgbBlue + iVar1);
      puVar2[-1] = *(byte *)((uint)puVar2[-1] + iVar1);
      *puVar2 = *(byte *)((uint)*puVar2 + iVar1);
      puVar2 = puVar2 + 4;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}
