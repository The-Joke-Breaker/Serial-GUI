#include <stdio.h>		//Indlæs standard I/O definitioner
#include <fcntl.h>		//Indlæs filkontroldefinitioner 
#include <termios.h>	//Indlæs POSIX terminal kontrol biblioteket
#include <sys/ioctl.h>	//Indlæs I/O bibloteket til systemet
#include "Constants.h"	//Indlæs globale konstanter
#include <string.h>		//Indlæs stringbiblioteket
#include <stdlib.h>		//Indlæs standardbiblioteket
#include <unistd.h>		//Indlæs POSIX-standardbiblioteket

void error(char *emsg){//skaber en fejlbesked med emsg beskeden.
	GtkWidget *dialog; 
	
	dialog = gtk_message_dialog_new (GTK_WINDOW(window),
		GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_ERROR,
		GTK_BUTTONS_CLOSE,"%s",emsg);
	
	gtk_window_set_title (GTK_WINDOW(dialog),"Kontakt din systemadministrator!");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
char init(){//Initialiserer porten så den sender et signal arduinoen forstår. (standard karakterstørrelse er 7 bit)
    struct termios toptions; //Indstiller termios biblioteket. 
    char fd = open(port, O_RDWR); //Definer kommandoen til at åbne serielporten med: Det er tilladt at skrive og læse
    
    if (fd == -1){return -1;} //hvis FD giver værdien -1 blev porten ikke åbnet rigtigt.

    if (tcgetattr(fd, &toptions) == -1) { //Indlæs nuværende indstillinger fra porten 
        error("FEJL: Kunne ikke indlæse serielportindstillingerne.");return -1;}

	cfsetispeed(&toptions, B9600); //sæt indgangshastigheden af serielporten
	cfsetospeed(&toptions, B9600); //sæt udgangshastigheden af serielporten

	toptions.c_cflag &= ~PARENB; //Fjern parity bit
	toptions.c_cflag &= ~CSTOPB; //Send kun en stop bit
	toptions.c_cflag &= ~CSIZE; //Lås karakterstørrelse op 
	toptions.c_cflag |= CS8; //Sæt karakterstørrelse til 8 bit
	toptions.c_cflag |= CREAD | CLOCAL;  //Tillad læsning og ignorer modem status linjer
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY); //Deaktiver terminalkontrolfunktioner
	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //Gør signalet råt
	toptions.c_oflag &= ~OPOST; //Gør signalet råt
    
	tcsetattr(fd, TCSANOW, &toptions); //Sæt instillingerne med det samme

	if( tcsetattr(fd, TCSAFLUSH, &toptions) == -1){ //Sæt indstillingerne efter rengøring af buffer
		error("FEJL: Kunne ikke konfigurere porten.");return -1;}
	
    return fd;
}
char com(char data[10]){
	char fd = -1;
	fd = init();
            
	if( fd==-1 ) {error("FEJL: Kunne ikke åbne porten."); return -1;}
	else printf("\nÅbnede: %s\n",port);
           
	tcflush(fd, TCIOFLUSH); //Rengør ind- og udgangsbuffer
	char len = strlen(data); //find længden af dataen
    char n = write(fd, data, len); //Skriv dataen til porten
    
    if( n!=len ){ error("FEJL: Kunne ikke skrive data til porten"); return -1;}
	else {printf("\nSender data: %s\n", data);}
	
	return 0;
}
void opstart(){ //Første gang man sender genstarter senderen. Dette forhindrer den første sending i at blive tabt I løbet af denne tid.
	char data[10];
	sprintf(data,"\a%s",start); //Rengør indput på kafebrikken, send skrald til kafebrikken og rengør indput på kafebrikken igen
	if(com(data)==-1){return;}
	usleep(2200*1000);//Senderen tager omkring 2 sekunder for at starte op
}
void ttyUSB0(){
	memset(port, 0, 255); //Sæt alt data i string til NULL
	sprintf(port,"/dev/ttyUSB0");
	printf("\nPort er nu sat til: %s\n", port);
	opstart();
}
void ttyUSB1(){
	memset(port, 0, 255); //Sæt alt data i string til NULL
	sprintf(port,"/dev/ttyUSB1");
	printf("\nPort er nu sat til: %s\n", port);
	opstart();
}
char overflow(){ //Tjek om stack smashing vil ske.
	char err;
	if(strlen(gtk_entry_buffer_get_text(buffer1))>6){err=1; error("FEJL: Identifikationsnøgle 1 overskrider specifikationerne!");}
	if(strlen(gtk_entry_buffer_get_text(buffer2))>6){err=1; error("FEJL: Identifikationsnøgle 2 overskrider specifikationerne!");}
	if(strlen(gtk_entry_buffer_get_text(buffer3))>6){err=1; error("FEJL: Identifikationsnøgle 3 overskrider specifikationerne!");}
	if(err==1){return -1;}
	return 0; 
}
void sluk(){ //Denne funktion sender en string serielt der slukker kafebrikkens lys
	char key[7];
	char buffer;
	buffer=strtol(gtk_entry_buffer_get_text(buffersend),NULL,10); //Lav buffersend om til en int med base 10 og skriv det til char buffer
	if(overflow()==-1){return;}
	if(buffer == 1){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer1));} //Kopier informationen fra buffer1 til key
	if(buffer == 2){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer2));} //Kopier informationen fra buffer2 til key
	if(buffer == 3){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer3));} //Kopier informationen fra buffer3 til key
	char data[10];
	sprintf(data,"\a\e%s",key); //Rengører indput på kafebrikken, aktiverer sluk kommandoen og sender nøglen til kafebrikken
	com(data);
}
void taend(){ //Denne funktion sender en string serielt der tænder kafebrikkens lys
	char key[7];
	char buffer;
	buffer=strtol(gtk_entry_buffer_get_text(buffersend),NULL,10);
	if(overflow()==-1){return;}
	if(buffer == 1){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer1));}
	if(buffer == 2){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer2));}
	if(buffer == 3){sprintf(key,"%s",gtk_entry_buffer_get_text(buffer3));}
	char data[10];
	sprintf(data,"\a%s",key); //Rengører indput på kafebrikken og sender nøglen til kafebrikken (Uden sluk kommandoen aktiverer dette lyset)
	com(data);
}
char loadfunc(){
	char file = open(filename, O_RDONLY);
	
	if (file == -1){error("FEJL: Kunne ikke indlæse konfigurationsfilen.");return -1;}
	
	memset(port, 0, 255); //Sæt alt data i string til NULL
	memset(buff, 0, 255);
	read(file,buff,255);
	
	//Tæl om der er nok udråbstegn og at der ikke er tomme string i konfigurationsfilen til at den er valid for at undgå segfault
	char exclamation = 0;
	char *secubuff = buff;
	while ((secubuff = strchr(secubuff, '!')) != NULL){
		exclamation++;
		secubuff++;
		if (secubuff[0]=='!'){{error("FEJL: Konfigurationsfilen er ikke valid!");return -1;}}
		if (exclamation>8){break;}}
	if (exclamation<8){error("FEJL: Konfigurationsfilen er ikke valid!");return -1;}
	
	printf("%s",buff);
	char *loadbuff;
	char portbuff[255];
	memset(portbuff, 0, 255);
	strtok(buff,"!"); //åben buffer og smid kommentar før første udråbstegn ud.
	loadbuff = strtok(NULL,"!"); //Smid data fra første til andet udråbsteg ind i indlæsningsbuffer
	strncpy(portbuff,loadbuff,strlen(loadbuff)); //kopier fra indlæsningsbuffer til portbuffer
	printf("\n%s\n",portbuff);
	sprintf(port,"%s",portbuff); //print portbufferen til portstring.
	strtok(NULL,"!"); //Smid kommentar fra andet til tredje udråbsteg ud
	loadbuff = strtok(NULL,"!"); //Smid data fra tredje til fjerde udråbsteg ind i indlæsningsbuffer
	strncpy(key1,loadbuff,6); //kopier 6 tegn fra indlæsningsbuffer til nøglebuffer key1
	strtok(NULL,"!");
	loadbuff = strtok(NULL,"!");
	strncpy(key2,loadbuff,6);
	strtok(NULL,"!");
	loadbuff = strtok(NULL,"!");
	strncpy(key3,loadbuff,6);
	g_sprintf(gkey1,"%s",key1); //lav nøglebuffer om til en gtk kompatibel buffer med gchar
	g_sprintf(gkey2,"%s",key2);
	g_sprintf(gkey3,"%s",key3);
	gtk_entry_buffer_set_text(buffer1,gkey1,6);//sæt den kompatible buffer til at være den nye nøgle
	gtk_entry_buffer_set_text(buffer2,gkey2,6);
	gtk_entry_buffer_set_text(buffer3,gkey3,6);
	close(file);
	return 0;
}
void autoload(){
	memset(buff, 0, 255); //Sæt alt data i buffer til NULL
	char cfile = open("configpos", O_RDONLY); //åben fil der viser position af konfigurationsfil med tilladelse til at læse filen.
	
	if (cfile == -1){error("ADVARSEL: Ingen konfigurationsfil er blevet valgt.");return;} //hvis filen ikke kan indlæses gå ud af loopet.
	
	read(cfile,buff,255); //Læs filen ind i buffer
	filename = buff; //Sæt filnavnet fra buffer.
	printf("\nIndlæser konfigurationsfil: %s\n",filename);
	close(cfile); //Luk filen
	char error = loadfunc(); //start indlæsningsfunktion
	
	if (error == -1){return;} //hvis der er fejl i loadfunc gør dette
	
	opstart();
}
void cpos(){//finder konfigurationsfilens placering
	FILE *cfile = fopen("configpos", "w");
	fprintf(cfile,"%s",filename);
	fclose(cfile);
}
void save(){
	GtkWidget *dialog;
	GtkFileChooser *chooser; //Definer filvælger
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE; //Definer filvælgerhandling som gem.
	gchar res;
	
	dialog = gtk_file_chooser_dialog_new ("Gem Konfigurationsfil",
		GTK_WINDOW(window),action,("Annuller"),GTK_RESPONSE_CANCEL,("Gem"),
		GTK_RESPONSE_ACCEPT,NULL); //Lav en gem menu der har en gem knap og en annuller knap
	
	chooser = GTK_FILE_CHOOSER (dialog); //Sæt filvælgeren i dialogen
	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE); //Spørg før brugeren erstatter en fil
	res = gtk_dialog_run (GTK_DIALOG (dialog)); //res viser dialogresultatet
	
	if (res == GTK_RESPONSE_ACCEPT){
		filename = gtk_file_chooser_get_filename (chooser);
		printf("\nSkriver til: %s\n",filename);
		FILE *file = fopen(filename, "w");
		sprintf(key1,"%s",gtk_entry_buffer_get_text(buffer1));
		sprintf(key2,"%s",gtk_entry_buffer_get_text(buffer2));
		sprintf(key3,"%s",gtk_entry_buffer_get_text(buffer3));
		char *portbuff = port;
		fprintf(file,"port = "); //skriver kommentar/forklaringspunk til filen
		fprintf(file,"!%s",portbuff); //skriver datapunkt med ! foran til filen
		fprintf(file,"! key1 = "); //skriver kommentar/forklaringspunk med ! foran til filen
		fprintf(file,"!%s",key1);
		fprintf(file,"! key2 = ");
		fprintf(file,"!%s",key2);
		fprintf(file,"! key3 = ");
		fprintf(file,"!%s",key3);
		fprintf(file,"!");
		fclose(file);
		cpos();
		g_free (filename); //frigør filnavnet
   }
	if (res == GTK_RESPONSE_CANCEL){}
	
	gtk_widget_destroy (dialog);
}
void load(){
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gchar res;
	
	dialog = gtk_file_chooser_dialog_new ("Indlæs konfigurationsfil",
		GTK_WINDOW(window),action,("_Annuller"),GTK_RESPONSE_CANCEL,("_Vælg fil"),
		GTK_RESPONSE_ACCEPT,NULL); //Lav en åbn menu der har en Vælg fil knap og en annuller knap
	
	chooser = GTK_FILE_CHOOSER (dialog);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	
	if (res == GTK_RESPONSE_ACCEPT){
		memset(buff, 0, 255);
		filename = gtk_file_chooser_get_filename (chooser);
		char error = loadfunc();
		if (error == 0){ //hvis der ikke er fejl i loadfunc gør dette
			cpos();
			g_free (filename);
			opstart();
		}
	}
   if (res == GTK_RESPONSE_CANCEL){}
	
	gtk_widget_destroy (dialog);
}
void setport(){
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileFilter *filter = gtk_file_filter_new ();
	gtk_file_filter_add_pattern (filter, "tty*");
	gtk_file_filter_set_name (filter, "Serielporte");
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	
	dialog = gtk_file_chooser_dialog_new ("Sæt Port",GTK_WINDOW(window),action
	,("_Cancel"),GTK_RESPONSE_CANCEL,("_Open"),GTK_RESPONSE_ACCEPT,NULL);
	
	chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog),"/dev/");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),filter);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	
	if (res == GTK_RESPONSE_ACCEPT){
		sprintf(port,"%s",gtk_file_chooser_get_filename (chooser)); //sæt porten til den valgte port
		opstart();
	}
	if (res == GTK_RESPONSE_CANCEL){}
	
	gtk_widget_destroy (dialog);//Luk dialogvinduet
}
