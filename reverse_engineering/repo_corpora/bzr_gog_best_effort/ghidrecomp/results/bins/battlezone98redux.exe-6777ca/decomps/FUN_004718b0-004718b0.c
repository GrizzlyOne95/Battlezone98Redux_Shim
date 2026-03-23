
void __fastcall FUN_004718b0(int param_1)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  void *pvVar6;
  bool bVar7;
  float10 fVar8;
  undefined4 local_48;
  float local_2c;
  int local_20;
  int local_1c;
  int *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084765c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar3 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x34) + 0x18))
                    (DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (*(int *)(iVar3 + 0x14) == 0x41504300) {
    FUN_00462590();
    local_18 = (int *)FUN_005e0f70(1);
    local_1c = 0;
    local_2c = 1e+30;
    if ((local_18 != (int *)0x0) && (cVar2 = (**(code **)(*local_18 + 0x68))(), cVar2 != '\0')) {
      local_1c = FUN_00466740(*(undefined4 *)(param_1 + 0x34),local_18);
      fVar8 = (float10)FUN_00461110();
      local_2c = (float)fVar8;
    }
    for (local_20 = 0x4b; local_20 < 0x50; local_20 = local_20 + 1) {
      piVar4 = (int *)FUN_005e0f70(local_20);
      if (piVar4 != (int *)0x0) {
        iVar3 = FUN_00466740(*(undefined4 *)(param_1 + 0x34),piVar4);
        fVar8 = (float10)FUN_00461110();
        fVar1 = (float)fVar8;
        if (local_2c <= fVar1) {
          if (iVar3 != 0) {
            FUN_00460640(1);
          }
        }
        else {
          bVar7 = local_1c != 0;
          local_2c = fVar1;
          local_1c = iVar3;
          local_18 = piVar4;
          if (bVar7) {
            FUN_00460640(1);
          }
        }
      }
    }
    iVar3 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
    *(undefined4 *)(iVar3 + 0xd0) = 0;
    *(undefined4 *)(iVar3 + 0xc4) = 0;
    *(undefined4 *)(iVar3 + 200) = 0;
    *(undefined4 *)(iVar3 + 0xd4) = 0;
    if (local_18 == (int *)0x0) {
      *(undefined4 *)(param_1 + 0x20) = 3;
    }
    else {
      uVar5 = FUN_00462380();
      *(undefined4 *)(param_1 + 0x3c) = uVar5;
      iVar3 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x34) + 0x18))();
      fVar1 = *(float *)(iVar3 + 0x604);
      pvVar6 = operator_new(0x15c);
      local_8 = 0;
      if (pvVar6 == (void *)0x0) {
        local_48 = 0;
      }
      else {
        local_48 = FUN_004e7a80(*(undefined4 *)(param_1 + 0x34),local_18,local_1c,fVar1 - 5.0);
      }
      *(undefined4 *)(param_1 + 0x38) = local_48;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  ExceptionList = local_10;
  return;
}

