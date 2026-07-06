// Exports the reconstructed C++ object model from the 1.5 program (bzint.pdb) to JSON:
// game-relevant class/struct layouts (fields with offset+type), member-function lists,
// enums, and a full type index. Read-only. Run headless with -process bzone.exe.
//
//   -postScript ExportObjectModel.java <outJsonPath>
//@category BSim

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.*;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.GhidraClass;
import ghidra.program.model.symbol.*;

public class ExportObjectModel extends GhidraScript {

	// Names worth exporting in full detail (the game object model + supporting systems).
	private static final String GAME_RE =
		".*(Craft|Ordnance|Weapon|Shot|Explosion|Object|Vehicle|Tank|Turret|Wingman|Pilot|" +
		"Building|Powerup|Mine|Ammo|Health|Scrap|Silo|AI|Ai|Team|Player|Mission|Misn|Terrain|" +
		"Collision|Damage|Hover|Walker|Flyer|Nav|Path|Odf|Config|Recycler|Factory|Armory|" +
		"Constructor|Bomber|Scout|Command).*";

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		String out = args.length >= 1 ? args[0] : "object_model.json";

		DataTypeManager dtm = currentProgram.getDataTypeManager();

		// Index all structures/unions by simple name (keep the richest definition per name).
		Map<String, Composite> comps = new HashMap<>();
		List<ghidra.program.model.data.Enum> enums = new ArrayList<>();
		int nStruct = 0, nUnion = 0, nEnum = 0, nTypedef = 0;
		Iterator<DataType> it = dtm.getAllDataTypes();
		while (it.hasNext()) {
			DataType dt = it.next();
			if (dt instanceof Structure) {
				nStruct++;
				keepRichest(comps, (Composite) dt);
			}
			else if (dt instanceof Union) {
				nUnion++;
				keepRichest(comps, (Composite) dt);
			}
			else if (dt instanceof ghidra.program.model.data.Enum) {
				nEnum++;
				enums.add((ghidra.program.model.data.Enum) dt);
			}
			else if (dt instanceof TypeDef) {
				nTypedef++;
			}
		}

		// Member functions per class namespace.
		SymbolTable st = currentProgram.getSymbolTable();
		Map<String, List<Symbol>> methodsByClass = new HashMap<>();
		Iterator<GhidraClass> ci = st.getClassNamespaces();
		while (ci.hasNext()) {
			GhidraClass gc = ci.next();
			List<Symbol> ms = new ArrayList<>();
			for (Symbol s : st.getSymbols(gc)) {
				if (s.getSymbolType() == SymbolType.FUNCTION) {
					ms.add(s);
				}
			}
			if (!ms.isEmpty()) {
				methodsByClass.put(gc.getName(), ms);
			}
		}

		StringBuilder json = new StringBuilder();
		json.append("{\n");
		json.append("  \"program\": \"").append(esc(currentProgram.getName())).append("\",\n");
		json.append("  \"counts\": {\"structs\":").append(nStruct)
			.append(",\"unions\":").append(nUnion)
			.append(",\"enums\":").append(nEnum)
			.append(",\"typedefs\":").append(nTypedef)
			.append(",\"classes_with_methods\":").append(methodsByClass.size())
			.append("},\n");

		// Game-relevant composites (full field layout + methods).
		List<String> names = new ArrayList<>(comps.keySet());
		Collections.sort(names);
		json.append("  \"game_classes\": [\n");
		boolean first = true;
		int emitted = 0;
		for (String name : names) {
			if (!name.matches(GAME_RE)) {
				continue;
			}
			Composite c = comps.get(name);
			if (!first) {
				json.append(",\n");
			}
			first = false;
			emitted++;
			json.append("    {\"name\":\"").append(esc(name)).append("\"");
			json.append(",\"kind\":\"").append(c instanceof Union ? "union" : "struct").append("\"");
			json.append(",\"size\":").append(c.getLength());
			DataTypeComponent[] members = c.getComponents();
			// base-class hint: first member that is itself a Composite at offset 0
			if (members.length > 0 && members[0].getOffset() == 0
					&& members[0].getDataType() instanceof Composite) {
				json.append(",\"base_hint\":\"")
					.append(esc(members[0].getDataType().getName())).append("\"");
			}
			json.append(",\"fields\":[");
			for (int i = 0; i < members.length; i++) {
				DataTypeComponent m = members[i];
				if (i > 0) {
					json.append(",");
				}
				String fn = m.getFieldName() != null ? m.getFieldName() : ("f_" + m.getOffset());
				json.append("{\"offset\":").append(m.getOffset())
					.append(",\"name\":\"").append(esc(fn))
					.append("\",\"type\":\"").append(esc(m.getDataType().getName()))
					.append("\",\"size\":").append(m.getLength()).append("}");
			}
			json.append("]");
			// methods
			List<Symbol> ms = methodsByClass.get(name);
			json.append(",\"methods\":[");
			if (ms != null) {
				ms.sort(Comparator.comparing(s -> s.getAddress().getOffset()));
				for (int i = 0; i < ms.size(); i++) {
					if (i > 0) {
						json.append(",");
					}
					json.append("{\"name\":\"").append(esc(ms.get(i).getName()))
						.append("\",\"va\":\"0x").append(Long.toHexString(ms.get(i).getAddress().getOffset()))
						.append("\"}");
				}
			}
			json.append("]}");
		}
		json.append("\n  ],\n");

		// Game-relevant enums.
		json.append("  \"game_enums\": [\n");
		enums.sort(Comparator.comparing(DataType::getName));
		first = true;
		for (ghidra.program.model.data.Enum e : enums) {
			if (!e.getName().matches(GAME_RE)) {
				continue;
			}
			if (!first) {
				json.append(",\n");
			}
			first = false;
			json.append("    {\"name\":\"").append(esc(e.getName())).append("\",\"values\":[");
			String[] enames = e.getNames();
			for (int i = 0; i < enames.length; i++) {
				if (i > 0) {
					json.append(",");
				}
				json.append("{\"name\":\"").append(esc(enames[i]))
					.append("\",\"value\":").append(e.getValue(enames[i])).append("}");
			}
			json.append("]}");
		}
		json.append("\n  ],\n");

		// Full index of every composite (name,kind,size) for browsing.
		json.append("  \"all_types\": [\n");
		first = true;
		for (String name : names) {
			Composite c = comps.get(name);
			if (!first) {
				json.append(",\n");
			}
			first = false;
			json.append("    {\"name\":\"").append(esc(name))
				.append("\",\"kind\":\"").append(c instanceof Union ? "union" : "struct")
				.append("\",\"size\":").append(c.getLength()).append("}");
		}
		json.append("\n  ]\n}\n");

		try (BufferedWriter w = new BufferedWriter(new FileWriter(out))) {
			w.write(json.toString());
		}
		println("game_classes emitted: " + emitted);
		println("wrote " + out);
	}

	private static void keepRichest(Map<String, Composite> map, Composite c) {
		Composite prev = map.get(c.getName());
		if (prev == null || c.getNumComponents() > prev.getNumComponents()) {
			map.put(c.getName(), c);
		}
	}

	private static String esc(String s) {
		if (s == null) {
			return "";
		}
		StringBuilder b = new StringBuilder(s.length() + 8);
		for (int i = 0; i < s.length(); i++) {
			char ch = s.charAt(i);
			switch (ch) {
				case '"': b.append("\\\""); break;
				case '\\': b.append("\\\\"); break;
				case '\n': b.append("\\n"); break;
				case '\r': b.append("\\r"); break;
				case '\t': b.append("\\t"); break;
				default:
					if (ch < 0x20) {
						b.append(String.format("\\u%04x", (int) ch));
					}
					else {
						b.append(ch);
					}
			}
		}
		return b.toString();
	}
}
