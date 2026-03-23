
void __fastcall FUN_006d4a20(allocator<char> *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  puVar2 = (undefined4 *)FUN_00447eb0(uVar1);
  uVar1 = *puVar2;
  std::allocator<char>::allocator<char>(param_1);
  FUN_006decb0(uVar1);
  return;
}

