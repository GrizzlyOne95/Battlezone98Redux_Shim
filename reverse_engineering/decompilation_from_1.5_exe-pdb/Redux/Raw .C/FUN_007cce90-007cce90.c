
void __fastcall FUN_007cce90(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined8 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848fd8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>(&DAT_008a09b8);
  local_8 = 0;
  uVar4 = FUN_00689eb0(uVar1);
  FUN_00689ec0((float)uVar4 * *(float *)(param_1 + 0x2944),
               (float)((ulonglong)uVar4 >> 0x20) * *(float *)(param_1 + 0x2944));
  while( true ) {
    uVar2 = FUN_0041f870();
    fVar3 = (float10)FUN_00689ce0(DAT_0091552c,uVar2);
    if (*(float *)(param_1 + 0x10) <= (float)fVar3) break;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"\nT");
  }
  FUN_00689ec0(uVar4);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

