
void __thiscall FUN_005e2260(int param_1,int param_2,float param_3)

{
  int iVar1;
  
  iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  *(float *)(param_1 + 0xc4) = param_3 * *(float *)(iVar1 + 0xe0) + *(float *)(param_1 + 0xc4);
  return;
}

