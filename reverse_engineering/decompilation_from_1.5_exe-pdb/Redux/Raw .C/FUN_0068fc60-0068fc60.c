
void FUN_0068fc60(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if ((DAT_00930f08 != 0) && ((&DAT_02ce9b18)[*(char *)(param_1 + 4) * 0x1e0] != '\0')) {
    uVar1 = *(undefined4 *)(DAT_00920f04 + *(char *)(param_1 + 4) * 4);
    FUN_006a5fd0("AI_UnitRemove Team %d Unit %p\n",(int)*(char *)(param_1 + 4),*param_1,uVar1);
    if ((*(uint *)(param_1[2] + 0x70) >> 1 & 1) == 0) {
      if ((*(int *)(param_1[2] + 0x74) == 0) && (*(int *)(param_1[2] + 0x78) == 0)) {
        if (param_1[0x15] == 2) {
          FUN_006a5fd0("AI_UnitRemove (Building Associated Unit)   Team %d Unit %p",
                       (int)*(char *)(param_1 + 4),*param_1,uVar1);
        }
        else {
          FUN_006a5fd0("AI_UnitRemove (Combat)   Team %d Unit %p",(int)*(char *)(param_1 + 4),
                       *param_1,uVar1);
          FUN_00694c10(param_1);
        }
      }
      else {
        FUN_006a5fd0("AI_UnitRemove (Water or Mineral transport)  Team %d Unit %p",
                     (int)*(char *)(param_1 + 4),*param_1,uVar1);
      }
    }
    else {
      FUN_006a5fd0("AI_UnitRemove (CC)       Team %d Unit %o",(int)*(char *)(param_1 + 4),*param_1,
                   uVar1);
      if (param_1[0xc] == 0) {
        FUN_006a5fd0("  Removing unassigned construction crew\n");
        FUN_006907b0(*(undefined4 *)(DAT_00920f04 + *(char *)(param_1 + 4) * 4),param_1);
      }
      else if (param_1[0xe] == 0) {
        FUN_006a5fd0("  Removing assigned construction crew - shot dead\n");
        FUN_006905d0((int)*(char *)(param_1 + 4),param_1[0xc]);
        FUN_00690920((int)*(char *)(param_1 + 4),param_1[0xf]);
        FUN_00690020((int)*(char *)(param_1 + 4),0,param_1);
      }
      else {
        FUN_006a5fd0("  Removing assigned construction crew with bldg under construction\n");
        FUN_00690920((int)*(char *)(param_1 + 4),param_1[0xf]);
      }
    }
  }
  return;
}

