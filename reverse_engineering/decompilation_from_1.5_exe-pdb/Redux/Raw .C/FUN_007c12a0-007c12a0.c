
void __fastcall FUN_007c12a0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int *piVar4;
  code *pcVar5;
  code *pcVar6;
  int local_38;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858b58;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x148) != 0) {
    DAT_008e8c7f = 0;
    iVar1 = FUN_007d4450(local_14);
    if (10 < iVar1) {
      uVar2 = FUN_007d43e0(local_2c);
      local_8 = 0;
      pcVar6 = FUN_004bc8c0;
      pcVar5 = FUN_0056f740;
      FUN_0081e820("Skipped ",FUN_0056f740,iVar1," frames while playing ",uVar2);
      uVar2 = FUN_0081e660();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
      pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar1);
      uVar2 = FUN_004bc590(pbVar3);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar6);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    FUN_00623ff0();
    FUN_007d21c0(*(undefined4 *)(param_1 + 0x148));
    FUN_007d21c0(*(undefined4 *)(param_1 + 0x144));
    if (*(undefined4 **)(param_1 + 0x148) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x148))(1);
    }
    if (*(undefined4 **)(param_1 + 0x144) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x144))(1);
    }
    *(undefined4 *)(param_1 + 0x148) = 0;
    *(undefined4 *)(param_1 + 0x144) = 0;
    FUN_0078c480(0);
    iVar1 = FUN_007d2250();
    for (local_38 = 0; local_38 < iVar1; local_38 = local_38 + 1) {
      piVar4 = (int *)FUN_007d2270(local_38);
      (**(code **)(*piVar4 + 0x24))(1);
    }
    (**(code **)(**(int **)(param_1 + 0x15c) + 0x24))(DAT_009455dc == '\0');
    (**(code **)(**(int **)(param_1 + 0x160) + 0x24))(DAT_009455dc);
    (**(code **)(**(int **)(param_1 + 0x164) + 0x24))(DAT_009455dc == '\0');
    (**(code **)(**(int **)(param_1 + 0x168) + 0x24))(DAT_009455dc);
    FUN_007c1780();
    FUN_007d3e80(0x3c,0x59,0);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

