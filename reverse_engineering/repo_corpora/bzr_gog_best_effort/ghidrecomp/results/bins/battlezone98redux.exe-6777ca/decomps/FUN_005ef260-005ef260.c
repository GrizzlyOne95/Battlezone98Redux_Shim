
void __fastcall FUN_005ef260(int param_1)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  undefined4 uVar6;
  bool bVar7;
  float10 fVar8;
  undefined4 local_58;
  undefined4 local_50;
  float local_48;
  float local_3c;
  int local_28;
  int local_24;
  int local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c738;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00462590(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_1c = FUN_005e0f70(3);
  iVar4 = *(int *)(*(int *)(param_1 + 0x20) + 0xc4);
  if ((iVar4 < 0) || ((iVar4 < 1 && (*(int *)(*(int *)(param_1 + 0x20) + 0xc0) == 0)))) {
    if ((local_1c != 0) &&
       ((cVar2 = FUN_00472700(), cVar2 == '\0' && (cVar2 = FUN_004723d0(), cVar2 == '\0')))) {
      local_1c = 0;
    }
  }
  else {
    local_1c = 0;
  }
  local_28 = 0;
  local_3c = 3.4028235e+38;
  local_18 = FUN_00462630(*(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb0));
  if (local_18 == 0) {
    if ((local_1c == 0) || (*(int *)(*(int *)(param_1 + 0x20) + 0x228) == 0)) {
      for (local_24 = 0x3c; local_24 < 0x41; local_24 = local_24 + 1) {
        iVar4 = FUN_005e0f70(local_24);
        if (iVar4 != 0) {
          uVar6 = (**(code **)(*(int *)(iVar4 + 0x18) + 0xc))();
          uVar6 = (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x18) + 0xc))(uVar6);
          fVar8 = (float10)FUN_00462010(uVar6);
          if ((local_1c == 0) || ((float)fVar8 < 90000.0)) {
            iVar3 = FUN_00466740(*(undefined4 *)(param_1 + 0x20),iVar4);
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
              local_18 = iVar4;
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
    local_28 = FUN_00466740(*(undefined4 *)(param_1 + 0x20),local_18);
  }
  if (local_18 == 0) {
    if (local_1c == 0) {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    else {
      pvVar5 = operator_new(0x134);
      local_8 = 1;
      if (pvVar5 == (void *)0x0) {
        local_58 = 0;
      }
      else {
        local_58 = FUN_006086e0(*(undefined4 *)(param_1 + 0x20));
      }
      local_8 = 0xffffffff;
      *(undefined4 *)(param_1 + 0x34) = local_58;
      uVar6 = FUN_00462380();
      *(undefined4 *)(param_1 + 0x30) = uVar6;
    }
  }
  else {
    iVar4 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
    if (*(int *)(iVar4 + 0x14) == 0x52444550) {
      iVar4 = (*(code *)**(undefined4 **)(local_18 + 0x18))();
      local_48 = *(float *)(iVar4 + 0x160);
    }
    else {
      fVar8 = (float10)FUN_00462470();
      iVar4 = FUN_00462400();
      local_48 = (float)fVar8 + *(float *)(iVar4 + 0xc);
    }
    pvVar5 = operator_new(0x15c);
    local_8 = 0;
    if (pvVar5 == (void *)0x0) {
      local_50 = 0;
    }
    else {
      local_50 = FUN_004e7a80(*(undefined4 *)(param_1 + 0x20),local_18,local_28,local_48);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x34) = local_50;
    uVar6 = FUN_00462380();
    *(undefined4 *)(param_1 + 0x30) = uVar6;
  }
  ExceptionList = local_10;
  return;
}

