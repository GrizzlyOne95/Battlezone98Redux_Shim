
undefined4
FUN_006cc9c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,ios_base *param_4,byte param_5
            ,int param_6)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  time_put<char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_> *ptVar6;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852ba0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  iVar2 = FUN_0048a830(uVar1);
  if (iVar2 != 0) {
    uVar3 = FUN_006cf480(*(undefined4 *)(param_6 + 0x18));
    FUN_006dcf90(&stack0x0000001c,&DAT_008962a0,uVar3);
  }
  iVar2 = FUN_0048a830(uVar1);
  if (iVar2 != 0) {
    uVar3 = FUN_006cf480(*(undefined4 *)(param_6 + 0x18));
    FUN_006dcf90(&stack0x0000001c,&DAT_00896248,uVar3);
  }
  iVar2 = FUN_0048a830(uVar1);
  if (iVar2 != 0) {
    uVar3 = FUN_006cf480(*(undefined4 *)(param_6 + 0x10));
    FUN_006dcf90(&stack0x0000001c,&DAT_00896250,uVar3);
  }
  iVar2 = FUN_0048a830();
  if (iVar2 != 0) {
    uVar3 = FUN_006cf480(*(undefined4 *)(param_6 + 0x10));
    FUN_006dcf90(&stack0x0000001c,&DAT_00896170,uVar3);
  }
  iVar2 = FUN_0041f870();
  uVar4 = std::ios_base::getloc(param_4);
  local_8._0_1_ = 1;
  iVar5 = FUN_004170c0();
  iVar5 = iVar5 + iVar2;
  uVar1 = (uint)param_5;
  uVar3 = param_1;
  ptVar6 = (time_put<char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_> *)
           FUN_006dcfe0(uVar4,param_1,param_2,param_3,param_4,uVar1,param_6,iVar2,iVar5);
  std::time_put<char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_>::put
            (ptVar6,uVar3,param_2,param_3,param_4,uVar1,param_6,iVar2,iVar5);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00417b50();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return param_1;
}

