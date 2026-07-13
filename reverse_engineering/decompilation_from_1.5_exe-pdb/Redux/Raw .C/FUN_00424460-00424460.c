
uint FUN_00424460(uint param_1)

{
  undefined4 local_8;
  
  local_8 = 0;
  if ((param_1 & 1) == 0) {
    local_8 = 4;
  }
  if ((param_1 & 2) == 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 0x10;
  }
  return local_8;
}

