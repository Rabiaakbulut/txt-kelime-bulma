/*
* BLM3010 hafta3 odevi
* @author Rabia Akbulut  170420822   
* 
* Bu program verilen kelimeyi verilen txt dosyasinda arar.
* Kelimeyi buldugunda satir ve sutun bilgilerini dondurur
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//@param kacKereVar kac kere aranan kelime textte var
int kacKereVar=0;

/*
Bu Fonksiyon aranan kelime satirda varsa kolon ve satir bilgisini yazdirmaya yardim eder
@param kelime aranan kelime
@param satirdakiYazi tex dosyasindaki satirdaki yazi
@param satir indexi
@param kolon indexi
@param eslesenHarfSayisi aranan kelime ile texteki eslesen harf sayisi
*/

int eslesmeVarsaKonumDondur(char *kelime,char *satirdakiYazi,int satir,int kolon)
{

     int eslesenHarfSayisi=0;
     for(int i=0; i<strlen(kelime); i++)
     {
      /*textin ya da satirin sonuna gelmissek aranan kelime alt satirda devam ediyor olabilir
      *boyle bir durum mevcutsa ust satirda eslesen harf sayisi baska bir fonksiyonda kullanmak
      * uzere kaydediyoruz. bini cikarmamin nedeni diger returnler ile karismamasi icin
      */
      if(satirdakiYazi[kolon]=='\n' || satirdakiYazi[kolon]=='\0' )  
      {
      if(eslesenHarfSayisi>1 || satirdakiYazi[kolon-1]==kelime[0])
      {
      return eslesenHarfSayisi-1000;
      }
      break;
      }
//aranan kelime ile eslesme oldukca eslesen harf sayisi arttir
      if(satirdakiYazi[kolon]==kelime[i])     {  eslesenHarfSayisi++;}    
      else
      {
      if(i==strlen(kelime)-1) //kontrol ettigimiz harf aranan harfin son harfiyse donguden cikiyoruz
      break;
      else
      i--;
      if(eslesenHarfSayisi>0) //iki tane yan yana aranan kelimenin bas harfi gelirse text kolonunda bir geri gidiyoruz
      {
      kolon--;  //boylece kacirdigimiz bir harf olmayacak
      if(i==0){i--;
}
}                    
      eslesenHarfSayisi=0;  //bu kisma dusersek eslesme olmamistir bu yüzden resetliyoruz
}    
      kolon++;//diger harflerden bakmaya devam ediyoruz

      }

if(eslesenHarfSayisi==strlen(kelime))  //tum harfler uyumluysa kelimenin baslangic kolonunu dondur
{
return kolon-strlen(kelime);
}
else{//if(eslesenHarfSayisi==0)
return -2;    //eslesme olmadiysa -2 dondur
}

}


/*
@param kelime aranan kelime
@param satir kacinci satirdayiz
@param eslesmeSayisi ust satirin sonunda eslesen harf sayisi
@param kelime2 eslesmesi gereken geri kalan harfler
@param satirbilgisi ust satirin altina gitmek icin kullandigimiz degisken
@param kolonindex alt satirda eslesme varsa dondurecegimiz index
@param r dongu degiskeni
*/
void altSatiriKontrolEt(char *kelime,int satir, int eslesmeSayisi,char *dosyaadi)
{

FILE *fp = fopen(dosyaadi, "r");  //Klasik dosya acam islemleri
    if(fp == NULL) {
        perror("Dosya acilamadi");
        exit(1);
    }
   
    char satirdakiYazi[128];
    char kelime2[strlen(kelime)-eslesmeSayisi];
    int satirbilgisi=1;
    satir++; //alt satira bakacagimiz icin arttirdik
    int kolonindex=0;
    while(fgets(satirdakiYazi, sizeof(satirdakiYazi), fp) != NULL) { //satır döngüüsü
   
    /*ust satira gelince eslesmenin kacinci kolondan itibaren basladigini tutmaya
    yarayan if dongumuz */
    if(satir-satirbilgisi==1)
     {
     
while(satirdakiYazi[kolonindex+1]!='\n' )
{
kolonindex++;
}
kolonindex=kolonindex-eslesmeSayisi+1;
}

     if(satirbilgisi==satir){//alt satira ulastik
           int r=0;
for(r=0; r<strlen(kelime2); r++) //eslesmesi gereken geri kalan harfleri kelime2 ye atadik
{
kelime2[r]=kelime[r+eslesmeSayisi];
}

int sonuc2=eslesmeVarsaKonumDondur(kelime2,satirdakiYazi,satir,0); //kelime2 yi alt satirda ariyoruz
if(sonuc2>=0)//eslesme olunca yani ust satirin devamiysa yazidiryoruz
{
printf("satir: %d column :%d\n",satir-1,kolonindex+1);
kacKereVar++;
break;
}
else{
break; //alt satirla eslesmediyse bir sey yazdirmiyoruz
}
}

else{

satirbilgisi++; //alt satira ulasana kadar satir bilgisini arttiriyoruz

}

 }
 fclose(fp);
     
}
 
 /*
 main fonksiyonunda satirdaki kolonlari eslesme var mi yok mu ogrenmek icin yukaridaki fonksiyonlar gonderiyoruz
 eslesme sonuclarina gore de bilgileri yazdiriyoruz
 *@param satirdakiYazi text satirlari
 *@param kelime aranacak olan kelime
 *@param satir satir indexi
 *@param kolon kolon indexi
 */
 int main(int argc,char *argv[]) {
     FILE *fp = fopen(argv[2], "r");  //dosya acma islemleri
     if(fp == NULL) {
         perror("Dosya acilamadi");
         exit(1);
     }
 
 
     char satirdakiYazi[128];
     //char kelime[10]="ece";
     char *kelime=argv[1];

    
     int satir=1;
     int kolon=0;
     int sonuc;
     while(fgets(satirdakiYazi, sizeof(satirdakiYazi), fp) != NULL) { //satır döngüüsü
        kolon=0;
        sonuc=eslesmeVarsaKonumDondur(kelime,satirdakiYazi,satir,kolon);
        do{
       
        if(sonuc==-2) //eslesme yoksa bitir
        {
        break;
}
else if(sonuc<-500) //eslesme alt satirda devam edebilme ihtimali varsa
{

altSatiriKontrolEt(kelime,satir,sonuc+1000,argv[2]); //bini cikardik. yukarda acikaldim
break;
}
else{
        printf("satir: %d column :%d\n",satir,sonuc+1); //eslesme varsa bilgileri yazdir
        kacKereVar++;
        kolon=sonuc+strlen(kelime);
       
for(int i=kolon; i<kolon+strlen(kelime)+1; i++) //satirda kelime aramak icin hala yer varmi diye kontrol
{
if(satirdakiYazi[i]=='\n')
  {
  break; //yeer yoksa bitir diger satirlara gec
 
    }
}
//kolon-strlen(kelime)-1 diyerek ic ice gecmis kelimeleri ya da cakisanlari da tespit ediyoruz
sonuc=eslesmeVarsaKonumDondur(kelime,satirdakiYazi,satir,kolon-strlen(kelime)+1);//satir bitmediyse kontrol etmeye devam et        
        }
}while(1);      
   
        satir++;//diger satirlara bakmaya devam
}
printf("toplamda bulunan '%s' sayisi: %d\n",kelime,kacKereVar);
 
     fclose(fp);
     return 0;
 }


