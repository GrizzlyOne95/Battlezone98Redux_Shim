
void FUN_0066c0bd(void)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar1 = FUN_00669fa0();
  *(undefined4 *)(unaff_EBP + -0x1c) = uVar1;
  if (**(int **)(unaff_EBP + -0x14) != 0) {
    FUN_0066cab0(**(undefined4 **)(unaff_EBP + -0x14),
                 *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 4));
    iVar2 = (*(int *)(*(int *)(unaff_EBP + -0x14) + 8) - **(int **)(unaff_EBP + -0x14)) / 0x54;
    uVar1 = **(undefined4 **)(unaff_EBP + -0x14);
    std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr
              (*(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> **)
                (unaff_EBP + -0x14));
    FUN_004b3230(uVar1,iVar2);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x14));
  *(int *)(*(int *)(unaff_EBP + -0x14) + 8) =
       *(int *)(unaff_EBP + 8) * 0x54 + *(int *)(unaff_EBP + -0x18);
  *(int *)(*(int *)(unaff_EBP + -0x14) + 4) =
       *(int *)(unaff_EBP + -0x1c) * 0x54 + *(int *)(unaff_EBP + -0x18);
  **(undefined4 **)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x18);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

