/*
 * Entry: 0058587a
 * Name: lzo1y_optimize
 * Namespace: Global
 * Signature: int lzo1y_optimize(uchar * param_1, ulong param_2, uchar * param_3, ulong * param_4, void * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lzo1y_optimize(uchar *param_1,ulong param_2,uchar *param_3,ulong *param_4,void *param_5)

{
  ulong uVar1;
  char cVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  char *_Src;
  uchar *puVar6;
  uint uVar7;
  int iVar8;
  ulong unaff_ESI;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  uchar *unaff_EDI;
  byte *pbVar12;
  byte *pbVar13;
  uchar *local_c;
  byte *local_8;
  
  pbVar9 = param_1;
  pbVar3 = param_1 + param_2;
  uVar1 = *param_4;
  *param_4 = 0;
  bVar5 = *param_1;
  param_2 = 0;
  param_1 = (uchar *)0x0;
  pbVar12 = param_3;
  if (bVar5 < 0x12) goto LAB_005858d0;
  puVar6 = (uchar *)(bVar5 - 0x11);
  pbVar9 = pbVar9 + 1;
  if (puVar6 < (uchar *)0x4) goto LAB_0058598d;
  do {
    do {
      pbVar13 = pbVar12;
      pbVar11 = pbVar9;
      local_c = (uchar *)0xffffffff;
      *pbVar13 = *pbVar11;
      pbVar12 = pbVar13 + 1;
      puVar6 = puVar6 + -1;
      pbVar9 = pbVar11 + 1;
    } while (puVar6 != (uchar *)0x0);
    bVar5 = pbVar11[1];
    puVar6 = (uchar *)(uint)bVar5;
    pbVar10 = pbVar11 + 2;
    if ((uchar *)0xf < puVar6) goto LAB_00585a3e;
    iVar8 = (uint)*pbVar10 * -4 - (uint)(bVar5 >> 2);
    *pbVar12 = pbVar12[iVar8 + -0x401];
    pbVar9 = pbVar11 + 3;
    pbVar13[2] = pbVar12[iVar8 + -0x400];
    pbVar13[3] = pbVar12[iVar8 + -0x3ff];
    pbVar12 = pbVar13 + 4;
    param_1 = (uchar *)0x0;
LAB_0058596a:
    while( true ) {
      if (local_c == (uchar *)0xffffffff) {
        param_2 = (ulong)(pbVar9 + -2);
        local_c = (uchar *)(*(byte *)param_2 & 3);
        param_1 = local_c;
      }
      puVar6 = local_c;
      if (local_c != (uchar *)0x0) break;
LAB_005858d0:
      if ((pbVar3 <= pbVar9) || (param_3 + uVar1 < pbVar12)) {
LAB_00585ccb:
        *param_4 = (int)pbVar12 - (int)param_3;
        return -7;
      }
      puVar6 = (uchar *)(uint)*pbVar9;
      pbVar10 = pbVar9 + 1;
      if (puVar6 < (uchar *)0x10) {
        if (puVar6 == (uchar *)0x0) {
          iVar8 = 0xf;
          for (; *pbVar10 == 0; pbVar10 = pbVar10 + 1) {
            iVar8 = iVar8 + 0xff;
          }
          puVar6 = (uchar *)(iVar8 + (uint)*pbVar10);
          pbVar10 = pbVar10 + 1;
        }
        param_1 = puVar6 + 3;
        param_2 = (ulong)pbVar9;
        goto LAB_00585915;
      }
LAB_00585a3e:
      local_c = (uchar *)0xffffffff;
      if (puVar6 < (uchar *)0x40) {
        if (puVar6 < (uchar *)0x20) {
          uVar7 = (uint)puVar6 & 7;
          if (uVar7 == 0) {
            iVar8 = 7;
            for (; *pbVar10 == 0; pbVar10 = pbVar10 + 1) {
              iVar8 = iVar8 + 0xff;
            }
            uVar7 = iVar8 + (uint)*pbVar10;
            pbVar10 = pbVar10 + 1;
          }
          pbVar9 = pbVar10 + 2;
          if (pbVar12 + (uint)pbVar10[1] * -0x40 +
                        (((uint)puVar6 & 8) * -0x800 - (uint)(*pbVar10 >> 2)) == pbVar12) {
            *param_4 = (int)pbVar12 - (int)param_3;
            return -(uint)(pbVar9 != pbVar3) & (-(uint)(pbVar9 < pbVar3) & 0xfffffffc) - 4;
          }
          local_8 = pbVar12 + (uint)pbVar10[1] * -0x40 +
                              (((uint)puVar6 & 8) * -0x800 - (uint)(*pbVar10 >> 2)) + -0x4000;
        }
        else {
          uVar7 = (uint)puVar6 & 0x1f;
          if (uVar7 == 0) {
            iVar8 = 0x1f;
            for (; *pbVar10 == 0; pbVar10 = pbVar10 + 1) {
              iVar8 = iVar8 + 0xff;
            }
            uVar7 = iVar8 + (uint)*pbVar10;
            pbVar10 = pbVar10 + 1;
          }
          local_8 = pbVar12 + (uint)pbVar10[1] * -0x40 + (-1 - (uint)(*pbVar10 >> 2));
          pbVar9 = pbVar10 + 2;
        }
        if (param_2 != 0) {
          if (uVar7 == 1) {
            if (param_1 == (uchar *)0x0) {
              if ((pbVar9[-2] & 3) == 0) {
                bVar5 = *pbVar9;
                if (bVar5 < 0x10) goto LAB_00585bc9;
                *(byte *)param_2 = *(byte *)param_2 | 3;
                local_c = (uchar *)0x0;
                param_1 = (uchar *)0x3;
                copy3(pbVar12 + -(int)local_8,unaff_EDI,unaff_ESI);
              }
            }
            else if (((param_1 < (uchar *)0x4) && ((pbVar9[-2] & 3) == 0)) &&
                    (bVar5 = *pbVar9, bVar5 < 0x10)) {
LAB_00585bc9:
              if ((bVar5 != 0) && (param_1 + bVar5 + 3 < (uchar *)0x10)) {
                puVar6 = (uchar *)(uint)*pbVar9;
                *(byte *)param_2 = *(byte *)param_2 & 0xfc;
                pbVar10 = pbVar9 + 1;
                copy3(pbVar12 + -(int)local_8,unaff_EDI,unaff_ESI);
                if (param_1 != (uchar *)0x0) {
                  memmove((void *)(param_2 + 3),(void *)(param_2 + 2),(size_t)param_1);
                }
                param_1 = param_1 + 6 + (int)puVar6;
                cVar2 = (char)param_1;
                param_2 = param_2 + 2;
                goto LAB_00585ad7;
              }
            }
          }
        }
      }
      else {
        local_8 = pbVar12 + ((uint)*pbVar10 * -4 - ((uint)puVar6 >> 2 & 3)) + -1;
        pbVar9 = pbVar10 + 1;
        uVar7 = ((uint)puVar6 >> 4) - 3;
        if (((((param_2 != 0) && (uVar7 == 1)) && ((uchar *)0x3 < param_1)) &&
            (((pbVar10[-1] & 3) == 0 && (bVar5 = *pbVar9, bVar5 < 0x10)))) &&
           ((bVar5 != 0 && (param_1 + bVar5 + 3 < (uchar *)0x10)))) {
          puVar6 = (uchar *)(uint)*pbVar9;
          pbVar10 = pbVar10 + 2;
          copy3(pbVar12 + -(int)local_8,unaff_EDI,unaff_ESI);
          param_1 = param_1 + 6 + (int)puVar6;
          cVar2 = (char)param_1;
LAB_00585ad7:
          *(char *)param_2 = cVar2 + -3;
          *pbVar12 = *local_8;
          pbVar12 = pbVar12 + 1;
          local_8 = local_8 + 1;
          goto LAB_00585c50;
        }
      }
      *pbVar12 = *local_8;
      pbVar12[1] = local_8[1];
      pbVar12 = pbVar12 + 2;
      local_8 = local_8 + 2;
      do {
        *pbVar12 = *local_8;
        pbVar12 = pbVar12 + 1;
        local_8 = local_8 + 1;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
LAB_0058598d:
    do {
      pbVar13 = pbVar12;
      pbVar11 = pbVar9;
      local_c = (uchar *)0xffffffff;
      *pbVar13 = *pbVar11;
      pbVar12 = pbVar13 + 1;
      puVar6 = puVar6 + -1;
      pbVar9 = pbVar11 + 1;
    } while (puVar6 != (uchar *)0x0);
    bVar5 = pbVar11[1];
    puVar6 = (uchar *)(uint)bVar5;
    pbVar10 = pbVar11 + 2;
    if (pbVar3 <= pbVar10) goto LAB_00585ccb;
    pbVar9 = pbVar10;
    if (param_3 + uVar1 < pbVar12) goto LAB_005858d0;
    if ((uchar *)0xf < puVar6) goto LAB_00585a3e;
    pbVar4 = pbVar12 + ((uint)*pbVar10 * -4 - (uint)(bVar5 >> 2));
    local_8 = pbVar4 + -1;
    pbVar9 = pbVar11 + 3;
    if ((param_2 == 0) || ((pbVar11[1] & 3) != 0)) {
LAB_00585a2e:
      *pbVar12 = *local_8;
      pbVar13[2] = *pbVar4;
      pbVar12 = pbVar13 + 3;
      goto LAB_0058596a;
    }
    bVar5 = *pbVar9;
    if (param_1 != (uchar *)0x1) {
      if (bVar5 < 0x10) goto LAB_00585a17;
      goto LAB_00585a2e;
    }
    if (0xf < bVar5) {
      *(byte *)param_2 = *(byte *)param_2 | 3;
      local_c = (uchar *)0x0;
      pbVar11[1] = *local_8;
      param_1 = (uchar *)0x3;
      if ((int)pbVar12 - (int)local_8 == 1) {
        bVar5 = *local_8;
      }
      else {
        bVar5 = *pbVar4;
      }
      pbVar11[2] = bVar5;
      goto LAB_00585a2e;
    }
LAB_00585a17:
    if ((bVar5 == 0) || ((uchar *)0xf < param_1 + bVar5 + 2)) goto LAB_00585a2e;
    puVar6 = (uchar *)(uint)*pbVar9;
    *(byte *)param_2 = *(byte *)param_2 & 0xfc;
    pbVar10 = pbVar11 + 4;
    pbVar11[2] = *local_8;
    if ((int)pbVar12 - (int)local_8 == 1) {
      bVar5 = *local_8;
    }
    else {
      bVar5 = *pbVar4;
    }
    _Src = (char *)(param_2 + 2);
    pbVar11[3] = bVar5;
    if (param_1 != (uchar *)0x0) {
      memmove((void *)(param_2 + 3),_Src,(size_t)param_1);
    }
    param_1 = param_1 + 5 + (int)puVar6;
    *_Src = (char)param_1 + -3;
    param_2 = (ulong)_Src;
LAB_00585c50:
    *pbVar12 = *local_8;
    pbVar12[1] = local_8[1];
    pbVar12 = pbVar12 + 2;
LAB_00585915:
    *pbVar12 = *pbVar10;
    pbVar12[1] = pbVar10[1];
    pbVar12[2] = pbVar10[2];
    pbVar9 = pbVar10 + 3;
    pbVar12 = pbVar12 + 3;
  } while( true );
}
