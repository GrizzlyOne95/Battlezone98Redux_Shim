
void FUN_006b04a0(void)

{
  undefined1 local_14 [8];
  int *local_c;
  undefined1 local_5;
  
  FUN_004fbb60();
  local_5 = 2;
  if (*local_c != -1) {
    FUN_006ae9c0(*local_c,&local_5,1,local_14);
  }
  if (local_c[1] != -1) {
    FUN_006ae9c0(local_c[1],&local_5,1,local_14);
  }
  return;
}

