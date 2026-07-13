
void FUN_00593da0(int param_1,int param_2,undefined4 *param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_00417780(param_1);
  *param_3 = *puVar1;
  uVar2 = FUN_00417780(param_4,param_5);
  FUN_00593b40(param_1,0,param_2 - param_1 >> 2,uVar2);
  return;
}

