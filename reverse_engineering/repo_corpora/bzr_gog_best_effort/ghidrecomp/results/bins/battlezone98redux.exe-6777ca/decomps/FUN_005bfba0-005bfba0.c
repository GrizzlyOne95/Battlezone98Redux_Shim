
undefined4 __fastcall FUN_005bfba0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  undefined8 uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0xc) + 0x18) + 0xc))();
  uVar5 = FUN_0045c460(*puVar1,puVar1[1],puVar1[2]);
  fVar4 = (float)((ulonglong)uVar5 >> 0x20);
  if (((((float)uVar5 - DAT_02cd912c < 20.0) || (DAT_02cd9124 - (float)uVar5 < 20.0)) ||
      (fVar4 - DAT_02cd9130 < 20.0)) || (DAT_02cd9128 - fVar4 < 20.0)) {
    iVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0xc) + 0x18) + 0x30))();
    *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x200;
    uVar3 = 0;
  }
  else {
    if (((*(int *)(local_8 + 0x1c) == 7) &&
        (local_c = FUN_00462630(*(undefined4 *)(local_8 + 0x3c)), local_c != 0)) &&
       (iVar2 = (*(code *)**(undefined4 **)(local_c + 0x18))(), *(int *)(iVar2 + 0x1c) == 4)) {
      return 0;
    }
    local_1c = 0x461c4000;
    local_14 = FUN_00463d90(*(undefined4 *)(local_8 + 0x34),&local_1c);
    if (local_14 == 0) {
      if (*(int *)(local_8 + 0x1c) == 7) {
        uVar3 = 0;
      }
      else {
        local_20 = 0x471c4000;
        local_18 = FUN_00463240(*(undefined4 *)(local_8 + 0x34),&local_20);
        if (local_18 == 0) {
          uVar3 = 0;
        }
        else {
          if (*(int *)(local_8 + 0x24) == 0) {
            *(undefined4 *)(local_8 + 0x24) = *(undefined4 *)(local_8 + 0x1c);
            *(undefined4 *)(local_8 + 0x20) = 7;
            *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x3c);
            uVar3 = FUN_00477590(local_18);
            *(undefined4 *)(local_8 + 0x3c) = uVar3;
            *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x10);
            *(undefined4 *)(local_8 + 0x10) = 0;
          }
          else {
            *(undefined4 *)(local_8 + 0x20) = *(undefined4 *)(local_8 + 0x24);
            *(undefined4 *)(local_8 + 0x3c) = *(undefined4 *)(local_8 + 0x28);
            *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x2c);
            *(undefined4 *)(local_8 + 0x24) = 0;
            *(undefined4 *)(local_8 + 0x28) = 0;
            *(undefined4 *)(local_8 + 0x2c) = 0;
          }
          uVar3 = 1;
        }
      }
    }
    else {
      if (*(int *)(local_8 + 0x24) == 0) {
        *(undefined4 *)(local_8 + 0x24) = *(undefined4 *)(local_8 + 0x1c);
        *(undefined4 *)(local_8 + 0x20) = 7;
        *(undefined4 *)(local_8 + 0x28) = *(undefined4 *)(local_8 + 0x3c);
        uVar3 = FUN_00477590(local_14);
        *(undefined4 *)(local_8 + 0x3c) = uVar3;
        *(undefined4 *)(local_8 + 0x2c) = *(undefined4 *)(local_8 + 0x10);
        *(undefined4 *)(local_8 + 0x10) = 0;
      }
      else {
        *(undefined4 *)(local_8 + 0x20) = *(undefined4 *)(local_8 + 0x24);
        *(undefined4 *)(local_8 + 0x3c) = *(undefined4 *)(local_8 + 0x28);
        *(undefined4 *)(local_8 + 0x10) = *(undefined4 *)(local_8 + 0x2c);
        *(undefined4 *)(local_8 + 0x24) = 0;
        *(undefined4 *)(local_8 + 0x28) = 0;
        *(undefined4 *)(local_8 + 0x2c) = 0;
      }
      uVar3 = 1;
    }
  }
  return uVar3;
}

