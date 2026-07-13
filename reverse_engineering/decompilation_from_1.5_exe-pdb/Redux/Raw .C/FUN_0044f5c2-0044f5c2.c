
undefined4 FUN_0044f5c2(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = size();
  *(int *)(unaff_EBP + 0x10) = iVar1 + *(int *)(unaff_EBP + 0x10);
  if (**(int **)(unaff_EBP + -0x18) != 0) {
    FID_conflict__Destroy
              (**(undefined4 **)(unaff_EBP + -0x18),*(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 4)
              );
    iVar1 = *(int *)(*(int *)(unaff_EBP + -0x18) + 8) - **(int **)(unaff_EBP + -0x18) >> 2;
    uVar2 = **(undefined4 **)(unaff_EBP + -0x18);
    Getal(unaff_EBP + -0x13);
    FUN_0044f3e0(uVar2,iVar1);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x18));
  *(int *)(*(int *)(unaff_EBP + -0x18) + 8) =
       *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + -0x2c) * 4;
  *(int *)(*(int *)(unaff_EBP + -0x18) + 4) =
       *(int *)(unaff_EBP + -0x1c) + *(int *)(unaff_EBP + 0x10) * 4;
  **(undefined4 **)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + -0x1c);
  uVar2 = *(undefined4 *)(unaff_EBP + -0x38);
  uVar3 = *(undefined4 *)(unaff_EBP + 8);
  FID_conflict_begin(unaff_EBP + -0x3c);
  FID_conflict_operator_(uVar3,uVar2);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

