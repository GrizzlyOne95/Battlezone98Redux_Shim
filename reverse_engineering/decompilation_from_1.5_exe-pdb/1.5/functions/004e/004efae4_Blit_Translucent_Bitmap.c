/*
 * Entry: 004efae4
 * Name: Blit_Translucent_Bitmap
 * Namespace: Global
 * Signature: void Blit_Translucent_Bitmap(char * param_1, char * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl
Blit_Translucent_Bitmap
          (char *param_1,char *param_2,long param_3,long param_4,long param_5,long param_6)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  char *pcVar8;
  uint *puVar9;
  
  if (param_3 < 8) {
    do {
      iVar7 = -param_3;
      do {
        param_1[iVar7 + param_3] =
             Translucency_Table[0][CONCAT11(param_2[iVar7 + param_3],param_1[iVar7 + param_3])];
        bVar4 = iVar7 < -1;
        iVar7 = iVar7 + 1;
      } while (bVar4);
      param_1 = param_1 + param_5;
      param_2 = param_2 + param_6;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  else {
    do {
      uVar5 = -(int)param_1 & 3;
      iVar7 = param_3 - uVar5;
      puVar9 = (uint *)param_1;
      pcVar8 = param_2;
      for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        cVar3 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *(uchar *)puVar9 = Translucency_Table[0][CONCAT11(cVar3,(uchar)*puVar9)];
        puVar9 = (uint *)((int)puVar9 + 1);
      }
      do {
        iVar7 = iVar7 + -4;
        pcVar1 = pcVar8 + 2;
        uVar6 = CONCAT11(Translucency_Table[0][CONCAT11(pcVar8[1],*(uchar *)((int)puVar9 + 1))],
                         Translucency_Table[0][CONCAT11(*pcVar8,(uchar)*puVar9)]);
        pcVar2 = pcVar8 + 3;
        pcVar8 = pcVar8 + 4;
        *puVar9 = (uint)uVar6 |
                  CONCAT22(uVar6,CONCAT11(Translucency_Table[0]
                                          [CONCAT11(*pcVar2,*(uchar *)((int)puVar9 + 3))],
                                          Translucency_Table[0]
                                          [CONCAT11(*pcVar1,*(uchar *)((int)puVar9 + 2))])) << 0x10;
        puVar9 = puVar9 + 1;
      } while (3 < iVar7);
      for (; iVar7 != 0; iVar7 = iVar7 + -1) {
        cVar3 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *(uchar *)puVar9 = Translucency_Table[0][CONCAT11(cVar3,(uchar)*puVar9)];
        puVar9 = (uint *)((int)puVar9 + 1);
      }
      param_1 = param_1 + param_5;
      param_2 = param_2 + param_6;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}
