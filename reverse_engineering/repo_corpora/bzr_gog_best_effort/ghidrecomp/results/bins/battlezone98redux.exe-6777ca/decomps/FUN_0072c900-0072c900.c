
allocator<char> * __thiscall FUN_0072c900(allocator<char> *param_1,allocator<char> *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_40 [28];
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  allocator<char> *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859a78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = param_1;
  if (param_2 != param_1) {
    local_24 = FUN_006d0d10(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_20 = FUN_006d0d10();
    cVar1 = FUN_0044bb90();
    if (cVar1 != '\0') {
      cVar1 = FUN_006dc8e0(local_24,local_20);
      if (cVar1 != '\0') {
        FUN_0072d4c0();
      }
    }
    FUN_0072d4e0(param_2);
    uVar2 = std::allocator<char>::allocator<char>(local_18);
    uVar2 = FUN_00417780(uVar2);
    FUN_0072d550(uVar2);
    local_8 = 0;
    uVar2 = std::allocator<char>::allocator<char>(local_18);
    puVar3 = (undefined4 *)FUN_00447eb0(uVar2);
    uVar2 = *puVar3;
    puVar3 = (undefined4 *)FUN_00416430(local_18,local_40);
    uVar6 = puVar3[1];
    uVar5 = *puVar3;
    uVar4 = std::allocator<char>::allocator<char>(param_2);
    std::allocator<char>::allocator<char>(local_18);
    FUN_007301c0(uVar4,uVar5,uVar6,uVar2);
    while( true ) {
      local_1c = FUN_0072d580();
      if (local_1c == 0) break;
      FUN_0072d510(&local_1c);
    }
    local_8 = 0xffffffff;
    FUN_006d1400();
  }
  ExceptionList = local_10;
  return local_18;
}

