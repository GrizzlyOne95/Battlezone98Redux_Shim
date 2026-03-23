
void __thiscall FUN_0070bee0(allocator<char> *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857610;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00710240();
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  uVar3 = std::allocator<char>::allocator<char>(param_1);
  FUN_00416430(iVar1,uVar3);
  local_8 = 0;
  uVar3 = FUN_00417780(param_2);
  uVar3 = FUN_00417780(iVar1 + 0x10,uVar3);
  FUN_00717300(uVar2,uVar3);
  local_8 = CONCAT31(local_8._1_3_,1);
  uVar3 = FUN_00417780(iVar1 + 0x28);
  FUN_00717330(uVar2,uVar3);
  FUN_0070bfbd();
  return;
}

