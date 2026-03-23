
void FUN_006844ec(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 uVar2;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = size();
  *(int *)(unaff_EBP + -0x18) = iVar1 + *(int *)(unaff_EBP + -0x18);
  if (**(int **)(unaff_EBP + -0x14) != 0) {
    FUN_00683c40(**(undefined4 **)(unaff_EBP + -0x14),
                 *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 4));
    iVar1 = *(int *)(*(int *)(unaff_EBP + -0x14) + 8) - **(int **)(unaff_EBP + -0x14) >> 2;
    uVar2 = **(undefined4 **)(unaff_EBP + -0x14);
    std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr
              (*(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> **)
                (unaff_EBP + -0x14));
    FUN_004b3230(uVar2,iVar1);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x14));
  *(int *)(*(int *)(unaff_EBP + -0x14) + 8) =
       *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x24) * 4;
  *(int *)(*(int *)(unaff_EBP + -0x14) + 4) =
       *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x18) * 4;
  **(undefined4 **)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x1c);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

