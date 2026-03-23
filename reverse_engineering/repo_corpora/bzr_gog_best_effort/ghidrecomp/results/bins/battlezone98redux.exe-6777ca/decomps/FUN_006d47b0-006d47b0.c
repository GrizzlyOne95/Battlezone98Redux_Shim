
void __thiscall FUN_006d47b0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853038;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006d1110(param_1);
  local_8 = 0;
  cVar1 = FUN_006d45c0(param_2);
  if (cVar1 == '\0') {
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  else {
    uVar3 = FUN_006b6270(param_2,&DAT_00898b64,param_3,&DAT_0087a44c,uVar2);
    pcVar5 = FUN_006d45f0;
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(*(undefined4 *)(param_1 + 0xc),&DAT_00871534,FUN_006d45f0,&DAT_00898b64,
                          &DAT_00871534,uVar3);
    pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar5);
    uVar3 = FUN_004bc590(pbVar4);
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_004bc590(uVar3);
    FUN_004bc590(uVar3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::flush
              (*(basic_ostream<char,struct_std::char_traits<char>_> **)(param_1 + 0xc));
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  ExceptionList = local_10;
  return;
}

