/*
 * Entry: 00510924
 * Name: Grassfire_Init
 * Namespace: Global
 * Signature: void Grassfire_Init(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Grassfire_Init(int param_1,int param_2)

{
  size_t _Size;
  
  Debug_Assert((uint)(grassfire_initialised == 0),0x4f,".\\Schedule\\Grasfire.c",
               "!grassfire_initialised");
  default_rows = param_1;
  grassfire_initialised = 1;
  default_columns = param_2;
  default_temp = NR_Imatrix(0,param_1 + -1,0,param_2 + -1);
  default_inbuf = calloc(1,param_2 << 2);
  _Size = param_2 * 4 + 8;
  default_this_one = calloc(1,_Size);
  default_other = calloc(1,_Size);
  return;
}
