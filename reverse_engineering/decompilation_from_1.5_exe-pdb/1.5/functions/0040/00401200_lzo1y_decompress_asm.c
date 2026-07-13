/*
 * Entry: 00401200
 * Name: lzo1y_decompress_asm
 * Namespace: Global
 * Signature: undefined lzo1y_decompress_asm()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* lzo1y_decompress_asm */

undefined8 __cdecl lzo1y_decompress_asm(byte *param_1,int param_2,byte *param_3,int *param_4)

{
  uint uVar1;
  undefined4 uVar2;
  ushort uVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 in_EDX;
  byte *pbVar8;
  uint uVar9;
  undefined3 uVar10;
  ushort *puVar11;
  ushort *puVar12;
  byte *pbVar13;
  
  uVar9 = 0;
  puVar11 = (ushort *)(param_1 + 1);
  bVar4 = *param_1;
  pbVar13 = param_3;
  if (bVar4 < 0x12) goto LAB_00401243;
  uVar6 = (uint)(byte)(bVar4 - 0x11);
  uVar7 = uVar6;
  puVar12 = puVar11;
  if (3 < (byte)(bVar4 - 0x11)) goto LAB_0040124e;
LAB_00401262:
  for (; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pbVar13 = (byte)*puVar12;
    puVar12 = (ushort *)((int)puVar12 + 1);
    pbVar13 = pbVar13 + 1;
  }
  uVar6 = CONCAT31((int3)(uVar6 >> 8),(byte)*puVar12);
  puVar11 = (ushort *)((int)puVar12 + 1);
  if (0xf < (byte)*puVar12) goto LAB_00401290;
  uVar9 = CONCAT31((int3)(uVar9 >> 8),*(byte *)puVar11);
  puVar12 = puVar12 + 1;
  pbVar8 = pbVar13 + (-0x401 - ((uVar6 >> 2) + uVar9 * 4));
  *pbVar13 = *pbVar8;
  pbVar13[1] = pbVar8[1];
  pbVar13[2] = pbVar8[2];
  pbVar13 = pbVar13 + 3;
LAB_00401307:
  do {
    uVar6 = (byte)puVar12[-1] & 3;
    if (((byte)puVar12[-1] & 3) == 0) {
      bVar4 = (byte)*puVar12;
      puVar11 = (ushort *)((int)puVar12 + 1);
LAB_00401243:
      uVar6 = (uint)bVar4;
      if (bVar4 < 0x10) break;
    }
    else {
      do {
        puVar11 = puVar12;
        *pbVar13 = (byte)*puVar11;
        pbVar13 = pbVar13 + 1;
        uVar6 = uVar6 - 1;
        puVar12 = (ushort *)((int)puVar11 + 1);
      } while (uVar6 != 0);
      uVar6 = (uint)*(byte *)((int)puVar11 + 1);
      puVar11 = puVar11 + 1;
    }
LAB_00401290:
    bVar4 = (byte)uVar6;
    uVar10 = (undefined3)(uVar9 >> 8);
    if (bVar4 < 0x40) {
      if (bVar4 < 0x20) {
        if (bVar4 < 0x10) {
          uVar3 = *puVar11;
          puVar12 = (ushort *)((int)puVar11 + 1);
          *pbVar13 = pbVar13[-1 - ((uVar6 >> 2) + CONCAT31(uVar10,(byte)uVar3) * 4)];
          bVar4 = (pbVar13 + (-1 - ((uVar6 >> 2) + CONCAT31(uVar10,(byte)uVar3) * 4)))[1];
          uVar9 = CONCAT31(uVar10,bVar4);
          pbVar13[1] = bVar4;
          pbVar13 = pbVar13 + 2;
          goto LAB_00401307;
        }
        iVar5 = 0;
        if ((uVar6 & 7) == 0) {
          while( true ) {
            uVar3 = *puVar11;
            puVar11 = (ushort *)((int)puVar11 + 1);
            uVar9 = CONCAT31((int3)(uVar9 >> 8),(byte)uVar3);
            if ((byte)uVar3 != 0) break;
            iVar5 = iVar5 + 0xff;
          }
          uVar7 = uVar9 + 9 + iVar5;
        }
        else {
          uVar7 = (uVar6 & 7) + 2;
        }
        uVar9 = CONCAT22((short)(((uVar6 & 8) << 0xd) >> 0x10),*puVar11);
        puVar12 = puVar11 + 1;
        uVar6 = uVar9 >> 2;
        if (uVar6 == 0) {
          iVar5 = CONCAT31((uint3)(uVar9 >> 10),uVar7 != 3);
          if (param_1 + param_2 < puVar12) {
            iVar5 = 4;
          }
          else if (puVar12 < param_1 + param_2) {
            iVar5 = 8;
          }
          *param_4 = (int)pbVar13 - (int)param_3;
          return CONCAT44(in_EDX,-iVar5);
        }
        pbVar8 = pbVar13 + (-0x4000 - uVar6);
      }
      else {
        iVar5 = 0;
        if ((uVar6 & 0x1f) == 0) {
          while( true ) {
            uVar3 = *puVar11;
            puVar11 = (ushort *)((int)puVar11 + 1);
            uVar9 = CONCAT31((int3)(uVar9 >> 8),(byte)uVar3);
            if ((byte)uVar3 != 0) break;
            iVar5 = iVar5 + 0xff;
          }
          uVar7 = iVar5 + 0x21 + uVar9;
        }
        else {
          uVar7 = (uVar6 & 0x1f) + 2;
        }
        puVar12 = puVar11 + 1;
        pbVar8 = pbVar13 + (-1 - (uint)(*puVar11 >> 2));
        if (*puVar11 >> 2 < 3) goto code_r0x0040132a;
      }
LAB_004012e6:
      uVar9 = uVar7 >> 2;
      if (uVar9 != 0) {
        do {
          uVar2 = *(undefined4 *)pbVar8;
          pbVar8 = pbVar8 + 4;
          *(undefined4 *)pbVar13 = uVar2;
          pbVar13 = pbVar13 + 4;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
        uVar7 = uVar7 & 3;
        uVar9 = 0;
        if (uVar7 == 0) goto LAB_00401307;
      }
      do {
        bVar4 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        *pbVar13 = bVar4;
        pbVar13 = pbVar13 + 1;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
      goto LAB_00401307;
    }
    uVar9 = CONCAT31(uVar10,(byte)*puVar11);
    uVar1 = (uVar6 >> 2 & 3) + uVar9 * 4;
    puVar12 = (ushort *)((int)puVar11 + 1);
    pbVar8 = pbVar13 + (-1 - uVar1);
    uVar7 = (uVar6 >> 4) - 1;
    if (2 < uVar1) goto LAB_004012e6;
code_r0x0040132a:
    for (; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pbVar13 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar13 = pbVar13 + 1;
    }
  } while( true );
  iVar5 = 0;
  if (bVar4 == 0) {
    while( true ) {
      uVar3 = *puVar11;
      puVar11 = (ushort *)((int)puVar11 + 1);
      uVar9 = CONCAT31((int3)(uVar9 >> 8),(byte)uVar3);
      if ((byte)uVar3 != 0) break;
      iVar5 = iVar5 + 0xff;
    }
    uVar6 = iVar5 + 0x12 + uVar9;
  }
  else {
    uVar6 = uVar6 + 3;
  }
LAB_0040124e:
  uVar7 = uVar6 & 3;
  uVar6 = uVar6 >> 2;
  do {
    uVar2 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 2;
    *(undefined4 *)pbVar13 = uVar2;
    pbVar13 = pbVar13 + 4;
    uVar6 = uVar6 - 1;
    puVar12 = puVar11;
  } while (uVar6 != 0);
  goto LAB_00401262;
}
