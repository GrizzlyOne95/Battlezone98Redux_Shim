
void FUN_006b78d0(void)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  ulong uVar4;
  undefined4 uVar5;
  char **_EndPtr;
  int _Radix;
  char *local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  uint local_108;
  int local_104;
  undefined1 local_fe;
  char local_fd;
  undefined1 local_fc [136];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850cf6;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("Content-Length");
  local_8 = 0;
  FUN_006b7490(local_2c);
  cVar1 = FUN_0041f890(uVar2);
  local_fd = cVar1 == '\0';
  local_108 = (uint)(byte)local_fd;
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (local_fd == '\0') {
    basic_string<>("Transfer-Encoding");
    local_8 = 5;
    pcVar3 = "chunked";
    uVar5 = FUN_006b7490(local_5c);
    local_fe = FUN_00427270(uVar5,pcVar3);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    basic_string<>("Content-Length");
    local_8 = 1;
    local_110 = FUN_006b7490(local_74);
    local_8 = 0xffffffff;
    ~basic_string<>();
    _Radix = 10;
    _EndPtr = &local_120;
    pcVar3 = (char *)FUN_0041f870();
    uVar4 = strtoul(pcVar3,_EndPtr,_Radix);
    *(ulong *)(local_104 + 0x3c) = uVar4;
    if (*(uint *)(local_104 + 0x40) < *(uint *)(local_104 + 0x3c)) {
      basic_string<>("HTTP message body too large");
      local_8 = 2;
      local_11c = basic_string<>();
      local_8._0_1_ = 3;
      local_114 = local_11c;
      local_118 = basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,4);
      local_10c = local_118;
      FUN_006b7140(local_44,0x19d,local_118,local_114);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_fc,(ThrowInfo *)&DAT_008d838c);
    }
    *(undefined4 *)(local_104 + 0x44) = 1;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

