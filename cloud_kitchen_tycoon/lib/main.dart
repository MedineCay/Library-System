import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() => runApp(const CloudKitchenApp());

class Area {
  final String id, title;
  final IconData icon;
  final Color color;
  Area(this.id, this.title, this.icon, this.color);
}

class CloudKitchenApp extends StatelessWidget {
  const CloudKitchenApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData.dark().copyWith(scaffoldBackgroundColor: const Color(0xFF0F0F0F)),
      home: const Dashboard(),
    );
  }
}

class Dashboard extends StatefulWidget {
  const Dashboard({super.key});
  @override
  State<Dashboard> createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  String status = "Bir alan seçin...";
  List alinanlar = [];
  double memnuniyet = 0, harcanan = 0;
  String? selectedAreaId;

  final List<Area> gameAreas = [
    Area("Alan_1", "Kampüs", Icons.school, Colors.blue),
    Area("Alan_2", "İş Merkezi", Icons.business_center, Colors.teal),
    Area("Alan_3", "Lüks Semt", Icons.villa, Colors.purple),
    Area("Alan_4", "Sanayi", Icons.factory, Colors.orange),
    Area("Alan_5", "Terminal", Icons.flight_takeoff, Colors.red),
    Area("Alan_6", "Turistik", Icons.fort, Colors.amber),
    Area("Alan_7", "AVM", Icons.shopping_bag, Colors.pink),
    Area("Alan_8", "Banliyö", Icons.family_restroom, Colors.green),
    Area("Alan_9", "Eğlence", Icons.nightlife, Colors.indigo),
    Area("Alan_10", "Teknopark", Icons.biotech, Colors.cyan),
  ];

  Future<void> optimizeEt() async {
    if (selectedAreaId == null) return;
    setState(() => status = "GAMSpy strateji kuruyor...");
    
    try {
      final res = await http.get(Uri.parse('http://127.0.0.1:8000/optimize?bolge=$selectedAreaId&konsept=İtalyan&butce=3000'));
      
      if (res.statusCode == 200) {
        final decoded = json.decode(res.body);
        
        // --- KRİTİK DEBUG: Python tam olarak ne gönderiyor? ---
        print("PYTHON CEVABI: $decoded"); 

        // Verinin nerede olduğunu kontrol edelim
        var responseData = decoded['veriler'] ?? decoded;

        setState(() {
          // Liste ismini kontrol et (alinanlar mı yoksa başka bir şey mi?)
          alinanlar = responseData['alinanlar'] ?? [];
          
          // Python'dan gelen anahtar isimlerini kontrol et
          // Hem 'toplam_memnuniyet' hem de 'puan' ihtimalini deniyoruz
          memnuniyet = (responseData['toplam_memnuniyet'] ?? responseData['puan'] ?? 0).toDouble();
          
          // Hem 'harcanan_para' hem de 'maliyet' ihtimalini deniyoruz
          harcanan = (responseData['harcanan_para'] ?? responseData['maliyet'] ?? 0).toDouble();
          
          status = alinanlar.isEmpty ? "Veri boş geldi!" : "Strateji Hazır! 👨‍🍳";
        });
      }
    } catch (e) {
      print("FLUTTER HATASI: $e");
      setState(() => status = "Veri işleme hatası!");
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("👨‍🍳 Cloud-Kitchen Tycoon"), backgroundColor: Colors.transparent, elevation: 0),
      body: Column(
        children: [
          SizedBox(
            height: 120,
            child: ListView.builder(
              scrollDirection: Axis.horizontal,
              itemCount: gameAreas.length,
              itemBuilder: (context, i) => GestureDetector(
                onTap: () => setState(() => selectedAreaId = gameAreas[i].id),
                child: Container(
                  width: 100, margin: const EdgeInsets.all(8),
                  decoration: BoxDecoration(
                    color: selectedAreaId == gameAreas[i].id ? gameAreas[i].color : Colors.white10,
                    borderRadius: BorderRadius.circular(15),
                    border: Border.all(color: selectedAreaId == gameAreas[i].id ? Colors.white : Colors.transparent),
                  ),
                  child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
                    Icon(gameAreas[i].icon, color: Colors.white),
                    const SizedBox(height: 5),
                    Text(gameAreas[i].title, style: const TextStyle(fontSize: 10)),
                  ]),
                ),
              ),
            ),
          ),
          Expanded(
            child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
              Text(status, style: const TextStyle(fontSize: 18, color: Colors.amber, fontWeight: FontWeight.bold)),
              const SizedBox(height: 20),
              Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly, children: [
                _stat("PUAN", memnuniyet.toString(), Colors.green),
                _stat("MALİYET", "${harcanan.toInt()} TL", Colors.red),
              ]),
              const SizedBox(height: 20),
              Expanded(
                child: ListView.builder(
                  itemCount: alinanlar.length,
                  itemBuilder: (context, i) => ListTile(
                    leading: const Icon(Icons.restaurant, size: 18),
                    title: Text(alinanlar[i].toString()),
                  ),
                ),
              ),
            ]),
          ),
          Padding(
            padding: const EdgeInsets.all(20.0),
            child: ElevatedButton(
              onPressed: optimizeEt,
              style: ElevatedButton.styleFrom(backgroundColor: Colors.amber, minimumSize: const Size(double.infinity, 60)),
              child: const Text("STRATEJİ OLUŞTUR", style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold)),
            ),
          ),
        ],
      ),
    );
  }

  Widget _stat(String label, String value, Color color) {
    return Column(children: [
      Text(label, style: const TextStyle(fontSize: 12, color: Colors.white54)),
      Text(value, style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold, color: color)),
    ]);
  }
}
