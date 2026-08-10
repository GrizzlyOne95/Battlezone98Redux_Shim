#!/usr/bin/env python3
"""Export Battlezone 1.5's shell UI into a machine-readable manifest.

The 1.5 multiplayer screens are not plain Win32 dialogs. The dialog resource
carries only the real controls -- edit boxes, list boxes, the rich-edit chat
pane -- while every visible button, label, option box, flag picker and
background plate is a C++ object constructed in the dialog procedure with
hard-coded 640x480 pixel coordinates.

So a faithful export needs both halves:

  * the RT_DIALOG templates out of bzone.exe, decoded from dialog units,
  * the widget constructor calls out of the PDB-symbolised Ghidra decompile.

This produces one JSON document describing both, plus the shell button art
extracted from RT_BITMAP. It reads only; nothing in the game install or the
decompile is modified.

Usage:
    python export-bz15-ui.py --install <Battlezone_Install> \
                             --decompile <BZ1_Source/1.5> \
                             --out <output dir> [--bitmaps]
"""
from __future__ import annotations

import argparse
import io
import json
import os
import re
import struct
import sys

RT_BITMAP, RT_DIALOG, RT_STRING = 2, 5, 6

STD_CLASS = {0x80: 'BUTTON', 0x81: 'EDIT', 0x82: 'STATIC',
             0x83: 'LISTBOX', 0x84: 'SCROLLBAR', 0x85: 'COMBOBOX'}

# Dialog procedure -> resource id, from the Shell_DialogBoxParam call sites.
DIALOG_PROCS = {
    'STransportDlgProc': 0x69,   # transport select + character/flag picker
    'NetGameDlgProc': 0x7ED,     # multiplayer game setup
    'RoomDlgProc': 0x98,
    'NameDlgProc': 0x96,         # nickname entry
    'GameDlgProc': 0x9A,
    'PasswordDlgProc': 0x9B,
    'FilterDlgProc': 0x81D,
    'PhoneDlgProc': None,
    'ShellDlgProc': None,   # main menu; also an asm fallback
}

# nTransportMode values assigned in STransportDlgProc, and the background plate
# each one selects.
TRANSPORT_MODES = {
    1: {'name': 'Modem', 'background': 'bitmap\\multip1b.bmp'},
    2: {'name': 'Null Modem (serial)', 'background': 'bitmap\\multip1a.bmp'},
    3: {'name': 'Internet (TCP/IP)', 'background': 'bitmap\\multip1c.bmp'},
    4: {'name': 'IPX (LAN)', 'background': 'bitmap\\multip1.bmp'},
    5: {'name': 'none selected (initial)', 'background': 'bitmap\\multip1.bmp'},
}


# --------------------------------------------------------------------------
# PE resources
# --------------------------------------------------------------------------

def load_pe(path):
    with open(path, 'rb') as f:
        data = f.read()
    e = struct.unpack_from('<I', data, 0x3C)[0]
    nsec = struct.unpack_from('<H', data, e + 6)[0]
    optsz = struct.unpack_from('<H', data, e + 20)[0]
    secoff = e + 24 + optsz
    secs = []
    for i in range(nsec):
        o = secoff + i * 40
        vsz, va, rsz, ptr = struct.unpack_from('<IIII', data, o + 8)
        secs.append((va, vsz, ptr, rsz))
    rsrc_rva = struct.unpack_from('<I', data, e + 24 + 96 + 2 * 8)[0]
    return data, secs, rsrc_rva


def rva_to_off(secs, rva):
    for va, vsz, ptr, rsz in secs:
        if va <= rva < va + max(vsz, rsz):
            return ptr + (rva - va)
    return None


def walk_resources(data, secs, base, off, path, out):
    nnamed, nid = struct.unpack_from('<HH', data, off + 12)
    entries = off + 16
    for i in range(nnamed + nid):
        name, offset = struct.unpack_from('<II', data, entries + i * 8)
        if name & 0x80000000:
            no = base + (name & 0x7FFFFFFF)
            ln = struct.unpack_from('<H', data, no)[0]
            key = data[no + 2:no + 2 + ln * 2].decode('utf-16-le')
        else:
            key = name
        if offset & 0x80000000:
            walk_resources(data, secs, base, base + (offset & 0x7FFFFFFF), path + [key], out)
        else:
            drva, dsize = struct.unpack_from('<II', data, base + offset)
            fo = rva_to_off(secs, drva)
            out.append((path + [key], data[fo:fo + dsize]))


def read_sz_or_ord(buf, pos):
    first = struct.unpack_from('<H', buf, pos)[0]
    if first == 0x0000:
        return '', pos + 2
    if first == 0xFFFF:
        return struct.unpack_from('<H', buf, pos + 2)[0], pos + 4
    chars = []
    while True:
        c = struct.unpack_from('<H', buf, pos)[0]
        pos += 2
        if c == 0:
            break
        chars.append(chr(c))
    return ''.join(chars), pos


def decode_dialog(buf):
    # DLGTEMPLATEEX leads with dlgVer=1 then signature=0xFFFF, in that order.
    dlgver, sig = struct.unpack_from('<HH', buf, 0)
    ex = (dlgver == 1 and sig == 0xFFFF)
    if ex:
        _, _, _, exstyle, style, cdit, x, y, cx, cy = struct.unpack_from('<HHIIIHhhhh', buf, 0)
        pos = 26
    else:
        style, exstyle, cdit, x, y, cx, cy = struct.unpack_from('<IIHhhhh', buf, 0)
        pos = 18

    d = {'extended': ex, 'style': '0x%08X' % style, 'exstyle': '0x%08X' % exstyle,
         'x': x, 'y': y, 'cx': cx, 'cy': cy}
    _, pos = read_sz_or_ord(buf, pos)          # menu
    _, pos = read_sz_or_ord(buf, pos)          # window class
    title, pos = read_sz_or_ord(buf, pos)
    d['title'] = title

    if style & 0x00000040:                      # DS_SETFONT
        if ex:
            pt = struct.unpack_from('<H', buf, pos)[0]
            pos += 6
        else:
            pt = struct.unpack_from('<H', buf, pos)[0]
            pos += 2
        face, pos = read_sz_or_ord(buf, pos)
        d['font'] = {'point': pt, 'face': face}

    items = []
    for _ in range(cdit):
        pos = (pos + 3) & ~3
        if ex:
            _, iexstyle, istyle, ix, iy, icx, icy, iid = struct.unpack_from('<IIIhhhhI', buf, pos)
            pos += 24
        else:
            istyle, iexstyle, ix, iy, icx, icy, iid = struct.unpack_from('<IIhhhhH', buf, pos)
            pos += 18
        icls, pos = read_sz_or_ord(buf, pos)
        itxt, pos = read_sz_or_ord(buf, pos)
        extra = struct.unpack_from('<H', buf, pos)[0]
        pos += 2 + extra
        if isinstance(icls, int):
            icls = STD_CLASS.get(icls, '0x%02X' % icls)
        items.append({'class': icls, 'id': iid, 'id_hex': '0x%04X' % iid,
                      'du': {'x': ix, 'y': iy, 'cx': icx, 'cy': icy},
                      'style': '0x%08X' % istyle, 'exstyle': '0x%08X' % iexstyle,
                      'text': itxt})
    d['items'] = items
    return d


def export_bitmaps(resources, outdir):
    try:
        from PIL import Image
    except ImportError:
        print('  (Pillow not installed; skipping bitmap export)', file=sys.stderr)
        return {}

    os.makedirs(outdir, exist_ok=True)
    index = {}
    for path, blob in resources:
        if not path or path[0] != RT_BITMAP:
            continue
        name = str(path[1])
        try:
            biSize, biWidth, biHeight, _, biBitCount, biCompression = \
                struct.unpack_from('<IiiHHI', blob, 0)
            clrUsed = struct.unpack_from('<I', blob, 32)[0]
            if biBitCount <= 8:
                palette = (clrUsed if clrUsed else (1 << biBitCount)) * 4
            else:
                palette = 12 if biCompression == 3 else 0
            header = b'BM' + struct.pack('<IHHI', 14 + len(blob), 0, 0, 14 + biSize + palette)
            img = Image.open(io.BytesIO(header + blob)).convert('RGBA')
            fn = 'bmp_%s.png' % name
            img.save(os.path.join(outdir, fn))
            index[name] = {'file': fn, 'w': biWidth, 'h': abs(biHeight), 'bpp': biBitCount}
        except Exception as exc:
            print('  bitmap %s failed: %s' % (name, exc), file=sys.stderr)
    return index


# --------------------------------------------------------------------------
# Decompile scraping
# --------------------------------------------------------------------------

NUM = r'(-?(?:0x[0-9a-fA-F]+|\d+))'


def num(v):
    return int(v, 16) if v.lower().startswith(('0x', '-0x')) else int(v)


# Constructors worth recovering, and how many arguments each pushes. `this`
# travels in ECX under __thiscall and is not pushed. Counts come from the
# PDB-derived signatures in function_index.tsv.
ASM_CTORS = {
    'ShellButton::ShellButton': ('ShellButton', 11),
    'TextLabel::TextLabel': ('TextLabel', 7),
    'OptionBox::OptionBox': ('OptionBox', 6),
    'ShellBitmap::ShellBitmap': ('ShellBitmap', 3),
    'FlagList::FlagList': ('FlagList', 3),
}

PUSH_IMM = re.compile(r'^\s*[0-9a-f]+:\s+pushl\s+\$(0x[0-9a-fA-F]+|\d+)')
PUSH_REG = re.compile(r'^\s*[0-9a-f]+:\s+pushl\s+%(\w+)')
PUSH_MEM = re.compile(r'^\s*[0-9a-f]+:\s+pushl\s+(0x[0-9a-fA-F]+)')
MOV_IMM = re.compile(r'^\s*[0-9a-f]+:\s+movl\s+\$(0x[0-9a-fA-F]+|\d+),\s*%(\w+)')
XOR_SELF = re.compile(r'^\s*[0-9a-f]+:\s+xorl\s+%(\w+),\s*%(\w+)')
CALL = re.compile(r'^\s*([0-9a-f]+):\s+calll\s+(0x[0-9a-fA-F]+)')


def read_c_string(data, secs, va):
    off = rva_to_off(secs, va - 0x400000)
    if off is None:
        return None
    end = data.find(b'\x00', off, off + 512)
    if end < 0:
        return None
    try:
        return data[off:end].decode('ascii')
    except UnicodeDecodeError:
        return None


def resolve_reg(lines, idx, reg, limit=400):
    """Constant-propagate one register backwards from `idx`. Returns None when
    the value comes from somewhere this simple scan cannot see, which is
    reported rather than guessed at."""
    for j in range(idx - 1, max(0, idx - limit) - 1, -1):
        m = XOR_SELF.match(lines[j])
        if m and m.group(1) == reg and m.group(2) == reg:
            return 0
        m = MOV_IMM.match(lines[j])
        if m and m.group(2) == reg:
            return num(m.group(1))
    return None


def scrape_widgets_asm(asm_path, addr_names, data, secs):
    """Recover the same constructor calls from a disassembly listing.

    NetGameDlgProc and ShellDlgProc both exceeded Ghidra's decompiler timeout,
    so the multiplayer *game setup* screen is only available as assembly.
    """
    lines = open(asm_path, encoding='utf-8', errors='replace').read().splitlines()
    widgets = []
    for i, line in enumerate(lines):
        m = CALL.match(line)
        if not m:
            continue
        target = num(m.group(2))
        kind_info = ASM_CTORS.get(addr_names.get(target, ''))
        if not kind_info:
            continue
        kind, argc = kind_info

        args = []
        j = i - 1
        while j >= 0 and len(args) < argc:
            ln = lines[j]
            mi = PUSH_IMM.match(ln)
            if mi:
                args.append(num(mi.group(1)))
                j -= 1
                continue
            mr = PUSH_REG.match(ln)
            if mr:
                args.append(resolve_reg(lines, j, mr.group(1)))
                j -= 1
                continue
            mm = PUSH_MEM.match(ln)
            if mm:
                args.append({'global': mm.group(1)})
                j -= 1
                continue
            if re.match(r'^\s*[0-9a-f]+:\s+(movl|leal|cmpl|testl|xorl|movzbl|movsbl)\b', ln):
                j -= 1
                continue
            break

        if len(args) != argc:
            continue
        # Arguments are pushed right-to-left, so walking backwards from the
        # call meets them in declaration order already -- do not reverse.

        w = {'kind': kind, 'call_site': '0x%s' % m.group(1), 'source': 'asm'}
        if kind == 'ShellButton':
            label = args[10]
            w.update(bitmaps={'off': args[2], 'over': args[3], 'on': args[4]},
                     px={'x': args[5], 'y': args[6], 'w': args[7], 'h': args[8]},
                     flag=args[9],
                     label=read_c_string(data, secs, label) if isinstance(label, int) and label else None)
        elif kind == 'TextLabel':
            text_ = args[1]
            w.update(text=read_c_string(data, secs, text_) if isinstance(text_, int) and text_ else None,
                     px={'x': args[2], 'y': args[3], 'w': args[4], 'h': args[5]}, flag=args[6])
        elif kind == 'OptionBox':
            w.update(index=args[1], px={'x': args[2], 'y': args[3], 'w': args[4], 'h': args[5]})
        elif kind == 'ShellBitmap':
            f = args[0]
            w.update(file=read_c_string(data, secs, f) if isinstance(f, int) and f else None,
                     px={'x': args[1], 'y': args[2]})
        elif kind == 'FlagList':
            w.update(px={'x': args[1], 'y': args[2]})
        widgets.append(w)
    return widgets


def load_addr_names(decompile_dir):
    names = {}
    with open(os.path.join(decompile_dir, 'function_index.tsv'), encoding='utf-8', errors='replace') as f:
        next(f)
        for line in f:
            parts = line.rstrip('\n').split('\t')
            if len(parts) > 1:
                names[int(parts[0], 16)] = parts[1]
    return names


def find_failed_asm(decompile_dir, name):
    folder = os.path.join(decompile_dir, 'failed_asm')
    if not os.path.isdir(folder):
        return None, None
    for fn in os.listdir(folder):
        if fn.endswith('_%s.asm' % name):
            return fn.split('_', 1)[0], os.path.join(folder, fn)
    return None, None


def find_function_file(decompile_dir, name):
    index = os.path.join(decompile_dir, 'function_index.tsv')
    with open(index, encoding='utf-8', errors='replace') as f:
        next(f)
        for line in f:
            parts = line.rstrip('\n').split('\t')
            if len(parts) > 1 and parts[1] == name:
                addr = parts[0]
                folder = os.path.join(decompile_dir, 'functions', addr[:4])
                if os.path.isdir(folder):
                    for fn in os.listdir(folder):
                        if fn.startswith(addr + '_'):
                            return addr, os.path.join(folder, fn)
    return None, None


def flatten(text):
    """Collapse Ghidra's line wrapping and its spacing around punctuation, so a
    call written across four lines matches the same pattern as one written on
    a single line."""
    flat = re.sub(r'\s+', ' ', text)
    return re.sub(r'\s*([(),])\s*', r'\1', flat)


def scrape_widgets(text):
    """Pull the widget constructor calls out of one decompiled dialog proc.

    Every constructor here takes literal coordinates, which is what makes this
    worth scraping rather than hand-transcribing.
    """
    flat = flatten(text)
    widgets = []

    # ShellButton(this, hwnd, hinst, bmpOff, bmpOver, bmpOn, x, y, w, h, flag, "label")
    pat = re.compile(
        r'(\w+)\s*=\s*ShellButton::ShellButton\(\w+,\w+,shell_hInstance,'
        + ','.join([NUM] * 8) + r',(?:"([^"]*)"|\(char \*\)0x0)\)')
    for m in pat.finditer(flat):
        name, *vals = m.groups()[:9]
        label = m.group(10)
        v = [num(x) for x in vals]
        widgets.append({'kind': 'ShellButton', 'var': name,
                        'bitmaps': {'off': v[0], 'over': v[1], 'on': v[2]},
                        'px': {'x': v[3], 'y': v[4], 'w': v[5], 'h': v[6]},
                        'flag': v[7], 'label': label})

    # TextLabel(this, hwnd, "text", x, y, w, h, flag)
    pat = re.compile(r'(\w+)\s*=\s*TextLabel::TextLabel\(\w+,\w+,"([^"]*)",'
                     + ','.join([NUM] * 5) + r'\)')
    for m in pat.finditer(flat):
        name, text_, *vals = m.groups()
        v = [num(x) for x in vals]
        widgets.append({'kind': 'TextLabel', 'var': name, 'text': text_,
                        'px': {'x': v[0], 'y': v[1], 'w': v[2], 'h': v[3]}, 'flag': v[4]})

    # OptionBox(this, hwnd, index, x, y, w, h)
    pat = re.compile(r'(\w+)\s*=\s*OptionBox::OptionBox\(\w+,\w+,'
                     + ','.join([NUM] * 5) + r'\)')
    for m in pat.finditer(flat):
        name, *vals = m.groups()
        v = [num(x) for x in vals]
        widgets.append({'kind': 'OptionBox', 'var': name, 'index': v[0],
                        'px': {'x': v[1], 'y': v[2], 'w': v[3], 'h': v[4]}})

    # OptionBox::LoadItemList(box, slot, "text", value)
    pat = re.compile(r'OptionBox::LoadItemList\((\w+),' + NUM + r',"([^"]*)",' + NUM + r'\)')
    items = {}
    for m in pat.finditer(flat):
        items.setdefault(m.group(1), []).append(
            {'slot': num(m.group(2)), 'text': m.group(3), 'value': num(m.group(4))})
    for w in widgets:
        if w['kind'] == 'OptionBox' and w['var'] in items:
            w['items'] = sorted(items[w['var']], key=lambda i: i['slot'])

    # ShellBitmap(this, "bitmap\\x.bmp", a, b)  -- background plates
    pat = re.compile(r'(\w+)\s*=\s*ShellBitmap::ShellBitmap\(\w+,"([^"]*)",'
                     + NUM + r',' + NUM + r'\)')
    for m in pat.finditer(flat):
        widgets.append({'kind': 'ShellBitmap', 'var': m.group(1),
                        'file': m.group(2).replace('\\\\', '\\'),
                        'px': {'x': num(m.group(3)), 'y': num(m.group(4))}})

    # FlagList(this, hwnd, x, y)
    for m in re.finditer(r'(\w+)\s*=\s*FlagList::FlagList\(\w+,\w+,' + NUM + r',' + NUM + r'\)', flat):
        widgets.append({'kind': 'FlagList', 'var': m.group(1),
                        'px': {'x': num(m.group(2)), 'y': num(m.group(3))}})

    # ShellButton::SetLabelPos(button, x, y, w, h)
    for m in re.finditer(r'ShellButton::SetLabelPos\((\w+),' + ','.join([NUM] * 4) + r'\)', flat):
        for w in widgets:
            if w.get('var') == m.group(1):
                w['label_px'] = {'x': num(m.group(2)), 'y': num(m.group(3)),
                                 'w': num(m.group(4)), 'h': num(m.group(5))}

    # ShellButton::SetSoundFile(button, "over.wav", "click.wav")
    for m in re.finditer(r'ShellButton::SetSoundFile\((\w+),"([^"]*)","([^"]*)"\)', flat):
        for w in widgets:
            if w.get('var') == m.group(1):
                w['sounds'] = {'over': m.group(2), 'click': m.group(3)}

    # read_text_label("section", "key", <var>->labelText/textData)
    for m in re.finditer(r'read_text_label\("([^"]*)","([^"]*)",(\w+)->\w+\)', flat):
        for w in widgets:
            if w.get('var') == m.group(3):
                w['string_key'] = {'section': m.group(1), 'key': m.group(2)}

    return widgets


def scrape_movewindow(text):
    """Recover MoveWindow placements for the real Win32 controls.

    Ghidra hoists the arguments into locals, so track the last literal assigned
    to each name and resolve the call against that.
    """
    placements = []
    env = {}
    pending_id = None
    pending_var = None
    assign = re.compile(r'^\s*(\w+)\s*=\s*' + NUM + r'\s*;')
    getitem = re.compile(r'(\w+)\s*=\s*GetDlgItem\s*\(\s*\(HWND\)\w+\s*,\s*' + NUM + r'\s*\)')
    movewin = re.compile(r'MoveWindow\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*,')

    for line in text.splitlines():
        m = assign.match(line)
        if m:
            env[m.group(1)] = num(m.group(2))
            continue
        m = getitem.search(line)
        if m:
            pending_var, pending_id = m.group(1), num(m.group(2))
            continue
        m = movewin.search(line)
        if m and pending_id is not None and m.group(1) == pending_var:
            try:
                x, y, w, h = (env[m.group(i)] for i in range(2, 6))
            except KeyError:
                continue
            placements.append({'id': pending_id, 'id_hex': '0x%04X' % pending_id,
                               'px': {'x': x, 'y': y, 'w': w, 'h': h}})
            pending_id = None
    return placements


# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--install', required=True, help='Battlezone_Install directory (holds bzone.exe)')
    ap.add_argument('--decompile', required=True, help='BZ1_Source/1.5 directory')
    ap.add_argument('--out', required=True, help='output directory')
    ap.add_argument('--bitmaps', action='store_true', help='also export RT_BITMAP art as PNG')
    args = ap.parse_args()

    exe = os.path.join(args.install, 'bzone.exe')
    data, secs, rsrc = load_pe(exe)
    base = rva_to_off(secs, rsrc)
    resources = []
    walk_resources(data, secs, base, base, [], resources)

    dialogs = {}
    for path, blob in resources:
        if path and path[0] == RT_DIALOG:
            try:
                dialogs[str(path[1])] = decode_dialog(blob)
            except Exception as exc:
                dialogs[str(path[1])] = {'error': str(exc)}

    os.makedirs(args.out, exist_ok=True)

    addr_names = load_addr_names(args.decompile)

    screens = {}
    for proc, resid in DIALOG_PROCS.items():
        addr, fpath = find_function_file(args.decompile, proc)
        if fpath:
            text = open(fpath, encoding='utf-8', errors='replace').read()
            widgets = scrape_widgets(text)
            placements = scrape_movewindow(text)
            origin = 'decompile'
        else:
            # NetGameDlgProc and ShellDlgProc exceeded Ghidra's decompiler
            # timeout; the package ships assembly for those instead.
            addr, apath = find_failed_asm(args.decompile, proc)
            if not apath:
                print('  %s: not in the decompile or the asm fallback' % proc, file=sys.stderr)
                continue
            widgets = scrape_widgets_asm(apath, addr_names, data, secs)
            placements = []
            origin = 'asm-fallback'
        entry = {
            'proc': proc,
            'proc_address': '0x%s' % addr,
            'source': origin,
            'dialog_resource': resid,
            'template': dialogs.get(str(resid)) if resid else None,
            'widgets': widgets,
            'control_placements': placements,
        }
        if proc == 'STransportDlgProc':
            entry['transport_modes'] = TRANSPORT_MODES
        screens[proc] = entry

    manifest = {
        'source': {'exe': os.path.abspath(exe), 'decompile': os.path.abspath(args.decompile)},
        'note': ('Shell coordinates are pixels in the 640x480 shell. Dialog template '
                 'coordinates are dialog units; convert with the template font '
                 '(4 horizontal units = 1 average char width, 8 vertical = 1 char height).'),
        'screens': screens,
        'dialogs': dialogs,
    }

    if args.bitmaps:
        manifest['bitmaps'] = export_bitmaps(resources, os.path.join(args.out, 'bitmaps'))

    out_path = os.path.join(args.out, 'bz15-ui.json')
    with open(out_path, 'w', encoding='utf-8') as f:
        json.dump(manifest, f, indent=1)

    print('wrote %s' % out_path)
    for proc, entry in screens.items():
        kinds = {}
        for w in entry['widgets']:
            kinds[w['kind']] = kinds.get(w['kind'], 0) + 1
        print('  %-20s res=%-6s %-13s controls=%-3d %s'
              % (proc,
                 entry['dialog_resource'],
                 entry['source'],
                 len(entry['control_placements']),
                 ' '.join('%s=%d' % kv for kv in sorted(kinds.items()))))
    if args.bitmaps:
        print('  bitmaps: %d' % len(manifest.get('bitmaps', {})))


if __name__ == '__main__':
    main()
