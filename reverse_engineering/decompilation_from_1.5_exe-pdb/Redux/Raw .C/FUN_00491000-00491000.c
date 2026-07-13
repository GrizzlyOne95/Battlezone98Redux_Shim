
int * __thiscall
FUN_00491000(int param_1,int param_2,int param_3,int param_4,float param_5,float param_6)

{
  int *local_8;
  
  for (local_8 = (int *)(param_1 + 0x28); (local_8 < *(int **)(param_1 + 0x5028) && (*local_8 != 0))
      ; local_8 = local_8 + 5) {
  }
  if (local_8 == *(int **)(param_1 + 0x5028)) {
    *(int *)(param_1 + 0x5028) = *(int *)(param_1 + 0x5028) + 0x14;
  }
  *local_8 = param_2;
  local_8[1] = param_3;
  local_8[2] = param_4;
  local_8[3] = (int)param_5;
  local_8[4] = (int)(((param_6 - 1.0) * param_5 * (float)local_8[2]) / (float)local_8[1]);
  return local_8;
}

