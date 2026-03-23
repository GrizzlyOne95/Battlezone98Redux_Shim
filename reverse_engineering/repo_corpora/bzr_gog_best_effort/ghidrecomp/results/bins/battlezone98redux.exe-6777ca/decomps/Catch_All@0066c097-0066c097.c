
void Catch_All_0066c097(void)

{
  int unaff_EBP;
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(unaff_EBP + 8);
  uVar1 = *(undefined4 *)(unaff_EBP + -0x18);
  std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr
            (*(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> **)(unaff_EBP + -0x14))
  ;
  FUN_004b3230(uVar1,uVar2);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

