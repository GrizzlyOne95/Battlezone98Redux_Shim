
void FUN_004fc020(char *param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  void *pvVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  char *local_9c;
  char *local_94;
  char *local_90;
  char *local_8c;
  undefined4 *local_88;
  undefined4 local_80 [10];
  double local_58;
  double local_50;
  double local_48;
  float local_40;
  float fStack_38;
  float fStack_34;
  float fStack_2c;
  char local_28 [20];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a9cf;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004886e0();
  DAT_0091831c = 0xffffffff;
  cVar1 = FUN_00488d80();
  if (cVar1 != '\0') {
    FUN_00482850();
    FUN_00764790();
    uVar2 = FUN_0076ea20();
    FUN_004828f0(uVar2);
    FUN_00489dc0();
  }
  if (param_2 == 0) {
    local_9c = param_1;
    local_90 = local_28;
    do {
      cVar1 = *local_9c;
      *local_90 = cVar1;
      local_9c = local_9c + 1;
      local_90 = local_90 + 1;
    } while (cVar1 != '\0');
    puVar3 = (undefined1 *)FUN_004fbaf0();
    if (puVar3 != (undefined1 *)0x0) {
      *puVar3 = 0;
    }
    FUN_00780c00();
    FUN_007800c0();
    iVar4 = FUN_00780160();
    if (((iVar4 != 0) && (iVar4 = FUN_007859d0(), iVar4 != 0)) &&
       (iVar4 = FUN_0077e990(), iVar4 != 0)) {
      FUN_0077ea10();
      FUN_0067e1d0();
      FUN_004b6ec0();
      FUN_00822de0();
      FUN_00591c00();
      FUN_004e0f70();
      FUN_00783590();
      puVar6 = &DAT_008fe1e0;
      puVar7 = local_80;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      local_58 = (double)((fStack_34 + local_40) / 2.0);
      local_48 = (double)((fStack_2c + fStack_38) / 2.0);
      fVar8 = (float10)FUN_007855e0();
      local_50 = (double)((float)fVar8 + 2.0);
      FUN_004e1190();
      local_94 = param_1;
      local_8c = &DAT_00915540;
      do {
        cVar1 = *local_94;
        *local_8c = cVar1;
        local_94 = local_94 + 1;
        local_8c = local_8c + 1;
      } while (cVar1 != '\0');
      iVar4 = FUN_004fbaf0();
      if (iVar4 == 0) {
        local_88 = (undefined4 *)&DAT_0091553f;
        puVar6 = local_88;
        do {
          local_88 = puVar6;
          puVar6 = (undefined4 *)((int)local_88 + 1);
        } while (*(char *)((int)local_88 + 1) != '\0');
        *(undefined4 *)((int)local_88 + 1) = 0x6e7a622e;
        *(undefined1 *)((int)local_88 + 5) = 0;
      }
      iVar4 = FUN_00417c70();
      FUN_0045c990();
      if (iVar4 != 0) {
        pvVar5 = operator_new(200);
        local_8 = 0;
        if (pvVar5 != (void *)0x0) {
          FUN_00608d40();
        }
        local_8 = 0xffffffff;
        uVar2 = FUN_004e0f70();
        *(undefined4 *)(iVar4 + 0xec) = uVar2;
      }
      FUN_00822de0();
      FUN_00822a70();
      FUN_0045d4f0();
      FUN_004dcc90();
      operator==<>();
      if (DAT_009173b7 == '\0') {
        FUN_00461ed0();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

