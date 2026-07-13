
undefined4 FUN_007859d0(undefined4 param_1)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  undefined4 uVar7;
  float10 fVar8;
  undefined2 *local_10;
  
  iVar1 = FUN_00786340();
  iVar6 = DAT_02c319e0;
  if (iVar1 == 0) {
    if ((DAT_02c319d8 == (undefined2 *)0x0) && (DAT_02c319e0 != 0)) {
      sVar2 = DAT_02c319e0 * 0x20000 + 0xc;
      fVar8 = (float10)FUN_00787b60(&DAT_0089d064,"Height",0,&DAT_02cc40c0);
      iVar1 = FUN_00787ac0(&DAT_0089d064,"Width",0xffffffff,&DAT_02cc40c0);
      iVar3 = FUN_00787ac0(&DAT_0089d064,"Depth",0xffffffff,&DAT_02cc40c0);
      if (DAT_009454b8 == 0) {
        iVar4 = FUN_007d6950("Terrain height file \"%s.hgt\" not found",param_1);
        if (iVar4 == 0) {
          return 0;
        }
      }
      else {
        FUN_007d6c70("Terrain height file \"%s.hgt\" not found\nFilling terrain with default height\n"
                     ,param_1);
      }
      DAT_02c319dc = sVar2;
      puVar5 = malloc(sVar2);
      DAT_02c319d8 = puVar5;
      *puVar5 = 1;
      puVar5[1] = 8;
      puVar5[2] = (short)(iVar1 >> ((byte)puVar5[1] & 0x1f));
      puVar5[3] = (short)(iVar3 >> ((byte)puVar5[1] & 0x1f));
      *(undefined4 *)(puVar5 + 4) = 10;
      puVar5 = DAT_02c319d8 + iVar6 * 0x10000 + 6;
      for (local_10 = DAT_02c319d8 + 2; local_10 < puVar5; local_10 = local_10 + 1) {
        *local_10 = (short)(int)((float)fVar8 / 0.1);
      }
    }
    if ((DAT_02c319d0 == (void *)0x0) && (DAT_02c319e0 != 0)) {
      sVar2 = DAT_02c319e0 << 0xd;
      if (DAT_009454b8 == 0) {
        iVar6 = FUN_007d6950("Terrain material file \"%s.mat\" not found",param_1);
        if (iVar6 == 0) {
          return 0;
        }
      }
      else {
        FUN_007d6c70("Terrain material file \"%s.mat\" not found\nFilling terrain with default material\n"
                     ,param_1);
      }
      DAT_02c319d4 = sVar2;
      DAT_02c319d0 = malloc(sVar2);
      memset(DAT_02c319d0,0,sVar2);
    }
  }
  if ((DAT_02c319d8 == (undefined2 *)0x0) || (DAT_02c319d0 == (void *)0x0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = 1;
  }
  return uVar7;
}

