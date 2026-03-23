
void FUN_0062c100(int param_1)

{
  undefined4 *local_8;
  
  local_8 = DAT_02a1f498;
  do {
    if (local_8 == (undefined4 *)0x0) {
LAB_0062c149:
      FUN_008245a0(&DAT_02a1f49c,param_1);
      DAT_00920c64 = DAT_00920c64 + -1;
      return;
    }
    if (local_8[2] == param_1) {
      FUN_008245a0(&DAT_02a1f498,local_8);
      DAT_00920c64 = DAT_00920c64 + -1;
      goto LAB_0062c149;
    }
    local_8 = (undefined4 *)*local_8;
  } while( true );
}

