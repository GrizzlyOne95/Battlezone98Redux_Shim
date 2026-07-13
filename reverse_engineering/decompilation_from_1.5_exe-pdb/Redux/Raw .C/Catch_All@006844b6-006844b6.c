
void Catch_All_006844b6(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  FUN_00683c40(*(undefined4 *)(unaff_EBP + -0x1c),*(undefined4 *)(unaff_EBP + -0x20));
  uVar2 = *(undefined4 *)(unaff_EBP + -0x24);
  uVar1 = *(undefined4 *)(unaff_EBP + -0x1c);
  std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr
            (*(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> **)(unaff_EBP + -0x14))
  ;
  FUN_004b3230(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

