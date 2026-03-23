
void FUN_00732750(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  allocator<char> *paStack_38;
  undefined4 *puStack_34;
  uint uStack_30;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  allocator<char> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859c98;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_34 = (undefined4 *)param_3;
  paStack_38 = (allocator<char> *)0x732784;
  FUN_006decb0();
  puStack_34 = (undefined4 *)0x73278c;
  cVar1 = FUN_00730540();
  if (cVar1 == '\0') {
    puStack_34 = &param_3;
    paStack_38 = local_14;
    uStack_3c = 0x7327a7;
    FUN_00416430();
    local_8 = 0;
    puStack_34 = (undefined4 *)0x7327b9;
    local_18 = FUN_006d4b30();
    puStack_34 = (undefined4 *)0x7327c7;
    local_1c = FUN_006d4b30();
    puStack_34 = (undefined4 *)0x7327d5;
    uStack_3c = std::allocator<char>::allocator<char>(local_14 + 4);
    local_20 = (undefined1 *)&paStack_38;
    uStack_40 = param_3;
    FUN_006e4350();
    uStack_3c = 0x7327f2;
    uVar2 = std::allocator<char>::allocator<char>(local_14 + 4);
    local_24 = (undefined1 *)&uStack_40;
    FUN_006e4350(param_2,uVar2);
    FUN_00734010(&local_1c,&local_18);
    puStack_34 = (undefined4 *)0x73281c;
    std::allocator<char>::allocator<char>(param_1);
    puStack_34 = (undefined4 *)0x732823;
    puStack_34 = (undefined4 *)get();
    paStack_38 = (allocator<char> *)0x73282c;
    std::allocator<char>::allocator<char>(local_14);
    paStack_38 = (allocator<char> *)0x732833;
    FUN_0045ba10();
    puStack_34 = (undefined4 *)0x73283e;
    puStack_34 = (undefined4 *)FUN_006d0d10();
    paStack_38 = (allocator<char> *)0x73284a;
    FUN_006d0d10();
    paStack_38 = (allocator<char> *)0x732851;
    FUN_007305a0();
    puStack_34 = (undefined4 *)0x732859;
    FUN_00703d50();
    local_8 = 0xffffffff;
    puStack_34 = (undefined4 *)0x732868;
    FUN_00730900();
  }
  ExceptionList = local_10;
  return;
}

