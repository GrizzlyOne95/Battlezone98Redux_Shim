/*
 * Entry: 004efda8
 * Name: Blit_Alpha_Bitmap
 * Namespace: Global
 * Signature: void Blit_Alpha_Bitmap(char * param_1, char * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blit_Alpha_Bitmap(char *param_1,char *param_2,long param_3,long param_4,long param_5,long param_6)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uchar *puVar9;
  
  if (param_3 < 5) {
    do {
      iVar2 = -param_3;
      do {
        param_1[iVar2 + param_3] =
             Headlight_Mask_Luma[0][CONCAT11(param_2[iVar2 + param_3],param_1[iVar2 + param_3])];
        bVar1 = iVar2 < -1;
        iVar2 = iVar2 + 1;
      } while (bVar1);
      param_1 = param_1 + param_5;
      param_2 = param_2 + param_6;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  else {
    iVar7 = param_6 - param_3;
    iVar2 = param_5 - param_3;
    uVar5 = param_3;
    if ((param_3 & 3U) != 0) {
      param_3 = param_3 - 4;
      uVar5 = param_3;
    }
LAB_004efe12:
    do {
      uVar6 = uVar5;
      if (*(int *)param_2 == -1) {
        param_1 = param_1 + 4;
        param_2 = (char *)((int)param_2 + 4);
        uVar5 = uVar6 - 4;
        if (uVar6 - 4 != 0 && 3 < (int)uVar6) goto LAB_004efe12;
        if ((int)uVar6 < 4) goto LAB_004efe64;
      }
      else {
        puVar9 = (uchar *)param_1;
        cVar3 = '\x04';
        do {
          while( true ) {
            iVar8 = *(int *)param_2;
            param_1 = (char *)(puVar9 + 1);
            if ((char)iVar8 != -1) break;
            param_2 = (char *)((int)param_2 + 1);
            cVar4 = cVar3 + -1;
            bVar1 = cVar3 < '\x01';
            puVar9 = (uchar *)param_1;
            cVar3 = cVar4;
            if (cVar4 == '\0' || bVar1) {
              uVar5 = uVar6 - 4;
              if (uVar6 - 4 != 0 && 3 < (int)uVar6) goto LAB_004efe12;
              if (3 < (int)uVar6) goto LAB_004efe24;
              goto LAB_004efe64;
            }
          }
          param_2 = (char *)((int)param_2 + 1);
          cVar4 = cVar3 + -1;
          *puVar9 = Headlight_Mask_Luma[0][CONCAT11((char)iVar8,*puVar9)];
          bVar1 = '\0' < cVar3;
          puVar9 = (uchar *)param_1;
          cVar3 = cVar4;
        } while (cVar4 != '\0' && bVar1);
        uVar5 = uVar6 - 4;
        if (uVar5 != 0 && 3 < (int)uVar6) goto LAB_004efe12;
        if (uVar5 != 0) {
LAB_004efe64:
          do {
            iVar8 = *(int *)param_2;
            puVar9 = (uchar *)(param_1 + 1);
            cVar3 = (char)uVar6;
            if ((char)iVar8 == -1) {
              param_2 = (char *)((int)param_2 + 1);
              uVar6 = (uint)(byte)(cVar3 - 1U);
              param_1 = (char *)puVar9;
              if ((byte)(cVar3 - 1U) == 0 || cVar3 < '\x01') break;
              goto LAB_004efe64;
            }
            param_2 = (char *)((int)param_2 + 1);
            uVar6 = (uint)(byte)(cVar3 - 1U);
            *param_1 = Headlight_Mask_Luma[0][CONCAT11((char)iVar8,*param_1)];
            param_1 = (char *)puVar9;
          } while ((byte)(cVar3 - 1U) != 0 && '\0' < cVar3);
        }
      }
LAB_004efe24:
      param_2 = (char *)((int)param_2 + iVar7);
      param_1 = param_1 + iVar2;
      iVar8 = param_4 + -1;
      bVar1 = 0 < param_4;
      uVar5 = param_3;
      param_4 = iVar8;
    } while (iVar8 != 0 && bVar1);
  }
  return;
}
