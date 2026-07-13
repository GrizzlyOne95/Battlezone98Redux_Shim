/*
 * Entry: 00597a7d
 * Name: DXGetErrorDescriptionA
 * Namespace: Global
 * Signature: char * DXGetErrorDescriptionA(T_HRESULT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl DXGetErrorDescriptionA(int param_1)

{
  if (param_1 < -0x7789fdb4) {
    if (param_1 == -0x7789fdb5) {
      return "This surface can not be restored because it was created in a different mode.";
    }
    if (param_1 < -0x7ffbfc0d) {
      if (param_1 == -0x7ffbfc0e) {
        return "A registry entry is corrupt.";
      }
      if (param_1 < -0x7ffbfdc6) {
        if (param_1 == -0x7ffbfdc7) {
          return "This Advise cannot be canceled because it was not successfully set.";
        }
        if (param_1 < -0x7ffbfde9) {
          if (param_1 == -0x7ffbfdea) {
            return "An object or name was not found.";
          }
          if (param_1 < -0x7ffbfdfa) {
            if (param_1 == -0x7ffbfdfb) {
              return 
              "The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode. & This operation cannot be performed because the filter is active."
              ;
            }
            if (param_1 < -0x7ffbfeab) {
              if (param_1 == -0x7ffbfeac) {
                return "Class not registered";
              }
              if (param_1 < -0x7fffbffb) {
                if (param_1 == -0x7fffbffc) {
                  return "Operation aborted";
                }
                if (param_1 == -0x7ffffff6) {
                  return "The data necessary to complete this operation is not yet available.";
                }
                if (param_1 == -0x7fffbfff) {
                  return "The function called is not supported at this time";
                }
                if (param_1 == -0x7fffbffe) {
                  return "The requested COM interface is not available";
                }
                if (param_1 == -0x7fffbffd) {
                  return "Invalid pointer";
                }
              }
              else {
                if (param_1 == -0x7fffbffb) {
                  return "An undetermined error occurred";
                }
                if (param_1 == -0x7fff0001) {
                  return "Catastrophic failure";
                }
                if (param_1 == -0x7ffbfef0) {
                  return "This object does not support aggregation";
                }
              }
            }
            else {
              if (param_1 == -0x7ffbfe10) {
                return "CoInitialize has not been called.";
              }
              if (param_1 == -0x7ffbfe0f) {
                return "CoInitialize has already been called.";
              }
              if (param_1 == -0x7ffbfe00) {
                return 
                "Unable to IDirectInputJoyConfig_Acquire because the user does not have sufficient privileges to change the joystick configuration. & An invalid media type was specified"
                ;
              }
              if (param_1 == -0x7ffbfdff) {
                return "The device is full. & An invalid media subtype was specified.";
              }
              if (param_1 == -0x7ffbfdfe) {
                return 
                "Not all the requested information fit into the buffer. & This object can only be created as an aggregated object."
                ;
              }
              if (param_1 == -0x7ffbfdfd) {
                return "The effect is not downloaded. & The enumerator has become invalid.";
              }
              if (param_1 == -0x7ffbfdfc) {
                return 
                "The device cannot be reinitialized because there are still effects attached to it. & At least one of the pins involved in the operation is already connected."
                ;
              }
            }
          }
          else {
            switch(param_1) {
            case -0x7ffbfdfa:
              return 
              "The effect could not be downloaded because essential information is missing.  For example, no axes have been associated with the effect, or no type-specific information has been created. & One of the specified pins supports no media types."
              ;
            case -0x7ffbfdf9:
              return 
              "Attempted to read buffered device data from a device that is not buffered. & There is no common media type between these pins."
              ;
            case -0x7ffbfdf8:
              return 
              "An attempt was made to modify parameters of an effect while it is playing.  Not all hardware devices support altering the parameters of an effect while it is playing. & Two pins of the same direction cannot be connected together."
              ;
            case -0x7ffbfdf7:
              return 
              "The operation could not be completed because the device is not plugged in. & The operation cannot be performed because the pins are not connected."
              ;
            case -0x7ffbfdf6:
              return 
              "SendDeviceData failed because more information was requested to be sent than can be sent to the device.  Some devices have restrictions on how much data can be sent to them.  (For example, there might be a limit on the number of buttons that can be pressed at once.) & No sample buffer allocator is available."
              ;
            case -0x7ffbfdf5:
              return 
              "A mapper file function failed because reading or writing the user or IHV settings file failed. & A run-time error occurred."
              ;
            case -0x7ffbfdf4:
              return "No buffer space has been set";
            case -0x7ffbfdf3:
              return "The buffer is not big enough.";
            case -0x7ffbfdf2:
              return "An invalid alignment was specified.";
            case -0x7ffbfdf1:
              return "Cannot change allocated memory while the filter is active.";
            case -0x7ffbfdf0:
              return "One or more buffers are still active.";
            case -0x7ffbfdef:
              return "Cannot allocate a sample when the allocator is not active.";
            case -0x7ffbfdee:
              return "Cannot allocate memory because no size has been set.";
            case -0x7ffbfded:
              return "Cannot lock for synchronization because no clock has been defined.";
            case -0x7ffbfdec:
              return "Quality messages could not be sent because no quality sink has been defined.";
            case -0x7ffbfdeb:
              return "A required interface has not been implemented.";
            }
          }
        }
        else {
          switch(param_1) {
          case -0x7ffbfde9:
            return "No combination of intermediate filters could be found to make the connection.";
          case -0x7ffbfde8:
            return "No combination of filters could be found to render the stream.";
          case -0x7ffbfde7:
            return "Could not change formats dynamically.";
          case -0x7ffbfde6:
            return "No color key has been set.";
          case -0x7ffbfde5:
            return "Current pin connection is not using the IOverlay transport.";
          case -0x7ffbfde4:
            return "Current pin connection is not using the IMemInputPin transport.";
          case -0x7ffbfde3:
            return "Setting a color key would conflict with the palette already set.";
          case -0x7ffbfde2:
            return "Setting a palette would conflict with the color key already set.";
          case -0x7ffbfde1:
            return "No matching color key is available.";
          case -0x7ffbfde0:
            return "No palette is available.";
          case -0x7ffbfddf:
            return "Display does not use a palette.";
          case -0x7ffbfdde:
            return "Too many colors for the current display settings.";
          case -0x7ffbfddd:
            return "The state changed while waiting to process the sample.";
          case -0x7ffbfddc:
            return "The operation could not be performed because the filter is not stopped.";
          case -0x7ffbfddb:
            return "The operation could not be performed because the filter is not paused.";
          case -0x7ffbfdda:
            return "The operation could not be performed because the filter is not running.";
          case -0x7ffbfdd9:
            return "The operation could not be performed because the filter is in the wrong state.";
          case -0x7ffbfdd8:
            return "The sample start time is after the sample end time.";
          case -0x7ffbfdd7:
            return "The supplied rectangle is invalid.";
          case -0x7ffbfdd6:
            return "This pin cannot use the supplied media type.";
          case -0x7ffbfdd5:
            return "This sample cannot be rendered.";
          case -0x7ffbfdd4:
            return "This sample cannot be rendered because the end of the stream has been reached.";
          case -0x7ffbfdd3:
            return "An attempt to add a filter with a duplicate name failed.";
          case -0x7ffbfdd2:
            return "A time-out has expired.";
          case -0x7ffbfdd1:
            return "The file format is invalid.";
          case -0x7ffbfdd0:
            return "The list has already been exhausted.";
          case -0x7ffbfdcf:
            return "The filter graph is circular.";
          case -0x7ffbfdce:
            return "Updates are not allowed in this state.";
          case -0x7ffbfdcd:
            return "An attempt was made to queue a command for a time in the past.";
          case -0x7ffbfdcc:
            return "The queued command has already been canceled.";
          case -0x7ffbfdcb:
            return "Cannot render the file because it is corrupt.";
          case -0x7ffbfdca:
            return "An overlay advise link already exists.";
          case -0x7ffbfdc8:
            return "No full-screen modes are available.";
          }
        }
      }
      else {
        switch(param_1) {
        case -0x7ffbfdc6:
          return "A full-screen mode is not available.";
        case -0x7ffbfdc5:
          return "Cannot call IVideoWindow methods while in full-screen mode.";
        case -0x7ffbfdc0:
          return "The media type of this file is not recognized.";
        case -0x7ffbfdbf:
          return "The source filter for this file could not be loaded.";
        case -0x7ffbfdbd:
          return "A file appeared to be incomplete.";
        case -0x7ffbfdbc:
          return "The version number of the file is invalid.";
        case -0x7ffbfdb9:
          return "This file is corrupt: it contains an invalid class identifier.";
        case -0x7ffbfdb8:
          return "This file is corrupt: it contains an invalid media type.";
        case -0x7ffbfdb7:
          return "No time stamp has been set for this sample.";
        case -0x7ffbfdaf:
          return "No media time stamp has been set for this sample.";
        case -0x7ffbfdae:
          return "No media time format has been selected.";
        case -0x7ffbfdad:
          return "Cannot change balance because audio device is mono only.";
        case -0x7ffbfdab:
switchD_00597e57_caseD_80040255:
          return "Cannot play back the video stream: no suitable decompressor could be found.";
        case -0x7ffbfdaa:
          return 
          "Cannot play back the audio stream: no audio hardware is available, or the hardware is not responding."
          ;
        case -0x7ffbfda7:
switchD_00597e57_caseD_80040259:
          return "Cannot play back the video stream: format \'RPZA\' is not supported.";
        case -0x7ffbfda5:
          return "ActiveMovie cannot play MPEG movies on this processor.";
        case -0x7ffbfda4:
          return "Cannot play back the audio stream: the audio format is not supported.";
        case -0x7ffbfda3:
          return "Cannot play back the video stream: the video format is not supported.";
        case -0x7ffbfda2:
          return 
          "ActiveMovie cannot play this video stream because it falls outside the constrained standard."
          ;
        case -0x7ffbfda1:
          return 
          "Cannot perform the requested function on an object that is not in the filter graph.";
        case -0x7ffbfd9f:
          return 
          "Cannot get or set time related information on an object that is using a time format of TIME_FORMAT_NONE."
          ;
        case -0x7ffbfd9e:
          return 
          "The connection cannot be made because the stream is read only and the filter alters the data."
          ;
        case -0x7ffbfd9c:
          return "The buffer is not full enough.";
        case -0x7ffbfd9b:
          return "Cannot play back the file.  The format is not supported.";
        case -0x7ffbfd9a:
          return "Pins cannot connect due to not supporting the same transport.";
        case -0x7ffbfd97:
          return "The Video CD can\'t be read correctly by the device or is the data is corrupt.";
        case -0x7ffbfd8f:
          return 
          "There is not enough Video Memory at this display resolution and number of colors. Reducing resolution might help."
          ;
        case -0x7ffbfd8e:
          return "The VideoPort connection negotiation process has failed.";
        case -0x7ffbfd8d:
          return 
          "Either DirectDraw has not been installed or the Video Card capabilities are not suitable. Make sure the display is not in 16 color mode."
          ;
        case -0x7ffbfd8c:
          return "No VideoPort hardware is available, or the hardware is not responding.";
        case -0x7ffbfd8b:
          return "No Capture hardware is available, or the hardware is not responding.";
        case -0x7ffbfd8a:
          return "This User Operation is inhibited by DVD Content at this time.";
        case -0x7ffbfd89:
          return "This Operation is not permitted in the current domain.";
        case -0x7ffbfd88:
          return 
          "The specified button is invalid or is not present at the current time, or there is no button present at the specified location."
          ;
        case -0x7ffbfd87:
          return "DVD-Video playback graph has not been built yet.";
        case -0x7ffbfd86:
          return "DVD-Video playback graph building failed.";
        case -0x7ffbfd85:
          return "DVD-Video playback graph could not be built due to insufficient decoders.";
        case -0x7ffbfd84:
          return 
          "Version number of DirectDraw not suitable. Make sure to install dx5 or higher version.";
        case -0x7ffbfd83:
          return 
          "Copy protection cannot be enabled. Please make sure any other copy protected content is not being shown now."
          ;
        case -0x7ffbfd81:
          return "This object cannot be used anymore as its time has expired.";
        case -0x7ffbfd7f:
          return "The operation cannot be performed at the current playback speed.";
        case -0x7ffbfd7e:
          return "The specified menu doesn\'t exist.";
        case -0x7ffbfd7d:
          return "The specified command was either cancelled or no longer exists.";
        case -0x7ffbfd7c:
          return "The data did not contain a recognized version.";
        case -0x7ffbfd7b:
          return "The state data was corrupt.";
        case -0x7ffbfd7a:
          return "The state data is from a different disc.";
        case -0x7ffbfd79:
          return "The region was not compatible with the current drive.";
        case -0x7ffbfd78:
          return "The requested DVD stream attribute does not exist.";
        case -0x7ffbfd77:
          return "Currently there is no GoUp (Annex J user function) program chain (PGC).";
        case -0x7ffbfd76:
          return "The current parental level was too low.";
        case -0x7ffbfd75:
          return "The current audio is not karaoke content.";
        case -0x7ffbfd72:
          return "Frame step is not supported on this configuration.";
        case -0x7ffbfd71:
          return "The specified stream is disabled and cannot be selected.";
        case -0x7ffbfd70:
          return 
          "The operation depends on the current title number, however the navigator has not yet entered the VTSM or the title domains, so the \'current\' title index is unknown."
          ;
        case -0x7ffbfd6f:
          return "The specified path does not point to a valid DVD disc.";
        case -0x7ffbfd6e:
          return "There is currently no resume information.";
        case -0x7ffbfd6d:
          return 
          "This thread has already blocked this output pin.  There is no need to call IPinFlowControl::Block() again."
          ;
        case -0x7ffbfd6c:
          return 
          "IPinFlowControl::Block() has been called on another thread.  The current thread cannot make any assumptions about this pin\'s block state."
          ;
        case -0x7ffbfd6b:
          return "An operation failed due to a certification failure.";
        case -0x7ffbfd00:
          return 
          "Device driver-specific codes. Unless the specific driver has been precisely identified, no meaning should be attributed to these values other than that the driver originated the error."
          ;
        case -0x7ffbfcff:
          return "DIERR_DRIVERFIRST+1";
        case -0x7ffbfcfe:
          return "DIERR_DRIVERFIRST+2";
        case -0x7ffbfcfd:
          return "DIERR_DRIVERFIRST+3";
        case -0x7ffbfcfc:
          return "DIERR_DRIVERFIRST+4";
        case -0x7ffbfcfb:
          return "DIERR_DRIVERFIRST+5";
        case -0x7ffbfce9:
          return "Debugger is present.";
        }
      }
    }
    else if (param_1 < -0x7ffbf6fe) {
      if (param_1 == -0x7ffbf6ff) {
        return "Could not initialize Direct3D.";
      }
      switch(param_1) {
      case -0x7ffbfc01:
        return "Device installer errors.";
      case -0x7ffbfc00:
        return "Registry entry or DLL for class installer invalid or class installer not found.";
      case -0x7ffbfbff:
        return 
        "The user cancelled the install operation. & The stream already has allocated samples and the surface doesn\'t match the sample format."
        ;
      case -0x7ffbfbfe:
        return 
        "The INF file for the selected device could not be found or is invalid or is damaged. & The specified purpose ID can\'t be used for the call."
        ;
      case -0x7ffbfbfd:
        return "No stream can be found with the specified attributes.";
      case -0x7ffbfbfc:
        return "Seeking not supported for this object.";
      case -0x7ffbfbfb:
        return "The stream formats are not compatible.";
      case -0x7ffbfbfa:
        return "The sample is busy.";
      case -0x7ffbfbf9:
        return 
        "The object can\'t accept the call because its initialize function or equivalent has not been called."
        ;
      case -0x7ffbfbf8:
        return "MS_E_SOURCEALREADYDEFINED";
      case -0x7ffbfbf7:
        return "The stream type is not valid for this operation.";
      case -0x7ffbfbf6:
        return "The object is not in running state.";
      }
    }
    else if (param_1 < -0x7ff8fffd) {
      if (param_1 == -0x7ff8fffe) {
LAB_005996c2:
        return "The system cannot find the file specified.";
      }
      switch(param_1) {
      case -0x7ffbf6fe:
        return "No device could be found with the specified device settings.";
      case -0x7ffbf6fd:
        return "A media file could not be found.";
      case -0x7ffbf6fc:
        return 
        "The device interface has a non-zero reference count, meaning that some objects were not released."
        ;
      case -0x7ffbf6fb:
        return "An error occurred when attempting to create a device.";
      case -0x7ffbf6fa:
        return "An error occurred when attempting to reset a device.";
      case -0x7ffbf6f9:
        return "An error occurred in the device create callback function.";
      case -0x7ffbf6f8:
        return "An error occurred in the device reset callback function.";
      case -0x7ffbf6f7:
        return "Incorrect version of Direct3D or D3DX.";
      case -0x7ffbf6f6:
        return "The device was removed.";
      }
    }
    else if (param_1 < -0x7ff8ffea) {
      if (param_1 == -0x7ff8ffeb) {
LAB_00598262:
        return "This object has not been initialized";
      }
      switch(param_1) {
      case -0x7ff8fffd:
switchD_00598233_caseD_80070003:
        return "The system cannot find the path specified.";
      case -0x7ff8fffc:
switchD_00598233_caseD_80070004:
        return "The system cannot open the file.";
      case -0x7ff8fffb:
        return "Access is denied";
      case -0x7ff8fffa:
        return "Invalid handle";
      case -0x7ff8fff8:
switchD_00598233_caseD_80070008:
        return "Not enough storage is available to process this command.";
      case -0x7ff8fff7:
switchD_00598233_caseD_80070009:
        return "The storage control block address is invalid.";
      case -0x7ff8fff6:
switchD_00598233_caseD_8007000a:
        return "The environment is incorrect.";
      case -0x7ff8fff5:
switchD_00598233_caseD_8007000b:
        return "An attempt was made to load a program with an incorrect format.";
      case -0x7ff8fff4:
        return "The operation cannot be performed unless the device is acquired.";
      case -0x7ff8fff2:
        return "Ran out of memory";
      }
    }
    else if (param_1 < -0x7789fea1) {
      if (param_1 == -0x7789fea2) {
        return 
        "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays."
        ;
      }
      if (param_1 < -0x7789ff4b) {
        if (param_1 == -0x7789ff4c) {
          return 
          "Operation could not be carried out because there is no alpha accleration hardware present or available."
          ;
        }
        if (param_1 < -0x7789ffeb) {
          if (param_1 == -0x7789ffec) {
            return "This surface can not be detached from the requested surface.";
          }
          if (param_1 < -0x7ff8fb7e) {
            if (param_1 == -0x7ff8fb7f) {
              return 
              "The application was written for an unsupported prerelease version of DirectInput.";
            }
            if (param_1 == -0x7ff8ffe2) {
              return "Access to the device has been lost.  It must be re-acquired.";
            }
            if (param_1 == -0x7ff8ffa9) {
              return "An invalid parameter was passed to the returning function";
            }
            if (param_1 == -0x7ff8ff89) {
              return 
              "The object could not be created due to an incompatible driver version or mismatched or incomplete driver components."
              ;
            }
            if (param_1 == -0x7ff8ff56) {
              return "The operation cannot be performed while the device is acquired.";
            }
            if (param_1 == -0x7ff8fefd) {
              return "No more items.";
            }
            if (param_1 == -0x7ff8fb82) {
              return "The application requires a newer version of DirectInput.";
            }
          }
          else {
            if (param_1 == -0x7ff8fb70) {
              return "The specified property ID is not supported for the specified property set.";
            }
            if (param_1 == -0x7ff8fb6e) {
              return "The specified property set is not supported.";
            }
            if ((param_1 == -0x7ff8fb21) || (param_1 == -0x7789fffb)) goto LAB_00598355;
            if (param_1 == -0x7789fff6) {
              return "This surface can not be attached to the requested surface.";
            }
          }
        }
        else if (param_1 < -0x7789ff87) {
          if (param_1 == -0x7789ff88) {
            return "DirectDraw does not support the requested mode";
          }
          if (param_1 == -0x7789ffd8) {
            return "Support is currently not available.";
          }
          if (param_1 == -0x7789ffc9) {
            return "An exception was encountered while performing the requested operation";
          }
          if (param_1 == -0x7789ffa6) {
            return "Height of rectangle provided is not a multiple of reqd alignment";
          }
          if (param_1 == -0x7789ffa1) {
            return "Unable to match primary surface creation request with existing primary surface."
            ;
          }
          if (param_1 == -0x7789ff9c) {
            return "One or more of the caps bits passed to the callback are incorrect.";
          }
          if (param_1 == -0x7789ff92) {
            return "DirectDraw does not support provided Cliplist.";
          }
        }
        else {
          if (param_1 == -0x7789ff7e) {
            return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.";
          }
          if (param_1 == -0x7789ff6f) {
            return "pixel format was invalid as specified";
          }
          if (param_1 == -0x7789ff6a) {
            return "Rectangle provided was invalid.";
          }
          if (param_1 == -0x7789ff60) {
            return "Operation could not be carried out because one or more surfaces are locked";
          }
          if (param_1 == -0x7789ff56) {
            return "There is no 3D present.";
          }
        }
      }
      else if (param_1 < -0x7789ff00) {
        if (param_1 == -0x7789ff01) {
          return "Requested item was not found";
        }
        if (param_1 < -0x7789ff23) {
          if (param_1 == -0x7789ff24) {
            return 
            "Operation could not be carried out because there is no hardware support of the dest color key."
            ;
          }
          if (param_1 == -0x7789ff4b) {
            return 
            "Operation could not be carried out because there is no stereo hardware present or available."
            ;
          }
          if (param_1 == -0x7789ff4a) {
            return 
            "Operation could not be carried out because there is no hardware present which supports stereo surfaces"
            ;
          }
          if (param_1 == -0x7789ff33) {
            return "no clip list available";
          }
          if (param_1 == -0x7789ff2e) {
            return 
            "Operation could not be carried out because there is no color conversion hardware present or available."
            ;
          }
          if (param_1 == -0x7789ff2c) {
            return 
            "Create function called without DirectDraw object method SetCooperativeLevel being called."
            ;
          }
          if (param_1 == -0x7789ff29) {
            return "Surface doesn\'t currently have a color key";
          }
        }
        else {
          if (param_1 == -0x7789ff22) {
            return "No DirectDraw support possible with current display driver";
          }
          if (param_1 == -0x7789ff1f) {
            return 
            "Operation requires the application to have exclusive mode but the application does not have exclusive mode."
            ;
          }
          if (param_1 == -0x7789ff1a) {
            return "Flipping visible surfaces is not supported.";
          }
          if (param_1 == -0x7789ff10) {
            return "There is no GDI present.";
          }
          if (param_1 == -0x7789ff06) {
            return 
            "Operation could not be carried out because there is no hardware present or available.";
          }
        }
      }
      else if (param_1 < -0x7789fec3) {
        if (param_1 == -0x7789fec4) {
          return 
          "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette."
          ;
        }
        if (param_1 == -0x7789fefc) {
          return 
          "Operation could not be carried out because there is no overlay hardware present or available."
          ;
        }
        if (param_1 == -0x7789fef2) {
          return 
          "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other."
          ;
        }
        if (param_1 == -0x7789fee8) {
          return 
          "Operation could not be carried out because there is no appropriate raster op hardware present or available."
          ;
        }
        if (param_1 == -0x7789fede) {
          return 
          "Operation could not be carried out because there is no rotation hardware present or available."
          ;
        }
        if (param_1 == -0x7789feca) {
          return 
          "Operation could not be carried out because there is no hardware support for stretching";
        }
      }
      else {
        if (param_1 == -0x7789fec3) {
          return 
          "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette."
          ;
        }
        if (param_1 == -0x7789fec0) {
          return 
          "DirectDraw Surface is not in 8 bit color mode and the requested operation requires 8 bit color."
          ;
        }
        if (param_1 == -0x7789feb6) {
          return 
          "Operation could not be carried out because there is no texture mapping hardware present or available."
          ;
        }
        if (param_1 == -0x7789feb1) {
          return 
          "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations."
          ;
        }
        if (param_1 == -0x7789feac) {
          return 
          "Operation could not be carried out because there is no hardware support for zbuffer blting."
          ;
        }
      }
    }
    else if (param_1 < -0x7789fdcd) {
      if (param_1 == -0x7789fdce) {
        return 
        "A DirectDraw object representing this driver has already been created for this process.";
      }
      if (param_1 < -0x7789fe33) {
        if (param_1 == -0x7789fe34) {
          return "The requested surface is not attached.";
        }
        if (param_1 < -0x7789fe65) {
          if (param_1 == -0x7789fe66) {
            return "This surface is already attached to the surface it is being attached to.";
          }
          if (param_1 == -0x7789fe98) {
            return "The hardware needed for the requested operation has already been allocated.";
          }
          if (param_1 == -0x7789fe84) {
            return "Out of video memory";
          }
          if (param_1 == -0x7789fe82) {
            return "hardware does not support clipped overlays";
          }
          if (param_1 == -0x7789fe80) {
            return "Can only have ony color key active at one time for overlays";
          }
          if (param_1 == -0x7789fe7d) {
            return 
            "Access to this palette is being refused because the palette is already locked by another thread."
            ;
          }
          if (param_1 == -0x7789fe70) {
            return "No src color key specified for this operation.";
          }
        }
        else {
          if (param_1 == -0x7789fe5c) {
            return 
            "This surface is already a dependency of the surface it is being made a dependency of.";
          }
          if (param_1 == -0x7789fe52) {
            return 
            "Access to this surface is being refused because the surface is already locked by another thread."
            ;
          }
          if (param_1 == -0x7789fe4d) {
            return 
            "Access to this surface is being refused because no driver exists which can supply a pointer to the surface. This is most likely to happen when attempting to lock the primary surface when no DCI provider is present. Will also happen on attempts to lock an optimized surface."
            ;
          }
          if (param_1 == -0x7789fe48) {
            return "Access to Surface refused because Surface is obscured.";
          }
          if (param_1 == -0x7789fe3e) {
            return 
            "Access to this surface is being refused because the surface is gone. The DIRECTDRAWSURFACE object representing this surface should have Restore called on it."
            ;
          }
        }
      }
      else if (param_1 < -0x7789fdf6) {
        if (param_1 == -0x7789fdf7) {
          return "The specified stream contains invalid data";
        }
        if (param_1 == -0x7789fe2a) {
          return "Height requested by DirectDraw is too large.";
        }
        if (param_1 == -0x7789fe20) {
          return 
          "Size requested by DirectDraw is too large --  The individual height and width are OK.";
        }
        if (param_1 == -0x7789fe16) {
          return "Width requested by DirectDraw is too large.";
        }
        if (param_1 == -0x7789fe02) {
          return "Pixel format requested is unsupported by DirectDraw";
        }
        if (param_1 == -0x7789fdf8) {
          return "Bitmask in the pixel format requested is unsupported by DirectDraw";
        }
      }
      else {
        if (param_1 == -0x7789fde7) {
          return "vertical blank is in progress";
        }
        if (param_1 == -0x7789fde4) {
          return "Was still drawing";
        }
        if (param_1 == -0x7789fde2) {
          return "The specified surface type requires specification of the COMPLEX flag";
        }
        if (param_1 == -0x7789fdd0) {
          return "Rectangle provided was not horizontally aligned on reqd. boundary";
        }
        if (param_1 == -0x7789fdcf) {
          return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.";
        }
      }
    }
    else {
      switch(param_1) {
      case -0x7789fdcd:
        return 
        "A hardware only DirectDraw object creation was attempted but the driver did not support any hardware."
        ;
      case -0x7789fdcc:
        return "this process already has created a primary surface";
      case -0x7789fdcb:
        return "software emulation not available.";
      case -0x7789fdca:
        return "region passed to Clipper::GetClipList is too small.";
      case -0x7789fdc9:
        return 
        "an attempt was made to set a clip list for a clipper objec that is already monitoring an hwnd."
        ;
      case -0x7789fdc8:
        return "No clipper object attached to surface object";
      case -0x7789fdc7:
        return 
        "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND."
        ;
      case -0x7789fdc6:
        return 
        "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state."
        ;
      case -0x7789fdc5:
        return 
        "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created."
        ;
      case -0x7789fdc4:
        return "No palette object attached to this surface.";
      case -0x7789fdc3:
        return "No hardware support for 16 or 256 color palettes.";
      case -0x7789fdc2:
        return "If a clipper object is attached to the source surface passed into a BltFast call.";
      case -0x7789fdc1:
        return "No blter.";
      case -0x7789fdc0:
        return "No DirectDraw ROP hardware.";
      case -0x7789fdbf:
        return "returned when GetOverlayPosition is called on a hidden overlay";
      case -0x7789fdbe:
        return 
        "returned when GetOverlayPosition is called on a overlay that UpdateOverlay has never been called on to establish a destionation."
        ;
      case -0x7789fdbd:
        return 
        "returned when the position of the overlay on the destionation is no longer legal for that destionation."
        ;
      case -0x7789fdbc:
        return "returned when an overlay member is called for a non-overlay surface";
      case -0x7789fdbb:
        return 
        "An attempt was made to set the cooperative level when it was already set to exclusive.";
      case -0x7789fdba:
        return "An attempt has been made to flip a surface that is not flippable.";
      case -0x7789fdb9:
        return "Can\'t duplicate primary & 3D surfaces, or surfaces that are implicitly created.";
      case -0x7789fdb8:
        return 
        "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted."
        ;
      case -0x7789fdb7:
        return 
        "Windows can not create any more DCs, or a DC was requested for a paltte-indexed surface when the surface had no palette AND the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC)"
        ;
      case -0x7789fdb6:
        return "No DC was ever created for this surface.";
      }
    }
  }
  else if (param_1 < -0x7789fd93) {
    if (param_1 == -0x7789fd94) {
      return 
      "A DC has already been returned for this surface. Only one DC can be retrieved per surface.";
    }
    switch(param_1) {
    case -0x7789fdb4:
      return "This surface can not be restored because it is an implicitly created surface.";
    case -0x7789fdb3:
      return "The surface being used is not a palette-based surface";
    case -0x7789fdb2:
      return "The display is currently in an unsupported mode";
    case -0x7789fdb1:
      return 
      "Operation could not be carried out because there is no mip-map texture mapping hardware present or available."
      ;
    case -0x7789fdb0:
      return 
      "The requested action could not be performed because the surface was of the wrong type.";
    case -0x7789fda8:
      return 
      "Device does not support optimized surfaces, therefore no video memory optimized surfaces";
    case -0x7789fda7:
      return "Surface is an optimized surface, but has not yet been allocated any memory";
    case -0x7789fda6:
      return 
      "Attempt was made to create or set a device window without first setting the focus window";
    case -0x7789fda5:
      return "Attempt was made to set a palette on a mipmap sublevel";
    }
  }
  else if (param_1 < -0x7766fffb) {
    if (param_1 == -0x7766fffc) {
      return "The geomery scanner failed to process the data.";
    }
    if (param_1 < -0x7789f782) {
      if (param_1 == -0x7789f783) {
        return "Contect protection not available";
      }
      if (param_1 < -0x7789fc71) {
        if (param_1 == -0x7789fc72) {
          return "Bad file float size";
        }
        if (param_1 < -0x7789fc98) {
          if (param_1 == -0x7789fc99) {
LAB_00598b0c:
            return "No more objects";
          }
          if (param_1 < -0x7789fd49) {
            if (param_1 == -0x7789fd4a) {
              return "D3D has not yet been initialized.";
            }
            if (param_1 < -0x7789fd4d) {
              if (param_1 == -0x7789fd4e) {
                return "There is more data available than the specified buffer size could hold";
              }
              if (param_1 == -0x7789fd8a) {
                return 
                "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory."
                ;
              }
              if (param_1 == -0x7789fd80) {
                return "The attempt to page lock a surface failed.";
              }
              if (param_1 == -0x7789fd6c) {
                return "The attempt to page unlock a surface failed.";
              }
              if (param_1 == -0x7789fd58) {
                return 
                "An attempt was made to page unlock a surface with no outstanding page locks.";
              }
            }
            else {
              if (param_1 == -0x7789fd4d) {
                return "The data has expired and is therefore no longer valid.";
              }
              if (param_1 == -0x7789fd4c) {
                return "The mode test has finished executing.";
              }
              if (param_1 == -0x7789fd4b) {
                return "The mode test has switched to a new mode.";
              }
            }
          }
          else {
            if (param_1 == -0x7789fd49) {
              return "The video port is not active";
            }
            if (param_1 == -0x7789fd48) {
              return "The monitor does not have EDID data.";
            }
            if (param_1 == -0x7789fd47) {
              return "The driver does not enumerate display mode refresh rates.";
            }
            if (param_1 == -0x7789fd45) {
              return 
              "Surfaces created by one direct draw device cannot be used directly by another direct draw device."
              ;
            }
            if (param_1 == -0x7789fc9c) goto LAB_00598ada;
            if (param_1 == -0x7789fc9b) goto LAB_00598ad0;
            if (param_1 == -0x7789fc9a) {
              return "Internal error";
            }
          }
        }
        else {
          switch(param_1) {
          case -0x7789fc98:
            return "Bad intrinsics";
          case -0x7789fc97:
            return "No more stream handles";
          case -0x7789fc96:
switchD_00598b2b_caseD_8876036a:
            return "No more data";
          case -0x7789fc95:
switchD_00598b2b_caseD_8876036b:
            return "Bad cache file";
          case -0x7789fc94:
            return "No internet";
          case -0x7789fc7c:
            return "Bad object";
          case -0x7789fc7b:
            return "Bad value";
          case -0x7789fc7a:
            return "Bad type";
          case -0x7789fc79:
switchD_00598b2b_caseD_88760387:
            return "Not found";
          case -0x7789fc78:
            return "Not done yet";
          case -0x7789fc77:
switchD_00598b2b_caseD_88760389:
            return "File not found";
          case -0x7789fc76:
            return "Resource not found";
          case -0x7789fc75:
            return "Bad resource";
          case -0x7789fc74:
            return "Bad file type";
          case -0x7789fc73:
            return "Bad file version";
          }
        }
      }
      else if (param_1 < -0x7789f7de) {
        if (param_1 == -0x7789f7df) {
          return "Conflicting render state";
        }
        if (param_1 < -0x7789f7e7) {
          if (param_1 == -0x7789f7e8) {
            return "Wrong texture format";
          }
          if (param_1 == -0x7789fc71) {
            return "Bad file";
          }
          if (param_1 == -0x7789fc70) {
            return "Parse error";
          }
          if (param_1 == -0x7789fc6f) {
LAB_00598ada:
            return "Bad array size";
          }
          if (param_1 == -0x7789fc6e) {
LAB_00598ad0:
            return "Bad data reference";
          }
          if (param_1 == -0x7789fc6d) goto LAB_00598b0c;
          if (param_1 == -0x7789fc6c) goto switchD_00598b2b_caseD_8876036a;
          if (param_1 == -0x7789fc6b) goto switchD_00598b2b_caseD_8876036b;
        }
        else {
          if (param_1 == -0x7789f7e7) {
            return "Unsupported color operation";
          }
          if (param_1 == -0x7789f7e6) {
            return "Unsupported color arg";
          }
          if (param_1 == -0x7789f7e5) {
            return "Unsupported alpha operation";
          }
          if (param_1 == -0x7789f7e4) {
            return "Unsupported alpha arg";
          }
          if (param_1 == -0x7789f7e3) {
            return "Too many operations";
          }
          if (param_1 == -0x7789f7e2) {
            return "Conflicting texture filter";
          }
          if (param_1 == -0x7789f7e1) {
            return "Unsupported factor value";
          }
        }
      }
      else if (param_1 < -0x7789f795) {
        if (param_1 == -0x7789f796) {
          return "Not available";
        }
        if (param_1 == -0x7789f7de) {
          return "Unsupported texture filter";
        }
        if (param_1 == -0x7789f7da) {
          return "Conflicting texture palette";
        }
        if (param_1 == -0x7789f7d9) {
          return "Driver internal error";
        }
        if (param_1 == -0x7789f79a) goto switchD_00598b2b_caseD_88760387;
        if (param_1 == -0x7789f799) {
          return "More data";
        }
        if (param_1 == -0x7789f798) {
          return "Device lost";
        }
        if (param_1 == -0x7789f797) {
          return "Device not reset";
        }
      }
      else {
        if (param_1 == -0x7789f795) {
          return "Invalid device";
        }
        if (param_1 == -0x7789f794) {
          return "Invalid call";
        }
        if (param_1 == -0x7789f793) {
          return "Driver invalid call";
        }
        if (param_1 == -0x7789f790) {
          return "Hardware device was removed";
        }
        if (param_1 == -0x7789f78c) {
          return "Hardware adapter reset by OS";
        }
        if (param_1 == -0x7789f785) {
          return "Overlay is not supported";
        }
        if (param_1 == -0x7789f784) {
          return "Overlay format is not supported";
        }
      }
    }
    else if (param_1 < -0x7785fffb) {
      if (param_1 == -0x7785fffc) {
        return "Unsupported.";
      }
      if (param_1 < -0x7787ff87) {
        if (param_1 == -0x7787ff88) {
          return "No sound driver is available for use";
        }
        if (param_1 < -0x7789f4a5) {
          if (param_1 == -0x7789f4a6) {
            return "Loaded mesh has no data";
          }
          if (param_1 < -0x7789f4a9) {
            if (param_1 == -0x7789f4aa) {
              return "Cannot attr sort";
            }
            if (param_1 == -0x7789f782) {
              return "Unsupported cryptographic system";
            }
            if (param_1 == -0x7789f77c) {
              return "Presentation statistics are disjoint";
            }
            if (param_1 == -0x7789f4ac) {
              return "Can not modify index buffer";
            }
            if (param_1 == -0x7789f4ab) {
              return "Invalid mesh";
            }
          }
          else {
            if (param_1 == -0x7789f4a9) {
              return "Skinning not supported";
            }
            if (param_1 == -0x7789f4a8) {
              return "Too many influences";
            }
            if (param_1 == -0x7789f4a7) {
              return "Invalid data";
            }
          }
        }
        else {
          if (param_1 == -0x7789f4a5) {
            return "Duplicate named fragment";
          }
          if (param_1 == -0x7789f4a4) {
            return "Can Not remove last item";
          }
          if (param_1 == -0x7787fff6) {
            return 
            "The call failed because resources (such as a priority level) were already being used by another caller"
            ;
          }
          if (param_1 == -0x7787ffe2) {
            return "The control (vol, pan, etc.) requested by the caller is not available";
          }
          if (param_1 == -0x7787ffce) {
            return "This call is not valid for the current state of this object";
          }
          if (param_1 == -0x7787ffba) {
            return 
            "The caller does not have the priority level required for the function to succeed";
          }
          if (param_1 == -0x7787ff9c) {
            return "The specified WAVE format is not supported";
          }
        }
      }
      else if (param_1 < -0x7787ff2d) {
        if (param_1 == -0x7787ff2e) {
          return "The GUID specified in an audiopath file does not match a valid MIXIN buffer";
        }
        if (param_1 == -0x7787ff7e) {
LAB_00598355:
          return "This object is already initialized";
        }
        if (param_1 == -0x7787ff6a) {
          return "The buffer memory has been lost, and must be restored";
        }
        if (param_1 == -0x7787ff60) {
          return "Another app has a higher priority level, preventing this call from succeeding";
        }
        if (param_1 == -0x7787ff56) goto LAB_00598262;
        if (param_1 == -0x7787ff4c) {
          return "Tried to create a DSBCAPS_CTRLFX buffer shorter than DSBSIZE_FX_MIN milliseconds";
        }
        if (param_1 == -0x7787ff42) {
          return "Attempt to use DirectSound 8 functionality on an older DirectSound object";
        }
        if (param_1 == -0x7787ff38) {
          return "A circular loop of send effects was detected";
        }
      }
      else {
        if (param_1 == -0x7787ff24) {
          return "Requested effects are not available";
        }
        if (param_1 == -0x7787ee9f) {
          return "The object requested was not found (numerically equal to DMUS_E_NOT_FOUND)";
        }
        if (param_1 == -0x7786ffff) {
LAB_0059901a:
          return "There are too many unique state objects.";
        }
        if (param_1 == -0x7786fffe) goto switchD_00598b2b_caseD_88760389;
        if (param_1 == -0x7785ffff) {
          return 
          "The application has made an erroneous API call that it had enough information to avoid. This error is intended to denote that the application should be altered to avoid the error. Use of the debug version of the DXGI.DLL will provide run-time debug output with further information."
          ;
        }
        if (param_1 == -0x7785fffe) {
          return 
          "The item requested was not found. For GetPrivateData calls, this means that the specified GUID had not been previously associated with the object."
          ;
        }
        if (param_1 == -0x7785fffd) {
          return 
          "The specified size of the destination buffer is too small to hold the requested data.";
        }
      }
    }
    else if (param_1 < -0x7769fffe) {
      if (param_1 == -0x7769ffff) {
        return "Invalid XAudio2 API call or arguments";
      }
      if (param_1 < -0x7785ffde) {
        if (param_1 == -0x7785ffdf) {
          return 
          "The application attempted to perform an operation on an DXGI output that is only legal after the output has been claimed for exclusive owenership."
          ;
        }
        if (param_1 == -0x7785fffb) {
          return "Hardware device removed.";
        }
        if (param_1 == -0x7785fffa) {
          return "Device hung due to badly formed commands.";
        }
        if (param_1 == -0x7785fff9) {
          return "Device reset due to a badly formed commant.";
        }
        if (param_1 == -0x7785fff6) {
          return "Was still drawing.";
        }
        if ((param_1 == -0x7785fff5) || (param_1 == -0x7785fff4)) {
LAB_0059909f:
          return "The requested functionality is not supported by the device or the driver.";
        }
        if (param_1 == -0x7785ffe0) {
          return "An internal driver error occurred.";
        }
      }
      else {
        if (param_1 == -0x7785ffde) goto LAB_0059909f;
        if (param_1 == -0x7785ffdd) {
          return "Remote desktop client disconnected.";
        }
        if (param_1 == -0x7785ffdc) {
          return "Remote desktop client is out of memory.";
        }
        if (param_1 == -0x7783ffff) goto LAB_0059901a;
        if (param_1 == -0x7783fffe) goto switchD_00598b2b_caseD_88760389;
        if (param_1 == -0x7783fffd) {
          return "Therea are too many unique view objects.";
        }
        if (param_1 == -0x7783fffc) {
          return "Deferred context requires Map-Discard usage pattern";
        }
      }
    }
    else if (param_1 < -0x7767affd) {
      if (param_1 == -0x7767affe) {
        return "Indicates the specified font does not exist.";
      }
      if (param_1 == -0x7769fffe) {
        return "Hardware XMA decoder error";
      }
      if (param_1 == -0x7769fffd) {
        return "Failed to create an audio effect";
      }
      if (param_1 == -0x7769fffc) {
        return "Device invalidated (unplugged, disabled, etc)";
      }
      if (param_1 == -0x7768ffff) {
        return "Requested audio format unsupported.";
      }
      if (param_1 == -0x7767d080) {
        return "The pixel format is not supported.";
      }
      if (param_1 == -0x7767b000) {
        return "Indicates an error in an input file such as a font file.";
      }
      if (param_1 == -0x7767afff) {
        return 
        "Indicates an error originating in DirectWrite code, which is not expected to occur but is safe to recover from."
        ;
      }
    }
    else {
      if (param_1 == -0x7767affd) {
        return 
        "A font file could not be opened because the file, directory, network location, drive, or other storage location does not exist or is unavailable."
        ;
      }
      if (param_1 == -0x7767affc) {
        return 
        "A font file exists but could not be opened due to access denied, sharing violation, or similar error."
        ;
      }
      if (param_1 == -0x7767affb) {
        return "A font collection is obsolete due to changes in the system.";
      }
      if (param_1 == -0x7767affa) {
        return "The given interface is already registered.";
      }
      if (param_1 == -0x7766ffff) {
        return "The object was not in the correct state to process the method.";
      }
      if (param_1 == -0x7766fffe) {
        return "The object has not yet been initialized.";
      }
      if (param_1 == -0x7766fffd) {
        return "The requested opertion is not supported.";
      }
    }
  }
  else if (param_1 < -0x7538fffe) {
    if (param_1 == -0x7538ffff) {
      return "The engine is already initialized.";
    }
    switch(param_1) {
    case -0x7766fffb:
      return "D2D could not access the screen.";
    case -0x7766fffa:
      return "A valid display state could not be determined.";
    case -0x7766fff9:
      return "The supplied vector is zero.";
    case -0x7766fff8:
      return "An internal error (D2D bug) occurred. On checked builds, we would assert.";
    case -0x7766fff7:
      return "The display format we need to render is not supported by the hardware device.";
    case -0x7766fff6:
      return "A call to this method is invalid.";
    case -0x7766fff5:
      return "No HW rendering device is available for this operation.";
    case -0x7766fff4:
      return 
      "here has been a presentation error that may be recoverable. The caller needs to recreate, rerender the entire frame, and reattempt present."
      ;
    case -0x7766fff3:
      return "Shader construction failed because it was too complex.";
    case -0x7766fff2:
      return "Shader compilation failed.";
    case -0x7766fff1:
      return "Requested DX surface size exceeded maximum texture size.";
    case -0x7766fff0:
      return "The requested D2D version is not supported.";
    case -0x7766ffef:
      return "Invalid number.";
    case -0x7766ffee:
      return "Objects used together must be created from the same factory instance.";
    case -0x7766ffed:
      return "A layer resource can only be in use once at any point in time.";
    case -0x7766ffec:
      return "The pop call did not match the corresponding push call";
    case -0x7766ffea:
      return "The push and pop calls were unbalanced";
    case -0x7766ffe9:
      return "Attempt to copy from a render target while a layer or clip rect is applied";
    case -0x7766ffe8:
      return "The brush types are incompatible for the call.";
    case -0x7766ffe7:
      return "An unknown win32 failure occurred.";
    case -0x7766ffe6:
      return "The render target is not compatible with GDI";
    case -0x7766ffe5:
      return "A text client drawing effect object is of the wrong type";
    case -0x7766ffe4:
      return 
      "The application is holding a reference to the IDWriteTextRenderer interface after the corresponding DrawText or DrawTextLayout call has returned. The IDWriteTextRenderer instance will be zombied."
      ;
    }
  }
  else if (param_1 < -0x7538fefe) {
    if (param_1 == -0x7538feff) {
      return "Error writing a file during auditioning.";
    }
    switch(param_1) {
    case -0x7538fffe:
      return "The engine has not been initialized.";
    case -0x7538fffd:
      return "The engine has expired (demo or pre-release version).";
    case -0x7538fffc:
      return "No notification callback.";
    case -0x7538fffb:
      return "Notification already registered.";
    case -0x7538fffa:
      return "Invalid usage.";
    case -0x7538fff9:
      return "Invalid data.";
    case -0x7538fff8:
      return "Fail to play due to instance limit.";
    case -0x7538fff7:
      return "Global Settings not loaded.";
    case -0x7538fff6:
      return "Invalid variable index.";
    case -0x7538fff5:
      return "Invalid category.";
    case -0x7538fff4:
      return "Invalid cue index.";
    case -0x7538fff3:
      return "Invalid wave index.";
    case -0x7538fff2:
      return "Invalid track index.";
    case -0x7538fff1:
      return "Invalid sound offset or index.";
    case -0x7538fff0:
      return "Error reading a file.";
    case -0x7538ffef:
      return "Unknown event type.";
    case -0x7538ffee:
      return "Invalid call of method of function from callback.";
    case -0x7538ffed:
      return "No wavebank exists for desired operation.";
    case -0x7538ffec:
      return "Unable to select a variation.";
    case -0x7538ffeb:
      return "There can be only one audition engine.";
    case -0x7538ffea:
      return "The wavebank is not prepared.";
    case -0x7538ffe9:
      return "No audio device found.";
    case -0x7538ffe8:
      return "Invalid entry count for channel maps.";
    case -0x7538ffe7:
      return "Time offset for seeking is beyond the cue end.";
    case -0x7538ffe6:
      return "Time offset for seeking is beyond the wave end.";
    case -0x7538ffe5:
      return "Friendly names are not included in the bank.";
    }
  }
  else if (param_1 < 9) {
    if (param_1 == 8) goto switchD_00598233_caseD_80070008;
    if (param_1 < -0x3ff31feb) {
      if (param_1 == -0x3ff31fec) {
        return "Element content is invalid according to the DTD or schema.";
      }
      if (param_1 < -0x3ff31ffc) {
        if (param_1 == -0x3ff31ffd) {
          return "Entity \'%1\' contains an infinite entity reference loop.";
        }
        if (param_1 < -0x7538fef9) {
          if (param_1 == -0x7538fefa) {
            return "Missing a DSP parameter.";
          }
          if (param_1 == -0x7538fefe) {
            return "Missing a soundbank.";
          }
          if (param_1 == -0x7538fefd) {
            return "Missing an RPC curve.";
          }
          if (param_1 == -0x7538fefc) {
            return "Missing data for an audition command.";
          }
          if (param_1 == -0x7538fefb) {
            return "Unknown command.";
          }
        }
        else {
          if (param_1 == -0x7538fef9) {
            return "Wave does not exist in auditioned wavebank.";
          }
          if (param_1 == -0x7538fef8) {
            return "Failed to create a directory for streaming wavebank data.";
          }
          if (param_1 == -0x7538fef7) {
            return "Invalid audition session.";
          }
          if (param_1 == -0x3ff31ffe) {
            return "Reference to undefined entity \'%1\'.";
          }
        }
      }
      else {
        switch(param_1) {
        case -0x3ff31ffc:
          return "Cannot use the NDATA keyword in a parameter entity declaration.";
        case -0x3ff31ffb:
          return "Cannot use a general parsed entity \'%1\' as the value for attribute \'%2\'.";
        case -0x3ff31ffa:
          return "Cannot use unparsed entity \'%1\' in an entity reference.";
        case -0x3ff31ff9:
          return "Cannot reference an external general parsed entity \'%1\' in an attribute value.";
        case -0x3ff31ff3:
          return "The element \'%1\' is used but not declared in the DTD or schema.";
        case -0x3ff31ff2:
          return 
          "The attribute \'%1\' references the ID \'%2\', which is not defined in the document.";
        case -0x3ff31fef:
          return "Element cannot be empty according to the DTD or schema.";
        case -0x3ff31fee:
          return "Element content is incomplete according to the DTD or schema.";
        case -0x3ff31fed:
          return "The name of the top-most element must match the name of the DOCTYPE declaration.";
        }
      }
    }
    else if (param_1 < -0x3ff31ddc) {
      if (param_1 == -0x3ff31ddd) {
        return 
        "The validate method failed because the document does not contain exactly one root node.";
      }
      switch(param_1) {
      case -0x3ff31feb:
        return "The attribute \'%1\' on this element is not defined in the DTD or schema.";
      case -0x3ff31fea:
        return 
        "Attribute \'%1\' has a value that does not match the fixed value defined in the DTD or schema."
        ;
      case -0x3ff31fe9:
        return "Attribute \'%1\' has an invalid value according to the DTD or schema.";
      case -0x3ff31fe8:
        return "Text is not allowed in this element according to the DTD or schema.";
      case -0x3ff31fe7:
        return "An attribute declaration cannot contain multiple fixed values: \'%1\'.";
      case -0x3ff31fe4:
        return "Reference to undeclared element: \'%1\'.";
      case -0x3ff31fe2:
        return "Attribute \'%1\' must be a #FIXED attribute.";
      case -0x3ff31fe0:
        return "Required attribute \'%1\' is missing.";
      case -0x3ff31fda:
        return "Expecting: %1.";
      }
    }
    else if (param_1 < 4) {
      if (param_1 == 3) goto switchD_00598233_caseD_80070003;
      if (param_1 == -0x3ff31ddc) {
        return 
        "The validate method failed because a DTD or schema was not specified in the document.";
      }
      if (param_1 == 0) {
        return "The function completed successfully";
      }
      if (param_1 == 1) {
        return "Call successful, but returned FALSE";
      }
      if (param_1 == 2) goto LAB_005996c2;
    }
    else {
      if (param_1 == 4) goto switchD_00598233_caseD_80070004;
      if (param_1 == 5) {
        return "Access is denied.";
      }
      if (param_1 == 6) {
        return "The handle is invalid.";
      }
    }
  }
  else if (param_1 < 0x40269) {
    if (param_1 == 0x40268) {
      return "The graph can\'t be cued because of lack of or corrupt data.";
    }
    if (param_1 < 0x40246) {
      if (param_1 == 0x40245) {
        return "The file contained some property settings that were not used.";
      }
      if (param_1 < 0x40004) {
        if (param_1 == 0x40003) {
          return "End of stream. Sample not updated.";
        }
        if (param_1 == 9) goto switchD_00598233_caseD_80070009;
        if (param_1 == 10) goto switchD_00598233_caseD_8007000a;
        if (param_1 == 0xb) goto switchD_00598233_caseD_8007000b;
        if (param_1 == 0xe) {
          return "The system cannot find the drive specified.";
        }
      }
      else {
        if (param_1 == 0x40103) {
          return "The end of the list has been reached.";
        }
        if (param_1 == 0x4022d) {
          return "An attempt to add a filter with a duplicate name succeeded with a modified name.";
        }
        if (param_1 == 0x40237) {
          return "The state transition has not completed.";
        }
        if (param_1 == 0x40242) {
          return "Some of the streams in this movie are in an unsupported format.";
        }
      }
    }
    else if (param_1 < 0x40259) {
      if (param_1 == 0x40258) {
        return "Cannot play back the audio stream: no audio hardware is available.";
      }
      if (param_1 == 0x40246) {
        return "Some connections have failed and have been deferred.";
      }
      if (param_1 == 0x40250) {
        return "The resource specified is no longer needed.";
      }
      if (param_1 == 0x40254) {
        return 
        "A connection could not be made with the media type in the persistent graph, but has been made with a negotiated media type."
        ;
      }
      if (param_1 == 0x40257) goto switchD_00597e57_caseD_80040255;
    }
    else {
      if (param_1 == 0x4025a) goto switchD_00597e57_caseD_80040259;
      if (param_1 == 0x40260) {
        return "The value returned had to be estimated.  It\'s accuracy can not be guaranteed.";
      }
      if (param_1 == 0x40263) {
        return "This success code is reserved for internal purposes within ActiveMovie.";
      }
      if (param_1 == 0x40267) {
        return "The stream has been turned off.";
      }
    }
  }
  else if (param_1 < 0x8760879) {
    if (param_1 == 0x8760878) {
      return "Client window is occluded (minimized or other fullscreen)";
    }
    if (param_1 < 0x4028e) {
      if (param_1 == 0x4028d) {
        return "The seek into the movie was not frame accurate.";
      }
      if (param_1 == 0x40270) {
        return "The stop time for the sample was not set.";
      }
      if (param_1 == 0x4027e) {
        return 
        "There was no preview pin available, so the capture pin output is being split to provide both capture and preview."
        ;
      }
      if (param_1 == 0x40280) {
        return 
        "The current title was not a sequential set of chapters (PGC), and the returned timing information might not be continuous."
        ;
      }
      if (param_1 == 0x4028c) {
        return 
        "The audio stream did not contain sufficient information to determine the contents of each channel."
        ;
      }
    }
    else {
      if (param_1 == 0x876086f) {
        return "The call succeeded but there won\'t be any mipmaps generated";
      }
      if (param_1 == 0x8760875) {
        return "Resource not resident in memory";
      }
      if (param_1 == 0x8760876) {
        return "Resource resident in shared memory";
      }
      if (param_1 == 0x8760877) {
        return "Desktop display mode has changed";
      }
    }
  }
  else if (param_1 < 0x87a0006) {
    if (param_1 == 0x87a0005) {
      return "No access to desktop.";
    }
    if (param_1 == 0x878000a) {
      return "The call succeeded, but we had to substitute the 3D algorithm";
    }
    if (param_1 == 0x87a0001) {
      return 
      "The target window or output has been occluded. The application should suspend rendering operations if possible."
      ;
    }
    if (param_1 == 0x87a0002) {
      return "Target window is clipped.";
    }
    if (param_1 == 0x87a0004) {
LAB_00599932:
      return "";
    }
  }
  else {
    if (param_1 == 0x87a0006) goto LAB_00599932;
    if (param_1 == 0x87a0007) {
      return "Display mode has changed";
    }
    if (param_1 == 0x87a0008) {
      return "Display mode is changing";
    }
  }
  return "n/a";
}
