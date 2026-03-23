
undefined1 * __fastcall FUN_007c3d10(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  
  uVar1 = size();
  if (*(uint *)(param_1 + 0x1dc) < uVar1) {
    puVar3 = (undefined4 *)FUN_004200d0(*(undefined4 *)(param_1 + 0x1dc));
    puVar2 = (undefined1 *)std::allocator<char>::allocator<char>((allocator<char> *)*puVar3);
  }
  else {
    puVar2 = &DAT_008a1ad8;
  }
  return puVar2;
}

