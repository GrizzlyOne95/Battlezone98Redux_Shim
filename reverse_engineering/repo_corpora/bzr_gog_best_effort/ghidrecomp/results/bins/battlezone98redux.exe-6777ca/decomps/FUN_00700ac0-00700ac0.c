
/* WARNING: Removing unreachable block (ram,0x00700acd) */

void __thiscall FUN_00700ac0(allocator<char> *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 local_8;
  
  local_8 = FUN_006d7740(param_2);
  puVar1 = &local_8;
  std::allocator<char>::allocator<char>(param_1);
  FUN_007054c0(puVar1);
  return;
}

