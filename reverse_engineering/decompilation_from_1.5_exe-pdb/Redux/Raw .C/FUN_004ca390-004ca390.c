
void __fastcall FUN_004ca390(int param_1)

{
  undefined1 local_10 [4];
  undefined4 local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x34) != 0) {
    FUN_0044dc60(0,0);
  }
  FUN_0062d4b0(*(undefined4 *)(local_8 + 0xc));
  FUN_0062d410(*(undefined4 *)(local_8 + 0xc),*(undefined4 *)(*(int *)(local_8 + 8) + 0x2c));
  if (*(int *)(local_8 + 0x10) != 0) {
    FUN_0062d310(*(undefined4 *)(local_8 + 0x10),"fun3d\\Explosion.cpp");
  }
  local_c = *(undefined4 *)(local_8 + 4);
  FUN_0042d920(local_10,local_c);
  return;
}

