// ==========================
// PIN 7-SEGMENT (a b c d e f g)
// ==========================
int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = 6;
int segF = 7;
int segG = 8;

// ==========================
// PIN OUTPUT DAN INPUT
// ==========================
int relay = 9;   // Relay output
int buzzer = 10; // Buzzer
int button = 11; // Push button reset

// ==========================
// VARIABEL TIMER
// ==========================
int angka = 9;         // Timer mulai dari 9
bool counting = false; // Status sedang menghitung atau tidak

// ==========================
// FUNGSI TAMPIL ANGKA PADA 7-SEGMENT
// ==========================
void tampil(int n)
{
    bool data[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    digitalWrite(segA, data[n][0]);
    digitalWrite(segB, data[n][1]);
    digitalWrite(segC, data[n][2]);
    digitalWrite(segD, data[n][3]);
    digitalWrite(segE, data[n][4]);
    digitalWrite(segF, data[n][5]);
    digitalWrite(segG, data[n][6]);
}

// ==========================
// SETUP
// ==========================
void setup()
{
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);

    pinMode(relay, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(button, INPUT_PULLUP);

    digitalWrite(relay, HIGH); // Relay awal OFF
    tampil(9);                 // Tampilkan angka awal
}

// ==========================
// LOOP UTAMA
// ==========================
void loop()
{

    // ==========================
    // RESET MANUAL DENGAN BUTTON
    // ==========================
    if (digitalRead(button) == LOW)
    {
        angka = 9;               // Set angka kembali ke 9
        counting = true;         // Mulai hitung
        tone(buzzer, 2000, 150); // Bunyi singkat tanda reset
        tampil(angka);
        delay(250); // Anti-bounce
    }

    // ==========================
    // PROSES HITUNG MUNDUR
    // ==========================
    if (counting)
    {
        delay(1000); // Delay 1 detik
        angka--;     // Turun 1 detik

        // Bunyi singkat tiap detik turun
        if (angka >= 0)
        {
            tampil(angka);
            tone(buzzer, 2500, 80);
        }

        // ==========================
        // SAAT MENCAPAI 0 DETIK
        // ==========================
        if (angka == 0)
        {
            digitalWrite(relay, LOW); // Relay ON
            tone(buzzer, 2000);       // Buzzer hidup terus

            delay(5000); // Buzzer hidup 5 detik

            noTone(buzzer);            // Matikan buzzer
            digitalWrite(relay, HIGH); // Relay kembali OFF

            // RESET OTOMATIS KE 9 DETIK SETELAH 5 DETIK
            angka = 9;
            tampil(angka);
            counting = false; // Stop hitung, tunggu tombol lagi
        }
    }
}
