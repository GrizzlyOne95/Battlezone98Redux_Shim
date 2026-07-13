
void __fastcall FUN_005fc2b0(int param_1)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  void *pvVar6;
  bool bVar7;
  float10 fVar8;
  undefined4 local_4c;
  float local_3c;
  int local_28;
  int local_24;
  int local_20;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d1ac;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar4 = *(int *)(param_1 + 0x34);
  iVar3 = FUN_00462380(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(int *)(iVar4 + 0xb0) == iVar3) {
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  else {
    FUN_00462590();
    local_18 = FUN_005e0f70(3);
    iVar4 = *(int *)(*(int *)(param_1 + 0x34) + 0xc4);
    if ((iVar4 < 0) || ((iVar4 < 1 && (*(int *)(*(int *)(param_1 + 0x34) + 0xc0) == 0)))) {
      if ((local_18 != 0) &&
         ((cVar2 = FUN_00472680(), cVar2 == '\0' && (cVar2 = FUN_004723d0(), cVar2 == '\0')))) {
        local_18 = 0;
      }
    }
    else {
      local_18 = 0;
    }
    local_28 = 0;
    local_3c = 3.4028235e+38;
    local_20 = FUN_00462630(*(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0));
    if (local_20 == 0) {
      if ((local_18 == 0) ||
         (cVar2 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))(), cVar2 != '\0')) {
        for (local_24 = 0x41; local_24 < 0x46; local_24 = local_24 + 1) {
          iVar4 = FUN_005e0f70(local_24);
          if (iVar4 != 0) {
            uVar5 = (**(code **)(*(int *)(iVar4 + 0x18) + 0xc))();
            uVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar5);
            fVar8 = (float10)FUN_00462010(uVar5);
            if ((local_18 == 0) || ((float)fVar8 < 90000.0)) {
              iVar3 = FUN_00466740(*(undefined4 *)(param_1 + 0x34),iVar4);
              fVar8 = (float10)FUN_00461110();
              fVar1 = (float)fVar8;
              if (local_3c <= fVar1) {
                if (iVar3 != 0) {
                  FUN_00460640(1);
                }
              }
              else {
                bVar7 = local_28 != 0;
                local_3c = fVar1;
                local_28 = iVar3;
                local_20 = iVar4;
                if (bVar7) {
                  FUN_00460640(1);
                }
              }
            }
          }
        }
      }
    }
    else {
      FUN_00466740(*(undefined4 *)(param_1 + 0x34),local_20);
    }
    if (local_20 == 0) {
      if ((local_18 == 0) ||
         (cVar2 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))(), cVar2 == '\0')) {
        *(undefined4 *)(param_1 + 0x20) = 3;
      }
      else {
        pvVar6 = operator_new(0x134);
        local_8 = 0;
        if (pvVar6 == (void *)0x0) {
          local_4c = 0;
        }
        else {
          local_4c = FUN_006086e0(*(undefined4 *)(param_1 + 0x34));
        }
        local_8 = 0xffffffff;
        *(undefined4 *)(param_1 + 0x38) = local_4c;
        uVar5 = FUN_00462380();
        *(undefined4 *)(param_1 + 0x3c) = uVar5;
      }
    }
    else {
      cVar2 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))();
      if (cVar2 == '\0') {
        (**(code **)(**(int **)(param_1 + 0x34) + 100))();
      }
      uVar5 = FUN_00462380();
      *(undefined4 *)(param_1 + 0x3c) = uVar5;
      *(undefined4 *)(param_1 + 0x20) = 9;
    }
  }
  ExceptionList = local_10;
  return;
}

