
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00792d30(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  int *piVar4;
  code *pcVar5;
  code *pcVar6;
  int local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853818;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x14c) != 0) {
    DAT_00945548 = 1;
    if (*(char *)(param_1 + 0x15c) == '\0') {
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
      FUN_0078c480(0);
      if (*(int *)(param_1 + 0x14c) != 0) {
        FUN_007d21c0(*(undefined4 *)(param_1 + 0x14c));
      }
      FUN_007d21c0(*(undefined4 *)(param_1 + 0x148));
      if (*(undefined4 **)(param_1 + 0x14c) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0x14c))(1);
      }
      if (*(undefined4 **)(param_1 + 0x148) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0x148))(1);
      }
      *(undefined4 *)(param_1 + 0x14c) = 0;
      *(undefined4 *)(param_1 + 0x148) = 0;
      iVar1 = FUN_007d2250();
      for (local_34 = 0; local_34 < iVar1; local_34 = local_34 + 1) {
        piVar4 = (int *)FUN_007d2270(local_34);
        (**(code **)(*piVar4 + 0x24))(1);
      }
      FUN_007932c0();
    }
    else {
      FUN_00623ff0();
      FUN_0078c480(0);
      if (*(int *)(param_1 + 0x14c) != 0) {
        FUN_007d21c0(*(undefined4 *)(param_1 + 0x14c));
      }
      FUN_007d21c0(*(undefined4 *)(param_1 + 0x148));
      if (*(undefined4 **)(param_1 + 0x14c) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0x14c))(1);
      }
      if (*(undefined4 **)(param_1 + 0x148) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0x148))(1);
      }
      *(undefined4 *)(param_1 + 0x14c) = 0;
      *(undefined4 *)(param_1 + 0x148) = 0;
      FUN_007c9170(0);
      FUN_0081e0c0("Game stopped after mission success video\n");
      FUN_00434170(2);
      _DAT_00918330 = 1;
      DAT_00918328 = 0;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

