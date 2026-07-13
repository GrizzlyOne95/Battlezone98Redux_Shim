
void __fastcall FUN_0041a1c0(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  uint local_7c;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844b40;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_7c = (uint)(*(char *)(param_1 + 4) != '\0');
  local_14 = uVar2;
  basic_string<>("TAP:ACTIVE");
  local_8 = 0;
  puVar3 = (uint *)FUN_00421c70(local_2c);
  *puVar3 = local_7c;
  local_8 = 0xffffffff;
  ~basic_string<>(uVar2);
  if (*(char *)(param_1 + 4) != '\0') {
    basic_string<>("TAP:TIME");
    local_8 = 1;
    uVar1 = *(undefined4 *)(param_1 + 0x80);
    puVar4 = (undefined4 *)FUN_00421c70(local_44);
    *puVar4 = uVar1;
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("TAP:X");
    local_8 = 2;
    puVar4 = (undefined4 *)FUN_00421c70(local_5c);
    *puVar4 = *(undefined4 *)(param_1 + 0xc);
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("TAP:Y");
    local_8 = 3;
    puVar4 = (undefined4 *)FUN_00421c70(local_74);
    *puVar4 = *(undefined4 *)(param_1 + 0x10);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

