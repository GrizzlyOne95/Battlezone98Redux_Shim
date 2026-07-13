/*
 * Entry: 00584c9a
 * Name: swd_search
 * Namespace: Global
 * Signature: void swd_search(lzo1y_999_swd_t * param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_search(lzo1y_999_swd_t *param_1,ulong param_2,ulong param_3)

{
  uchar *puVar1;
  int *piVar2;
  uchar uVar3;
  int iVar4;
  int iVar5;
  int in_EAX;
  uchar *puVar6;
  uint uVar7;
  uchar *puVar8;
  uint uVar9;
  
  iVar4 = *(int *)(in_EAX + 0x154);
  iVar5 = *(int *)(in_EAX + 0x24);
  puVar1 = (uchar *)(iVar4 + 0x16c + in_EAX);
  uVar9 = *(uint *)(in_EAX + 0x1c);
  uVar3 = puVar1[uVar9 - 1];
  do {
    if (param_2 == 0) {
      return;
    }
    param_2 = param_2 - 1;
    puVar8 = param_1->b + in_EAX;
    if ((((puVar8[uVar9 - 1] == uVar3) && (puVar8[uVar9] == puVar1[uVar9])) && (*puVar8 == *puVar1))
       && (puVar8[1] == puVar1[1])) {
      puVar6 = puVar1 + 2;
      puVar8 = puVar8 + 2;
      do {
        puVar6 = puVar6 + 1;
        if ((uchar *)(iVar5 + iVar4 + 0x16c + in_EAX) <= puVar6) break;
        puVar8 = puVar8 + 1;
      } while (*puVar6 == *puVar8);
      uVar7 = (int)puVar6 - (int)puVar1;
      if ((uVar7 < 0x22) && (piVar2 = (int *)(in_EAX + 0xbc + uVar7 * 4), *piVar2 == 0)) {
        *piVar2 = (int)((int)&param_1->swd_n + 1);
      }
      if (uVar9 < uVar7) {
        *(uint *)(in_EAX + 0x1c) = uVar7;
        *(lzo1y_999_swd_t **)(in_EAX + 0xb8) = param_1;
        if (uVar7 == *(uint *)(in_EAX + 0x24)) {
          return;
        }
        if (*(uint *)(in_EAX + 0x10) <= uVar7) {
          return;
        }
        if (*(ushort *)(in_EAX + 0x2e16a + (int)param_1 * 2) < uVar7) {
          return;
        }
        uVar3 = puVar1[uVar7 - 1];
        uVar9 = uVar7;
      }
    }
    param_1 = (lzo1y_999_swd_t *)(uint)*(ushort *)(in_EAX + 0x1516c + (int)param_1 * 2);
  } while( true );
}
