
void __thiscall FUN_006b3570(undefined4 *param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_34 [4];
  undefined4 *local_30;
  allocator<char> local_2c [16];
  undefined1 local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  local_30 = param_1;
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    *(undefined2 *)local_30 = 0x17;
    uVar2 = FUN_006b0010(param_3);
    *(undefined2 *)((int)local_30 + 2) = uVar2;
    local_30[1] = 0;
    FUN_006b3340(local_1c);
    FUN_006b2fb0(local_2c);
    puVar4 = (undefined4 *)std::allocator<char>::allocator<char>(local_2c);
    local_30[2] = *puVar4;
    local_30[3] = puVar4[1];
    local_30[4] = puVar4[2];
    local_30[5] = puVar4[3];
    uVar3 = FUN_004170c0();
    local_30[6] = uVar3;
  }
  else {
    *(undefined2 *)local_30 = 2;
    uVar2 = FUN_006b0010(param_3);
    *(undefined2 *)((int)local_30 + 2) = uVar2;
    FUN_006b32b0(local_34);
    uVar3 = FUN_006b2e30();
    uVar3 = FUN_006afff0(uVar3);
    local_30[1] = uVar3;
  }
  FUN_0083e885();
  return;
}

