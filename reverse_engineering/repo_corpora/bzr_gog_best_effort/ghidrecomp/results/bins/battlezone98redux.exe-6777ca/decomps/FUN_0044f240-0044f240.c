
void __fastcall FUN_0044f240(_Container_base0 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5;
  
  if (*(int *)param_1 != 0) {
    std::_Container_base0::_Orphan_all(param_1);
    FID_conflict__Destroy(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    iVar1 = *(int *)(param_1 + 8) - *(int *)param_1 >> 2;
    uVar2 = *(undefined4 *)param_1;
    Getal(&local_5);
    FUN_0044f3e0(uVar2,iVar1);
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

