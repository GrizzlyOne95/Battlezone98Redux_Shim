
void __fastcall FUN_0056c320(int param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  allocator<char> *this;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  undefined4 local_8c;
  undefined4 local_78;
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
  puStack_c = &LAB_0084b307;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (DAT_00917f48 != 0) {
    pvVar3 = operator_new(0x48);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_8c = 0;
    }
    else {
      local_8c = FUN_0056ba90(param_1);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x60) = local_8c;
    pvVar3 = operator_new(0x1150);
    local_8 = 1;
    if (pvVar3 == (void *)0x0) {
      local_78 = 0;
    }
    else {
      local_78 = FUN_0059c1f0(param_1);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 100) = local_78;
    FUN_00571c60(1,uVar2);
    iVar4 = FUN_00572a70();
    if (iVar4 != 0) {
      uVar10 = FUN_0045c0c0(&DAT_008e8c74);
      FUN_004e0f70(uVar10);
      cVar1 = FUN_00571c30();
      if (cVar1 != '\0') {
        this = (allocator<char> *)FUN_005d9100(DAT_00917f50);
        if (this == (allocator<char> *)0x0) {
          if ((DAT_00918338 == 0) || (cVar1 = FUN_0041fc90(), cVar1 != '\0')) {
            uVar5 = FUN_0081cb40("multi_error","no_spawn_points");
            FUN_0056fcb0(uVar5);
            uVar5 = FUN_0081e820("Map has no spawn points\n");
            FUN_0081e710(uVar5);
          }
          else {
            uVar5 = FUN_0081cb40("multi_error","no_spawn_avail");
            FUN_0056fcb0(uVar5);
            uVar5 = FUN_0081e820("Could not get a spawn point\n");
            FUN_0081e710(uVar5);
          }
          DAT_00917f4c = 1;
          iVar4 = FUN_00434160();
          if (iVar4 != 2) {
            FUN_005d48b0();
          }
          goto LAB_0056c66f;
        }
        uVar5 = std::allocator<char>::allocator<char>(this);
        FUN_005704a0(uVar5);
        uVar5 = FUN_0056b910();
        iVar4 = FUN_00577200(uVar5);
        FUN_00576370(0);
        *(allocator<char> **)(iVar4 + 0x24) = this;
        Set(iVar4);
      }
      FUN_00570470(&local_20);
      puVar8 = &DAT_008fe1e0;
      puVar9 = local_60;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      local_38 = (double)local_20;
      local_30 = (double)local_1c;
      local_28 = (double)local_18;
      iVar4 = FUN_004e1190(local_60,DAT_00917f50,1,0xffffffff,0);
      pvVar3 = operator_new(200);
      local_8 = 2;
      if (pvVar3 != (void *)0x0) {
        FUN_00608d40(param_1,iVar4);
      }
      local_8 = 0xffffffff;
      FUN_004b8460();
      if ((*(int *)(iVar4 + 0xec) == 0) &&
         (iVar6 = (*(code *)**(undefined4 **)(iVar4 + 0x18))(), 0 < *(int *)(iVar6 + 0x50))) {
        iVar7 = FUN_00417c70();
        if (iVar4 == iVar7) {
          *(undefined4 *)(iVar4 + 0xec) = *(undefined4 *)(iVar6 + 0xd4);
        }
        else {
          *(undefined4 *)(iVar4 + 0xec) = *(undefined4 *)(iVar6 + 0xd0);
        }
      }
    }
  }
LAB_0056c66f:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

