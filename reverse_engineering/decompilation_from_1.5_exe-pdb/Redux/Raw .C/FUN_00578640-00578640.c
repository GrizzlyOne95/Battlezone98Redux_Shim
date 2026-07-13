
void __thiscall FUN_00578640(undefined4 param_1,undefined4 param_2,char param_3)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  if ((DAT_00917f48 != 0) && (iVar1 = FUN_00577200(param_2,param_1), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x8e) == '\0') {
      if (param_3 == '\0') {
        uVar2 = FUN_0041f870(*(undefined2 *)(iVar1 + 0x28),*(undefined1 *)(iVar1 + 0x68));
        uVar2 = FUN_0081cb40("multi_message","player_left",uVar2);
        FUN_0056fcb0("%s: %s (%ld,%d)",uVar2);
      }
      else {
        uVar2 = FUN_0041f870();
        uVar2 = FUN_0081cb40("multi_message","host_autokicked",uVar2);
        FUN_0056fcb0(uVar2);
      }
      FUN_00576710(param_2);
    }
    else {
      if (param_3 != '\0') {
        uVar2 = FUN_0081cb40("multi_error","player_kick");
        FUN_0056fcb0(&DAT_00879854,uVar2);
      }
      if (*(float *)(DAT_00917f48 + 0x868) == 0.0) {
        fVar3 = (float10)FUN_00822da0();
        *(float *)(DAT_00917f48 + 0x868) = (float)fVar3;
      }
      FUN_00570460();
    }
  }
  return;
}

