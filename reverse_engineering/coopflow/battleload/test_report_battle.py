import datetime as dt
import json
import tempfile
import unittest
from pathlib import Path
from report_battle import summarize


class ReportEvidence(unittest.TestCase):
    def test_injected_drops_retries_and_twelve_links(self):
        with tempfile.TemporaryDirectory() as temporary:
            run = Path(temporary)
            origin = 1791550000
            samples = []
            for phase, times in (("idle", (0,5)), ("combat", (10,20,30))):
                for seconds in times:
                    for client in range(4):
                        samples.append({"client":client,"phase":phase,
                            "at":dt.datetime.fromtimestamp(origin+seconds,dt.timezone.utc).isoformat(),
                            "cpuSeconds":seconds*.5,"commandMs":250,"workingSetBytes":1000,
                            "state":{"rampCompleted":10 if phase=="combat" else None,"finished":False,
                                     "simulationTime":seconds,"updates":seconds*20,
                                     "peakAI":80,"peakScrap":8,"scrapObserved":12}})
            (run/"battle-samples.jsonl").write_text("\n".join(json.dumps(s) for s in samples))
            packets=[]
            for source in range(4):
                for target in range(4):
                    if source==target: continue
                    for seconds in (1,3,12,22):
                        header = ("80" + "00"*16 + f"{seconds:02x}")
                        packets.append({"tsUnixMs":(origin+seconds)*1000,"source":f"127.0.0.1:{1000+source}",
                            "target":f"127.0.0.1:{1000+target}","disposition":"dropped_impair_loss" if seconds==22 else "forwarded",
                            "datagramHex":header+"aabb","transport":{"wireBytes":20,"headerBytes":18,
                                "kindNibble":0,"flagsByte":"0x80","seqA":7}})
            (run/"relay-trace.jsonl").write_text("\n".join(json.dumps(p) for p in packets))
            report=summarize(run)
            battle=report["rates"]["sustainedBattle"]
            self.assertEqual(battle["activeDirectedLinks"],12)
            self.assertEqual(sum(l["relayDrops"] for l in battle["links"].values()),12)
            self.assertEqual(sum(l["reliableRepeatedDatagrams"] for l in battle["links"].values()),12)
            self.assertAlmostEqual(battle["aggregateBzrDatagramKbps"],24*20*8/1000/20)
            self.assertAlmostEqual(report["clients"]["0"]["cpuEquivalentCores"],.5)
            (run/"battle-samples.jsonl").write_text(json.dumps(samples[0]))
            with self.assertRaisesRegex(ValueError,"missing idle/combat"):
                summarize(run)


if __name__ == "__main__":
    unittest.main()
