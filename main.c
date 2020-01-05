#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct sehir
{
    int plakaKodu;
    char sehirAdi[25];
    char cografiBolge[2];
    int komsuSayisi;
    struct sehir *onceki;
    struct sehir *sonraki;
    struct komsuPlaka *komsu;
};
struct sehir *ilk = NULL,*son=NULL;
struct komsuPlaka
{
    int plaka;
    struct komsuPlaka *sonra;
};
struct komsuPlaka *first=NULL,*ilki=NULL;
struct tutucu
{
    char satirTutucu[250];
};
struct tutucu *satirTut;
int satirSayac=0;
void komsuSil()
{

}
void cikti()
{
    FILE *fp=fopen("cikti.txt","w");
    struct sehir *iter=ilk;
    struct komsu *kkomsu;
    while (iter!=NULL)
    {
        fprintf(fp,"Sehir Plakasi: %d Sehir Adi: %s   Sehir Bolgesi: %s ->",iter->plakaKodu,iter->sehirAdi,iter->cografiBolge);
        fprintf(fp,"Komsu Plakalar");
        struct komsuPlaka *gecici=iter->komsu;
        while(gecici!=NULL)
        {
            fprintf(fp, "----->%d", gecici->plaka);
            gecici = gecici->sonra;
        }
        fprintf(fp,"\n\n");
        iter=iter->sonraki;
    }
    fclose(fp);
}
void sehirSil()
{
    struct sehir *silici=ilk;
    struct sehir *sonuncu=ilk;
    int kont = 1,kont2 = 1;
    int plaka;
    printf("Silmek istediginiz sehrin plaka kodunu giriniz:");
    scanf("%d", &plaka);
    while (sonuncu->sonraki != NULL)
    {
        sonuncu = sonuncu->sonraki;
    }
    if (plaka > sonuncu->plakaKodu)
    {
        printf("Bu plakaya ait il bulunmamaktadir");
        kont2 = 0;
    }
    if (plaka < ilk->plakaKodu)
    {
        printf("Bu plakaya ait il bulunmamaktadir");
        kont2 = 0;
    }
    if (kont2 == 1)
    {
        if (silici->plakaKodu == plaka)
        {
            ilk = silici->sonraki;
            printf("%s adli ve %d Plakali il basariyla silinmistir\n", silici->sehirAdi, silici->plakaKodu);
            free(silici);
            kont = 0;
        }
        if (kont == 1)
        {
            silici = ilk;
            while (silici->sonraki != NULL)
            {
                if (plaka == silici->plakaKodu)
                {
                    silici->onceki->sonraki = silici->sonraki;
                    silici->sonraki->onceki = silici->onceki;
                    printf("%s adli ve %d Plakali il basariyla silinmistir\n", silici->sehirAdi, silici->plakaKodu);
                    free(silici);
                    kont = 0;
                }
                silici = silici->sonraki;
            }
            if (kont == 1)
            {
                silici->onceki->sonraki = NULL;
                printf("%s adli ve %d Plakali il basariyla silinmistir\n", silici->sehirAdi, silici->plakaKodu);
                free(silici);
            }
        }
    }
}
//komsu ismini çift yönlü bağlı listten bularak plaka koduna ulaşacağız
void sehirleriSirala()
{
    struct sehir *root=ilk;
    while(root!=NULL)
    {
        struct sehir *root1=ilk;
        while(root1->sonraki!=NULL)
        {

            if(root1->plakaKodu > root1->sonraki->plakaKodu)
            {
                //struct sehir *swap;
                //plaka değişimi
                int degistir=root1->sonraki->plakaKodu;
                root1->sonraki->plakaKodu=root1->plakaKodu;
                root1->plakaKodu=degistir;
                //şehir adı değişimi
                char degistirAd[25];
                strcpy(degistirAd,root1->sonraki->sehirAdi);
                strcpy(root1->sonraki->sehirAdi,root1->sehirAdi);
                strcpy(root1->sehirAdi,degistirAd);
                //bölge
                char degistirBolge[25];
                strcpy(degistirBolge,root1->sonraki->cografiBolge);
                strcpy(root1->sonraki->cografiBolge,root1->cografiBolge);
                strcpy(root1->cografiBolge,degistirBolge);
                //komsu plakalar adres degişimi
                int degistirAdres=root1->sonraki->komsu;
                root1->sonraki->komsu=root1->komsu;
                root1->komsu=degistirAdres;
                //komsu sayısı degişimi
                int degistirKomsu=root1->sonraki->komsuSayisi;
                root1->sonraki->komsuSayisi=root1->komsuSayisi;
                root1->komsuSayisi=degistirKomsu;
            }
            root1=root1->sonraki;
        }
        root=root->sonraki;
    }
}
void komsulariSirala()
{

    struct sehir *root=ilk;
    while(root!=NULL)
    {

        struct komsuPlaka *temp=root->komsu;
        while(temp->sonra!=NULL)
        {
            struct komsuPlaka *temp1=root->komsu;
            while(temp1->sonra!=NULL)
            {
                if(temp1->plaka > temp1->sonra->plaka)
                {
                    int degistir=temp1->sonra->plaka;
                    temp1->sonra->plaka=temp1->plaka;
                    temp1->plaka=degistir;
                }
                temp1=temp1->sonra;
            }
            temp=temp->sonra;
        }
        root=root->sonraki;
    }
}
int plakaBul(char *x)
{
    int m;
    struct sehir *iter=ilk;
    while(iter!=NULL)
    {
        if(strcmp(iter->sehirAdi,x)==0)
        {
            m=iter->plakaKodu;
        }
        iter=iter->sonraki;
    }
    return m;
}
//komsular ekleniyor
void tekSonaEkle(struct komsuPlaka *eklenecek,struct sehir *olesine)
{
    if(first==NULL)
    {
        olesine->komsu = eklenecek;
        first = olesine->komsu;
    }
    else
    {
        while(first->sonra != NULL)
        {
            first= first->sonra;
        }
        eklenecek->sonra=NULL;
        first->sonra= eklenecek;
    }

}
void komsuEkle()
{
    FILE *txt=fopen("sehirler.txt","r");
    while(!feof(txt))
    {
        struct sehir *temp=ilk;
        while(temp!=NULL)
        {
            char satir[1000],*ayrac=",";
            fgets(satir,"%s",txt);
            char *kelime=strtok(satir,ayrac);
            kelime=strtok(NULL,ayrac);
            kelime=strtok(NULL,ayrac);
            int p=0;
            kelime=strtok(NULL,",\n");
            while(p<20)
            {
                if(kelime!=NULL)
                {
                    //printf("%s\n",kelime);
                    int geciciplaka=plakaBul(kelime);
                    struct komsuPlaka *geciciKomsu=(struct komsuPlaka *)malloc(sizeof(struct komsuPlaka));
                    geciciKomsu->plaka=geciciplaka;
                    geciciKomsu->sonra=NULL;
                    tekSonaEkle(geciciKomsu,temp);
                    //printf("%d\n",geciciplaka);
                    kelime=strtok(NULL,",\n");
                    p++;
                }
                else
                {
                    temp->komsuSayisi=p;
                    break;

                }

            }
            first=NULL;
            temp=temp->sonraki;
        }
    }
}
//Çift yönlü bağlı listede sona düğüm ekleyen fonksiyon
void sonaEkle(struct sehir *eklenecekSehir)
{
    if(ilk==NULL)
    {
        ilk=eklenecekSehir;
        son=ilk;
    }
    else
    {
        eklenecekSehir->onceki=son;
        son->sonraki=eklenecekSehir;
        son=son->sonraki;
    }
    satirSayac++;
}
void sehirBilgileriOkuAktar(FILE *sehirTXT)
{
    const char *ayrac=",";
    while(!feof(sehirTXT))//satirlar , matrise atylmak üzere ilk önce char dizisine atylyyor.
    {
        char satir[1500];
        fgets(satir,"%s",sehirTXT);
        //printf("%s\n",satir);
        //plaka alınıyor
        struct sehir *eklenecekSehir=(struct sehir *)malloc(sizeof(struct sehir));
        //plaka kopyalanıyor
        char *kelime = strtok(satir,ayrac);
        int gecici=atoi(kelime);
        eklenecekSehir->plakaKodu=gecici;
        eklenecekSehir->sonraki=NULL;
        eklenecekSehir->onceki=NULL;
        //printf("%d",eklenecekSehir->plakaKodu);
        //sehiradı kopyalanıyor
        kelime = strtok(NULL,ayrac);
        strcpy(eklenecekSehir->sehirAdi,kelime);
        //printf("%s",eklenecekSehir->sehirAdi);
        //bölge kopyalanıyor
        kelime = strtok(NULL,ayrac);
        strcpy(eklenecekSehir->cografiBolge,kelime);
        // printf("%s \n",eklenecekSehir->cografiBolge);
        sonaEkle(eklenecekSehir);
    }
    fclose(sehirTXT);
    komsuEkle();
}

void Listele()
{
    struct sehir *liste=ilk;
    while(liste!=NULL)
    {
        printf("%d %s %s ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
        struct komsuPlaka *liste2=liste->komsu;
        while(liste2!=NULL)
        {
            printf(" %d ",liste2->plaka);
            liste2=liste2->sonra;
        }
        printf("\n");
        liste=liste->sonraki;
    }
}
int main()
{
    FILE *sehirTXT;
    sehirTXT=fopen("sehirler.txt","r");
    int k=0;
    satirTut=(struct tutucu *)malloc(sizeof(struct tutucu));
    while(!feof(sehirTXT))
    {
        fgets(satirTut[k].satirTutucu,"%s",sehirTXT);
        satirTut=realloc(satirTut,sizeof(struct tutucu)*sizeof(struct tutucu)*100);
        //printf("%s\n",satirTut[k].satirTutucu);
        k++;
    }
    fclose(sehirTXT);
    sehirTXT=fopen("sehirler.txt","r");
    sehirBilgileriOkuAktar(sehirTXT);
    komsulariSirala();
    sehirleriSirala();
    //Listele();
    int secim=-1;
    while(secim!=0)
    {
ekleme1:
        printf("\n\n____Yapmak istediginiz islemi seciniz____\n");
        printf("\n 1 - Sehir Ekle\n 2 - Komsuluk Ekle\n 3 - Listele\n 4 - Sehir ismi ile arama\n");
        printf(" 5 - Plaka Kodu ile Arama\n 6 - Sehir Silme\n 7 - Komsuluk Silme\n 8 - Bolgesel Bilgi Listele\n");
        printf(" 9 - Komsu Sayisina gore listele\n 10 - Bonus\n 11 - Cikti olusturmak icin Islemleri Kaydet\n 0 - Cikis\n Secim:");
        scanf("%d",&secim);
ekleme:
        switch(secim)
        {
        case 1:
        {
            struct sehir *eklenecekSehir=(struct sehir *)malloc(sizeof(struct sehir));
            struct sehir *iter=ilk;
            printf("\n->Eklemek istediginiz sehrin bilgilerini giriniz\n:");
            printf("-Sehir plaka: ");
            scanf("%d",&eklenecekSehir->plakaKodu);
            printf("-Sehir Adi: ");
            scanf("%s",&eklenecekSehir->sehirAdi);
            printf("-Sehir Bolge: ");
            scanf("%s",&eklenecekSehir->cografiBolge);
            eklenecekSehir->sonraki=NULL;
            eklenecekSehir->onceki=NULL;
            while(iter!=NULL)
            {
                if(strcmp(iter->sehirAdi,eklenecekSehir->sehirAdi)==0 || strcmp(iter->cografiBolge,eklenecekSehir->cografiBolge)==0 || eklenecekSehir->plakaKodu==iter->plakaKodu)
                {
                    printf("\nBu sehir Listede Zaten var Ekleme yapamazsiniz.Menuye yonlendiriliyorsunuz...");
                    goto LOOP;
                }
                iter=iter->sonraki;
            }
            sonaEkle(eklenecekSehir);
            sehirleriSirala();

LOOP:
            break;
        }
        case 2:
        {
            int isterPlaka,ekleKomsuPlaka;
            printf("\n->komsu eklemek istediginiz sehrin plaka kodunu giriniz:\n");
            scanf("%d",&isterPlaka);
            printf("ekleyeceginiz komsu plakayi giriniz:");
            scanf("%d",&ekleKomsuPlaka);
            struct sehir *iter=ilk;
            struct komsuPlaka *geciciEkleme=(struct komsuPlaka *)malloc(sizeof(struct komsuPlaka));
            geciciEkleme->plaka=ekleKomsuPlaka;
            geciciEkleme->sonra=NULL;
            while(iter!=NULL)
            {
                if(iter->plakaKodu==isterPlaka)
                {
                    struct komsuPlaka  *itici=iter->komsu;
                    if(itici==NULL)
                    {
                        tekSonaEkle(geciciEkleme,iter);
                        break;
                    }
                    else
                    {
                        while(itici!=NULL)
                        {
                            if(itici->plaka==ekleKomsuPlaka)
                            {
                                printf("\nbu komsuluk zaten mevcut menuye yonlendiriliyorsunuz...\n");
                                goto LOOP1;
                            }
                            else if(itici->sonra==NULL)
                            {
                                itici->sonra=geciciEkleme;
                                break;
                            }
                            itici=itici->sonra;
                        }
                        break;
                    }
                }
                iter=iter->sonraki;
            }
            komsulariSirala();
LOOP1:
            break;
        }
        case 3:
        {
            Listele();
            break;
        }
        case 4:
        {
            char aranan[25];
            printf("\nAramak istediginiz sehrin adini giriniz:");
            scanf("%s",&aranan);
            struct sehir *iter=ilk;
            int cevap;
            while(iter!=NULL)
            {
                if(strcmp(iter->sehirAdi,aranan)==0)
                {
                    break;
                }
                iter=iter->sonraki;
            }
            if(iter==NULL)
            {
                printf("aramak istediginiz sehir listede yok eklemek ister misiniz(1/0)?");
                scanf("%d",&cevap);
                if(cevap==1)
                {
                    secim=1;
                    goto ekleme;
                }
                else
                    break;
            }
            struct sehir *liste=iter;
            printf("%d %s %s ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
            struct komsuPlaka *liste1=iter->komsu;
            while(liste1!=NULL)
            {
                struct sehir *sehirara=ilk;
                while(sehirara!=NULL)
                {
                    if(sehirara->plakaKodu==liste1->plaka)
                    {
                        printf("(%d %s %s) ",sehirara->plakaKodu,sehirara->sehirAdi,sehirara->cografiBolge);
                    }
                    sehirara=sehirara->sonraki;
                }
                liste1=liste1->sonra;
            }
            printf("\n");
            break;
        }
        case 5:
        {
            int aranan;
            printf("\nAramak istediginiz sehrin plaka kodunu giriniz:");
            scanf("%d",&aranan);
            struct sehir *iter=ilk;
            int cevap;
            while(iter!=NULL)
            {
                if(iter->plakaKodu==aranan)
                {
                    break;
                }
                iter=iter->sonraki;
            }
            if(iter==NULL)
            {
                printf("aramak istediginiz sehir listede yok eklemek ister misiniz(1/0)?");
                scanf("%d",&cevap);
                if(cevap==1)
                {
                    secim=1;
                    goto ekleme;
                }
                else
                    break;
            }
            struct sehir *liste=iter;
            printf("%d %s %s ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
            struct komsuPlaka *liste1=iter->komsu;
            while(liste1!=NULL)
            {
                struct sehir *sehirara=ilk;
                while(sehirara!=NULL)
                {
                    if(sehirara->plakaKodu==liste1->plaka)
                    {
                        printf("(%d %s %s) ",sehirara->plakaKodu,sehirara->sehirAdi,sehirara->cografiBolge);
                    }
                    sehirara=sehirara->sonraki;
                }
                liste1=liste1->sonra;
            }
            printf("\n");
            break;
        }

        case 6:
            sehirSil();
            break;
        case 7:
        {
            struct sehir *silkomsu=ilk,*son=ilk;
            struct komsuPlaka *silici;
            struct komsuPlaka *bironceki;
            int plaka;
            int komsuplaka;
            printf("Komsusunu Silmek istediginiz sehrin plakasini giriniz\n");
            scanf("%d",&plaka);
            printf("\n");
            while(son->sonraki!=NULL)
                son=son->sonraki;
            if(plaka>son->plakaKodu || plaka < 1)
            {
                printf("silmek istediginiz sehir listede yok menuye yonlendiriliyorsunuz...");
                goto ekleme1;
            }
            printf("Silmek istediginiz plakayi giriniz\n");
            scanf("%d",&komsuplaka);
            //komsu mevcutluğu sorgulanıyor
            struct sehir *belirleyici=ilk;
            struct komsuPlaka *bakici;
            int kontrol=0;
            while(belirleyici!=NULL)
            {
                if(belirleyici->plakaKodu==plaka)
                {
                    bakici=belirleyici->komsu;
                    while(bakici!=NULL)
                    {
                        if(komsuplaka==bakici->plaka)
                            kontrol++;
                            bakici=bakici->sonra;
                    }

                }
                belirleyici=belirleyici->sonraki;
            }
            if(kontrol==0)
            {
                printf("silmek istediginiz komsuluk mevcut degildir menuye yonlendiriliyorsunuz...");
                goto ekleme1;
            }
            while(silkomsu!=NULL)
            {
                silici=silkomsu->komsu;
                if(komsuplaka==silici->plaka)
                {
                    silkomsu->komsu=silici->sonra;
                    silkomsu->komsuSayisi=silkomsu->komsuSayisi-1;
                    free(silici);
                }
                else
                {
                    while (silici != NULL)
                    {
                        if (komsuplaka == silici->plaka)
                        {
                            if (silkomsu->komsuSayisi == 1)
                            {
                                silkomsu->komsu = NULL;
                                silkomsu->komsuSayisi = silkomsu->komsuSayisi - 1;
                            }
                            else
                            {
                                bironceki = silkomsu->komsu;
                                while (bironceki != NULL)
                                {
                                    if (bironceki->sonra == silici)
                                    {
                                        bironceki->sonra = silici->sonra;
                                        free(silici);
                                        silkomsu->komsuSayisi = silkomsu->komsuSayisi - 1;
                                    }
                                    bironceki = bironceki->sonra;
                                }
                            }
                        }
                        silici = silici->sonra;
                    }
                }
                silkomsu=silkomsu->sonraki;
            }
            break;
        }
        case 8:
        {
            char aranan[2];
            printf("\nHangi bolgedeki sehileri listelemek istersiniz(AK-DA-EG-GA-IA-MA-KA):");
            scanf("%s",&aranan);
            struct sehir *iter=ilk;
            while(iter!=NULL)
            {
                if(strcmp(aranan,iter->cografiBolge)==0)
                {
                    printf("%d %s %d \n",iter->plakaKodu,iter->sehirAdi,iter->komsuSayisi);
                }
                iter=iter->sonraki;
            }
            break;
        }
        case 9:
        {
            int kacinci;
            printf("\nKomsu sayisi kactan fazla olan sehirleri siralamak istersiniz:");
            scanf("%d",&kacinci);
            struct sehir *iter=ilk;
            while(iter!=NULL)
            {
                if(iter->komsuSayisi>kacinci)
                {
                    printf("%d %s %s ",iter->plakaKodu,iter->sehirAdi,iter->cografiBolge);
                    struct komsuPlaka *iter2=iter->komsu;
                    while(iter2!=NULL)
                    {
                        printf(" %d ",iter2->plaka);
                        iter2=iter2->sonra;
                    }
                    printf("\n");
                }
                iter=iter->sonraki;
            }
            break;
        }
        case 10:
            break;
        case 11:
            cikti();
            break;
        case 0:
            break;
        default:
            printf("Lutfen Gecerli Bir Islem Girin!");
            break;
        }
    }
    return 0;
}

