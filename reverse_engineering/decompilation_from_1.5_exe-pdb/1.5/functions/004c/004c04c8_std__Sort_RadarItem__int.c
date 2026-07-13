/*
 * Entry: 004c04c8
 * Name: std::_Sort<RadarItem_*,int>
 * Namespace: std
 * Signature: void _Sort<RadarItem_*,int>(RadarItem * param_1, RadarItem * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Sort<RadarItem_*,int>(RadarItem *param_1,RadarItem *param_2,int param_3)

{
  int iVar1;
  GameObject *in_ECX;
  RadarItem local_c;
  
  iVar1 = (int)param_2 - (int)param_1 >> 3;
  local_c.obj = in_ECX;
  local_c.z = (long)in_ECX;
  if (0x20 < iVar1) {
    do {
      if (param_3 < 1) break;
      _Unguarded_partition<RadarItem_*>(&local_c,param_1);
      param_3 = param_3 / 2 + (param_3 / 2) / 2;
      if ((int)((int)local_c.obj - (int)param_1 & 0xfffffff8U) <
          (int)((int)param_2 - local_c.z & 0xfffffff8U)) {
        _Sort<RadarItem_*,int>(param_1,(RadarItem *)local_c.obj,param_3);
        param_1 = (RadarItem *)local_c.z;
      }
      else {
        _Sort<RadarItem_*,int>((RadarItem *)local_c.z,param_2,param_3);
        param_2 = (RadarItem *)local_c.obj;
      }
      iVar1 = (int)param_2 - (int)param_1 >> 3;
    } while (0x20 < iVar1);
    if (0x20 < iVar1) {
      make_heap<RadarItem_*>(param_1,param_2);
      _Sort_heap<RadarItem_*>(param_1,param_2);
      return;
    }
  }
  if (1 < iVar1) {
    _Insertion_sort1<RadarItem_*,RadarItem>(param_1,param_2,(RadarItem *)0x0);
  }
  return;
}
