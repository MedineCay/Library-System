from gamspy import Container, Set, Parameter, Variable, Equation, Model, Sum, Sense
import pandas as pd

def run_supply_optimization(bolge, konsept, butce):
    c = Container()

    # 1. VERİ: GAMSpy'ın sevdiği formatta (Indexler başta olmalı)
    malzeme_verisi = pd.DataFrame({
        'id': ['Un', 'Et', 'Feslegen', 'Truf_Yagi', 'Ozel_Sos', 'Sebze', 'Deniz_Urunu', 'Baharat'],
        'maliyet': [100.0, 800.0, 150.0, 1200.0, 400.0, 200.0, 1500.0, 100.0],
        'kalite': [20.0, 80.0, 40.0, 150.0, 60.0, 30.0, 200.0, 20.0]
    })

    bolge_stratejileri = {
        "Alan_1": {"limit": 0.4, "min_puan": 40, "ad": "Kampüs"},
        "Alan_10": {"limit": 0.95, "min_puan": 220, "ad": "Teknopark"},
        # ... Diğer alanlar aynı kalabilir
    }

    ayar = bolge_stratejileri.get(bolge, {"limit": 0.6, "min_puan": 80, "ad": "Genel"})
    aktif_butce = butce * ayar["limit"]

    # 2. GAMSPY TANIMLARI (DÜZELTİLMİŞ)
    i = Set(c, name="i", records=malzeme_verisi['id'].values)
    
    # Records kısmında kolon isimlerini belirterek 'Un' kelimesini string olarak kalmasını sağlıyoruz
    maliyet = Parameter(c, name="maliyet", domain=[i], records=malzeme_verisi[['id', 'maliyet']])
    kalite = Parameter(c, name="kalite", domain=[i], records=malzeme_verisi[['id', 'kalite']])
    
    x = Variable(c, name="x", domain=[i], type="binary")

    # 3. DENKLEMLER
    butce_eq = Equation(c, name="butce_eq")
    butce_eq[...] = Sum(i, x[i] * maliyet[i]) <= aktif_butce

    kalite_eq = Equation(c, name="kalite_eq")
    kalite_eq[...] = Sum(i, x[i] * kalite[i]) >= ayar["min_puan"]

    # 4. ÇÖZÜM
    obj = Sum(i, x[i] * kalite[i])
    model = Model(c, name="Mutfak_Opt", equations=c.getEquations(), 
                  problem="MIP", sense=Sense.MAX, objective=obj)

    try:
        model.solve()
        alinanlar = [m for m in malzeme_verisi['id'] if x[m].level > 0.5]
        return {
            "alinanlar": alinanlar,
            "toplam_memnuniyet": round(obj.level, 2),
            "harcanan_para": round(sum(malzeme_verisi.loc[malzeme_verisi['id'] == m, 'maliyet'].values[0] for m in alinanlar), 2),
            "alan_adi": ayar["ad"]
        }
    except:
        return {"hata": "Bu bütçeyle bu bölgenin standartları karşılanamıyor!"}

# 2. 7 GÜNLÜK SİMÜLASYON DÖNGÜSÜ
def haftalik_simulasyon(secilen_alan_id):
    kasa = 6000 
    sabit_gider = 500
    konsept = "İtalyan"
    
    print(f"\n👨‍🍳 {konsept} Restoranı Simülasyonu")
    print(f"💰 Başlangıç Sermayesi: {kasa} TL")
    print("═"*55)

    for gun in range(1, 8):
        print(f"\n📅 GÜN {gun}")
        
        olaylar = [
            {"ad": "Sıradan Bir Gün", "m_etki": 1.0, "k_etki": 1.0},
            {"ad": "Lojistik Krizi (Maliyetler %40 Arttı)", "m_etki": 1.4, "k_etki": 1.0},
            {"ad": "Sosyal Medya Akımı (Gelir x2)", "m_etki": 1.0, "k_etki": 2.0},
            {"ad": "Sağlık Denetimi (Masraf Çıktı)", "m_etki": 1.0, "k_etki": 0.7}
        ]
        olay = random.choice(olaylar)
        print(f"📢 OLAY: {olay['ad']}")

        # Kasanın durumuna göre akıllı bütçe ayarı
        planlanan_butce = (kasa * 0.5) * olay["m_etki"]
        
        # GAMSpy Motorunu Çalıştır
        sonuc = run_supply_optimization(secilen_alan_id, konsept, planlanan_butce)
        
        if sonuc and sonuc['alinanlar']:
            harcanan = sonuc['harcanan_para']
            puan = sonuc['toplam_memnuniyet'] * olay["k_etki"]
            
            # Dinamik Gelir Formülü
            gelir = puan * 20 
            net_kar = gelir - harcanan - sabit_gider
            kasa += net_kar

            print(f"📍 Alan: {sonuc['alan_adi']} | 📦 Malzemeler: {', '.join(sonuc['alinanlar'])}")
            print(f"📈 Puan: {puan:.1f} | 💸 Harcanan: {harcanan:.1f} TL | 💰 Gelir: {gelir:.1f} TL")
            print(f"📊 Net Kar: {net_kar:.1f} TL | 🏦 Kasa: {kasa:.2f} TL")
        else:
            print("⚠️ KRİZ! GAMSpy bu bütçeyle bölge standartlarını karşılayamadı!")
            kasa -= sabit_gider
            print(f"📉 Sadece sabit giderler ödendi. Kasa: {kasa:.2f} TL")

        if kasa <= 0:
            print("\n💀 İFLAS! Pilot, restoranın kapısına kilit vuruldu.")
            break

    print("\n" + "═"*55)
    print(f"🏁 FİNAL KASASI: {kasa:.2f} TL")
    print("═"*55)

# 3. ÇALIŞTIRMA
if __name__ == "__main__":
    # Test için rastgele bir alan seçelim (Örn: Alan_3 - Lüks Semt)
    haftalik_simulasyon("Alan_3")