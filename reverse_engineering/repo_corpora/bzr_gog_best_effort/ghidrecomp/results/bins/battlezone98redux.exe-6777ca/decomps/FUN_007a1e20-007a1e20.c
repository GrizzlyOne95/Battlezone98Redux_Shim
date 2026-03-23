
void __fastcall FUN_007a1e20(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_150 [8];
  undefined4 uStack_148;
  uint uStack_144;
  undefined1 *puStack_140;
  uint uStack_13c;
  undefined1 *puStack_138;
  uint uStack_134;
  undefined4 local_130;
  undefined1 *local_12c;
  undefined4 local_128;
  int *local_124;
  int *local_120;
  int *local_11c;
  int *local_118;
  int *local_114;
  int *local_110;
  int *local_10c;
  uint local_108;
  byte local_104;
  byte local_103;
  char local_102;
  char local_101;
  uint local_100;
  int local_fc;
  undefined1 local_f8 [56];
  byte local_c0;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008600c6;
  local_10 = ExceptionList;
  uStack_134 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_100 = 0;
  local_fc = param_1;
  local_14 = uStack_134;
  while( true ) {
    puStack_138 = (undefined1 *)0x7a1e7d;
    uVar1 = FUN_007cb5a0();
    if (uVar1 <= local_100) break;
    puStack_138 = (undefined1 *)0x7a1e9a;
    iVar2 = FUN_007c48b0();
    local_108 = iVar2 + local_100;
    puStack_138 = &DAT_008a1ad8;
    uStack_13c = 0x7a1eb3;
    basic_string<>();
    local_8 = 0;
    puStack_138 = (undefined1 *)0x7a1ecb;
    uVar1 = size();
    if (local_108 < uVar1) {
      puStack_138 = (undefined1 *)0x7a1ee2;
      FUN_00769eb0();
      local_8._0_1_ = 1;
      puStack_138 = local_f8;
      uStack_13c = local_108;
      puStack_140 = (undefined1 *)0x7a1f05;
      piVar3 = (int *)FUN_004200d0();
      local_12c = abStack_150;
      local_130 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            (abStack_150,
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)(*piVar3 + 0xdc));
      local_8._0_1_ = 2;
      local_128 = local_130;
      FUN_00764770();
      local_8._0_1_ = 1;
      local_102 = FUN_007528e0();
      local_101 = local_102;
      if (local_102 == '\0') {
        puStack_138 = (undefined1 *)local_100;
        uStack_13c = 0x7a2004;
        puVar4 = (undefined4 *)FUN_004200d0();
        local_124 = (int *)*puVar4;
        puStack_138 = (undefined1 *)0x0;
        uStack_13c = 0x7a2021;
        (**(code **)(*local_124 + 0x24))();
      }
      else {
        puStack_138 = (undefined1 *)local_100;
        uStack_13c = 0x7a1f7d;
        puVar4 = (undefined4 *)FUN_004200d0();
        local_120 = (int *)*puVar4;
        puStack_138 = (undefined1 *)0x1;
        uStack_13c = 0x7a1f9a;
        (**(code **)(*local_120 + 0x24))();
        uStack_13c = (uint)local_c0;
        puStack_140 = local_2c;
        uStack_144 = 0x7a1fab;
        FUN_00764770();
        uStack_144 = 0x7a1fb2;
        FUN_007527e0();
        local_8._0_1_ = 3;
        uStack_13c = 0x7a1fbe;
        uStack_13c = FUN_0041f870();
        puStack_140 = (undefined1 *)local_100;
        uStack_144 = 0x7a1fd7;
        FUN_004200d0();
        puStack_140 = (undefined1 *)0x7a1fde;
        FUN_007d2870();
        local_8._0_1_ = 1;
        uStack_13c = 0x7a1fea;
        ~basic_string<>();
      }
      uStack_13c = local_108;
      puStack_140 = (undefined1 *)0x7a2039;
      piVar3 = (int *)FUN_004200d0();
      local_104 = *(byte *)(*piVar3 + 0xb3);
      uStack_13c = local_100;
      puStack_140 = (undefined1 *)0x7a205f;
      puVar4 = (undefined4 *)FUN_004200d0();
      local_10c = (int *)*puVar4;
      uStack_13c = (uint)local_104;
      puStack_140 = (undefined1 *)0x7a2082;
      (**(code **)(*local_10c + 0x24))();
      puStack_140 = (undefined1 *)local_108;
      uStack_144 = 0x7a209a;
      piVar3 = (int *)FUN_004200d0();
      puStack_140 = (undefined1 *)(*piVar3 + 0x10);
      uStack_144 = 0x7a20bf;
      local_103 = (**(code **)(**(int **)(local_fc + 0x1c4) + 0x54))();
      uStack_144 = local_100;
      uStack_148 = 0x7a20dd;
      puVar4 = (undefined4 *)FUN_004200d0();
      local_114 = (int *)*puVar4;
      uStack_144 = (uint)local_103;
      uStack_148 = 0x7a2100;
      (**(code **)(*local_114 + 0x24))();
      local_8 = (uint)local_8._1_3_ << 8;
      puStack_138 = (undefined1 *)0x7a210f;
      FUN_00753670();
    }
    else {
      puStack_138 = (undefined1 *)local_100;
      uStack_13c = 0x7a212c;
      puVar4 = (undefined4 *)FUN_004200d0();
      local_11c = (int *)*puVar4;
      puStack_138 = (undefined1 *)0x0;
      uStack_13c = 0x7a2149;
      (**(code **)(*local_11c + 0x24))();
      uStack_13c = local_100;
      puStack_140 = (undefined1 *)0x7a2161;
      puVar4 = (undefined4 *)FUN_004200d0();
      local_118 = (int *)*puVar4;
      uStack_13c = 0;
      puStack_140 = (undefined1 *)0x7a217e;
      (**(code **)(*local_118 + 0x24))();
      puStack_140 = (undefined1 *)local_100;
      uStack_144 = 0x7a2196;
      puVar4 = (undefined4 *)FUN_004200d0();
      local_110 = (int *)*puVar4;
      puStack_140 = (undefined1 *)0x0;
      uStack_144 = 0x7a21b3;
      (**(code **)(*local_110 + 0x24))();
    }
    local_8 = 0xffffffff;
    puStack_138 = (undefined1 *)0x7a21c2;
    ~basic_string<>();
    local_100 = local_100 + 1;
  }
  ExceptionList = local_10;
  uStack_134 = 0x7a21dc;
  FUN_0083e885();
  return;
}

