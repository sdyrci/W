#include <stdlib.h>
#include <stdio.h>
#define yaz printf
#define oku scanf

int main()
{
    float tutar, odenen;

    yaz("urunun tutarini giriniz (Lütfen TL cinsinden giriniz...) : ");
    oku("%f",&tutar);

    yaz("odenen tutari giriniz (Lütfen TL cinsinden giriniz...) : ");
    oku("%f",&odenen);

    if(odenen<tutar)
    {
        yaz("yetersiz bakiye....\n");
        return 1;
    }

    int krs=(int)((odenen-tutar)*100.0+0.5);
    int top_adet=0;
    
    int para_krs[]={20000,10000,5000,2000,1000,500,100,50,25,10,5,1};
    yaz("para ustu: %.2f TL \n",krs/100.0);

    for(int i=0; i<12;i++)
    {
        if(krs>=para_krs[i])
        {
            int adet=krs/para_krs[i];
            krs%=para_krs[i];
            top_adet+=adet;

            if(para_krs[i]>=100)
            {
                yaz("%d adet %d TL\n",adet,para_krs[i]/100);

            }
            else
            {
                yaz("%d adet %d kurus\n",adet,para_krs[i]);
            } 
             
        }
    }

    yaz("toplam verilen kupur sayisi: %d\n",top_adet);
    return 0;

}