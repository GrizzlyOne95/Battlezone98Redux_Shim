
void __fastcall FUN_0078cb40(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  int *piVar5;
  code *pcVar6;
  code *pcVar7;
  int local_38;
  undefined1 local_31;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085eb28;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x164) != 0) {
    DAT_008e8c7e = 0;
    iVar2 = FUN_007d4450(local_14);
    if (10 < iVar2) {
      uVar3 = FUN_007d43e0(local_2c);
      local_8 = 0;
      pcVar7 = FUN_004bc8c0;
      pcVar6 = FUN_0056f740;
      FUN_0081e820("Skipped ",FUN_0056f740,iVar2," frames while playing ",uVar3);
      uVar3 = FUN_0081e660();
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
      pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
      pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,iVar2);
      uVar3 = FUN_004bc590(pbVar4);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    FUN_00623ff0();
    FUN_0078e5f0();
    FUN_007d21c0(*(undefined4 *)(param_1 + 0x164));
    FUN_007d21c0(*(undefined4 *)(param_1 + 0x160));
    if (*(undefined4 **)(param_1 + 0x164) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x164))(1);
    }
    if (*(undefined4 **)(param_1 + 0x160) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x160))(1);
    }
    *(undefined4 *)(param_1 + 0x164) = 0;
    *(undefined4 *)(param_1 + 0x160) = 0;
    FUN_0078c480(0);
    iVar2 = FUN_007d2250();
    for (local_38 = 0; local_38 < iVar2; local_38 = local_38 + 1) {
      piVar5 = (int *)FUN_007d2270(local_38);
      (**(code **)(*piVar5 + 0x24))(1);
    }
    if (*(int *)(param_1 + 0x178) != 0) {
      piVar5 = (int *)FUN_007647b0();
      if ((piVar5 == (int *)0x0) || (cVar1 = (**(code **)(*piVar5 + 4))(), cVar1 == '\0')) {
        local_31 = 0;
      }
      else {
        local_31 = 1;
      }
      (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(local_31);
    }
    FUN_007cc5c0(1);
    if (*(int *)(param_1 + 0x16c) != 0) {
      FUN_007cc5c0(1);
    }
    FUN_0078dde0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

