
void FUN_0068fb10(undefined4 *param_1)

{
  if ((&DAT_02ce9b18)[*(char *)(param_1 + 4) * 0x1e0] != '\0') {
    FUN_006a5fd0("AI_UnitAdd Team %d ptr %p\n",(int)*(char *)(param_1 + 4),*param_1);
    param_1[9] = 0;
    param_1[0xc] = 0;
    param_1[0x17] = 1;
    param_1[0x16] = 1;
    param_1[0x18] = 1;
    if ((*(uint *)(param_1[2] + 0x70) >> 1 & 1) == 0) {
      if ((*(int *)(param_1[2] + 0x74) == 0) && (*(int *)(param_1[2] + 0x78) == 0)) {
        if (param_1[0x15] == 2) {
          FUN_006a5fd0("AI_UnitAdd (Building Associated Unit)  Team %d Unit %p",
                       (int)*(char *)(param_1 + 4),*param_1);
        }
        else {
          FUN_006a5fd0("AI_UnitAdd (Combat)   Team %d Unit %p",(int)*(char *)(param_1 + 4),*param_1)
          ;
          FUN_00694ba0(param_1);
        }
      }
      else {
        FUN_006a5fd0("AI_UnitAdd (Water or Mineral transport)  Team %d Unit %p",
                     (int)*(char *)(param_1 + 4),*param_1);
      }
    }
    else {
      FUN_006a5fd0("AI_UnitAdd (CC)       Team %d Unit %p",(int)*(char *)(param_1 + 4),*param_1);
      FUN_00690770(*(undefined4 *)(DAT_00920f04 + *(char *)(param_1 + 4) * 4),param_1);
    }
  }
  return;
}

