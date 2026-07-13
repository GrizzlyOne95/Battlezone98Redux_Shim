/*
 * Entry: 004efcb2
 * Name: Blit_Transparent_Bitmap
 * Namespace: Global
 * Signature: void Blit_Transparent_Bitmap(char * param_1, char * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blit_Transparent_Bitmap
          (char *param_1,char *param_2,long param_3,long param_4,long param_5,long param_6)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  byte bVar4;
  uint uVar6;
  int iVar8;
  int iVar9;
  char cVar5;
  uint uVar7;
  
  if (param_3 < 4) {
    do {
      iVar2 = -param_3;
      do {
        if (param_1[iVar2 + param_3] != -1) {
          param_1[iVar2 + param_3] = param_1[iVar2 + param_3];
        }
        bVar1 = iVar2 < -1;
        iVar2 = iVar2 + 1;
      } while (bVar1);
      param_1 = param_1 + param_5;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  else {
    iVar8 = param_6 - param_3;
    iVar2 = param_5 - param_3;
    uVar6 = param_3;
    if ((param_3 & 3U) != 0) {
      param_3 = param_3 - 4;
      uVar6 = param_3;
    }
LAB_004efd14:
    do {
      uVar7 = uVar6;
      if (*(int *)param_2 == -1) {
        param_1 = param_1 + 4;
        param_2 = (char *)((int)param_2 + 4);
        uVar6 = uVar7 - 4;
        if (uVar7 - 4 != 0 && 3 < (int)uVar7) goto LAB_004efd14;
        if ((int)uVar7 < 4) goto LAB_004efd4c;
      }
      else {
        cVar5 = '\x04';
        do {
          iVar9 = *(int *)param_2;
          param_2 = (char *)((int)param_2 + 1);
          if ((char)iVar9 != -1) {
            *param_1 = (char)iVar9;
          }
          param_1 = param_1 + 1;
          cVar3 = cVar5 + -1;
          bVar1 = '\0' < cVar5;
          cVar5 = cVar3;
        } while (cVar3 != '\0' && bVar1);
        uVar6 = uVar7 - 4;
        if (uVar6 != 0 && 3 < (int)uVar7) goto LAB_004efd14;
        if (uVar6 != 0) {
LAB_004efd4c:
          do {
            iVar9 = *(int *)param_2;
            param_2 = (char *)((int)param_2 + 1);
            if ((char)iVar9 != -1) {
              *param_1 = (char)iVar9;
            }
            param_1 = param_1 + 1;
            cVar5 = (char)uVar7;
            bVar4 = cVar5 - 1;
            uVar7 = (uint)bVar4;
          } while (bVar4 != 0 && '\0' < cVar5);
        }
      }
      param_2 = (char *)((int)param_2 + iVar8);
      param_1 = param_1 + iVar2;
      iVar9 = param_4 + -1;
      bVar1 = 0 < param_4;
      uVar6 = param_3;
      param_4 = iVar9;
    } while (iVar9 != 0 && bVar1);
  }
  return;
}
