
void __fastcall FUN_006a9310(int param_1)

{
  uint uStack_114;
  undefined1 local_50 [4];
  undefined1 *local_4c;
  undefined4 local_48;
  int *local_44;
  undefined4 local_40;
  int *local_3c;
  int *local_34;
  int local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fc7b;
  local_10 = ExceptionList;
  uStack_114 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_114;
  ExceptionList = &local_10;
  local_8 = 0;
  local_2c = param_1;
  for (local_1c = 0; local_1c < *(int *)(local_2c + -8); local_1c = local_1c + 1) {
    local_18 = local_1c * 400 + *(int *)(local_2c + -0xc);
    local_3c = (int *)FUN_006a9180();
    local_4c = &stack0xfffffee4;
    local_20 = local_3c;
    FUN_006a9160(&stack0x00000004);
    (**(code **)(*local_20 + 0x1c))(*(undefined4 *)(local_18 + 4),local_18 + 0x188,local_50);
    local_34 = (int *)FUN_006a9180();
    local_24 = local_34;
    local_48 = (**(code **)(*local_34 + 0x30))(*(undefined4 *)(local_18 + 4));
    _snprintf((char *)(local_18 + 8),0x80,"%s",local_48);
    local_44 = (int *)FUN_006a9180();
    local_28 = local_44;
    local_40 = (**(code **)(*local_44 + 0x38))(*(undefined4 *)(local_18 + 4));
    _snprintf((char *)(local_18 + 0x88),0x100,"%s");
  }
  FUN_006a94ed();
  return;
}

