
void FUN_007be465(void)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar1 = FUN_007be350();
  *(undefined4 *)(unaff_EBP + -0x20) = uVar1;
  if (**(int **)(unaff_EBP + -0x18) != 0) {
    FID_conflict__Destroy
              (**(undefined4 **)(unaff_EBP + -0x18),*(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 4)
              );
    iVar2 = (*(int *)(*(int *)(unaff_EBP + -0x18) + 8) - **(int **)(unaff_EBP + -0x18)) / 0x28;
    uVar1 = **(undefined4 **)(unaff_EBP + -0x18);
    Getal(unaff_EBP + -0x13);
    deallocate(uVar1,iVar2);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x18));
  *(int *)(*(int *)(unaff_EBP + -0x18) + 8) =
       *(int *)(unaff_EBP + 8) * 0x28 + *(int *)(unaff_EBP + -0x1c);
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       *(int *)(unaff_EBP + -0x20) * 0x28 + *(int *)(unaff_EBP + -0x1c);
  **(undefined4 **)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + -0x1c);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

