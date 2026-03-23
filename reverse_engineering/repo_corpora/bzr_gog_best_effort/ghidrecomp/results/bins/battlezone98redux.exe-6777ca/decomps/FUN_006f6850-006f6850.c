
int FUN_006f6850(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  int local_10;
  
  uVar1 = param_1 - param_2;
  if (uVar1 < param_3) {
    FUN_006bdf90("get_next_capacity, allocator\'s max_size reached");
  }
  puVar2 = (uint *)FUN_006ff5b0(&param_3,&param_2);
  if (uVar1 < *puVar2) {
    local_10 = param_1;
  }
  else {
    local_10 = param_2 + *puVar2;
  }
  return local_10;
}

