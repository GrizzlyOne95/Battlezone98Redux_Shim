
void __thiscall FUN_00430530(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = FID_conflict_max_size();
  if ((iVar1 - *(int *)(param_1 + 4)) - 1U < param_2) {
                    /* WARNING: Subroutine does not return */
    std::_Xlength_error("list<T> too long");
  }
  *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_2;
  return;
}

