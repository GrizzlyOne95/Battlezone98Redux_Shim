
void FUN_0076c0f0(void)

{
  int iVar1;
  undefined1 local_e0 [168];
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d92b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0076ef40("modEnabled.dat",2,0x40,1);
  local_8 = 0;
  FUN_004bb540(local_2c);
  local_8._0_1_ = 1;
  while( true ) {
    local_20 = FUN_004bb570(local_38);
    local_8._0_1_ = 2;
    local_1c = local_20;
    local_11 = FID_conflict_operator<(local_20);
    local_8._0_1_ = 1;
    FUN_004bb3b0();
    if (local_11 == '\0') break;
    iVar1 = FUN_0076f9f0();
    FUN_00574730(local_e0,iVar1 + 0x60);
    FUN_004bc590(local_e0,&DAT_0087a44c);
    FUN_00732df0();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  FUN_0076f0b0();
  local_8 = 0xffffffff;
  FUN_0076c200();
  ExceptionList = local_10;
  return;
}

