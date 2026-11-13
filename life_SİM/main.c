#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Genel akis: amac, kaynaklar, komutlar, zaman kurallari ve puanlama.

    // her calistirmada farkli zar gelmesi icin rastgelelik baslatma
    srand(time(NULL));

    // temel durum degiskenleri (0-100 arasi tutulacak)
    int saglik=100;
    int enerji=100;
    int oksijen=100;
    int modulHasari=0;

    // kaynaklar ve durum degiskenleri
    int su=0;
    int yedekParca=0;
    int kilitMuhurlu=0; // 0 ise acik, 1 ise kapali

    // gun, tur ve firtina degiskenleri
    int gun=1;
    int tur=0;
    int firtinaSuresi=0;

    // dongu kontrol degiskenleri
    int zorlukGecerli=0;
    int oyunBitti=0;
    char zorluk;
    char gorevler;

    // Gecerli bir zorluk girilene kadar secim istenir; harflerin buyuk veya kucuk olmasi sonucu degistirmez.
    do {
        printf("Zorluk seciniz (K:Kolay, N:Normal, Z:Zor): ");
        scanf(" %c", &zorluk);

        // Buyuk ve kucuk harf durumlari ayni baslangic degerlerine dallanir.
        switch (zorluk) {
            case 'K':
            case 'k':
                saglik=100; enerji=100; oksijen=100; su=20; yedekParca=5; modulHasari=10; firtinaSuresi=3;
                zorlukGecerli=1; // dogru girildi donguden cikabilir
                break;
            case 'N':
            case 'n':
                saglik=90; enerji=80; oksijen=85; su=10; yedekParca=3; modulHasari=25; firtinaSuresi=5;
                zorlukGecerli=1;
                break;
            case 'Z':
            case 'z':
                saglik=75; enerji=60; oksijen=70; su=4; yedekParca=1; modulHasari=45; firtinaSuresi=7;
                zorlukGecerli=1;
                break;
            default:
                printf("Yanlis girdiniz tekrar deneyin.\n");
                break;
        }
    } while (zorlukGecerli==0);

    // Ana dongude her komut kendi kaynak ve tur etkisini uygular.
    // turHarcandi sifir baslar; yalnizca basarili ve zaman ilerleten eylemler bunu bir yapar.
    do {
        printf("\nGun: %d Tur: %d\n", gun, tur);
        printf("G:Kesif O:Oksijen T:Tamir D:Durum U:Uyu K:Firtina H:Sifre Q:Cikis\n");
        printf("Seciminiz: ");
        scanf(" %c", &gorevler);

        int turHarcandi=0; // gecerli komut girilirse 1 olacak

        switch (gorevler) {
            case 'G':
            case 'g':
                            // Kesif kaynak bulma sansi ile yaralanma riskini birlikte tasir.
                            // enerji yetmiyorsa iptal et
                if (enerji<15) {
                    printf("Enerji yetmiyor.\n");
                    break;
                }
                enerji=enerji-15;
                oksijen=oksijen-10;
                turHarcandi=1;

                // enerji ve oksijen iyiyse bulma sansi artar
                int esik=30;
                if (enerji>40 && oksijen>30) {
                    esik=60;
                }

                // 0-99 arasi rastgele zar atma
                int zar=rand()%100;
                printf("Zar: %d/Esik: %d -> ", zar, esik);

                // en az 3 farkli sonuc (su, parca, bos)
                if (zar<esik) {
                    int bulunanSu=(rand()%5)+2;
                    su=su+bulunanSu;
                    printf("BASARILI %d su buldun.\n", bulunanSu);
                } else if (zar<esik+25) {
                    int bulunanParca=(rand()%2)+1;
                    yedekParca=yedekParca+bulunanParca;
                    printf("BASARILI %d parca buldun.\n", bulunanParca);
                } else {
                    printf("BASARISIZ eli bos dondun.\n");
                }

                // yaralanma kontrolu
                int yaralanmaZari=rand()%100;
                printf("Zar: %d/Esik: 10 -> ", yaralanmaZari);
                if (yaralanmaZari<10 || modulHasari>70) {
                    saglik=saglik-15;
                    printf("BASARILI yaralandin canin azaldi.\n");
                } else {
                    printf("BASARISIZ sorun yok.\n");
                }
                break;

            case 'O':
            case 'o':
                // kaynak kontrolu
                if (su<2 || enerji<10) {
                    printf("Su veya enerji yetersiz.\n");
                    break;
                }
                int girilenSu;
                printf("Kac su harcanacak (Mevcut %d): ", su);
                scanf("%d", &girilenSu);

                if (girilenSu<=0 || girilenSu>su || girilenSu<2) {
                    printf("Hatali miktar girdiniz.\n");
                    break;
                }

                // mod operatoru ile tek sayi girildiyse 1 birimi depoda birakiyoruz
                int artik=girilenSu%2;
                int kullanilan=girilenSu-artik;
                su=su-kullanilan;
                enerji=enerji-10;
                oksijen=oksijen+(kullanilan/2)*3; // her 2 suya 3 oksijen
                turHarcandi=1;

                printf("Oksijen uretildi. Artan su: %d\n", artik);
                break;

            case 'T':
            case 't':
                if (yedekParca<=0 || modulHasari==0) {
                    printf("Parca yok veya hasar sifir.\n");
                    break;
                }

                // hasar seviyesine gore 3 kademeli tamir (if - else if - else)
                if (modulHasari<=30) {
                    modulHasari=modulHasari-15;
                    yedekParca=yedekParca-1;
                } else if (modulHasari<=70) {
                    if (yedekParca>=2) {
                        modulHasari=modulHasari-30;
                        yedekParca=yedekParca-2;
                    } else {
                        modulHasari=modulHasari-15;
                        yedekParca=yedekParca-1;
                    }
                } else {
                    if (yedekParca>=3) {
                        modulHasari=modulHasari-45;
                        yedekParca=yedekParca-3;
                    } else {
                        modulHasari=modulHasari-(15*yedekParca);
                        yedekParca=0;
                    }
                }
                turHarcandi=1;
                printf("Tamir bitti.\n");
                break;

            case 'D':
            case 'd':
                // durum raporu tur harcamaz o yuzden turHarcandi=1 yapmadik
                printf("Saglik: %d Enerji: %d Oksijen: %d Su: %d Parca: %d Hasar: %d Kilit: %d\n", saglik, enerji, oksijen, su, yedekParca, modulHasari, kilitMuhurlu);
                if (oksijen<25) {
                    printf("Oksijen az!\n");
                }
                if (saglik<30) {
                    printf("Saglik az!\n");
                }
                if (modulHasari>70) {
                    printf("Hasar cok fazla!\n");
                }
                // hepsi normal ise tek kosulla kontrol
                if (oksijen>=25 && saglik>=30 && modulHasari<=70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                break;

            case 'U':
            case 'u':
                enerji=enerji+25;
                oksijen=oksijen-5;
                turHarcandi=1;

                // ic ice if ile oksijen azsa can azaltma
                if (oksijen<20) {
                    saglik=saglik-10;
                    printf("Oksijen az oldugu icin uyurken canin azaldi.\n");
                } else {
                    saglik=saglik+15;
                    printf("Dinlendin canin ve enerjin artti.\n");
                }
                break;

            case 'K':
            case 'k':
                // Firtina boyunca her tur ayri hesaplanir; kilit sizintiyi onler.
                turHarcandi=1;
                int kayipSaglik=0;
                int kayipOksijen=0;
                int hasarliTur=0;
                int i;

                // zorluk seviyesine gore firtina dongusu (for zorunlu)
                for (i=1; i<=firtinaSuresi; i++) {
                    int firtinaZari=rand()%100;
                    int carpan=1;
                    // cift turlarda hasar iki katina cikar
                    if (i%2==0) {
                        carpan=2;
                    }

                    printf("Tur %d Zar: %d/Esik: 85 -> ", i, firtinaZari);

                    if (firtinaZari<30) {
                        saglik=saglik-(10*carpan);
                        kayipSaglik=kayipSaglik+(10*carpan);
                        hasarliTur++;
                        printf("BASARILI can kaybettin.\n");
                    } else if (firtinaZari<60) {
                        // kilit muhurluyse oksijen sizintisini continue ile atla
                        if (kilitMuhurlu==1) {
                            printf("Kilit muhurlu oksijen sizintisi olmadi.\n");
                            continue;
                        }
                        oksijen=oksijen-(12*carpan);
                        kayipOksijen=kayipOksijen+(12*carpan);
                        hasarliTur++;
                        printf("BASARILI oksijen sizdi.\n");
                    } else if (firtinaZari<85) {
                        modulHasari=modulHasari+(8*carpan);
                        hasarliTur++;
                        printf("BASARILI modul hasar aldi.\n");
                    } else {
                        printf("BASARISIZ zarar gormedin.\n");
                    }

                    // firtinada olurse donguyu break ile bitir
                    if (saglik<=0 || oksijen<=0) {
                        break;
                    }
                }
                printf("Firtina bitti. Hasarli tur: %d Kayip saglik: %d Kayip oksijen: %d\n", hasarliTur, kayipSaglik, kayipOksijen);
                break;

            case 'H':
            case 'h':
                // Sifre gun numarasindan turetilir ve uc tahmin hakki vardir.
                if (kilitMuhurlu==1 || enerji<5) {
                    printf("Kilit zaten kapali veya enerjin yok.\n");
                    break;
                }
                turHarcandi=1;
                // gun sayisina gore sifreyi bulma
                char sifre='A'+(gun%26);
                char tahmin;
                int deneme=0;
                int cozuldu=0;

                printf("Ipucu: A harfinden %d harf sonraki harf.\n", gun);

                // 3 hakli sifre deneme dongusu (do-while zorunlu)
                do {
                    if (enerji<5) {
                        break;
                    }
                    printf("Tahmin girin: ");
                    scanf(" %c", &tahmin);

                    // kucuk harf girildiyse buyuk harfe cevirme (ascii farki 32)
                    if (tahmin>='a' && tahmin<='z') {
                        tahmin=tahmin-32;
                    }

                    deneme++;
                    enerji=enerji-5;

                    if (tahmin==sifre) {
                        cozuldu=1;
                        kilitMuhurlu=1;
                        printf("Sifre dogru kilit muhurlendi.\n");
                    } else {
                        if (tahmin<sifre) {
                            printf("Yanlis ileri git.\n");
                        } else {
                            printf("Yanlis geri git.\n");
                        }
                    }
                } while (deneme<3 && cozuldu==0);

                // 3 hak biterse ve cozulemezse ceza
                if (cozuldu==0 && deneme>=3) {
                    modulHasari=modulHasari+20;
                    printf("Hakkin bitti modul hasar aldi.\n");
                }
                break;

            case 'Q':
            case 'q':
                oyunBitti=1;
                break;

            default:
                // gecersiz komutta tur harcanmaz
                printf("Gecersiz komut girdiniz.\n");
                break;
        }

        // Her uc gecerli hamlede yeni gun baslar ve oksijen azalir.
        // gecerli komut yapildiysa turu artir ve 3 turda bir gun atla
        if (turHarcandi==1) {
            tur++;
            if (tur%3==0) {
                gun++;
                oksijen=oksijen-8;
                printf("Yeni gune gecildi oksijen 8 azaldi.\n");
                if (modulHasari>70) {
                    saglik=saglik-5;
                    printf("Hasar yuksek oldugu icin 5 can kaybettin.\n");
                }
            }
        }

        // degiskenlerin 0 altina inmesini ve 100 ustune cikmasini engelleme
        if (saglik>100) saglik=100;
        if (saglik<0) saglik=0;
        if (enerji>100) enerji=100;
        if (enerji<0) enerji=0;
        if (oksijen>100) oksijen=100;
        if (oksijen<0) oksijen=0;
        if (modulHasari>100) modulHasari=100;
        if (modulHasari<0) modulHasari=0;

        // Degerler sinirlandiktan sonra bitis kosullari kontrol edilir.
        // olum veya 15. gunu bitirme kontrolu
        if (saglik<=0 || oksijen<=0 || gun>15) {
            oyunBitti=1;
        }

    } while (oyunBitti==0);

    // 15. gun tamamlandiysa gunu 15 olarak sabitleme
    int sonGun=gun;
    if (sonGun>15) {
        sonGun=15;
    }
    // Puan gun sayisi ve kalan saglik/oksijeni toplar, modul hasariyla azalir.
    // puan hesaplama formulu
    int puan=(sonGun*100)+saglik+oksijen-modulHasari;
    printf("Oyun bitti. Gun: %d Tur: %d Saglik: %d Oksijen: %d Hasar: %d Puan: %d\n", sonGun, tur, saglik, oksijen, modulHasari, puan);

    return 0;
}