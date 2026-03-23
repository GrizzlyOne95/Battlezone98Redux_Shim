
int FUN_0082afb0(ushort *param_1,int param_2,byte *param_3,int *param_4)

{
  ushort *puVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  
  puVar1 = (ushort *)((int)param_1 + param_2);
  *param_4 = 0;
  uVar3 = *param_1;
  pbVar9 = param_3;
  if ((byte)uVar3 < 0x12) goto LAB_0082afef;
  param_1 = (ushort *)((int)param_1 + 1);
  uVar7 = (byte)uVar3 - 0x11;
  pbVar10 = param_3;
  if (uVar7 < 4) goto LAB_0082b1d1;
  do {
    uVar3 = *param_1;
    param_1 = (ushort *)((int)param_1 + 1);
    *pbVar9 = (byte)uVar3;
    pbVar9 = pbVar9 + 1;
    uVar7 = uVar7 - 1;
  } while (uVar7 != 0);
LAB_0082b05a:
  uVar3 = *param_1;
  uVar7 = (uint)(byte)uVar3;
  puVar8 = (ushort *)((int)param_1 + 1);
  if (0xf < uVar7) goto LAB_0082b098;
  param_1 = param_1 + 1;
  iVar6 = (uint)*(byte *)puVar8 * -4 - (uint)(byte)((byte)uVar3 >> 2);
  *pbVar9 = pbVar9[iVar6 + -0x401];
  pbVar9[1] = pbVar9[iVar6 + -0x400];
  pbVar9[2] = pbVar9[iVar6 + -0x3ff];
  pbVar9 = pbVar9 + 3;
LAB_0082b1c4:
  uVar7 = (byte)param_1[-1] & 3;
  pbVar10 = pbVar9;
  if (((byte)param_1[-1] & 3) == 0) {
LAB_0082afef:
    uVar7 = (uint)(byte)*param_1;
    puVar8 = (ushort *)((int)param_1 + 1);
    if (uVar7 < 0x10) goto code_r0x0082affc;
  }
  else {
LAB_0082b1d1:
    puVar8 = (ushort *)((int)param_1 + 1);
    *pbVar10 = (byte)*param_1;
    pbVar9 = pbVar10 + 1;
    if (1 < uVar7) {
      bVar2 = *(byte *)puVar8;
      puVar8 = param_1 + 1;
      *pbVar9 = bVar2;
      pbVar9 = pbVar10 + 2;
      if (2 < uVar7) {
        *pbVar9 = (byte)*puVar8;
        pbVar9 = pbVar10 + 3;
        puVar8 = (ushort *)((int)param_1 + 3);
      }
    }
    uVar7 = (uint)(byte)*puVar8;
    puVar8 = (ushort *)((int)puVar8 + 1);
  }
LAB_0082b098:
  if (uVar7 < 0x40) {
    if (uVar7 < 0x20) {
      if (0xf < uVar7) {
        uVar5 = uVar7 & 7;
        if (uVar5 == 0) {
          iVar6 = 0;
          bVar2 = (byte)*puVar8;
          while (bVar2 == 0) {
            puVar8 = (ushort *)((int)puVar8 + 1);
            iVar6 = iVar6 + 0xff;
            bVar2 = *(byte *)puVar8;
          }
          uVar5 = iVar6 + 7 + (uint)(byte)*puVar8;
          puVar8 = (ushort *)((int)puVar8 + 1);
        }
        param_1 = puVar8 + 1;
        if (pbVar9 + ((uVar7 & 8) * -0x800 - (uint)(*puVar8 >> 2)) == pbVar9) {
          *param_4 = (int)pbVar9 - (int)param_3;
          if (param_1 == puVar1) {
            return 0;
          }
          return (-(uint)(param_1 < puVar1) & 0xfffffffc) - 4;
        }
        pbVar10 = pbVar9 + ((uVar7 & 8) * -0x800 - (uint)(*puVar8 >> 2)) + -0x4000;
        goto LAB_0082b15f;
      }
      uVar3 = *puVar8;
      param_1 = (ushort *)((int)puVar8 + 1);
      *pbVar9 = (pbVar9 + ((uint)(byte)uVar3 * -4 - (uVar7 >> 2)))[-1];
      pbVar9[1] = pbVar9[(uint)(byte)uVar3 * -4 - (uVar7 >> 2)];
      pbVar9 = pbVar9 + 2;
    }
    else {
      uVar5 = uVar7 & 0x1f;
      if (uVar5 == 0) {
        iVar6 = 0;
        if ((byte)*puVar8 == 0) {
          iVar6 = 0;
          do {
            puVar8 = (ushort *)((int)puVar8 + 1);
            iVar6 = iVar6 + 0xff;
          } while (*(byte *)puVar8 == 0);
        }
        uVar5 = iVar6 + 0x1f + (uint)(byte)*puVar8;
        puVar8 = (ushort *)((int)puVar8 + 1);
      }
      pbVar10 = pbVar9 + (-1 - (uint)(*puVar8 >> 2));
      param_1 = puVar8 + 1;
LAB_0082b15f:
      if ((uVar5 < 6) || ((int)pbVar9 - (int)pbVar10 < 4)) goto LAB_0082b0b9;
      pbVar11 = pbVar10 + 4;
      *(undefined4 *)pbVar9 = *(undefined4 *)pbVar10;
      pbVar9 = pbVar9 + 4;
      uVar5 = uVar5 - 2;
      do {
        uVar5 = uVar5 - 4;
        *(undefined4 *)pbVar9 = *(undefined4 *)pbVar11;
        pbVar11 = pbVar11 + 4;
        pbVar9 = pbVar9 + 4;
      } while (3 < uVar5);
      for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        bVar2 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        *pbVar9 = bVar2;
        pbVar9 = pbVar9 + 1;
      }
    }
  }
  else {
    param_1 = (ushort *)((int)puVar8 + 1);
    pbVar10 = pbVar9 + ((uint)(byte)*puVar8 * -4 - (uVar7 >> 2 & 3)) + -1;
    uVar5 = (uVar7 >> 4) - 3;
LAB_0082b0b9:
    *pbVar9 = *pbVar10;
    pbVar9[1] = pbVar10[1];
    pbVar9 = pbVar9 + 2;
    pbVar10 = pbVar10 + 2;
    do {
      bVar2 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      *pbVar9 = bVar2;
      pbVar9 = pbVar9 + 1;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  goto LAB_0082b1c4;
code_r0x0082affc:
  if (uVar7 == 0) {
    iVar6 = 0;
    iVar4 = 0;
    if (*(byte *)puVar8 == (byte)*param_1) {
      do {
        puVar8 = (ushort *)((int)puVar8 + 1);
        iVar6 = iVar6 + 0xff;
        iVar4 = iVar6;
      } while (*(byte *)puVar8 == 0);
    }
    uVar7 = iVar4 + 0xf + (uint)(byte)*puVar8;
    puVar8 = (ushort *)((int)puVar8 + 1);
  }
  param_1 = puVar8 + 2;
  *(undefined4 *)pbVar9 = *(undefined4 *)puVar8;
  pbVar9 = pbVar9 + 4;
  uVar7 = uVar7 - 1;
  if (uVar7 != 0) {
    if (uVar7 < 4) {
      do {
        uVar3 = *param_1;
        param_1 = (ushort *)((int)param_1 + 1);
        *pbVar9 = (byte)uVar3;
        pbVar9 = pbVar9 + 1;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
    else {
      do {
        uVar7 = uVar7 - 4;
        *(undefined4 *)pbVar9 = *(undefined4 *)param_1;
        param_1 = param_1 + 2;
        pbVar9 = pbVar9 + 4;
      } while (3 < uVar7);
      for (; uVar7 != 0; uVar7 = uVar7 - 1) {
        uVar3 = *param_1;
        param_1 = (ushort *)((int)param_1 + 1);
        *pbVar9 = (byte)uVar3;
        pbVar9 = pbVar9 + 1;
      }
    }
  }
  goto LAB_0082b05a;
}

