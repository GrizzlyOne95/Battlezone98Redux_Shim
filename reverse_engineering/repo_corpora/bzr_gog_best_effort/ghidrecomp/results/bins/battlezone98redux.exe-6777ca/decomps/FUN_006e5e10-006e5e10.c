
void __thiscall FUN_006e5e10(int param_1,_Locinfo *param_2,char param_3)

{
  lconv *plVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uStack_a4;
  char *local_7c;
  undefined1 local_44 [44];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854550;
  local_10 = ExceptionList;
  uStack_a4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_a4;
  ExceptionList = &local_10;
  local_18 = uStack_a4;
  plVar1 = std::_Locinfo::_Getlconv(param_2);
  std::_Locinfo::_Getcvt(param_2);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  local_8 = 0;
  if (param_3 == '\0') {
    local_7c = plVar1->grouping;
  }
  else {
    local_7c = "";
  }
  uVar2 = std::_Locinfo::_Getcvt(param_2);
  uVar2 = FUN_006f1af0(local_7c,0,uVar2);
  *(undefined4 *)(param_1 + 8) = uVar2;
  pcVar3 = std::_Locinfo::_Getfalse(param_2);
  uVar2 = FUN_006f1af0(pcVar3,0,local_44);
  *(undefined4 *)(param_1 + 0x10) = uVar2;
  pcVar3 = std::_Locinfo::_Gettrue(param_2);
  uVar2 = FUN_006f1af0(pcVar3,0,local_44);
  *(undefined4 *)(param_1 + 0x14) = uVar2;
  FUN_006e5f50();
  return;
}

