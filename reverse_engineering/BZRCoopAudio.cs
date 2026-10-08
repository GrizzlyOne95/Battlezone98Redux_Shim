// Core Audio session controls, scoped to the native test process ID.
// https://learn.microsoft.com/windows/win32/api/audioclient/nf-audioclient-isimpleaudiovolume-setmute
using System;
using System.Runtime.InteropServices;

namespace BZRCoopAudio {
    [ComImport, Guid("BCDE0395-E52F-467C-8E3D-C4579291692E")] class DeviceEnumerator { }
    [ComImport, Guid("A95664D2-9614-4F35-A746-DE8DB63617E6"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IDeviceEnumerator {
        [PreserveSig] int EnumAudioEndpoints(int flow, uint state, out IDeviceCollection devices);
    }
    [ComImport, Guid("0BD7A1BE-7A1A-44DB-8397-CC5392387B5E"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IDeviceCollection {
        [PreserveSig] int GetCount(out uint count);
        [PreserveSig] int Item(uint index, out IDevice device);
    }
    [ComImport, Guid("D666063F-1587-4E43-81F1-B948E807363F"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IDevice {
        [PreserveSig] int Activate(ref Guid iid, uint context, IntPtr parameters, [MarshalAs(UnmanagedType.IUnknown)] out object result);
    }
    [ComImport, Guid("77AA99A0-1BD6-484F-8BC7-2C654C9A9B6F"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface ISessionManager {
        [PreserveSig] int GetAudioSessionControl(IntPtr id, uint flags, out IntPtr control);
        [PreserveSig] int GetSimpleAudioVolume(IntPtr id, uint flags, out IntPtr volume);
        [PreserveSig] int GetSessionEnumerator(out ISessionEnumerator sessions);
    }
    [ComImport, Guid("E2F5BB11-0570-40CA-ACDD-3AA01277DEE8"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface ISessionEnumerator {
        [PreserveSig] int GetCount(out int count);
        [PreserveSig] int GetSession(int index, out ISessionControl control);
    }
    [ComImport, Guid("F4B1A599-7266-4319-A8CA-E70ACB11E8CD"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface ISessionControl { }
    [ComImport, Guid("BFB7FF88-7239-4FC9-8FA2-07C950BE9C6D"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface ISessionControl2 {
        [PreserveSig] int GetState(out int state);
        [PreserveSig] int GetDisplayName(out IntPtr name);
        [PreserveSig] int SetDisplayName(IntPtr name, IntPtr context);
        [PreserveSig] int GetIconPath(out IntPtr path);
        [PreserveSig] int SetIconPath(IntPtr path, IntPtr context);
        [PreserveSig] int GetGroupingParam(out Guid value);
        [PreserveSig] int SetGroupingParam(ref Guid value, IntPtr context);
        [PreserveSig] int RegisterAudioSessionNotification(IntPtr events);
        [PreserveSig] int UnregisterAudioSessionNotification(IntPtr events);
        [PreserveSig] int GetSessionIdentifier(out IntPtr id);
        [PreserveSig] int GetSessionInstanceIdentifier(out IntPtr id);
        [PreserveSig] int GetProcessId(out uint pid);
    }
    [ComImport, Guid("87CE5498-68D6-44E5-9215-6DA47EF883D8"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IVolume {
        [PreserveSig] int SetMasterVolume(float level, IntPtr context);
        [PreserveSig] int GetMasterVolume(out float level);
        [PreserveSig] int SetMute([MarshalAs(UnmanagedType.Bool)] bool mute, IntPtr context);
        [PreserveSig] int GetMute([MarshalAs(UnmanagedType.Bool)] out bool mute);
    }
    public static class Sessions {
        static void Check(int hr) { Marshal.ThrowExceptionForHR(hr); }
        static void Release(object value) { if (value != null) Marshal.ReleaseComObject(value); }
        public static int Mute(int processId) {
            object enumerator = new DeviceEnumerator();
            IDeviceCollection devices = null;
            int muted = 0;
            try {
                Check(((IDeviceEnumerator)enumerator).EnumAudioEndpoints(0, 1, out devices));
                uint deviceCount; Check(devices.GetCount(out deviceCount));
                for (uint d = 0; d < deviceCount; d++) {
                    IDevice device = null; object manager = null; ISessionEnumerator sessions = null;
                    try {
                        Check(devices.Item(d, out device));
                        Guid iid = typeof(ISessionManager).GUID;
                        Check(device.Activate(ref iid, 23, IntPtr.Zero, out manager));
                        Check(((ISessionManager)manager).GetSessionEnumerator(out sessions));
                        int count; Check(sessions.GetCount(out count));
                        for (int s = 0; s < count; s++) {
                            ISessionControl control = null;
                            try {
                                Check(sessions.GetSession(s, out control));
                                uint pid;
                                // S_OK only: never mute a session spanning several processes.
                                if (((ISessionControl2)control).GetProcessId(out pid) != 0 || pid != processId) continue;
                                IVolume volume = (IVolume)control;
                                Check(volume.SetMute(true, IntPtr.Zero));
                                bool isMuted; Check(volume.GetMute(out isMuted));
                                if (!isMuted) throw new InvalidOperationException("Audio session refused mute for PID " + processId);
                                muted++;
                            } finally { Release(control); }
                        }
                    } finally { Release(sessions); Release(manager); Release(device); }
                }
            } finally { Release(devices); Release(enumerator); }
            return muted;
        }
    }
}
