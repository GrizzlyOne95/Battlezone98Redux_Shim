
void FUN_005149b0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined1 local_f0 [216];
  undefined1 local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084ad53;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if ((DAT_02cc2f90 & 1) == 0) {
    DAT_02cc2f90 = DAT_02cc2f90 | 1;
    local_8 = 0;
    basic_string<>("apammo");
    local_8._0_1_ = 1;
    basic_string<>("aspilo");
    local_8._0_1_ = 2;
    basic_string<>("aspilo_fp");
    local_8._0_1_ = 3;
    basic_string<>("avfigh");
    local_8._0_1_ = 4;
    basic_string<>("avtest");
    local_8._0_1_ = 5;
    basic_string<>("nparr");
    local_8._0_1_ = 6;
    basic_string<>("npscr1");
    local_8._0_1_ = 7;
    basic_string<>("npscr2");
    local_8._0_1_ = 8;
    basic_string<>("npscr3");
    local_8._0_1_ = 9;
    puVar3 = (undefined4 *)FUN_00416430(local_f0,local_18);
    FUN_004b2fd0(*puVar3,puVar3[1]);
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_f0,0x18,9,~basic_string<>);
    FUN_0083e979(FUN_00866d10);
  }
  local_8 = 0xffffffff;
  cVar1 = FUN_004202c0(uVar2);
  if (cVar1 != '\0') {
    FUN_0045c660();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

