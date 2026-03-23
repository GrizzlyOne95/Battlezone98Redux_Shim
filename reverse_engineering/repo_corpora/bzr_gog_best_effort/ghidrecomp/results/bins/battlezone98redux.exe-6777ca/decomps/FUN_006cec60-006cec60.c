
void __fastcall FUN_006cec60(_Container_base0 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5;
  
  if (*(int *)param_1 != 0) {
    std::_Container_base0::_Orphan_all(param_1);
    FID_conflict__Destroy(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    iVar1 = *(int *)(param_1 + 8) - *(int *)param_1 >> 4;
    uVar2 = *(undefined4 *)param_1;
    Getal(&local_5);
    deallocate(uVar2,iVar1);
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

