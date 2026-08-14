from fastapi import FastAPI, Query
from fastapi.middleware.cors import CORSMiddleware
from restaurant_chainsupply import run_supply_optimization
import uvicorn

app = FastAPI(title="Cloud-Kitchen Tycoon API")

# --- CORS AYARI ---
# Flutter Web ile Python arasındaki iletişim köprüsü
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/")
def home():
    return {
        "mesaj": "Cloud-Kitchen Tycoon API Aktif!",
        "status": "Ready to Cook 👨‍🍳"
    }

@app.get("/optimize")
def optimize(
    bolge: str = Query(..., description="10 alandan biri (Alan_1, Alan_2...)"),
    konsept: str = Query("İtalyan", description="Restoran konsepti"),
    butce: float = Query(5000.0, description="Planlanan günlük bütçe")
):
    """
    Flutter'dan gelen alan seçimine göre GAMSpy motorunu tetikler.
    """
    print(f"🚀 Yeni İstek: Bölge: {bolge}, Bütçe: {butce} TL")
    
    try:
        # restaurant_chainsupply.py içindeki GAMSpy fonksiyonunu çağırıyoruz
        sonuc = run_supply_optimization(bolge, konsept, butce)
        
        # Eğer bütçe kısıtlar nedeniyle çözüm bulamazsa (Infeasible)
        if not sonuc or (isinstance(sonuc, dict) and "hata" in sonuc):
            return {
                "durum": "hata",
                "mesaj": sonuc.get("hata", "Bütçe bu bölgenin standartları için yetersiz!")
            }

        return {
            "durum": "basarili",
            "veriler": sonuc
        }

    except Exception as e:
        print(f"❌ Hata oluştu: {str(e)}")
        return {
            "durum": "hata",
            "mesaj": f"GAMSpy Motor Hatası: {str(e)}"
        }

if __name__ == "__main__":
    # Uygulamayı 8000 portunda başlat
    print("👨‍🍳 Mutfak sunucusu hazırlanıyor...")
    uvicorn.run(app, host="127.0.0.1", port=8000)
    