
void FUN_007a4260(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint local_4c;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b7a8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  local_14 = uVar2;
  do {
    uVar3 = FUN_007cb5a0(uVar2);
    if (uVar3 <= local_4c) {
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    iVar4 = FUN_007c48b0();
    basic_string<>(&DAT_008a1ad8);
    local_8 = 0;
    uVar3 = FUN_004170c0();
    if (local_4c < uVar3) {
      iVar4 = FUN_00752d30(iVar4 + local_4c);
      uVar5 = FUN_007527e0(local_44,*(undefined1 *)(iVar4 + 0x38));
      FUN_0045e0f0(uVar5);
      ~basic_string<>();
    }
    cVar1 = FUN_007d3360();
    if (cVar1 == '\x01') {
      cVar1 = operator!=<>(local_2c,&DAT_008a1ad8);
      if (cVar1 == '\0') goto LAB_007a43a5;
      FUN_00764760();
      cVar1 = FUN_00742cf0();
      if (cVar1 != '\x01') goto LAB_007a43a5;
      puVar6 = (undefined4 *)FUN_004200d0(local_4c);
      (**(code **)(*(int *)*puVar6 + 0x24))(1);
      uVar5 = FUN_0041f870();
      FUN_004200d0(local_4c);
      FUN_007d2870(uVar5);
    }
    else {
LAB_007a43a5:
      puVar6 = (undefined4 *)FUN_004200d0(local_4c);
      (**(code **)(*(int *)*puVar6 + 0x24))(0);
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
    local_4c = local_4c + 1;
  } while( true );
}

