
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0069f030(void)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  void *pvVar6;
  undefined1 *puVar7;
  size_t sVar8;
  undefined1 local_a4;
  undefined1 local_9c;
  size_t local_88;
  ushort *local_74;
  int local_64;
  int local_60;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00920c9a == '\0') {
    sVar8 = 0x9c;
    iVar2 = FUN_006a4030();
    DAT_02ceb7e8 = (int)calloc(DAT_009310c4 + 1 + iVar2,sVar8);
    DAT_02ceb7e0 = (int)calloc(0x10000,4);
    DAT_02ceb7f0 = (int)calloc(0x10000,4);
    DAT_02ceb7fc = 1;
    DAT_02ceb800 = 1;
    for (local_60 = 0; local_60 < 0x10000; local_60 = local_60 + 1) {
      *(undefined4 *)(DAT_02ceb7e0 + local_60 * 4) = 0;
    }
    for (local_60 = 0; local_60 < 0x10000; local_60 = local_60 + 1) {
      *(undefined4 *)(DAT_02ceb7f0 + local_60 * 4) = 0;
    }
    for (local_60 = 0; iVar2 = FUN_006a4030(), local_60 < iVar2; local_60 = local_60 + 1) {
      iVar2 = FUN_006a4040(local_60);
      if (*(int *)(DAT_02ceb7e0 + (uint)*(ushort *)(iVar2 + 0x5a) * 4) == 0) {
        if (*(short *)(iVar2 + 0x5c) != 0) {
          if (*(int *)(DAT_02ceb7f0 + (uint)*(ushort *)(iVar2 + 0x5c) * 4) == 0) {
            *(int *)(DAT_02ceb7f0 + (uint)*(ushort *)(iVar2 + 0x5c) * 4) = DAT_02ceb800;
            *(ushort *)(iVar2 + 0x5c) = (ushort)DAT_02ceb800;
            DAT_02ceb800 = DAT_02ceb800 + 1;
          }
          else {
            *(undefined2 *)(iVar2 + 0x5c) =
                 *(undefined2 *)(DAT_02ceb7f0 + (uint)*(ushort *)(iVar2 + 0x5c) * 4);
          }
        }
        *(int *)(DAT_02ceb7e0 + (uint)*(ushort *)(iVar2 + 0x5a) * 4) = DAT_02ceb7fc;
        *(ushort *)(iVar2 + 0x5a) = (ushort)DAT_02ceb7fc;
        DAT_02ceb7fc = DAT_02ceb7fc + 1;
      }
      else {
        FUN_006a5f50(2,"Duplicate Unit Prereqtype Found : %d",*(undefined2 *)(iVar2 + 0x5a));
        *(undefined2 *)(iVar2 + 0x5a) =
             *(undefined2 *)(DAT_02ceb7e0 + (uint)*(ushort *)(iVar2 + 0x5a) * 4);
      }
    }
    _DAT_02ceb7f4 = DAT_02ceb7fc;
    for (local_60 = 0; local_60 < DAT_009310c4; local_60 = local_60 + 1) {
      puVar3 = (ushort *)(local_60 * 0x80 + DAT_0093101c);
      if (*(int *)(DAT_02ceb7e0 + (uint)*puVar3 * 4) == 0) {
        if (puVar3[6] != 0) {
          if (*(int *)(DAT_02ceb7f0 + (uint)puVar3[6] * 4) == 0) {
            *(int *)(DAT_02ceb7f0 + (uint)puVar3[6] * 4) = DAT_02ceb800;
            puVar3[6] = (ushort)DAT_02ceb800;
            DAT_02ceb800 = DAT_02ceb800 + 1;
          }
          else {
            puVar3[6] = *(ushort *)(DAT_02ceb7f0 + (uint)puVar3[6] * 4);
          }
        }
        *(int *)(DAT_02ceb7e0 + (uint)*puVar3 * 4) = DAT_02ceb7fc;
        *puVar3 = (ushort)DAT_02ceb7fc;
        DAT_02ceb7fc = DAT_02ceb7fc + 1;
      }
      else {
        FUN_006a5f50(2,"Duplicate Building Prereqtype Found : %d",*puVar3);
        *puVar3 = *(ushort *)(DAT_02ceb7e0 + (uint)*puVar3 * 4);
      }
    }
    free((void *)DAT_02ceb7f0);
    DAT_02ceb7ec = (int)calloc(DAT_02ceb800,4);
    for (local_60 = 0; local_60 < DAT_02ceb800; local_60 = local_60 + 1) {
      *(undefined4 *)(DAT_02ceb7ec + local_60 * 4) = 0;
    }
    for (local_60 = 0; iVar2 = FUN_006a4030(), local_60 < iVar2; local_60 = local_60 + 1) {
      iVar2 = FUN_006a4040(local_60);
      uVar1 = *(ushort *)(iVar2 + 0x5c);
      if (uVar1 != 0) {
        puVar4 = malloc(8);
        puVar4[1] = (ushort)*(byte *)(iVar2 + 0x58);
        *puVar4 = *(undefined2 *)(iVar2 + 0x5a);
        *(undefined4 *)(puVar4 + 2) = *(undefined4 *)(DAT_02ceb7ec + (uint)uVar1 * 4);
        *(undefined2 **)(DAT_02ceb7ec + (uint)uVar1 * 4) = puVar4;
      }
    }
    for (local_60 = 0; local_60 < DAT_009310c4; local_60 = local_60 + 1) {
      puVar4 = (undefined2 *)(local_60 * 0x80 + DAT_0093101c);
      uVar1 = puVar4[6];
      if (uVar1 != 0) {
        puVar5 = malloc(8);
        puVar5[1] = (ushort)(*(uint *)(puVar4 + 0x12) >> 2) & 0xff;
        *puVar5 = *puVar4;
        *(undefined4 *)(puVar5 + 2) = *(undefined4 *)(DAT_02ceb7ec + (uint)uVar1 * 4);
        *(undefined2 **)(DAT_02ceb7ec + (uint)uVar1 * 4) = puVar5;
      }
    }
    for (local_60 = 0; iVar2 = FUN_006a4030(), local_60 < iVar2; local_60 = local_60 + 1) {
      iVar2 = FUN_006a4040(local_60);
      uVar1 = *(ushort *)(iVar2 + 0x5a);
      *(undefined1 *)(DAT_02ceb7e8 + (uint)uVar1 * 0x9c) = 0;
      *(int *)(DAT_02ceb7e8 + 4 + (uint)uVar1 * 0x9c) = iVar2;
      *(undefined1 *)(DAT_02ceb7e8 + 8 + (uint)uVar1 * 0x9c) = *(undefined1 *)(iVar2 + 0x58);
      *(undefined4 *)(DAT_02ceb7e8 + 0x18 + (uint)uVar1 * 0x9c) =
           *(undefined4 *)(DAT_02ceb7ec + (uint)*(ushort *)(iVar2 + 0x5c) * 4);
      pvVar6 = calloc(5,2);
      *(void **)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) = pvVar6;
      for (local_64 = 0; local_64 < 4; local_64 = local_64 + 1) {
        *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2) =
             *(undefined2 *)(DAT_02ceb7e0 + (uint)*(ushort *)(iVar2 + 0x5e + local_64 * 2) * 4);
        *(undefined2 *)(iVar2 + 0x5e + local_64 * 2) =
             *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2);
      }
      *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2) = 0;
      pvVar6 = calloc(5,2);
      *(void **)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) = pvVar6;
      for (local_64 = 0; local_64 < 4; local_64 = local_64 + 1) {
        *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2) =
             *(undefined2 *)(DAT_02ceb7e0 + (uint)*(ushort *)(iVar2 + 0x66 + local_64 * 2) * 4);
        *(undefined2 *)(iVar2 + 0x66 + local_64 * 2) =
             *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2);
      }
      *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2) = 0;
      for (local_64 = 0; local_64 < 0x10; local_64 = local_64 + 1) {
        *(undefined4 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x1c + local_64 * 4) = 0;
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x6c + local_64) = 0;
        if (((*(uint *)(&DAT_02ce9b10 + local_64 * 0x1e0) == (uint)*(byte *)(iVar2 + 0x58)) ||
            (*(byte *)(iVar2 + 0x58) == 0xffffffff)) &&
           (**(short **)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) != 0)) {
          local_9c = 1;
        }
        else {
          local_9c = 0;
        }
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x7c + local_64) = local_9c;
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x8c + local_64) = 0;
      }
    }
    for (local_60 = 0; local_60 < DAT_009310c4; local_60 = local_60 + 1) {
      puVar3 = (ushort *)(local_60 * 0x80 + DAT_0093101c);
      uVar1 = *puVar3;
      *(undefined1 *)(DAT_02ceb7e8 + (uint)uVar1 * 0x9c) = 1;
      *(ushort **)(DAT_02ceb7e8 + 4 + (uint)uVar1 * 0x9c) = puVar3;
      *(char *)(DAT_02ceb7e8 + 8 + (uint)uVar1 * 0x9c) = (char)(*(uint *)(puVar3 + 0x12) >> 2);
      *(undefined4 *)(DAT_02ceb7e8 + 0x18 + (uint)uVar1 * 0x9c) =
           *(undefined4 *)(DAT_02ceb7ec + (uint)puVar3[6] * 4);
      pvVar6 = calloc(5,2);
      *(void **)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) = pvVar6;
      for (local_64 = 0; local_64 < 4; local_64 = local_64 + 1) {
        *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2) =
             *(undefined2 *)(DAT_02ceb7e0 + (uint)puVar3[local_64 + 7] * 4);
        puVar3[local_64 + 7] =
             *(ushort *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2);
      }
      *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0xc + (uint)uVar1 * 0x9c) + local_64 * 2) = 0;
      pvVar6 = calloc(5,2);
      *(void **)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) = pvVar6;
      for (local_64 = 0; local_64 < 4; local_64 = local_64 + 1) {
        *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2) =
             *(undefined2 *)(DAT_02ceb7e0 + (uint)puVar3[local_64 + 0xb] * 4);
        puVar3[local_64 + 0xb] =
             *(ushort *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2);
      }
      *(undefined2 *)(*(int *)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) + local_64 * 2) = 0;
      for (local_64 = 0; local_64 < 0x10; local_64 = local_64 + 1) {
        *(undefined4 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x1c + local_64 * 4) = 0;
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x6c + local_64) = 0;
        if (((*(uint *)(&DAT_02ce9b10 + local_64 * 0x1e0) == (*(uint *)(puVar3 + 0x12) >> 2 & 0xff))
            || ((*(uint *)(DAT_0093101c + 0x24 + local_60 * 0x80) >> 2 & 0xff) == 0xffffffff)) &&
           (**(short **)(DAT_02ceb7e8 + 0x14 + (uint)uVar1 * 0x9c) != 0)) {
          local_a4 = 1;
        }
        else {
          local_a4 = 0;
        }
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x7c + local_64) = local_a4;
        *(undefined1 *)((uint)uVar1 * 0x9c + DAT_02ceb7e8 + 0x8c + local_64) = 0;
      }
    }
    free((void *)DAT_02ceb7e0);
    for (local_60 = 1; local_60 < DAT_02ceb7fc; local_60 = local_60 + 1) {
      for (local_74 = *(ushort **)(DAT_02ceb7e8 + 0x14 + local_60 * 0x9c); *local_74 != 0;
          local_74 = local_74 + 1) {
        if (*(char *)(DAT_02ceb7e8 + (uint)*local_74 * 0x9c) == '\0') {
          iVar2 = *(int *)(DAT_02ceb7e8 + 4 + (uint)*local_74 * 0x9c);
          *(uint *)(iVar2 + 0x70) = *(uint *)(iVar2 + 0x70) | 2;
        }
      }
    }
    sVar8 = 2;
    iVar2 = FUN_006a4030();
    DAT_02ceb7f8 = calloc(DAT_009310c4 + 1 + iVar2,sVar8);
    for (local_60 = 1; local_60 < DAT_02ceb7fc; local_60 = local_60 + 1) {
      DAT_02ceb7e4 = DAT_02ceb7f8;
      for (local_74 = *(ushort **)(DAT_02ceb7e8 + 0xc + local_60 * 0x9c); *local_74 != 0;
          local_74 = local_74 + 1) {
        FUN_006a0350(*local_74,&DAT_02ceb7e4);
      }
      *DAT_02ceb7e4 = 0;
      DAT_02ceb7e4 = DAT_02ceb7e4 + 1;
      FUN_006a03c0(DAT_02ceb7f8);
      local_88 = 1;
      for (DAT_02ceb7e4 = DAT_02ceb7f8; *DAT_02ceb7e4 != 0; DAT_02ceb7e4 = DAT_02ceb7e4 + 1) {
        local_88 = local_88 + 1;
      }
      pvVar6 = calloc(local_88,2);
      *(void **)(DAT_02ceb7e8 + 0x10 + local_60 * 0x9c) = pvVar6;
      memcpy(*(void **)(DAT_02ceb7e8 + 0x10 + local_60 * 0x9c),DAT_02ceb7f8,local_88 << 1);
    }
    free(DAT_02ceb7f8);
    DAT_00920c9a = '\x01';
    FUN_006a3a70(local_58);
    while (iVar2 = FUN_006a3b60(local_58), iVar2 != 0) {
      FUN_0069fff0(*(undefined2 *)(*(int *)(iVar2 + 8) + 0x5a),*(undefined1 *)(iVar2 + 0x10));
    }
    FUN_006a3c10(local_58);
    while (puVar7 = (undefined1 *)FUN_006a3c70(local_58), puVar7 != (undefined1 *)0x0) {
      FUN_0069fff0(**(undefined2 **)(puVar7 + 0x14),*puVar7);
    }
  }
  FUN_0083e885();
  return;
}

