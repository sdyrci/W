# Mars Kolonisi Yaşam Destek Simülatörü

C diliyle yazılmış, metin tabanlı ve tek karakterli komutlarla kontrol edilen bir hayatta kalma oyunudur. Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalan bir mühendisi yönetir ve kurtarma ekibi gelene kadar **15 gün** hayatta kalmaya çalışır.

Proje, Algoritma ve Programlama dersi ödevi kapsamında yalnızca C dilinin temel yapıları (`if–else`, `switch–case`, `for`, `do–while`, aritmetik ve mantıksal operatörler) kullanılarak geliştirilmiştir.

## İçindekiler

- [Özellikler](#özellikler)
- [Zorluk Seviyeleri](#zorluk-seviyeleri)
- [Komutlar](#komutlar)
- [Oyun Kuralları](#oyun-kuralları)
- [Kullanılan C Yapıları](#kullanılan-c-yapıları)
- [Dosya Yapısı](#dosya-yapısı)

## Özellikler

- Sağlık, enerji, oksijen, su, yedek parça, modül hasarı, hava kilidi durumu, gün ve tur sayacının takibi
- Üç zorluk seviyesi (Kolay, Normal, Zor)
- Büyük/küçük harf duyarsız komut sistemi
- Rastgele olayların `rand() % 100` ile üretilmesi; zar ve eşik değerinin ekrana yazdırılması
- Kum fırtınası simülasyonu (`for` döngüsü)
- Sınırlı denemeli hava kilidi şifresi (`do–while` döngüsü)
- Oyun sonunda puan hesaplı sonuç raporu

## Zorluk Seviyeleri

Program başlarken zorluk seviyesi sorulur. Geçersiz bir giriş yapılırsa seçim yeniden istenir.

| Giriş | Seviye | Başlangıç Suyu | Fırtına Süresi | Fırtına Hasarı |
|:-----:|--------|:--------------:|:--------------:|:--------------:|
| `K` | Kolay  | 15 | 3 tur | 5  |
| `N` | Normal | 10 | 5 tur | 10 |
| `Z` | Zor    | 5  | 7 tur | 15 |

Diğer başlangıç değerleri: Sağlık 100, Enerji 100, Oksijen 100, Yedek parça 2, Modül hasarı 0.

## Komutlar

| Komut | İşlev | Maliyet / Etki |
|:-----:|-------|----------------|
| `G` | Keşif görevi | Enerji −15, oksijen −10. Su bulma, yedek parça bulma veya eli boş dönme ihtimali vardır. Yaralanma riski taşır. |
| `O` | Oksijen üret | 2 birim su → 3 birim oksijen. Tek sayıda su girilirse 1 birim artık olarak kalır. Enerji −10. |
| `T` | Tamir | Hasar seviyesine göre 1, 2 veya 3 yedek parça harcanır. Enerji −10. |
| `D` | Durum raporu | Tüm değerleri ve kritik uyarıları gösterir. Tur harcamaz. |
| `U` | Uyu / dinlen | Enerji +25. Oksijen 20'nin altındaysa sağlık artmaz, azalır. |
| `K` | Kum fırtınası | Zorluk seviyesine bağlı sayıda tur boyunca rastgele olaylar yaşanır. |
| `H` | Hava kilidi şifresi | En fazla 3 denemede şifre tahmin edilir. Başarılırsa kilit mühürlenir. |
| `Q` | Çıkış | Oyunu sonlandırır ve sonuç raporunu yazdırır. |

Tanımsız komutlar uyarı verir ve tur harcamaz.

## Oyun Kuralları

### Zaman akışı

- Geçerli her komut tur sayacını 1 artırır (`D` ve tanımsız komutlar hariç).
- Her 3 turda bir (`tur % 3 == 0`) yeni gün başlar. Gün başında oksijen 8 azalır; modül hasarı 70'in üzerindeyse ayrıca 5 sağlık kaybedilir.

### Keşif (G)

- Enerji ve oksijen yüksekse (`enerji > 40 && oksijen > 30`) bulma eşiği yüksektir, aksi halde düşüktür.
- `zar < 10 || modulHasari > 70` koşulu sağlanırsa oyuncu yaralanır.
- Sonuçlar: su bulma, yedek parça bulma, eli boş dönme.

### Tamir (T)

| Modül hasarı | Kademe | Harcanan parça | Onarılan hasar |
|:------------:|--------|:--------------:|:--------------:|
| 0–30   | Hafif | 1 | 15 |
| 31–70  | Orta  | 2 | 30 |
| 71–100 | Ağır  | 3 | 45 |

### Kum fırtınası (K)

- Her turda bir zar atılır; sonuca göre can kaybı, oksijen sızıntısı, modül hasarı veya korunma gerçekleşir.
- Çift numaralı turlarda rüzgâr şiddetlenir ve hasar iki katına çıkar.
- Hava kilidi mühürlüyse oksijen sızıntısı olayı o tur atlanır (`continue`).
- Sağlık veya oksijen 0'a düşerse fırtına anında sonlanır (`break`).
- Fırtına sonunda hasar alınan tur sayısı ile kaybedilen sağlık ve oksijen özetlenir.

### Hava kilidi şifresi (H)

- Şifre sabit değildir: `sifre = 'A' + (gun % 26)`.
- Ekranda yalnızca ipucu gösterilir. Küçük harf girişi kabul edilir.
- 3 deneme hakkı vardır. Her yanlış denemede enerji 5 azalır ve "ileri git" / "geri git" ipucu verilir.
- Doğru şifrede hava kilidi mühürlenir. 3 deneme de başarısız olursa modül hasarı 20 artar.

### Sınırlandırma

Sağlık, enerji, oksijen ve modül hasarı her komuttan sonra 0–100 aralığında tutulur. Enerjisi yetmeyen oyuncu ilgili komutu çalıştıramaz; komut iptal edilir ve tur harcanmaz.

### Oyun sonu

- Sağlık veya oksijen 0'a düşerse oyun **kaybedilir**.
- 15. gün tamamlanırsa kurtarma ekibi gelir ve oyun **kazanılır**.
- `Q` ile çıkış yapılabilir.
- Hangi şekilde biterse bitsin hayatta kalınan gün, toplam tur, son durum değerleri ve puan yazdırılır.

### Puan hesabı

```
Puan = (gun × 100) + saglik + oksijen − modulHasari
```

Gün sayısı en büyük katkıyı yapar; böylece hayatta kalınan süre öncelikli olur. Sağlık ve oksijen kalan durumu, modül hasarı ise istasyonun bozulma düzeyini yansıtır.

## Kullanılan C Yapıları

| Yapı | Kullanıldığı yer |
|------|------------------|
| `switch–case` (fall-through) | Komut yönetimi ve zorluk seçimi (`case 'g': case 'G':`) |
| `default` | Tanımsız komut ve geçersiz seviye uyarısı |
| `if–else if–else` | Tamir kademeleri, keşif sonuçları, durum uyarıları |
| İç içe `if` | Dinlenme sırasında oksijen kontrolü |
| `for` + `break` + `continue` | Kum fırtınası |
| `do–while` | Zorluk seçimi, komut döngüsü, şifre doğrulama |
| `%` (mod) operatörü | Artık su, çift tur kontrolü, gün geçişi, şifre türetme |
| `&&`, `\|\|` | Keşif koşulları, durum raporu, şifre döngü koşulu |
| `rand()` / `srand(time(NULL))` | Tüm rastgele olaylar |

## Dosya Yapısı

```
.
├── mars.c       # Kaynak kod
└── README.md    # Proje açıklaması
```

## Lisans

Bu proje eğitim amaçlı hazırlanmıştır.
