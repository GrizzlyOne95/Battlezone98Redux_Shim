
allocator<char> * __fastcall FUN_006ac110(allocator<char> *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_20 [8];
  undefined4 local_18;
  allocator<char> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ffb8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  local_18 = FUN_006ac190(uVar1);
  uVar2 = FUN_006abbb0();
  FUN_00416430(local_18,uVar2);
  FUN_006aba00(local_20,"mutex");
  ExceptionList = local_10;
  return local_14;
}

