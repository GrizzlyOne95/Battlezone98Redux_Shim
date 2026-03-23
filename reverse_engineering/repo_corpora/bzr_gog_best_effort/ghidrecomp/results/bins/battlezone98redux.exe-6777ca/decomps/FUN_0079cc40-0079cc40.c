
void FUN_0079cc40(byte param_1,byte param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_54 [24];
  undefined4 uStack_3c;
  undefined4 uStack_38;
  uint uStack_34;
  uint uStack_30;
  uint uStack_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085fae8;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_30 = 0x79cc76;
  iVar1 = FUN_007a4220();
  if (iVar1 != 0) {
    uStack_30 = 0x79cc8c;
    iVar1 = FUN_007a4220();
    local_1c = *(undefined4 *)(iVar1 + 0x18);
    uStack_30 = 0x79cca0;
    iVar1 = FUN_007a4220();
    uStack_38 = *(undefined4 *)(iVar1 + 0x1c);
    uStack_30 = (uint)param_2;
    uStack_34 = (uint)param_1;
    uStack_3c = local_1c;
    local_24 = auStack_54;
    local_18 = uStack_38;
    local_28 = basic_string<>("playerLimit");
    local_8 = 0;
    uVar2 = *(undefined4 *)(local_14 + 0x19c);
    local_20 = local_28;
    iVar1 = FUN_0056f900(uVar2);
    local_8 = 0xffffffff;
    FUN_0079ba90(iVar1 + 0x120,uVar2);
  }
  ExceptionList = local_10;
  return;
}

