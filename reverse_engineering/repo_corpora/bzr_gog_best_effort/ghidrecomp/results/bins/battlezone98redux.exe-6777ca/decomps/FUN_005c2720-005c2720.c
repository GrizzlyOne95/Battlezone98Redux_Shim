
void __thiscall FUN_005c2720(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  int *local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  if ((-1 < *(int *)(param_1 + 0x308)) &&
     ((iVar2 = FUN_0062a540(*(undefined4 *)(param_1 + 0x308),&local_20), iVar2 != 0 ||
      (*local_20 != 1)))) {
    FUN_0062a5d0(*(undefined4 *)(local_8 + 0x308));
    *(undefined4 *)(local_8 + 0x308) = 0xffffffff;
  }
  local_18 = *(undefined4 *)(local_8 + 0x228);
  switch(local_18) {
  case 0:
    if (*(int *)(*(int *)(local_8 + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(local_8 + 0x228) = 1;
      *(undefined4 *)(*(int *)(local_8 + 0x230) + 0xe0) = 0;
      FUN_0062a270(*(undefined4 *)(local_8 + 0xf4),0,local_8 + 0x308);
      FUN_004376c0(*(int *)(local_8 + 0xf8) + 0x5d0,*(undefined4 *)(local_8 + 0xf4),0);
    }
    break;
  case 1:
    if (*(int *)(local_8 + 0x308) == -1) {
      *(undefined4 *)(local_8 + 0x228) = 2;
      *(undefined4 *)(local_8 + 0x30c) = 0x3f800000;
      local_c = FUN_005c24e0(local_8);
      cVar1 = FUN_005b5100();
      if ((cVar1 == '\0') && (local_c != 0)) {
        iVar2 = (*(code *)**(undefined4 **)(local_c + 0x18))();
        FUN_005b5060(*(undefined4 *)(iVar2 + 0x4c));
        FUN_004376c0(*(int *)(local_8 + 0xf8) + 0x5f4,*(undefined4 *)(local_8 + 0xf4),0);
        iVar2 = FUN_00572a70();
        if ((iVar2 == 0) || (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
          iVar2 = FUN_00572a70();
          if ((iVar2 == 0) || (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
            (**(code **)(*(int *)(local_c + 0x18) + 0x10))();
          }
          else {
            iVar2 = FUN_00572a70();
            if ((iVar2 != 0) && (cVar1 = FUN_004b9830(), cVar1 != '\0')) {
              FUN_004b7bd0();
              FUN_004b9940();
            }
          }
        }
      }
      else {
        cVar1 = FUN_005b5140();
        if ((cVar1 == '\0') && (local_1c = FUN_005c2680(local_8), local_1c != 0)) {
          local_10 = FUN_005b50e0();
          FUN_005b50a0(local_10);
          iVar2 = FUN_00572a70();
          if (iVar2 != 0) {
            local_10 = local_10 << 1;
          }
          iVar2 = local_10;
          FUN_00462590(local_10);
          FUN_005e1010(iVar2);
        }
      }
    }
    break;
  case 2:
    *(float *)(local_8 + 0x30c) = *(float *)(local_8 + 0x30c) - param_2;
    if (*(float *)(local_8 + 0x30c) <= 0.0) {
      *(undefined4 *)(local_8 + 0x228) = 3;
      if (-1 < *(int *)(local_8 + 0x308)) {
        FUN_0062a5d0(*(undefined4 *)(local_8 + 0x308));
        *(undefined4 *)(local_8 + 0x308) = 0xffffffff;
      }
      FUN_0062a270(*(undefined4 *)(local_8 + 0xf4),1,local_8 + 0x308);
      FUN_004376c0(*(int *)(local_8 + 0xf8) + 0x5e0,*(undefined4 *)(local_8 + 0xf4),0);
    }
    break;
  case 3:
    if (*(int *)(local_8 + 0x308) == -1) {
      *(undefined4 *)(local_8 + 0x228) = 0;
    }
  }
  cVar1 = FUN_004b9830();
  if (((cVar1 == '\0') && (*(char *)(local_8 + 0x79) != '\0')) &&
     (cVar1 = FUN_005b5140(), cVar1 == '\0')) {
    local_14 = FUN_005b50e0();
    FUN_005b50a0(local_14);
    iVar2 = FUN_00572a70();
    if (iVar2 != 0) {
      local_14 = local_14 << 1;
    }
    iVar2 = local_14;
    FUN_00462590(local_14);
    FUN_005e1010(iVar2);
  }
  FUN_004ebfd0(param_2);
  return;
}

