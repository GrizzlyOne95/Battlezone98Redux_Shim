
void FUN_005ea880(void)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined1 local_438 [1056];
  undefined1 local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084cf24;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if ((DAT_02cc319c & 1) == 0) {
    DAT_02cc319c = DAT_02cc319c | 1;
    local_8 = 0;
    basic_string<>("abbarr");
    local_8._0_1_ = 1;
    basic_string<>("abcomm");
    local_8._0_1_ = 2;
    basic_string<>("abhang");
    local_8._0_1_ = 3;
    basic_string<>("abhqcp");
    local_8._0_1_ = 4;
    basic_string<>("ablpad");
    local_8._0_1_ = 5;
    basic_string<>("ablpow");
    local_8._0_1_ = 6;
    basic_string<>("abmbld");
    local_8._0_1_ = 7;
    basic_string<>("abshld");
    local_8._0_1_ = 8;
    basic_string<>("absilo");
    local_8._0_1_ = 9;
    basic_string<>("abspow");
    local_8._0_1_ = 10;
    basic_string<>("abstor");
    local_8._0_1_ = 0xb;
    basic_string<>("abtowe");
    local_8._0_1_ = 0xc;
    basic_string<>("abwpow");
    local_8._0_1_ = 0xd;
    basic_string<>("apammo");
    local_8._0_1_ = 0xe;
    basic_string<>("aprepa");
    local_8._0_1_ = 0xf;
    basic_string<>("avcnst");
    local_8._0_1_ = 0x10;
    basic_string<>("avfigh");
    local_8._0_1_ = 0x11;
    basic_string<>("avmuf");
    local_8._0_1_ = 0x12;
    basic_string<>("avrecy");
    local_8._0_1_ = 0x13;
    basic_string<>("avscav");
    local_8._0_1_ = 0x14;
    basic_string<>("avslf");
    local_8._0_1_ = 0x15;
    basic_string<>("avtank");
    local_8._0_1_ = 0x16;
    basic_string<>("avturr");
    local_8._0_1_ = 0x17;
    basic_string<>("avturr_c");
    local_8._0_1_ = 0x18;
    basic_string<>("eggeizr1");
    local_8._0_1_ = 0x19;
    basic_string<>("gatst00");
    local_8._0_1_ = 0x1a;
    basic_string<>("ghartl00");
    local_8._0_1_ = 0x1b;
    basic_string<>("nparr");
    local_8._0_1_ = 0x1c;
    basic_string<>("npscr1");
    local_8._0_1_ = 0x1d;
    basic_string<>("npscr2");
    local_8._0_1_ = 0x1e;
    basic_string<>("npscr3");
    local_8._0_1_ = 0x1f;
    basic_string<>("sbbarr");
    local_8._0_1_ = 0x20;
    basic_string<>("sbcafe");
    local_8._0_1_ = 0x21;
    basic_string<>("sbcomm");
    local_8._0_1_ = 0x22;
    basic_string<>("sbhang");
    local_8._0_1_ = 0x23;
    basic_string<>("sbhqcp");
    local_8._0_1_ = 0x24;
    basic_string<>("sblpad");
    local_8._0_1_ = 0x25;
    basic_string<>("sblpow");
    local_8._0_1_ = 0x26;
    basic_string<>("sbshld");
    local_8._0_1_ = 0x27;
    basic_string<>("sbsilo");
    local_8._0_1_ = 0x28;
    basic_string<>("sbspow");
    local_8._0_1_ = 0x29;
    basic_string<>("sbtowe");
    local_8._0_1_ = 0x2a;
    basic_string<>("sbwpow");
    local_8._0_1_ = 0x2b;
    basic_string<>("sscr_1");
    local_8._0_1_ = 0x2c;
    puVar3 = (undefined4 *)FUN_00416430(local_438,local_18);
    FUN_004b2fd0(*puVar3,puVar3[1]);
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_438,0x18,0x2c,~basic_string<>);
    FUN_0083e979(FUN_008674b0);
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

