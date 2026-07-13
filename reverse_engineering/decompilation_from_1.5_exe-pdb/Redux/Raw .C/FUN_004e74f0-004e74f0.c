
void __fastcall FUN_004e74f0(int *param_1)

{
  char cVar1;
  void *pvVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  int local_28;
  undefined4 local_20 [2];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a4dc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1[2] == 6) {
    if (((char)param_1[0x4f] != '\0') && (param_1[0x4d] != 0)) {
      FUN_00460600(param_1[0x4d]);
    }
    param_1[0x4d] = 0;
    cVar1 = (**(code **)(*param_1 + 0x3c))(local_20);
    if (cVar1 == '\0') {
      param_1[3] = 0xd;
    }
    else {
      pvVar2 = operator_new(0x18);
      local_8 = 0;
      if (pvVar2 == (void *)0x0) {
        local_28 = 0;
      }
      else {
        puVar5 = local_20;
        uVar3 = (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(puVar5);
        local_28 = FUN_00460490(uVar3,puVar5);
      }
      local_8 = 0xffffffff;
      param_1[0x4d] = local_28;
      if (*(int *)(param_1[4] + 0x234) == 0) {
        uVar3 = (**(code **)(*(int *)(param_1[4] + 0x18) + 4))();
        iVar4 = (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(local_20[0],local_18,1,uVar3);
        puVar5 = (undefined4 *)
                 (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(*(undefined4 *)(iVar4 + 8));
        iVar4 = FUN_00466450(*puVar5);
        param_1[0x10] = iVar4;
      }
      *(undefined1 *)(param_1 + 0x4f) = 1;
      param_1[3] = 1;
    }
  }
  else {
    if ((param_1[0x10] != 0) && (param_1[0x10] != param_1[0x53])) {
      cVar1 = (**(code **)(*param_1 + 0x44))(local_14);
      if (cVar1 == '\0') {
        param_1[3] = 6;
        goto LAB_004e777c;
      }
    }
    param_1[0x53] = param_1[0x10];
    uVar3 = (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(param_1 + 10);
    fVar6 = (float10)FUN_00462010(uVar3);
    if (25.0 <= (float)fVar6) {
      iVar4 = FUN_004643e0(param_1[4],0);
      param_1[0x1f] = iVar4;
    }
    else {
      cVar1 = (**(code **)(*param_1 + 0x40))();
      if (cVar1 == '\0') {
        FUN_00602420();
      }
      else {
        param_1[3] = 6;
        param_1[0x1f] = 0;
      }
    }
  }
LAB_004e777c:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

