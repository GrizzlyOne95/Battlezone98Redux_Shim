
void __fastcall FUN_00821e30(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0061a000(param_1);
  if (iVar1 == 0) {
    FUN_007d65d0("Fsm error: Camera Stack Underfow");
  }
  DAT_00946738 = 0;
  DAT_0094673c = 0;
  DAT_00946740 = 3;
  iVar1 = FUN_00439e60();
  FUN_00688760(iVar1,*(undefined4 *)(*(int *)(iVar1 + 0x38) + 8),0,
               *(undefined4 *)(*(int *)(iVar1 + 0x38) + 0x10),
               *(undefined4 *)(*(int *)(iVar1 + 0x38) + 4));
  DAT_008eaad8 = 5;
  DAT_008eaad4 = 0;
  DAT_008eaad0 = std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
  ;
  return;
}

