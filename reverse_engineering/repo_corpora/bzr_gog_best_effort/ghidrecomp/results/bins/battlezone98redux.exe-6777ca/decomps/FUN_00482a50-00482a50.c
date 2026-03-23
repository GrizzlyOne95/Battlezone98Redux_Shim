
void FUN_00482a50(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  undefined1 local_4c [4];
  int local_48;
  int local_44;
  void *local_40;
  char local_39;
  int local_38;
  undefined1 local_34 [7];
  undefined1 local_2d;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847ac4;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puVar6 = local_34;
  local_14 = uVar2;
  FUN_0048a2b0(param_1);
  FID_conflict_begin(puVar6);
  puVar6 = local_4c;
  FUN_0048a2b0(param_1);
  FID_conflict_end(puVar6);
  local_2d = 0;
  cVar1 = operator!=<>(param_6,&DAT_008a1ad8,uVar2);
  if (cVar1 != '\0') {
    uVar7 = 0xffffffff;
    iVar3 = FUN_004170c0(0xffffffff);
    FUN_0045e1d0(local_2c,iVar3 + -3,uVar7);
    local_8 = 0;
    cVar1 = FUN_00427270(local_2c,&PTR_LAB_0087698c);
    if (cVar1 != '\0') {
      local_2d = 1;
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  local_39 = '\0';
  do {
    cVar1 = FID_conflict_operator__(local_4c);
    if (cVar1 == '\0') {
LAB_00482c3c:
      if (local_39 == '\0') {
        local_40 = operator_new(0xcc);
        local_8 = 1;
        if (local_40 == (void *)0x0) {
          local_44 = 0;
        }
        else {
          local_44 = FUN_00482d60();
        }
        local_48 = local_44;
        local_8 = 0xffffffff;
        local_38 = local_44;
        FID_conflict_operator_(param_2);
        FID_conflict_operator_(param_10);
        FID_conflict_operator_(param_3);
        FID_conflict_operator_(param_4);
        *(undefined4 *)(local_38 + 0x78) = param_5;
        FID_conflict_operator_(param_6);
        FID_conflict_operator_(param_7);
        *(undefined4 *)(local_38 + 0xac) = param_8;
        FID_conflict_operator_(param_9);
        *(undefined1 *)(local_38 + 200) = local_2d;
        FID_conflict_operator_(param_11);
        piVar5 = &local_38;
        FUN_0048a2b0(param_1);
        FUN_0041fe40(piVar5);
      }
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    puVar4 = (undefined4 *)FUN_00421ec0(param_2);
    cVar1 = FUN_00427310(*puVar4);
    if (cVar1 != '\0') {
      uVar7 = param_10;
      FUN_00421ec0(param_10);
      FID_conflict_operator_(uVar7);
      uVar7 = param_3;
      FUN_00421ec0(param_3);
      FID_conflict_operator_(uVar7);
      uVar7 = param_4;
      FUN_00421ec0(param_4);
      FID_conflict_operator_(uVar7);
      piVar5 = (int *)FUN_00421ec0();
      *(undefined4 *)(*piVar5 + 0x78) = param_5;
      uVar7 = param_6;
      FUN_00421ec0(param_6);
      FID_conflict_operator_(uVar7);
      uVar7 = param_7;
      FUN_00421ec0(param_7);
      FID_conflict_operator_(uVar7);
      piVar5 = (int *)FUN_00421ec0();
      *(undefined4 *)(*piVar5 + 0xac) = param_8;
      uVar7 = param_9;
      FUN_00421ec0(param_9);
      FID_conflict_operator_(uVar7);
      piVar5 = (int *)FUN_00421ec0();
      *(undefined1 *)(*piVar5 + 200) = local_2d;
      uVar7 = param_11;
      FUN_00421ec0(param_11);
      FID_conflict_operator_(uVar7);
      local_39 = '\x01';
      goto LAB_00482c3c;
    }
    FUN_00421ee0();
  } while( true );
}

