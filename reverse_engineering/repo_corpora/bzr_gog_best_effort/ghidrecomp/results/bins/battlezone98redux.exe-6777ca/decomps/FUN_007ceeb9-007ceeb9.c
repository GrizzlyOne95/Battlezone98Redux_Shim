
void FUN_007ceeb9(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_0048a830();
  *(int *)(unaff_EBP + 0x10) = iVar1 + *(int *)(unaff_EBP + 0x10);
  if (**(int **)(unaff_EBP + -0x48) != 0) {
    FID_conflict__Destroy
              (**(undefined4 **)(unaff_EBP + -0x48),*(undefined4 *)(*(int *)(unaff_EBP + -0x48) + 4)
              );
    iVar1 = (*(int *)(*(int *)(unaff_EBP + -0x48) + 8) - **(int **)(unaff_EBP + -0x48)) / 0x18;
    uVar2 = **(undefined4 **)(unaff_EBP + -0x48);
    Getal(unaff_EBP + -0x5f);
    deallocate(uVar2,iVar1);
  }
  std::_Container_base0::_Orphan_all(*(_Container_base0 **)(unaff_EBP + -0x48));
  *(int *)(*(int *)(unaff_EBP + -0x48) + 8) =
       *(int *)(unaff_EBP + -0x5c) * 0x18 + *(int *)(unaff_EBP + -0x4c);
  *(int *)(*(int *)(unaff_EBP + -0x48) + 4) =
       *(int *)(unaff_EBP + 0x10) * 0x18 + *(int *)(unaff_EBP + -0x4c);
  **(undefined4 **)(unaff_EBP + -0x48) = *(undefined4 *)(unaff_EBP + -0x4c);
  uVar2 = *(undefined4 *)(unaff_EBP + -100);
  uVar3 = *(undefined4 *)(unaff_EBP + 8);
  FID_conflict_begin(unaff_EBP + -0x68);
  FID_conflict_operator_(uVar3,uVar2);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

