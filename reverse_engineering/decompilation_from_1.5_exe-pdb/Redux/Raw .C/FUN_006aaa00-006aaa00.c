
void __thiscall FUN_006aaa00(int param_1,int *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  int iVar5;
  code *pcVar6;
  undefined1 auStack_d4 [160];
  int local_34;
  undefined1 *local_30;
  int *local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe6b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = param_2;
  if ((*(int *)(param_1 + 0x10) == *param_2) && (*(int *)(param_1 + 0x14) == param_2[1])) {
    local_34 = param_1;
    local_1c = param_1;
    if (param_2[2] == 1) {
      *(undefined1 *)(param_1 + 0xc) = 1;
      for (local_18 = 0; local_18 < *(int *)(local_1c + 8); local_18 = local_18 + 1) {
        local_14 = local_18 * 400 + *(int *)(local_1c + 4);
        local_2c = (int *)FUN_006aa210(uVar1);
        (**(code **)(*local_2c + 0x18))(*(undefined4 *)(local_14 + 4),local_14 + 0x188);
        local_24 = (int *)FUN_006aa210();
        uVar2 = (**(code **)(*local_24 + 0x30))(*(undefined4 *)(local_14 + 4),&DAT_00879d2c);
        _snprintf((char *)(local_14 + 8),0x80,"%s",uVar2);
        local_28 = (int *)FUN_006aa210();
        uVar2 = (**(code **)(*local_28 + 0x30))(*(undefined4 *)(local_14 + 4),&DAT_00895778);
        _snprintf((char *)(local_14 + 0x88),0x100,"%s",uVar2);
      }
    }
    else {
      FUN_00574400(3,1);
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0xe4) {
        local_30 = (undefined1 *)0x0;
      }
      else {
        local_30 = auStack_d4;
      }
      pcVar6 = FUN_004bc8c0;
      iVar5 = param_2[2];
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_30,"RequestStats - failed : ");
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar5);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar6);
      pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  return;
}

