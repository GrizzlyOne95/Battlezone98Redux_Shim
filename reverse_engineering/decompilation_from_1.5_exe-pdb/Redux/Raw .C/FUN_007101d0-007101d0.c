
void __fastcall FUN_007101d0(_Container_base0 *param_1)

{
  std::_Container_base0::_Orphan_all(param_1);
  FID_conflict__Destroy(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)param_1;
  return;
}

