
void __fastcall FUN_0056ece0(int *param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  allocator<char> *this;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  float10 fVar11;
  undefined8 uVar12;
  longlong lVar13;
  int local_84;
  undefined4 local_60 [10];
  double local_38;
  double local_30;
  double local_28;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b56e;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if ((DAT_00917f48 != 0) && (DAT_00917f4c == '\0')) {
    pvVar3 = operator_new(0x1150);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_84 = 0;
    }
    else {
      local_84 = FUN_0059c1f0();
    }
    local_8 = 0xffffffff;
    param_1[0x18] = local_84;
    FUN_00571c60();
    uVar12 = FUN_0045c0c0();
    iVar4 = FUN_004e0f70(uVar12,uVar2);
    cVar1 = FUN_00571c30();
    if (cVar1 != '\0') {
      this = (allocator<char> *)FUN_005d9100();
      if (this == (allocator<char> *)0x0) {
        if ((DAT_00918338 == 0) || (cVar1 = FUN_0041fc90(), cVar1 != '\0')) {
          FUN_0081cb40("multi_error","no_spawn_points");
          FUN_0056fcb0();
          uVar5 = FUN_0081e820();
          FUN_0081e710(uVar5);
        }
        else {
          FUN_0081cb40("multi_error","no_spawn_avail");
          FUN_0056fcb0();
          uVar5 = FUN_0081e820();
          FUN_0081e710(uVar5);
        }
        DAT_00917f4c = '\x01';
        iVar4 = FUN_00434160();
        if (iVar4 != 2) {
          FUN_005d48b0();
        }
        goto LAB_0056f0d5;
      }
      std::allocator<char>::allocator<char>(this);
      FUN_005704a0();
      FUN_0056b910();
      iVar6 = FUN_00577200();
      FUN_00576370();
      *(allocator<char> **)(iVar6 + 0x24) = this;
      Set();
    }
    FUN_00570470();
    puVar9 = &DAT_008fe1e0;
    puVar10 = local_60;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    local_38 = (double)local_20;
    local_30 = (double)local_1c;
    local_28 = (double)local_18;
    iVar6 = FUN_004e1190(local_60,DAT_00917f50,1,0xffffffff,0);
    pvVar3 = operator_new(200);
    local_8 = 1;
    if (pvVar3 != (void *)0x0) {
      FUN_00608d40(param_1,iVar6);
    }
    local_8 = 0xffffffff;
    FUN_004b8460();
    if ((*(int *)(iVar6 + 0xec) == 0) &&
       (iVar7 = (*(code *)**(undefined4 **)(iVar6 + 0x18))(), 0 < *(int *)(iVar7 + 0x50))) {
      iVar8 = FUN_00417c70();
      if (iVar6 == iVar8) {
        *(undefined4 *)(iVar6 + 0xec) = *(undefined4 *)(iVar7 + 0xd4);
      }
      else {
        *(undefined4 *)(iVar6 + 0xec) = *(undefined4 *)(iVar7 + 0xd0);
      }
    }
    lVar13 = FUN_0045dbb0();
    if (lVar13 == 0) {
      FUN_007d6a70("Could not find a recycler variant for %s",iVar4 + 0x38);
    }
    FUN_004e0f70(lVar13);
    local_38 = local_38 + 20.0;
    local_28 = local_28 + 20.0;
    fVar11 = (float10)FUN_007855e0(local_38,local_28);
    local_30 = (double)((float)fVar11 + 2.0);
    FUN_004e1190(local_60,DAT_00917f50,0,0xffffffff,0);
    FUN_00462590();
    FUN_005e1010();
    FUN_004b8460();
    (**(code **)(*param_1 + 0x1c))();
  }
LAB_0056f0d5:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

