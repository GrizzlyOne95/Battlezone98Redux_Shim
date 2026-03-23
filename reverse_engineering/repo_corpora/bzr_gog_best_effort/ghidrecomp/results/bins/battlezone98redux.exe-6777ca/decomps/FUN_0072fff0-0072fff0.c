
void __thiscall FUN_0072fff0(allocator<char> *param_1,allocator<char> *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_6;
  
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  uVar3 = std::allocator<char>::allocator<char>(param_2);
  cVar1 = FUN_0044bb90(uVar2,uVar3);
  if (cVar1 != '\0') {
    cVar1 = FUN_006dc8e0(uVar2,uVar3);
    if (cVar1 != '\0') {
      FUN_007306b0();
      FUN_00730690();
    }
  }
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (uVar2,uVar3,local_6);
  uVar4 = 0;
  uVar2 = FUN_006e1d50(0);
  uVar3 = FUN_006d0da0(uVar2);
  FUN_007322d0(uVar3,uVar2,uVar4);
  return;
}

