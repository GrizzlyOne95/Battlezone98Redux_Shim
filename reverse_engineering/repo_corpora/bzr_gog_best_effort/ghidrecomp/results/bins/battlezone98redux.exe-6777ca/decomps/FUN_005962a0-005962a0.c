
void __fastcall FUN_005962a0(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  if (DAT_00920f04 != 0) {
    if (param_1[0x21] < 0) {
      local_2c = 0;
    }
    else {
      local_2c = param_1[0x21];
    }
    local_14 = *(int *)(DAT_00920f04 + local_2c * 4);
    if (local_14 != 0) {
      iVar1 = *(int *)(local_14 + 0x78);
      iVar2 = *(int *)(local_14 + 0x7c);
      local_8 = param_1;
      for (local_10 = 0; local_10 < iVar1; local_10 = local_10 + 1) {
        for (local_c = 0; local_c < iVar2; local_c = local_c + 1) {
          iVar3 = *(int *)(*(int *)(*(int *)(local_14 + 0x80) + local_10 * 4) + local_c * 4);
          fVar4 = (float)local_c * 80.0 + (float)DAT_00931018 * 5.0;
          fVar5 = (float)local_10 * 80.0 + (float)DAT_00931020 * 5.0;
          fVar6 = fVar4 + 80.0;
          fVar7 = fVar5 + 80.0;
          (**(code **)(*local_8 + 0x24))(fVar4,fVar5,&local_28,&local_1c,iVar3,fVar6,fVar7);
          (**(code **)(*local_8 + 0x24))(fVar6,fVar7,&local_20,&local_24);
          iVar3 = FUN_00453d10(*(undefined4 *)(iVar3 + 4),0,10);
          local_18 = local_8[iVar3 + 0x4b];
          if (-1 < local_18) {
            FUN_0068b020(DAT_00917580,local_28 + 3,local_24 + 3,local_20 + -3,local_1c + -3,local_18
                         ,0);
            FUN_0068b020(DAT_00917580,local_28 + 2,local_24 + 2,local_20 + -2,local_1c + -2,local_18
                         ,0);
            FUN_0068b020(DAT_00917580,local_28 + 1,local_24 + 1,local_20 + -1,local_1c + -1,local_18
                         ,0);
          }
          FUN_0068b020(DAT_00917580,local_28,local_24,local_20,local_1c,DAT_00917584,0);
        }
      }
    }
  }
  return;
}

