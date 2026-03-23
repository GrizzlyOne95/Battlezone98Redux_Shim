
void __thiscall FUN_007a7c60(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_20;
  uint local_18;
  undefined1 local_6;
  _Wrap_alloc<class_std::allocator<unsigned_char>_> local_5;
  
  uVar2 = Getal(&local_6);
  FUN_00423c20(uVar2);
  if (*(int *)(param_1 + 8) == 0) {
    local_20 = 1;
  }
  else {
    local_20 = *(uint *)(param_1 + 8);
  }
  for (local_18 = local_20; (local_18 - *(int *)(param_1 + 8) < param_2 || (local_18 < 8));
      local_18 = local_18 << 1) {
    iVar3 = FID_conflict_max_size();
    if (iVar3 - local_18 < local_18) {
      FUN_004bc060();
    }
  }
  local_18 = local_18 - *(int *)(param_1 + 8);
  uVar1 = *(uint *)(param_1 + 0xc);
  iVar3 = allocate(*(int *)(param_1 + 8) + local_18);
  uVar2 = FUN_004bcb10(*(int *)(param_1 + 4) + uVar1 * 4,
                       *(int *)(param_1 + 4) + *(int *)(param_1 + 8) * 4,iVar3 + uVar1 * 4,&local_5)
  ;
  if (local_18 < uVar1) {
    FUN_004bcb10(*(undefined4 *)(param_1 + 4),*(int *)(param_1 + 4) + local_18 * 4,uVar2,&local_5);
    uVar2 = FUN_004bcb10(*(int *)(param_1 + 4) + local_18 * 4,*(int *)(param_1 + 4) + uVar1 * 4,
                         iVar3,&local_5);
    FUN_004276e0(uVar2,local_18,&local_5);
  }
  else {
    uVar2 = FUN_004bcb10(*(undefined4 *)(param_1 + 4),*(int *)(param_1 + 4) + uVar1 * 4,uVar2,
                         &local_5);
    FUN_004276e0(uVar2,local_18 - uVar1,&local_5);
    FUN_004276e0(iVar3,uVar1,&local_5);
  }
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            ((uchar *)(*(int *)(param_1 + 4) + uVar1 * 4),
             (uchar *)(*(int *)(param_1 + 4) + *(int *)(param_1 + 8) * 4),&local_5);
  if (*(int *)(param_1 + 4) != 0) {
    deallocate(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  }
  *(int *)(param_1 + 4) = iVar3;
  *(uint *)(param_1 + 8) = *(int *)(param_1 + 8) + local_18;
  return;
}

