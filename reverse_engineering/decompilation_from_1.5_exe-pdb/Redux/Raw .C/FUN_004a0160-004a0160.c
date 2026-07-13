
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004a0160(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  int local_1c;
  int local_18;
  int local_10;
  
  uVar2 = DAT_008e7732;
  if (DAT_009454b8 != 0) {
    DAT_008e7732 = 0;
    iVar3 = FUN_00481f10("build.odf");
    if (iVar3 == 0) {
      _DAT_009174dc = calloc(10,0x20);
      FUN_0049f5c0(_DAT_009174dc,0x6d615f62,0x74626d63);
      FUN_0049f5c0((int)_DAT_009174dc + 0x20,0x6d615f62,0x646f7270);
      FUN_0049f5c0((int)_DAT_009174dc + 0x40,0x6d615f62,0x67646c62);
      FUN_0049f5c0((int)_DAT_009174dc + 0x60,0x6d615f62,0x6e676973);
      FUN_0049f5c0((int)_DAT_009174dc + 0x80,0x6f735f62,0x74626d63);
      FUN_0049f5c0((int)_DAT_009174dc + 0xa0,0x6f735f62,0x646f7270);
      FUN_0049f5c0((int)_DAT_009174dc + 0xc0,0x6f735f62,0x67646c62);
      FUN_0049f5c0((int)_DAT_009174dc + 0xe0,0x6f735f62,0x6e676973);
      FUN_0049f5c0((int)_DAT_009174dc + 0x100,0x656e5f62,0x67646c62);
    }
    else {
      FUN_0049f5c0(&DAT_009174c4,0x6c697562,100);
    }
  }
  DAT_008e7732 = uVar2;
  for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
    *(undefined4 *)(param_1 + 0x102c + local_10 * 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1030 + local_10 * 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1034 + local_10 * 0x18) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x1038 + local_10 * 0x18) = 0xf149f2ca;
    *(undefined4 *)(param_1 + 0x103c + local_10 * 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1040 + local_10 * 0x18) = 0xf149f2ca;
  }
  *(undefined4 *)(param_1 + 0x111c) = 0x1d;
  *(undefined4 *)(param_1 + 0x1120) = 0;
  *(undefined4 *)(param_1 + 0x1124) = 0;
  *(undefined4 *)(param_1 + 0x1128) = 0;
  *(undefined4 *)(param_1 + 0x112c) = 0x1d;
  *(undefined4 *)(param_1 + 0x1130) = 0;
  *(undefined4 *)(param_1 + 0x1134) = 0;
  *(undefined4 *)(param_1 + 0x1138) = 0;
  *(undefined4 *)(param_1 + 0x1178) = 0;
  *(undefined4 *)(param_1 + 0x1194) = 0;
  *(undefined4 *)(param_1 + 0x1198) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x119c) = 0;
  *(undefined4 *)(param_1 + 0x117c) = 0xffffffff;
  *(undefined **)(param_1 + 0x1180) = &DAT_009174c4;
  *(undefined4 *)(param_1 + 0x1174) = 0;
  *(undefined4 *)(param_1 + 0x1184) = 0;
  *(undefined4 *)(param_1 + 0x1188) = 0;
  *(undefined4 *)(param_1 + 0x118c) = 0;
  *(undefined4 *)(param_1 + 0x1190) = 0xf;
  for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
    for (local_18 = 0; local_18 < *(int *)(param_1 + 0xfc4 + local_10 * 4); local_18 = local_18 + 1)
    {
      uVar4 = FUN_004cf880(*(undefined4 *)(param_1 + 0x18c + local_10 * 0x16c + local_18 * 4));
      *(undefined4 *)(param_1 + 0x18c + local_10 * 0x16c + local_18 * 4) = uVar4;
    }
  }
  *(undefined4 *)(param_1 + 0x1170) = 0;
  *(undefined4 *)(param_1 + 0x11a0) = 2;
  iVar3 = FUN_00462370();
  if (iVar3 == 0) {
    FUN_005e0bc0(1);
  }
  iVar3 = FUN_005e0f70(1);
  if (iVar3 != 0) {
    *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x10;
    iVar3 = (*(code *)**(undefined4 **)(iVar3 + 0x18))();
    for (local_1c = 0; local_1c < 9; local_1c = local_1c + 1) {
      iVar1 = *(int *)(iVar3 + 0x608 + local_1c * 4);
      if (iVar1 != 0) {
        iVar1 = *(int *)(iVar1 + 0x14);
        if (iVar1 == 0x41524d52) {
          *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x40;
        }
        else if (iVar1 == 0x434e5354) {
          *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x180;
        }
        else if (iVar1 == 0x46414354) {
          *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x20;
        }
      }
    }
  }
  iVar3 = FUN_005e0f70(2);
  if (iVar3 != 0) {
    *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x20;
  }
  iVar3 = FUN_005e0f70(3);
  if (iVar3 != 0) {
    *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x40;
  }
  iVar3 = FUN_005e0f70(4);
  if (iVar3 != 0) {
    *(uint *)(param_1 + 0x1190) = *(uint *)(param_1 + 0x1190) | 0x180;
  }
  return;
}

