#include <stdlib.h>
#include <stdio.h>

int main()
{

    float tutar,odenen;

    printf(" urunun ücretini giriniz: ");
    scanf("%f",&tutar);

    printf(" odenecek ücreti giriniz: ");
    scanf("%f",&odenen);

    int krs=(int)((odenen-tutar)*100.0+0.5);
    int top_adet=0;
    int adet;
    
    printf(" para ustu: %.2f tl \n",krs/100.0);

    adet=krs/20000;
    krs%=20000;
    top_adet+=adet;
    printf(" %d adet 200 tl \n",adet);

    adet=krs/10000;
    krs%=10000;
    top_adet+=adet;
    printf(" %d adet 100 tl \n",adet);

    adet=krs/5000;
    krs%=5000;
    top_adet+=adet;
    printf(" %d adet 50 tl \n",adet);


    adet=krs/2000;
    krs%=2000;
    top_adet+=adet;
    printf(" %d adet 20 tl \n",adet);

    adet=krs/1000;
    krs%=1000;
    top_adet+=adet;
    printf(" %d adet 10 tl \n",adet);

    adet=krs/500;
    krs%=500;
    top_adet+=adet;
    printf(" %d adet 5 tl \n",adet);

    adet=krs/100;
    krs%=100;
    top_adet+=adet;
    printf(" %d adet 1 tl \n",adet);

    adet=krs/50;
    krs%=50;
    top_adet+=adet;
    printf(" %d adet 50 kurus \n",adet);

    adet=krs/25;
    krs%=25;
    top_adet+=adet;
    printf(" %d adet 25 kurus \n",adet);

    adet=krs/10;
    krs%=10;
    top_adet+=adet;
    printf(" %d adet 10 kurus \n",adet);

    adet=krs/5;
    krs%=5;
    top_adet+=adet;
    printf(" %d adet 5 kurus \n",adet);

    adet=krs/1;
    krs%=1;
    top_adet+=adet;
    printf(" %d adet 1 kurus \n",adet);

    printf(" toplam verilen madeni para adedi: %d \n",top_adet);

    return 0;
}