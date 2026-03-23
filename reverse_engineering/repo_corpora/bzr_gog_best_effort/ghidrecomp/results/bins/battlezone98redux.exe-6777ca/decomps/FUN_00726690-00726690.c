
int __thiscall FUN_00726690(int param_1,int param_2)

{
  undefined4 local_c;
  
  FUN_004178a0(param_2);
  if (*(uint *)(param_1 + 8) < *(uint *)(param_2 + 8)) {
    local_c = -(*(int *)(param_2 + 8) - *(int *)(param_1 + 8));
  }
  else {
    local_c = *(int *)(param_1 + 8) - *(int *)(param_2 + 8);
  }
  return local_c;
}

