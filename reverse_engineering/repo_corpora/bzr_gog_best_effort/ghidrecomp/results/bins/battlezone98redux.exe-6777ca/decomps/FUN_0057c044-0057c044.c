
void FUN_0057c044(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 uVar2;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_004bb390();
  *(int *)(unaff_EBP + -0x1c) = iVar1 + *(int *)(unaff_EBP + -0x1c);
  if (**(int **)(unaff_EBP + -0x18) != 0) {
    FID_conflict__Destroy
              (**(undefined4 **)(unaff_EBP + -0x18),*(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 4)
              );
    iVar1 = *(int *)(*(int *)(unaff_EBP + -0x18) + 8) - **(int **)(unaff_EBP + -0x18);
    uVar2 = **(undefined4 **)(unaff_EBP + -0x18);
    Getal(unaff_EBP + -0x13);
    deallocate(uVar2,iVar1);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x18));
  *(int *)(*(int *)(unaff_EBP + -0x18) + 8) =
       *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + -0x28);
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + -0x1c);
  **(undefined4 **)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + -0x20);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

