// Reports what the bzint.pdb gave us BEYOND names: reconstructed C++ types, classes,
// and vftables sitting in the analyzed 1.5 program. Run headless with -process bzone.exe.
//@category BSim

import java.util.*;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.GhidraClass;
import ghidra.program.model.symbol.*;

public class ReportTypeStats extends GhidraScript {
	@Override
	protected void run() throws Exception {
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		int structs = 0, unions = 0, enums = 0, typedefs = 0, funcdefs = 0;
		Iterator<DataType> it = dtm.getAllDataTypes();
		while (it.hasNext()) {
			DataType dt = it.next();
			if (dt instanceof Structure) structs++;
			else if (dt instanceof Union) unions++;
			else if (dt instanceof ghidra.program.model.data.Enum) enums++;
			else if (dt instanceof TypeDef) typedefs++;
			else if (dt instanceof FunctionDefinition) funcdefs++;
		}
		println("STRUCTS=" + structs);
		println("UNIONS=" + unions);
		println("ENUMS=" + enums);
		println("TYPEDEFS=" + typedefs);
		println("FUNCDEFS=" + funcdefs);

		// C++ classes recovered (GhidraClass namespaces) + vftables.
		SymbolTable st = currentProgram.getSymbolTable();
		int classes = 0;
		List<String> gameClasses = new ArrayList<>();
		Iterator<GhidraClass> ci = st.getClassNamespaces();
		while (ci.hasNext()) {
			GhidraClass gc = ci.next();
			classes++;
			String n = gc.getName();
			if (n.matches(
				".*(Craft|Ordnance|Weapon|Object|Vehicle|Tank|Turret|Wingman|Pilot|" +
				"Building|Powerup|Mine|AI|Team|Player|Mission|Terrain|Collision|Damage).*")) {
				gameClasses.add(gc.getName(true));
			}
		}
		println("GHIDRA_CLASSES=" + classes);

		int vftables = 0;
		SymbolIterator si = st.getSymbolIterator("*vftable*", true);
		while (si.hasNext()) { si.next(); vftables++; }
		println("VFTABLES=" + vftables);

		Collections.sort(gameClasses);
		println("GAME_CLASS_SAMPLE (" + gameClasses.size() + " matched):");
		int shown = 0;
		for (String g : gameClasses) {
			println("  " + g);
			if (++shown >= 40) { println("  ..."); break; }
		}
	}
}
