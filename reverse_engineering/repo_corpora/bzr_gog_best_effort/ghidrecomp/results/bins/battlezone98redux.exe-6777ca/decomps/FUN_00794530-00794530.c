
void __fastcall FUN_00794530(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  code *pcVar5;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085f0c0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_MissionSuccess::vftable;
  local_8 = 0;
  if (param_1[0x53] != 0) {
    iVar1 = FUN_007d4450(local_14);
    if (10 < iVar1) {
      uVar2 = FUN_007d43e0(local_2c);
      local_8._0_1_ = 1;
      pcVar5 = FUN_004bc8c0;
      pcVar4 = FUN_0056f740;
      FUN_0081e820("Skipped ",FUN_0056f740,iVar1," frames while playing ",uVar2);
      uVar2 = FUN_0081e660();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar4);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar1);
      uVar2 = FUN_004bc590(pbVar3);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
    FUN_00623ff0();
    FUN_0078c480(0);
    if (param_1[0x53] != 0) {
      FUN_007d21c0(param_1[0x53]);
    }
    FUN_007d21c0(param_1[0x52]);
    if ((undefined4 *)param_1[0x53] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x53])(1);
    }
    if ((undefined4 *)param_1[0x52] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x52])(1);
    }
    param_1[0x53] = 0;
    param_1[0x52] = 0;
  }
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

