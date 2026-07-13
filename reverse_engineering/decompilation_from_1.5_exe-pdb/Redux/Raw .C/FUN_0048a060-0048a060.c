
/* WARNING: Removing unreachable block (ram,0x0048a0c8) */

_Container_base0 * __thiscall FUN_0048a060(_Container_base0 *param_1,_Container_base0 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  _Container_base0 *p_Var4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uStack_38;
  undefined1 local_18 [2];
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849160;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_38;
  ExceptionList = &local_10;
  if (param_1 != param_2) {
    uVar2 = Getal(&local_15);
    uVar3 = Getal(&local_16);
    operator!=<>(uVar3,uVar2);
    std::_Container_base0::_Orphan_all(param_1);
    cVar1 = FUN_0041fc90();
    if (cVar1 != '\0') {
      FUN_0048a850();
      p_Var4 = (_Container_base0 *)FUN_0048a28b();
      return p_Var4;
    }
    uVar5 = FUN_0048a830();
    uVar6 = FUN_0048a830();
    if (uVar6 <= uVar5) {
      uVar2 = _Move<>(*(int *)param_2,*(int *)(param_2 + 4),*(undefined4 *)param_1);
      FID_conflict__Destroy(uVar2,*(undefined4 *)(param_1 + 4));
      iVar7 = FUN_0048a830();
      *(int *)(param_1 + 4) = iVar7 * 0x18 + *(int *)param_1;
      p_Var4 = (_Container_base0 *)FUN_0048a28b();
      return p_Var4;
    }
    uVar5 = FUN_0048a810();
    uVar6 = FUN_0048a830();
    if (uVar6 <= uVar5) {
      iVar7 = FUN_0048a830();
      iVar7 = iVar7 * 0x18 + *(int *)param_2;
      _Move<>(*(int *)param_2,iVar7,*(undefined4 *)param_1);
      uVar2 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                        (iVar7,*(int *)(param_2 + 4),*(undefined4 *)(param_1 + 4));
      *(undefined4 *)(param_1 + 4) = uVar2;
      p_Var4 = (_Container_base0 *)FUN_0048a28b();
      return p_Var4;
    }
    if (*(int *)param_1 != 0) {
      FID_conflict__Destroy(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
      iVar7 = (*(int *)(param_1 + 8) - *(int *)param_1) / 0x18;
      uVar2 = *(undefined4 *)param_1;
      Getal(local_18);
      deallocate(uVar2,iVar7);
    }
    uVar2 = FUN_0048a830();
    cVar1 = FUN_0048a890(uVar2);
    if (cVar1 != '\0') {
      local_8 = 0;
      uVar2 = FID_conflict__Ucopy<class_std::move_iterator<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>_>
                        (*(int *)param_2,*(int *)(param_2 + 4),*(undefined4 *)param_1);
      *(undefined4 *)(param_1 + 4) = uVar2;
      p_Var4 = (_Container_base0 *)FUN_0048a27b();
      return p_Var4;
    }
  }
  ExceptionList = local_10;
  return param_1;
}

