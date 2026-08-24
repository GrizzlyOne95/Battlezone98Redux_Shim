# Custom-final campaign/focus trace

This trace is observational. It does not patch the fullscreen minimize policy.
It is gated to the exact Redux 2.2.301 instruction bytes used by both the
verified GOG and settled Steam processes.

When the workstation is unlocked, run:

```powershell
powershell -ExecutionPolicy Bypass -File reverse_engineering/run_campaign_focus_final_trace.ps1
```

Then complete or force the affected custom campaign's final mission, observe
the transition, and exit Redux. The script records a timestamped manifest and
trace under `reverse_engineering/runtime_traces/`.

The single run records Redux run state, selected screen, campaign, mission
index/count, result marker, archive/replay state, result-media filename, the
requested activation/focus/size/system messages, every `ShowWindow` call and
caller, foreground window/PID/process identity, and Ogre Theora clip
creation/playback. The decisive event is the first `WM_ACTIVATEAPP(FALSE)` and
the foreground owner immediately before Redux calls `ShowWindow(SW_MINIMIZE)`.

To attach to an already-running instance instead of launching one, pass
`-AttachPid <pid>`. For Steam, launch through Steam first and attach to the
settled game PID.
