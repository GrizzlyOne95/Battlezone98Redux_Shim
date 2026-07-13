
/* WARNING: Removing unreachable block (ram,0x0067af80) */

_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> * __thiscall
FUN_0067af20(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
            _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_2)

{
  char cVar1;
  _ExceptionHolder *p_Var2;
  _ExceptionHolder *p_Var3;
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *p_Var4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f4c0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_1 != param_2) {
    p_Var2 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_2);
    p_Var3 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
    operator!=<>(p_Var3,p_Var2);
    std::_Container_base0::_Orphan_all((_Container_base0 *)param_1);
    cVar1 = FUN_0041fc90();
    if (cVar1 != '\0') {
      FUN_0067b3a0();
      p_Var4 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_0067b136();
      return p_Var4;
    }
    uVar5 = size();
    uVar6 = size();
    if (uVar6 <= uVar5) {
      uVar7 = _Move<>(*(undefined4 *)param_2,*(undefined4 *)(param_2 + 4),*(undefined4 *)param_1);
      FUN_0067b470(uVar7,*(undefined4 *)(param_1 + 4));
      iVar8 = size();
      *(int *)(param_1 + 4) = *(int *)param_1 + iVar8 * 4;
      p_Var4 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_0067b136();
      return p_Var4;
    }
    uVar5 = FID_conflict_capacity();
    uVar6 = size();
    if (uVar6 <= uVar5) {
      iVar8 = size();
      iVar8 = *(int *)param_2 + iVar8 * 4;
      _Move<>(*(undefined4 *)param_2,iVar8,*(undefined4 *)param_1);
      uVar7 = FUN_0067bb80(iVar8,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_1 + 4));
      *(undefined4 *)(param_1 + 4) = uVar7;
      p_Var4 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_0067b136();
      return p_Var4;
    }
    if (*(int *)param_1 != 0) {
      FUN_0067b470(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
      iVar8 = *(int *)(param_1 + 8) - *(int *)param_1 >> 2;
      uVar7 = *(undefined4 *)param_1;
      std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
      FUN_004b3230(uVar7,iVar8);
    }
    uVar7 = size();
    cVar1 = FUN_0067b3e0(uVar7);
    if (cVar1 != '\0') {
      local_8 = 0;
      uVar7 = FUN_0067bb80(*(undefined4 *)param_2,*(undefined4 *)(param_2 + 4),
                           *(undefined4 *)param_1);
      *(undefined4 *)(param_1 + 4) = uVar7;
      p_Var4 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_0067b126();
      return p_Var4;
    }
  }
  ExceptionList = local_10;
  return param_1;
}

