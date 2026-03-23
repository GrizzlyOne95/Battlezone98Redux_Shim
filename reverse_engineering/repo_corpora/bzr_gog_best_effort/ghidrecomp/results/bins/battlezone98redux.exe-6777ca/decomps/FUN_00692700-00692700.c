
void FUN_00692700(undefined4 *param_1)

{
  int iVar1;
  undefined1 local_68 [4];
  undefined4 local_64;
  int local_60;
  int local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006a3c40(local_58,*param_1);
  while (local_5c = FUN_006a3c70(local_58), local_5c != 0) {
    iVar1 = _Val_type<>(local_5c);
    if ((iVar1 != 0) &&
       (local_60 = FUN_00690fc0(param_1,**(undefined2 **)(local_5c + 0x14),1,&local_64,local_68,
                                local_68), local_60 != 0)) {
      *(undefined4 *)(local_5c + 0x20) = local_64;
      *(undefined4 *)(local_5c + 0x24) =
           *(undefined4 *)(*(int *)(*(int *)(local_5c + 0x14) + 8) + 0x20);
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(local_5c);
    }
  }
  FUN_0083e885();
  return;
}

