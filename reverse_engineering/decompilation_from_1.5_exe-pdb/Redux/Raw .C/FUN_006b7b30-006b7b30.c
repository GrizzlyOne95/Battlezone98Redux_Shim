
void __thiscall FUN_006b7b30(int param_1,char *param_2)

{
  uint uVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_154 [88];
  undefined1 local_fc [184];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850d56;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x44) == 1) {
    puVar2 = (uint *)_Min_value<>(param_1 + 0x3c,&stack0x00000008,local_14);
    uVar1 = *puVar2;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_1 + 0x24),param_2,uVar1);
    *(uint *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) - uVar1;
    ExceptionList = local_10;
    FUN_0083e885();
    return;
  }
  if (*(int *)(param_1 + 0x44) == 2) {
    basic_string<>("Unexpected body encoding");
    local_8 = 0;
    uVar3 = basic_string<>();
    local_8._0_1_ = 1;
    uVar4 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_006b7140(local_44,500,uVar4,uVar3);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_154,(ThrowInfo *)&DAT_008d838c);
  }
  basic_string<>("Unexpected body encoding");
  local_8 = 3;
  uVar3 = basic_string<>();
  local_8._0_1_ = 4;
  uVar4 = basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,5);
  FUN_006b7140(local_2c,500,uVar4,uVar3);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_fc,(ThrowInfo *)&DAT_008d838c);
}

